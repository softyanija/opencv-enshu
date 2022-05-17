#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main (int argc, char **argv)
{
    int x, y;
    cv::Vec3b intensity;
    uchar p[3];
    cv::Mat img;

    // (1)画像を読み込む
    if (argc >= 2)
        img = cv::imread(argv[1], cv::IMREAD_COLOR);
    if (!img.data)
        return -1;

    // (1)画素値（R,G,B）を順次取得し，変更する
    cv::Size s = img.size();
    for (y = 0; y < s.height; y++) {
        for (x = 0; x < s.width; x++) {
            /* 画素値を直接操作する一例 */
            intensity = img.at<cv::Vec3b>(y, x);
            p[2] = intensity.val[0]; //B
            p[1] = intensity.val[1]; //G
            p[0] = intensity.val[2]; //R
            int r, g, b;
            r = cvRound ( 0.362718 * p[0] + 0.634689 * p[1] + -0.000196 * p[2]);
            g = cvRound ( 0.264182 * p[0] + 0.738208 * p[1] +  0.000146 * p[2]);
            b = cvRound (-0.020544 * p[0] + 0.019072 * p[1] +  0.999924 * p[2]);
            r = std::min(255, std::max(0, r));
            g = std::min(255, std::max(0, g));
            b = std::min(255, std::max(0, b));
            intensity.val[2] = r;
            intensity.val[1] = g;
            intensity.val[0] = b;
            img.at<cv::Vec3b>(y, x) = intensity;
        }
    }

    cv::namedWindow ("Image", cv::WINDOW_AUTOSIZE);
    cv::imshow ("Image", img);
    cv::waitKey (0);

    cv::destroyWindow ("Image");

    return 0;
}
