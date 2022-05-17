#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main (int argc, char **argv)
{
    cv::Mat frame;
    unsigned char c;

    // (1)指定された番号のカメラに対するキャプチャオブジェクトを作成する
    cv::VideoCapture capture(0);

    // (2)表示用ウィンドウをの初期化
    cv::namedWindow ("Capture", cv::WINDOW_AUTOSIZE);

    while (capture.isOpened()) {

      // (3)カメラから画像をキャプチャする
      capture.read(frame);

      // (4) カメラ画像の表示
      cv::imshow ("Capture", frame);

      // (5) 2msecだけキー入力を待つ
      c = cv::waitKey (2);
      if (c == '\x1b') // Escキー
        break;
    }

    cv::destroyWindow ("Capture");

    return 0;
}
