#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

int main (int argc, char **argv)
{
  cv::Mat frame;
  cv::Mat src_gray;
  unsigned char c;

  const char *cascade_name =
    "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml";
  cv::CascadeClassifier cascade;
  std::vector<cv::Rect> faces;
  static cv::Scalar colors[] = {
    {0, 0, 255}, {0, 128, 255},
    {0, 255, 255}, {0, 255, 0},
    {255, 128, 0}, {255, 255, 0},
    {255, 0, 0}, {255, 0, 255}
  };

  // (1)指定された番号のカメラに対するキャプチャオブジェクトを作成する
  cv::VideoCapture capture(0);

  // (2)表示用ウィンドウをの初期化
  cv::namedWindow ("Face Detection", CV_WINDOW_AUTOSIZE);

  // (4)ブーストされた分類器のカスケードを読み込む
  cascade.load(cascade_name);

  while (capture.isOpened()) {
    // (5)カメラから画像をキャプチャ
    capture.read(frame);

    // (6)読み込んだ画像のグレースケール化，ヒストグラムの均一化を行う
    cv::cvtColor (frame, src_gray, CV_BGR2GRAY);
    cv::equalizeHist (src_gray, src_gray);

    cascade.detectMultiScale(src_gray, faces,
                             1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(40, 40) );

    // (7)検出された全ての顔位置に，円を描画する
    int i = 0;
    for(std::vector<cv::Rect>::iterator r = faces.begin(); r != faces.end(); r++){
      cv::Point center;
      int radius;
      center.x = cvRound(r->x+r->width*0.5);
      center.y = cvRound(r->y+r->height*0.5);
      radius = cvRound ((r->width+r->height)*0.25);
      cv::circle (frame, center, radius, colors[(i++) % 8], 3, 8, 0);
    }


    // (8) カメラ画像の表示
    cv::imshow ("Face Detection", frame);

    // (9) 2msecだけキー入力を待つ
    c = cv::waitKey (2);
    if (c == '\x1b') // Escキー
      break;
  }

  cv::destroyWindow ("Face Detection");

  return 0;
}
