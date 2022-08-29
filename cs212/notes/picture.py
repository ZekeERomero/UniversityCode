#!/usr/bin/env python3
"""doc"""

import math
import image  #cImage
#from PIL import Image

size = 1000
win = image.ImageWin(size, size, "Image")

# do stuff with image here
pic = image.FileImage("horsesurf.jpg")
h = pic.getHeight()
w = pic.getWidth()
print(w, "x", h)

newpic = image.EmptyImage(w, h)

for y in range(h):
	for x in range(w):
		p = pic.get_pixel(x, y)
		print(p[0], p[1], p[2])

pic.draw(win)

input("pause")
