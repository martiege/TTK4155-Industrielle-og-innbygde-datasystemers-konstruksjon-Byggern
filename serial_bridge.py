import serial

ubit  = serial.Serial('/dev/ttyACM1', stopbits = 2)
#node1 = serial.Serial('/dev/ttyS0')

while True:
	print(ubit.read())
