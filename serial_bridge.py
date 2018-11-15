import serial
import sys

sys.stdout.flush()

ubit  = serial.Serial('/dev/ttyACM1', stopbits = 2, timeout = 0)
node1 = serial.Serial('/dev/ttyS0',   stopbits = 2, timeout = 0)

while True:
	u = ubit.read()
	if len(u) and ord(u):
		#print ord(u),
		node1.write(u)
	
	n = node1.read()
	if len(n) and ord(n):
		sys.stdout.write(n)
		if ord(n) == 0xFE:
			n = ubit.read()
			if len(n) and ord(n):
				ubit.write(n)
	#ubit.write(n)
	#node1.write(u)
