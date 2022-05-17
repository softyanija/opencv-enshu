#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
/* グローバル変数 */
#define font cv::FONT_HERSHEY_DUPLEX
cv::Mat frame;

/* プロトタイプ宣言 */
void on_trackbar (int val, void *);

int main (int argc, char *argv[])
{
  unsigned char c;

  // (1)指定された番号のカメラに対するキャプチャオブジェクトを作成する
  cv::VideoCapture capture(0);

  // (2)ウィンドウ，およびトラックバーを作成する
  cv::namedWindow ("Threshold", cv::WINDOW_AUTOSIZE);
  cv::createTrackbar ("Trackbar", "Threshold", 0, 250, on_trackbar);

  while (capture.isOpened()) {
    // (3)カメラから画像をキャプチャ
    capture.read(frame);

    // (4) 2msecだけキー入力を待つ
    c = cv::waitKey (2);
    if (c == '\x1b') // Escキー
      break;
  }

  cv::destroyWindow ("Threshold");

  return 0;
}

/* コールバック関数 */
void on_trackbar (int val, void *)
{
  int thread;
  cv::Mat src_img_gray, tmp_img1;
  std::ostringstream stream;

  // (1)トラックバー1の値を描画する
  stream << val;
  //thread = atoi(stream.str().c_str());
  thread = std::stoi(stream.str());

  // (2)グレースケール変換:cvtColor
  cv::cvtColor (frame, src_img_gray, cv::COLOR_BGR2GRAY);

  // (3)二値化:cvThreshold
  cv::threshold (src_img_gray, tmp_img1, thread, 255,  cv::THRESH_BINARY);

  // (4)画像を表示する
  cv::imshow ("Threshold", tmp_img1);
}
