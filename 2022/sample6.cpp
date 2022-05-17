#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/* グローバル変数 */
#define font cv::FONT_HERSHEY_DUPLEX
cv::Mat img;

/* プロトタイプ宣言 */
void on_mouse (int event, int x, int y, int flags, void *param);

int main (int argc, char *argv[])
{
  unsigned char c;

  // (1)画像領域を確保し，初期化する
  img = cv::Mat::zeros(480, 640, CV_8UC3);

  // (2)ウィンドウを作成し，マウスイベントに対するコールバック関数を登録する
  cv::namedWindow ("Image", cv::WINDOW_AUTOSIZE);
  cv::setMouseCallback ("Image", on_mouse, 0);
  cv::imshow ("Image", img);

  // (3)'Esc'キーが押された場合に終了する
  while (1) {
      c = cv::waitKey (2);
      if (c == '\x1b')
          return 1;
  }

  cv::destroyWindow ("Image");

  return 0;
}

/* コールバック関数 */
void on_mouse (int event, int x, int y, int flags, void *param)
{
  std::ostringstream stream;
  static int line = 0;
  const int max_line = 15, w = 15, h = 30;

  // (4)マウスイベントを取得
  switch (event) {
  case cv::EVENT_MOUSEMOVE:
    stream << "(" << x << ", " << y << ") cv::EVENT_MOUSEMOVE";
    break;
  case cv::EVENT_LBUTTONDOWN:
    stream << "(" << x << ", " << y << ") cv::EVENT_LBUTTONDOWN";
    break;
  case cv::EVENT_RBUTTONDOWN:
    stream << "(" << x << ", " << y << ") cv::EVENT_RBUTTONDOWN";
    break;
  case cv::EVENT_MBUTTONDOWN:
    stream << "(" << x << ", " << y << ") cv::EVENT_MBUTTONDOWN";
    break;
  case cv::EVENT_LBUTTONUP:
    stream << "(" << x << ", " << y << ") cv::EVENT_LBUTTONUP";
    break;
  case cv::EVENT_RBUTTONUP:
    stream << "(" << x << ", " << y << ") cv::EVENT_RBUTTONUP";
    break;
  case cv::EVENT_MBUTTONUP:
    stream << "(" << x << ", " << y << ") cv::EVENT_MBUTTONUP";
    break;
  case cv::EVENT_LBUTTONDBLCLK:
    stream << "(" << x << ", " << y << ") cv::EVENT_LBUTTONDBLCLK";
    break;
  case cv::EVENT_RBUTTONDBLCLK:
    stream << "(" << x << ", " << y << ") cv::EVENT_RBUTTONDBLCLK";
    break;
  case cv::EVENT_MBUTTONDBLCLK:
    stream << "(" << x << ", " << y << ") cv::EVENT_MBUTTONDBLCLK";
    break;
  }

  // (5)マウスボタン，修飾キーを取得
  if (flags & cv::EVENT_FLAG_LBUTTON)
    stream << " + LBUTTON";
  if (flags & cv::EVENT_FLAG_RBUTTON)
    stream << " + RBUTTON";
  if (flags & cv::EVENT_FLAG_MBUTTON)
    stream << " + MBUTTON";
  if (flags & cv::EVENT_FLAG_CTRLKEY)
    stream << " + CTRL";
  if (flags & cv::EVENT_FLAG_SHIFTKEY)
    stream << " + SHIFT";
  if (flags & cv::EVENT_FLAG_ALTKEY)
    stream << " + ALT";

  // (6)マウス座標，イベント，修飾キーなどを画像に描画，表示
  if (line > max_line) {
      cv::getRectSubPix (img, cv::Size(640, 480), cv::Point2f (320 - 0.5, 240 - 0.5 + h), img);
      cv::putText (img, stream.str(), cv::Point (w, 20 + h * max_line), font,
                   0.4, cv::Scalar(0, 200, 100), 1, cv::LINE_AA);
  }
  else {
    cv::putText (img, stream.str(), cv::Point (w, 20 + h * line), font,
                 0.4, cv::Scalar (0, 200, 100), 1, cv::LINE_AA);
  }
  line++;
  cv::imshow ("Image", img);
}
