#!/usr/bin/env python

import cv2
import sys

print sys.argv[1]
img = cv2.imread(sys.argv[1])

cv2.imshow("Image", img)
cv2.waitKey(0)
cv2.destroyAllWindows()

