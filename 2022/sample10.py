#!/usr/bin/env python
#-*- coding: utf-8 -*-

import cv2
import sys

print sys.argv[1]
img = cv2.imread(sys.argv[1])

# (1)画素値（R,G,B）を順次取得し，変更する
p = [0,0,0]
height, width = img.shape[:2]
for y in range(height):
    for x in range(width):
        # 画素値を直接操作する一例
        p[0] = img[y][x][0] # B
        p[1] = img[y][x][1] # G
        p[2] = img[y][x][2] # R
        img[y][x][0] = round(p[0] * 0.6 + 10)
        img[y][x][1] = round(p[1] * 1.0)
        img[y][x][2] = round(p[2] * 0.0)
        
cv2.namedWindow("Image")
cv2.imshow("Image", img)
cv2.waitKey(0)
cv2.destroyAllWindows()

