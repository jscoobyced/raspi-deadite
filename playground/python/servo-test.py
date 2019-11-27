import RPi._GPIO as GPIO
from time import sleep

servoPin = 18
GPIO.setmode(GPIO.BCM)
GPIO.setup(servoPin, GPIO.OUT)

p = GPIO.PWM(servoPin, 50)
p.start(0)

def SetAngle(angle):
	duty = angle / 18 + 2
	print(duty)
	GPIO.output(servoPin, True)
	p.ChangeDutyCycle(duty)
	sleep(1)
	GPIO.output(servoPin, False)
	p.ChangeDutyCycle(0)
	
SetAngle(0)
SetAngle(90)
SetAngle(180)
SetAngle(0)

p.stop()
GPIO.cleanup()
