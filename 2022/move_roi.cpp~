#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main (int argc, char **argv)
{
  cv::Mat frame, src_img_gray, roi_img_gray, tmp_img1;
    unsigned char c;

    // (1)指定された番号のカメラに対するキャプチャオブジェクトを作成する
    cv::VideoCapture capture(0);

    // (2)表示用ウィンドウをの初期化
    cv::namedWindow ("Capture", cv::WINDOW_AUTOSIZE);

    while (capture.isOpened()) {

      // (3)カメラから画像をキャプチャする
      capture.read(frame);

      cv::cvtColor (frame, src_img_gray, cv::COLOR_BGR2GRAY);

      cv::Size s = src_img_gray.size();
      cv::Rect roi = cv::Rect(s.width/2 - s.width/4,
			  s.height/2 - s.height/4,
			  s.width/2,
			  s.height/2);
      src_img_gray(roi).copyTo(roi_img_gray);

      cv::threshold( roi_img_gray, tmp_img1, 90, 255, cv::THRESH_BINARY);

      tmp_img1.copyTo(src_img_gray(roi));

      // (4) カメラ画像の表示
      cv::namedWindow ("ROI", cv::WINDOW_AUTOSIZE);
      cv::namedWindow ("Threshold", cv::WINDOW_AUTOSIZE);
      cv::namedWindow ("Threshold + ROI", cv::WINDOW_AUTOSIZE);
      cv::imshow ("ROI", roi_img_gray);
      cv::imshow ("Threshold", tmp_img1);
      cv::imshow ("Threshold + ROI", src_img_gray);

      // (5) 2msecだけキー入力を待つ
      c = cv::waitKey (2);
      if (c == '\x1b') // Escキー
        break;
    }

    cv::destroyWindow ("ROI");
    cv::destroyWindow ("Threshold");
    cv::destroyWindow ("Threshold + ROI");

    return 0;
}
