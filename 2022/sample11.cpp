#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main (int argc, char **argv)
{
  int x, y;
  cv::Vec3b intensity;
  cv::Mat src_img, src_img_gray, roi_img_gray, tmp_img1;

  // (1)画像を読み込む
  if (argc >= 2)
      src_img = cv::imread (argv[1],  cv::IMREAD_COLOR);
  if (!src_img.data)
      return -1;

  // (2)ROI 部分の処理の生成
  cv::Size s = src_img.size();
  for (y = s.height/2 - s.height/4; y < s.height/2 + s.height/4; y++) {
    for (x = s.width/2 - s.width/4; x < s.width/2 + s.width/4; x++) {
      intensity = src_img.at<cv::Vec3b>(y, x);
      int value = (intensity.val[0] + intensity.val[1] + intensity.val[2])/3;
      if ( value > 90 )  {
        value = 255;
      } else {
        value = 0;
      }
      intensity.val[0] = intensity.val[1] = intensity.val[2] = value;
      src_img.at<cv::Vec3b>(y, x) = intensity;
    }
  }
  // (3)グレースケール変換:cvtColor
  cv::cvtColor (src_img, src_img_gray, cv::COLOR_BGR2GRAY);

  // (4)ROI 部分の処理の生成
  for (y = s.height/2 - s.height/4; y < s.height/2 + s.height/4; y++) {
    for (x = s.width/2 - s.width/4; x < s.width/2 + s.width/4; x++) {

      unsigned char value = src_img_gray.at<unsigned char>(y, x);
      if ( value > 90 )  {
        value = 255;
      } else {
        value = 0;
      }
      src_img_gray.at<unsigned char>(y, x) = value;
    }
  }

  // (5)画像を表示する
  cv::namedWindow ("Threshold + ROI (Color)", cv::WINDOW_AUTOSIZE);
  cv::imshow ("Threshold + ROI (Color)", src_img);
  cv::namedWindow ("Threshold + ROI (Gray)", cv::WINDOW_AUTOSIZE);
  cv::imshow ("Threshold + ROI (Gray)", src_img_gray);

  cv::waitKey (0);

  cv::destroyWindow ("Threshold + ROI (Color)");
  cv::destroyWindow ("Threshold + ROI (Gray)");

  return 0;
}
