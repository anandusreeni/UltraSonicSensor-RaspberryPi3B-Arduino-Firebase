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
