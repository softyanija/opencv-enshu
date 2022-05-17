#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main (int argc, char **argv)
{
    cv::Mat src_img, src_img_gray, tmp_img1;

  // (1)画像を読み込む
  if (argc >= 2)
      src_img = cv::imread (argv[1],  cv::IMREAD_COLOR);
  if (!src_img.data)
      return -1;

  // (2)グレースケール変換:cvtColor
  cv::cvtColor (src_img, src_img_gray, cv::COLOR_BGR2GRAY);

  // (3)二値化:cvThreshold
  cv::threshold (src_img_gray, tmp_img1, 90, 255,  cv::THRESH_BINARY);

  // (4)画像を表示する
  cv::namedWindow ("Threshold", cv::WINDOW_AUTOSIZE);
  cv::imshow ("Threshold", tmp_img1);
  cv::waitKey (0);

  cv::destroyWindow ("Threshold");

  return 0;
}
