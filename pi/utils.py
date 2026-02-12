import numpy as np
import cv2
from enum import Enum
from PIL import Image

class UART_Command(Enum):
	GET_DATE = 0x00
	TAKE_SCREENSHOT = 0x01
	KILL_PROGRAM = 0xff

class BGR_Color(Enum):
    BLUE = [255, 0, 0]
    GREEN = [0, 255, 0]
    RED = [0, 0, 255]
    YELLOW = [0, 255, 255]
    
def get_mask(hsvframe, bgr_color):
    if bgr_color == BGR_Color.RED:
        lower_red1 = np.array([0, 120, 100])
        upper_red1 = np.array([7, 255, 250])
        lower_red2 = np.array([160, 120, 100])
        upper_red2 = np.array([179, 255, 250])
        mask1 = cv2.inRange(hsvframe, lower_red1, upper_red1)
        mask2 = cv2.inRange(hsvframe, lower_red2, upper_red2)
        return mask1 + mask2
    else:
        c = np.uint8([[bgr_color.value]])
        hsv_c = cv2.cvtColor(c, cv2.COLOR_BGR2HSV)
        lower_limit = hsv_c[0][0][0] - 15, 130, 100
        upper_limit = hsv_c[0][0][0] + 15, 255, 250
        lower_limit = np.array(lower_limit, dtype=np.uint8)
        upper_limit = np.array(upper_limit, dtype=np.uint8)
        mask = cv2.inRange(hsvframe, lower_limit, upper_limit)
        return mask

def draw_bbox(frame, mask, color_name):
    mask_ = Image.fromarray(mask)
    bbox = mask_.getbbox()
    if bbox:
        x, y, w, h = bbox
        cv2.rectangle(frame, (x, y), (w, h), (0, 255, 0), 4)
        cv2.putText(
            frame,
            color_name,
            (x, y - 10),  # position
            cv2.FONT_HERSHEY_SIMPLEX,
            0.8,            # size
            (0, 255, 0),    # color
            2,              # thickness
            cv2.LINE_AA
        )
    
def get_center(frame, size):
    h, w, _ = frame.shape
    cx, cy, = w // 2, h // 2
    center_square = frame[cy - size:cy + size, cx - size:cx + size]
    avg_color = center_square.mean(axis=(0, 1))
    print(f"Center color (BGR): {avg_color}")
    return avg_color

def draw_center_square(frame, size):
    thickness = 2
    h, w, _ = frame.shape
    cx, cy, = w // 2, h // 2
    cv2.rectangle(frame, (cx - size - thickness, cy - size - thickness), (cx + size + thickness, cy + size + thickness), (255, 255, 255), thickness)

def is_hsv_in_range(hsv_color, lower_limit, upper_limit):
    # for i in range(3):
    #     print (f"Checking HSV channel {i}: {lower_limit[i]} <= {hsv_color[i]} <= {upper_limit[i]}")
    return all(lower_limit[i] <= hsv_color[i] <= upper_limit[i] for i in range(3))

def detect_color(hsv_color):
    lower_red1 = np.array([0, 120, 100])
    upper_red1 = np.array([8, 255, 250])
    lower_red2 = np.array([160, 120, 100])
    upper_red2 = np.array([179, 255, 250])
    if is_hsv_in_range(hsv_color, lower_red1, upper_red1) or is_hsv_in_range(hsv_color, lower_red2, upper_red2):
        print(f"Detected color: {BGR_Color.RED.name}")
        return
    
    for color in BGR_Color:
        if color == BGR_Color.RED:
            continue
        c = np.uint8([[color.value]])
        hsv_c = cv2.cvtColor(c, cv2.COLOR_BGR2HSV)
        lower_limit = hsv_c[0][0][0] - 15, 130, 100
        upper_limit = hsv_c[0][0][0] + 15, 255, 250
        lower_limit = np.array(lower_limit, dtype=np.uint8)
        upper_limit = np.array(upper_limit, dtype=np.uint8)
        print(is_hsv_in_range(hsv_color, lower_limit, upper_limit))
        if is_hsv_in_range(hsv_color, lower_limit, upper_limit):
            print(f"Detected color: {color.name}")
            return
