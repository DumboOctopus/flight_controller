import serial
import RPi.GPIO as GPIO
import time
from ctypes import Structure, c_uint8, c_uint32
from enum import Enum

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

control = 4
DEVICE_ID = 48

GPIO.setup(control, GPIO.OUT)


class Handshake(Structure):
    _pack_ = 1
    _fields_ = [
        ("src_id", c_uint8),
        ("dest_id", c_uint8),
        ("priority", c_uint8),
        ("baudrate", c_uint8),
        ("info", c_uint8),
        ("uid", c_uint32),
    ]

    def print(self):
        print("Handshake")
        print("src_id", self.src_id)
        print("dest_id", self.dest_id)
        print("uid", self.uid)

    

ser = serial.Serial('/dev/ttyAMA0')
ser.baudrate = 115200
START_BYTE = b'\xa6'
HANDSHAKE = (b'\x21', 14)
BIND_INFO = (b'\x41', 0)

def send(data, orig):

    GPIO.output(control, 0)
    x = [
            166,
            33,
            14,
            48,
            16,
            10,
            0,
            4,
            49,
            50,
            51,
            52,
            224,
            143
        ]
    print("Sending handshake response");
    ser.write(bytes(x))
    ser.flush()
#    time.sleep(0.1)
    GPIO.output(control, 1)


GPIO.output(control, 1)
while True:
    data = ser.read()
    if data == START_BYTE:
        data = ser.read()
        length = int.from_bytes(ser.read(), byteorder='little')
        # decode packet type
        if data == HANDSHAKE[0]:
            s = Handshake.from_buffer(bytearray(ser.read(length)))
            #print(s.dest_id)

            s.print()

            send("hi", 'a')
        elif data == BIND_INFO[0]:
            print("bind info")
        else:
            print(f"unsupported {data}")
ser.close()
