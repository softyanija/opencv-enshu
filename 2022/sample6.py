#!/usr/bin/env python
#-*- coding: utf-8 -*-

import cv2
import numpy as np

img = None
def main():
    global img
    # (1)画像領域を確保し，初期化する
    img = np.zeros((480,640,3), np.uint8)

    # (2)ウィンドウを作成し，マウスイベントに対するコールバック関数を登録する
    cv2.namedWindow ("Image", cv2.WINDOW_AUTOSIZE);
    cv2.setMouseCallback ("Image", on_mouse, 0);
    cv2.imshow ("Image", img);

    while True:
        c = cv2.waitKey (2)
        if c == 27 :
            return 1;

    cv2.DestroyWindow ("Image");
    cv2.ReleaseImage (img);

# コールバック関数
def on_mouse(event, x, y, flags, param):
    global img
    # char str[64];
    max_line = 15
    w = 15
    h = 30
    str = ''
    if event == cv2.EVENT_MOUSEMOVE:
        str = "(%d,%d) %s" % (x, y, "MOUSE_MOVE")
    elif event == cv2.EVENT_LBUTTONDOWN:
        str = "(%d,%d) %s" % (x, y, "LBUTTON_DOWN")
    elif event == cv2.EVENT_RBUTTONDOWN:
        str = "(%d,%d) %s" % (x, y, "RBUTTON_DOWN")
    elif event == cv2.EVENT_MBUTTONDOWN:
        str = "(%d,%d) %s" % (x, y, "MBUTTON_DOWN")
    elif event == cv2.EVENT_LBUTTONUP:
        str = "(%d,%d) %s" % (x, y, "LBUTTON_UP")
    elif event == cv2.EVENT_RBUTTONUP:
        str = "(%d,%d) %s" % (x, y, "RBUTTON_UP")
    elif event == cv2.EVENT_MBUTTONUP:
        str = "(%d,%d) %s" % (x, y, "MBUTTON_UP")
    elif event == cv2.EVENT_LBUTTONDBLCLK:
        str = "(%d,%d) %s" % (x, y, "LBUTTON_DOUBLE_CLICK")
    elif event == cv2.EVENT_RBUTTONDBLCLK:
        str = "(%d,%d) %s" % (x, y, "RBUTTON_DOUBLE_CLICK")
    elif event == cv2.EVENT_MBUTTONDBLCLK:
        str = "(%d,%d) %s" % (x, y, "MBUTTON_DOUBLE_CLICK")

    # (5)マウスボタン，修飾キーを取得
    if (flags & cv2.EVENT_FLAG_LBUTTON):
        str += " + LBUTTON"
    elif (flags & cv2.EVENT_FLAG_RBUTTON):
        str += " + RBUTTON"
    elif (flags & cv2.EVENT_FLAG_MBUTTON):
        str += " + MBUTTON"
    elif (flags & cv2.EVENT_FLAG_CTRLKEY):
        str += " + CTRL"
    elif (flags & cv2.EVENT_FLAG_SHIFTKEY):
        str += " + SHIFT"
    elif (flags & cv2.EVENT_FLAG_ALTKEY):
        str += " + ALT"

    # (6)マウス座標，イベント，修飾キーなどを画像に描画，表示
    if on_mouse.line > max_line:
        img = cv2.getRectSubPix (img, (640,480), (320 - 0.5, 240 - 0.5 + h));
        cv2.putText (img, str, (w, 20 + h * max_line),
                     cv2.FONT_HERSHEY_DUPLEX, 0.4, (0, 200, 100));
    else:
        cv2.putText (img, str, (w, 20 + h * on_mouse.line),
                     cv2.FONT_HERSHEY_DUPLEX, 0.4, (0, 200, 100));

    on_mouse.line += 1
    cv2.imshow("Image", img);

## https://stackoverflow.com/questions/279561/
##      what-is-the-python-equivalent-of-static-variables-inside-a-function
on_mouse.line = 0;
main()
