#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main (int argc, char **argv)
{
    cv::Mat src_img, dst_img1, dst_img2, dst_img3;
    cv::Mat tmp_img;

    // (1)画像の読み込み
    if (argc >= 2)
      src_img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    if (!src_img.data)
        return -1;

    // (2)Sobelフィルタによる微分画像の作成
    cv::Sobel (src_img, tmp_img, CV_32F, 1, 1);
    cv::convertScaleAbs (tmp_img, dst_img1, 1, 0);

    // (3)画像のLaplacianの作成
    cv::Laplacian (src_img, tmp_img, CV_32F, 3);
    cv::convertScaleAbs (tmp_img, dst_img2, 1, 0);

    // (4)Cannyによるエッジ画像の作成
    cv::Canny (src_img, dst_img3, 50.0, 200.0);

    // (5)画像の表示
    cv::namedWindow ("Original", cv::WINDOW_AUTOSIZE);
    cv::imshow ("Original", src_img);
    cv::namedWindow ("Sobel", cv::WINDOW_AUTOSIZE);
    cv::imshow ("Sobel", dst_img1);
    cv::namedWindow ("Laplace", cv::WINDOW_AUTOSIZE);
    cv::imshow ("Laplace", dst_img2);
    cv::namedWindow ("Canny", cv::WINDOW_AUTOSIZE);
    cv::imshow ("Canny", dst_img3);
    cv::waitKey (0);

    cv::destroyWindow ("Original");
    cv::destroyWindow ("Sobel");
    cv::destroyWindow ("Laplace");
    cv::destroyWindow ("Canny");

    return 0;
}
