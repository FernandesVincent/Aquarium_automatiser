from picamera2 import Picamera2
import time
import cv2
import numpy as np
from utils import UART_Command, BGR_Color, get_mask, draw_bbox, get_center, draw_center_square, detect_color
import serial
import threading
from datetime import datetime

center_square_size = 10
ser = serial.Serial('/dev/ttyAMA0', 115200, timeout=None)
uart_command = None

def uart_listener():
	global uart_command
	while True:
		if ser.in_waiting > 0:
			# data = ser.readline().decode().strip()
			data = ser.read(1)
			uart_command = data[0]
			print(f"Received: {uart_command}")

threading.Thread(target=uart_listener, daemon=True).start()

picam2 = Picamera2()
picam2.configure(picam2.create_preview_configuration(raw={"size":(1640,1232)},main={"format":'RGB888',"size":(640,480)}))
picam2.start()
time.sleep(2)

while True:
	frame = picam2.capture_array()
	hsvframe = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
	
	# bmask = get_mask(hsvframe, BGR_Color.BLUE)
	# draw_bbox(frame, bmask, BGR_Color.BLUE.name)
	
	# rmask = get_mask(hsvframe, BGR_Color.RED)
	# draw_bbox(frame, rmask, BGR_Color.RED.name)
	
	# ymask = get_mask(hsvframe, BGR_Color.YELLOW)
	# draw_bbox(frame, ymask, BGR_Color.YELLOW.name)
	
	# gmask = get_mask(hsvframe, BGR_Color.GREEN)
	# draw_bbox(frame, gmask, BGR_Color.GREEN.name)

	draw_center_square(frame, center_square_size // 2)
		
	cv2.imshow("output", frame)
	key = cv2.waitKey(1) & 0xFF
	if key == ord('q') or uart_command == UART_Command.KILL_PROGRAM.value:
		uart_command = None
		break
	if uart_command == UART_Command.TAKE_SCREENSHOT.value:
		avg_color = np.uint8([[get_center(frame, center_square_size // 2)]])
		avg_color_hsv = cv2.cvtColor(avg_color, cv2.COLOR_BGR2HSV)
		print(f"Average color in HSV: {avg_color_hsv[0][0]}")
		detect_color(avg_color_hsv[0][0])
		uart_command = None
	if uart_command == UART_Command.GET_DATE.value:
		now = datetime.now()
		day_number = now.day
		day_name = now.isoweekday() - 1
		ser.write(bytes([0xAA, day_name, day_number]))
		uart_command = None

picam2.stop()
picam2.close()


