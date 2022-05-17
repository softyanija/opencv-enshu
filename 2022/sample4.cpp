#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

int main (int argc, char **argv)
{
  cv::Mat src_img, src_gray;
  const char *cascade_name =
  "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml";
  cv::CascadeClassifier cascade;
  std::vector<cv::Rect> faces;
  static cv::Scalar colors[] = {
    {0, 0, 255}, {0, 128, 255}, {0, 255, 255}, {0, 255, 0},
    {255, 128, 0}, {255, 255, 0}, {255, 0, 0}, {255, 0, 255}
  };

  // (1)画像を読み込む
  if (argc >= 2)
    src_img = cv::imread(argv[1], cv::IMREAD_COLOR);
  if (!src_img.data)
    return -1;

  // (2)ブーストされた分類器のカスケードを読み込む
  cascade.load(cascade_name);

  // (3)読み込んだ画像のグレースケール化，ヒストグラムの均一化を行う
  cv::cvtColor (src_img, src_gray, cv::COLOR_BGR2GRAY);
  cv::equalizeHist (src_gray, src_gray);

  // (4)物体（顔）検出.結果はfacesに格納する．
  cascade.detectMultiScale(src_gray, faces,
        1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(40, 40) );

  // (5)検出された全ての顔位置に，円を描画する
  int i = 0;
  for(std::vector<cv::Rect>::iterator r = faces.begin(); r != faces.end(); r++){
   cv::Point center;
   int radius;
   center.x = cvRound(r->x+r->width*0.5);
   center.y = cvRound(r->y+r->height*0.5);
   radius = cvRound ((r->width+r->height)*0.25);
   cv::circle (src_img, center, radius, colors[(i++) % 8], 3, 8, 0);
  }

  // (6)画像を表示，キーが押されたときに終了
  cv::namedWindow ("Face Detection", cv::WINDOW_AUTOSIZE);
  cv::imshow ("Face Detection", src_img);
  cv::waitKey (0);

  cv::destroyWindow ("Face Detection");

  return 0;
}
