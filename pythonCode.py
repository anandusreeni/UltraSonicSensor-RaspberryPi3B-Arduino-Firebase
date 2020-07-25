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