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
import time
ser = serial.Serial('/dev/ttyACM0',9600)
s = [0,1]
while True:
    read_serial=ser.readline()
    print read_serial
    time.sleep(1)
```    
If we are getting the output then we are good to go.

Let us Install Firebase libraries on our python 
Open Command Line and load following:

```bat
$ sudo apt-get update
$ sudo apt-get install python-pip python-dev ipython
$ sudo pip install google-cloud-storage
$ sudo pip install firebase
$ sudo pip install python-firebase
```
Now open up a firebase account and create a real time database

  - Create a free firebase account with your gmail id
  - Go To Console
  - Click on Add Project > Enter Your project Name> Click on Continue
  - If you want you can enable Google analytics
  - Click on Add firebase account
  - Click on database on Develop console in left side of the Screen. 
  - Click on create database 
    You can opt any of the two opions:
    
     **Production Mode**: Data will be private in default. We have to provide certain credentials for updating values to the database
     
     **Test Mode**:It is a public mode of data acceptance. It will be accepting datas without any security rules. Recommended only on hobby projects.
     
  - Lets proceed with test mode. Select real time database which wont have data storage capability. 
  - Open data in the screen and copy the URL like this **projectName.firebaseio.com/**
  - Paste this to following code in pi and execute it.
  
  ```python 
  import serial
  from firebase import firebase

  url = 'PASTE your Custom URL HERE'   # The copied url from firebase have to place here
  firebase = firebase.FirebaseApplication(url)   
  SerialValue = serial.Serial('/dev/ttyACM0',9600)
  s = [0,1]
  while True:
      readValue=SerialValue.readline()
      print readValue
      result = firebase.put("/Test Val","Value",readValue) # Sending the real time value, Test Val is just a parameter name. You can update it as you like
  ```    
  
Go back to data tab in firebase you can see Ultra sonic value is updated in real time manner
  
![Image of Circuit](https://raw.githubusercontent.com/anandusreeni/UltraSonicSensor-RaspberryPi3B-Arduino-Firebase/master/Output.jpg)





