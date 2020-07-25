# UltraSonicSensor-RaspberryPi3B-Arduino-Firebase
Here we are showing and Ultra sonic sensor value is read using arduino and transferred to Pi using serial communication. This shared value is sent to firebase using Pi. 

## Components Used

- Ultra Sonic Sensor (HR-04)
- USB to TTL Converter
- Arduino Uno
- Raspberrry 3B

### Step 1: Setting Up arduino and Connections

![Image of Circuit](https://raw.githubusercontent.com/anandusreeni/UltraSonicSensor-RaspberryPi3B-Arduino-Firebase/master/US%20FB%20Circuit.jpg)

Here we use Arduino UNO instead of voltage divider circuit. Raspberry Pi 3B accepts input voltage ranges upto 3.3 V. But Ultra sonic sensor output is 5v. So arduino recieves the value and it is processed and sent back to Raspberry Pi using serial communication. 



 #### Arduino Connections
 
 Arduino Pins | Ultrasonic Sensor Pins
 -------------|----------------------
 5 V          | VCC
 GND          | GND
 PIN 5        | Trigger PIN
 PIN 4        | Echo PIN



Let us now write the code for arduino uno to recieve the values from ultra sonic sensor and serially transmit it.

##### Arduino UNO Code

```c++
const int triggerPin = 5; // PIN 5 is set as trigger pin
const int echoPin = 4;  // PIN 5 is set as echo pin

void setup() {
   Serial.begin(9600); // Initiallizing serial communication
   pinMode(triggerPin, OUTPUT);
   pinMode(echoPin, INPUT);
}

void loop() {
   long duration, distance; // initialize variables
   digitalWrite(triggerPin, LOW); // creates an 8 cycle burst of ultrasound at 40 kHz.
   delayMicroseconds(2);
   digitalWrite(triggerPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(triggerPin, LOW);
   
   duration = pulseIn(echoPin, HIGH);  //Recieves transmitted waves durration
   distance = calcDistance(duration);  // calculating the distance
   Serial.println(distance);           // Serially printing the distance
   delay(1000);
}

long calcDistance(long duration) {
   return duration / 29 / 2;
}
```
### Step 2: Setting UP raspberry and Install firebase related libraries

The Raspberry Pi is a low cost, credit-card sized computer that plugs into a computer monitor or TV, and uses a standard keyboard and mouse. It is a capable little device that enables people of all ages to explore computing, and to learn how to program in languages like Scratch and Python. It’s capable of doing everything you’d expect a desktop computer to do, from browsing the internet and playing high-definition video, to making spreadsheets, word-processing, and playing games.

Letus Connect Arduino to the USB PORT of Raspberry Pi 3B using USB Cable

In Pi UART will be off by default. We have to enable **UART for serial communication**. You can use the following link for enabling serial communication on pi
https://learn.adafruit.com/adafruits-raspberry-pi-lesson-5-using-a-console-cable/enabling-serial-console

Then open command line and install **PySerial**

```bat
pip install pyserial
```

After that let us check whether data is read serially. Use the following code to verify it.

```python
import serial

ser = serial.Serial('/dev/ttyACM0',9600)
s = [0,1]
while True:
    read_serial=ser.readline()
    print read_serial
```    
    





