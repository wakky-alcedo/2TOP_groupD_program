import time
import serial

Arduino = serial.Serial("COM4", 9600)  # Create a serial object 'Arduino' to manage the serial port communication
time.sleep(3)

print("-----Connect Success-----")

arduino_status = 1
wait_status = 1

while True:
    if arduino_status == 1:
        com = input("Type command ON: ")  # Type command, send to Arduino
        Arduino.write(com.encode('utf-8'))
        arduino_status = 0
        wait_status = 1
    else:
        pass

    if Arduino.inWaiting():
        string = Arduino.readline().decode('utf-8')  # Check if there’s a response from Arduino
        print(string)
        arduino_status = 1
    else:
        if wait_status == 1:
            print("Waiting...")  # After sending command, UI shows 'Waiting'
            wait_status = 0
        else:
            pass
