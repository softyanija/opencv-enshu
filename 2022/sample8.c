#include <cv.h>
#include <highgui.h>
#include <stdio.h>

/* グローバル変数 */
CvFont font;
int value = 0;

/* プロトタイプ宣言 */
void on_trackbar (int val);

int
main (int argc, char *argv[])
{
  unsigned char c;
  IplImage *img = 0;

  // (1)画像領域を確保し，初期化する
  img = cvCreateImage (cvSize (400, 200), IPL_DEPTH_8U, 3);
  cvZero (img);
  cvInitFont (&font, CV_FONT_HERSHEY_DUPLEX, 1.0, 1.0, 0.0, 1, CV_AA);

  // (2)ウィンドウ，およびトラックバーを作成する
  cvNamedWindow ("Image", CV_WINDOW_AUTOSIZE);
  cvCreateTrackbar ("Trackbar", "Image", 0, 100, on_trackbar);

  while (1) {
    char str[64];

    // (3)トラックバー1の値を描画する
    cvRectangle (img, cvPoint (0, 0), cvPoint (400, 50), cvScalar (0, 0, 0, 0), CV_FILLED, 8, 0);
    snprintf (str, 64, "%d", value);
    cvPutText (img, str, cvPoint (15, 30), &font, CV_RGB (0, 200, 100));
    cvShowImage ("Image", img);

    c = cvWaitKey (2);
    if (c == '\x1b') // Escキー
      break;
  }

  cvDestroyWindow ("Image");
  cvReleaseImage (&img);

  return 0;
}

/* コールバック関数 */
void
on_trackbar (int val)
{
  // (4)トラックバー1の値を大域変数に代入する．
  value = val;
}
