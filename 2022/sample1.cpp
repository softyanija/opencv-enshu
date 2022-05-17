#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main (int argc, char **argv)
{
    cv::Mat src_img;
  // (1)ファイルから画像メモリに読み込む
  if (argc >= 2)
      src_img = cv::imread(argv[1], cv::IMREAD_COLOR);
  if (!src_img.data)
      return -1;

  // (2)ウィンドウを表示する
  cv::namedWindow("Image",  cv::WINDOW_AUTOSIZE);

  // (3)画像を表示する
  cv::imshow ("Image", src_img);

  // (4)キー入力を待つ
  cv::waitKey (0);

  // (5)ウィンドウを消去する
  cv::destroyWindow ("Image");

  return 0;
}
