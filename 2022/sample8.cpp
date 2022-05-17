#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/* グローバル変数 */
#define font cv::FONT_HERSHEY_DUPLEX
int value = 0;

/* プロトタイプ宣言 */
void on_trackbar (int val, void *);

int main (int argc, char *argv[])
{
  unsigned char c;
  cv::Mat img;

  // (1)画像領域を確保し，初期化する
  img = cv::Mat::zeros(480, 640, CV_8UC3);

  // (2)ウィンドウ，およびトラックバーを作成する
  cv::namedWindow ("Image", cv::WINDOW_AUTOSIZE);
  cv::createTrackbar ("Trackbar", "Image",
                      0, 100, on_trackbar);

  while (1) {
    std::ostringstream stream;

    // (3)トラックバー1の値を描画する
    cv::rectangle (img, cv::Point (0, 0),
                   cv::Point (400, 50),
                   cv::Scalar (0, 0, 0, 0),
                   -1, cv::LINE_AA);
    stream << value;//数値から文字列に変換するための処理
    cv::putText (img, stream.str(),
                 cv::Point (15, 30), font, 1,
                 cv::Scalar (0, 200, 100));
    cv::imshow ("Image", img);

    c = cv::waitKey (2);
    if (c == '\x1b') // Escキー
      break;

  }

  cv::destroyWindow ("Image");

  return 0;
}

/* コールバック関数 */
void on_trackbar (int val, void *)
{
  // (4)トラックバー1の値を大域変数に代入する．
   value = val;
}
