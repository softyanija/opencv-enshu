#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

//global val
#define font cv::FONT_HERSHEY_DUPLEX
int value = 0;

//proto
void on_trackbar (int val, void *);

int main (int argc, char **argv)
{
  cv::Mat frame, frame_gray, tmp_image;
  unsigned char c;

    // (1)指定された番号のカメラに対するキャプチャオブジェクトを作成する
    cv::VideoCapture capture(0);

    // (2)表示用ウィンドウをの初期化
    cv::namedWindow ("Capture", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar ("Trackbar", "Capture", 0, 255, on_trackbar);

    while (capture.isOpened()) {

      // (3)カメラから画像をキャプチャする
      capture.read(frame);

      // グレスケ変換
      cv::cvtColor (frame, frame_gray, cv::COLOR_BGR2GRAY);

      //二値化
      cv::threshold (frame_gray, tmp_image, value, 255, cv::THRESH_BINARY);

      // (4) カメラ画像の表示
      cv::imshow ("Capture", tmp_image);

      // (5) 2msecだけキー入力を待つ
      c = cv::waitKey (2);
      if (c == '\x1b') // Escキー
        break;
    }

    cv::destroyWindow ("Capture");

    return 0;
}

void on_trackbar (int val, void *)
{
  value = val;
}
