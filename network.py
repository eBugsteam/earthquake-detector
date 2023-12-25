import os
import re
#import serial
import time

# Define your network
network = "172.18.97.74/24"

# Establish a serial connection to the Arduino
# Change '/dev/ttyACM0' to the port where your Arduino is connected
arduino_port = '/dev/ttyACM0'
baud_rate = 9600
#ser = serial.Serial(arduino_port, baud_rate, timeout=1)
time.sleep(2)  # Wait for the connection to settle

def scan_network(network):
    # Scan the network using nmap
    scan_result = os.popen(f"nmap -sn {network}").read()
    # Extract MAC addresses from scan results
    mac_addresses = re.findall(r'MAC Address: ([0-9A-F:]{17})', scan_result)
    return len(mac_addresses)

def send_to_arduino(value):
    #ser.write(str(value).encode())
    time.sleep(2)  # Delay for Arduino to process the incoming data

try:
    while True:
        number_of_devices = scan_network(network)
        print(f"Devices connected: {number_of_devices}")
       # send_to_arduino(number_of_devices)
        # Wait for 30 seconds before next scan.
        # Adjust time based on how frequently you want to perform the scan.
        time.sleep(30)

except KeyboardInterrupt:
    #ser.close()
    print("Script terminated")
