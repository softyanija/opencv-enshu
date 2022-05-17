#!/usr/bin/env python
#-*- coding: utf-8 -*-

import cv2

# (1)指定された番号のカメラに対するキャプチャ構造体を作成する
capture = cv2.VideoCapture(0)

# (2)表示用ウィンドウをの初期化
cv2.namedWindow("Capture")

while True:
    # (3)カメラから画像をキャプチャする
    ret, frame = capture.read();

    # (4) カメラ画像の表示
    cv2.imshow("Capture", frame)

    c = cv2.waitKey(2)
    if c == 27: # Escキー
        break

capture.release()
cv2.destroyAllWindows()

