import time
import serial
from pprint import pprint

def Checksum(frame):
	checksum = 0
	checksum = sum(frame)
	checksum = (checksum & 0xFF)
	#print "chk "+hex(checksum),
	return  checksum

def main():
	ser = serial.Serial("/dev/ttyUSB0",115200, timeout=0.1)
	
	motorA = 0
	motorB = 0	

	while 1:
		for x in xrange(0,254):
			#<otorA and MotorB are when you will store the data to transmit
			motorA = x
			motorB = x
			#let's create the packet 
			frame = bytearray()
			frame.append(0xAC)
			frame.append(0x02) 
			frame.append(motorA)
			frame.append(motorB)
			frame.append(Checksum(frame))
			
			# let's prepare the string to display. 
			frame_string = "> "
			for i in xrange(0,len(frame)):
				frame_string +=  " " +hex(frame[i])			
			print frame_string

			#let's send the data to the Arduino  
			
			ser.write(frame)

			# And read the answer , this should match our sent data 
			
			print ser.readline()


if __name__ == "__main__":
	main()
