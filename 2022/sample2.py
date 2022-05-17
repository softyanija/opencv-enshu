#!/usr/bin/env python

import cv2
import sys

print sys.argv[1]
src_img = cv2.imread(sys.argv[1])

src_img_gray = cv2.cvtColor(src_img, cv2.COLOR_BGR2GRAY)
ret, tmp_img1 = cv2.threshold(src_img_gray, 90, 255, cv2.THRESH_BINARY)

cv2.imshow("Threshold", tmp_img1)
cv2.waitKey(0)
cv2.destroyAllWindows()

