#!/usr/bin/env python
#-*- coding: utf-8 -*-

import cv2
import numpy as np

value = 0
def main():
    global value
    img = None
    # (1)画像領域を確保し，初期化する
    img = np.zeros((480,640,3), np.uint8)

    # (2)ウィンドウ，およびトラックバーを作成する
    cv2.namedWindow ("Image", cv2.WINDOW_AUTOSIZE);
    cv2.createTrackbar ("Trackbar", "Image", 0, 100, on_trackbar);
    cv2.imshow ("Image", img);
    while True:

        # (3)トラックバー1の値を描画する
        cv2.rectangle (img, (0, 0), (400, 50), (0, 0, 0, 0), -1)
        str = "%d" % (value)
        cv2.putText (img, str, (15, 30), cv2.FONT_HERSHEY_DUPLEX, 1.0, (0, 200, 100))
        cv2.imshow ("Image", img);

        c = cv2.waitKey(2)
        if c == 27:
            return 1

# コールバック関数
def on_trackbar (val):
    global value
    value = val

main()
