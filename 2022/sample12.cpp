#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main (int argc, char **argv)
{
  int x, y;
  cv::Mat src_img, src_img_gray, roi_img_gray, tmp_img1;

  // (1)画像を読み込む
  if (argc >= 2)
      src_img = cv::imread (argv[1],  cv::IMREAD_COLOR);
  if (!src_img.data)
      return -1;

  // (2)グレースケール変換:cvtColor
  cv::cvtColor (src_img, src_img_gray, cv::COLOR_BGR2GRAY);

  // (3)ROI イメージの生成
  cv::Size s = src_img_gray.size();
  cv::Rect roi = cv::Rect(s.width/2  - s.width/4,   // left top (x)
                          s.height/2 - s.height/4,  // left top (y)
                          s.width/2,                // width
                          s.height/2);              // height
  src_img_gray(roi).copyTo(roi_img_gray);

  // (4)ROI画像の二値化:cvThreshold
  cv::threshold (roi_img_gray, tmp_img1, 90, 255,  cv::THRESH_BINARY);

  // (5)Mask画像の生成
  cv::Mat roi_mask = cv::Mat(s.height/2, s.width/2, src_img_gray.type());
  for (y = 0; y < s.height/2; y++) {
    for (x = 0; x < s.width/2; x++) {
      unsigned char value = roi_mask.at<unsigned char>(y, x);
      if ( ( ( pow((y - s.height/4), 2) / pow((s.height/4), 2) ) +
             ( pow((x - s.width/4 ), 2) / pow((s.width/4 ), 2) ) ) < 1 ) {
        value = 255;
      } else {
        value = 0;
      }
      roi_mask.at<unsigned char>(y, x) = value;
    }
  }

  // (6)グレースケール画像にROI画像を代入．
  tmp_img1.copyTo(src_img_gray(roi), roi_mask);

  // (7)画像を表示する
  cv::namedWindow ("ROI", cv::WINDOW_AUTOSIZE);
  cv::namedWindow ("Mask", cv::WINDOW_AUTOSIZE);
  cv::namedWindow ("Threshold", cv::WINDOW_AUTOSIZE);
  cv::namedWindow ("Threshold + ROI", cv::WINDOW_AUTOSIZE);
  cv::imshow ("ROI", roi_img_gray);
  cv::imshow ("Mask", roi_mask);
  cv::imshow ("Threshold", tmp_img1);
  cv::imshow ("Threshold + ROI", src_img_gray);

  cv::waitKey (0);

  cv::destroyWindow ("ROI");
  cv::destroyWindow ("Mask");
  cv::destroyWindow ("Threshold");
  cv::destroyWindow ("Threshold + ROI");

  return 0;
}
