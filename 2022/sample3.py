#!/usr/bin/env python

import cv2
import sys

print sys.argv[1]
src_img = cv2.imread(sys.argv[1], cv2.IMREAD_GRAYSCALE)

tmp_img = cv2.Sobel (src_img, cv2.CV_32F, 1, 0)
dst_img1 = cv2.convertScaleAbs (tmp_img)

tmp_img = cv2.Laplacian(src_img, cv2.CV_32F, 3)
dst_img2 = cv2.convertScaleAbs (tmp_img)

tmp_img = cv2.Canny(src_img, cv2.CV_32F, 50.0, 200.0, 3)
dst_img3 = cv2.convertScaleAbs (tmp_img)

cv2.imshow("Original", src_img)
cv2.imshow("Sobel", dst_img1)
cv2.imshow("Laplace", dst_img2)
cv2.imshow("Canny", dst_img3)
cv2.waitKey(0)
cv2.destroyAllWindows()

