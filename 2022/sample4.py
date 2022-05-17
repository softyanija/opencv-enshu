#!/usr/bin/env python

import cv2
import sys

colors = [(0, 0, 255), (0, 128, 255),
          (0, 255, 255), (9, 255, 0),
          (255, 128, 0), (255, 255, 0),
          (255, 0, 0), (255, 0, 255)]

print sys.argv[1]
src_img = cv2.imread(sys.argv[1])
cascade = cv2.CascadeClassifier("/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml")
src_gray = cv2.cvtColor(src_img, cv2.COLOR_BGR2GRAY)
faces = cascade.detectMultiScale(src_gray, 1.1, 1)

i = 0
for rect in faces:
    cv2.circle(src_img, tuple(rect[0:2]+rect[2:4]/2), int((rect[2]+rect[3])*0.25), colors[i], 2)
    i = (i + 1)%8

cv2.imshow("Face Detection", src_img)
cv2.waitKey(0)
cv2.destroyAllWindows()

