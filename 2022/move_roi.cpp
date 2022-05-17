#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int rect_x, rect_y, hoge, huga;

void on_mouse (int event, int x, int y, int flag, void *param);

int main (int argc, char **argv)
{
  cv::Mat frame, src_img_gray, roi_img_gray, tmp_img1;
    unsigned char c;

    // (1)指定された番号のカメラに対するキャプチャオブジェクトを作成する
    cv::VideoCapture capture(0);

    // (2)表示用ウィンドウをの初期化
    

     cv::namedWindow ("ROI", cv::WINDOW_AUTOSIZE);
      cv::namedWindow ("Threshold", cv::WINDOW_AUTOSIZE);
      cv::namedWindow ("Threshold + ROI", cv::WINDOW_AUTOSIZE);
      cv::setMouseCallback ("Threshold + ROI", on_mouse, 0);

      rect_x = 0;
      rect_y = 0;
    while (capture.isOpened()) {

      // (3)カメラから画像をキャプチャする
      capture.read(frame);

      cv::cvtColor (frame, src_img_gray, cv::COLOR_BGR2GRAY);

      cv::Size s = src_img_gray.size();
      if(rect_x + s.width/2 > s.width){
        hoge = s.width - rect_x;
      }else{
	hoge = s.width/2;
      }
      if(rect_y + s.height/2 > s.height){
        huga = s.height - rect_y;
      }else{
	huga = s.height/2;
      }
      
      cv::Rect roi = cv::Rect(rect_x,
			  rect_y,
			  hoge,
			  huga);
      src_img_gray(roi).copyTo(roi_img_gray);

      cv::threshold( roi_img_gray, tmp_img1, 90, 255, cv::THRESH_BINARY);

      tmp_img1.copyTo(src_img_gray(roi));

      // (4) カメラ画像の表示
     
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

void on_mouse (int event, int x, int y, int flags, void *param)
{
  std::ostringstream stream;
  static int line = 0;
  const int max_line = 15, w = 15, h = 30;

  // (4)マウスイベントを取得
  switch (event) {
  case cv::EVENT_MOUSEMOVE:
    stream << "(" << x << ", " << y << ") cv::EVENT_MOUSEMOVE";
    rect_x = x;
    rect_y = y;
    break;
  case cv::EVENT_LBUTTONDOWN:
    stream << "(" << x << ", " << y << ") cv::EVENT_LBUTTONDOWN";
    break;
  case cv::EVENT_RBUTTONDOWN:
    stream << "(" << x << ", " << y << ") cv::EVENT_RBUTTONDOWN";
    break;
  case cv::EVENT_MBUTTONDOWN:
    stream << "(" << x << ", " << y << ") cv::EVENT_MBUTTONDOWN";
    break;
  case cv::EVENT_LBUTTONUP:
    stream << "(" << x << ", " << y << ") cv::EVENT_LBUTTONUP";
    break;
  case cv::EVENT_RBUTTONUP:
    stream << "(" << x << ", " << y << ") cv::EVENT_RBUTTONUP";
    break;
  case cv::EVENT_MBUTTONUP:
    stream << "(" << x << ", " << y << ") cv::EVENT_MBUTTONUP";
    break;
  case cv::EVENT_LBUTTONDBLCLK:
    stream << "(" << x << ", " << y << ") cv::EVENT_LBUTTONDBLCLK";
    break;
  case cv::EVENT_RBUTTONDBLCLK:
    stream << "(" << x << ", " << y << ") cv::EVENT_RBUTTONDBLCLK";
    break;
  case cv::EVENT_MBUTTONDBLCLK:
    stream << "(" << x << ", " << y << ") cv::EVENT_MBUTTONDBLCLK";
    break;
  }

  // (5)マウスボタン，修飾キーを取得
  if (flags & cv::EVENT_FLAG_LBUTTON)
    stream << " + LBUTTON";
  if (flags & cv::EVENT_FLAG_RBUTTON)
    stream << " + RBUTTON";
  if (flags & cv::EVENT_FLAG_MBUTTON)
    stream << " + MBUTTON";
  if (flags & cv::EVENT_FLAG_CTRLKEY)
    stream << " + CTRL";
  if (flags & cv::EVENT_FLAG_SHIFTKEY)
    stream << " + SHIFT";
  if (flags & cv::EVENT_FLAG_ALTKEY)
    stream << " + ALT";

}
