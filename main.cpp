#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 2) { printf("argc = %i, error\n", argc); return -1;}
    double mullFactor = 0.0;
    (argc == 3) ? mullFactor = atof(argv[2]) : mullFactor = 0.0;

    Mat imageSrc;

    imageSrc = imread(argv[1], IMREAD_GRAYSCALE);


//    cv::Mat hist;
//    float h_ranges[] = {0, 180}; // hue is [0, 180]
//    float s_ranges[] = {0, 256};
//    const float* ranges[] = {h_ranges, s_ranges};
//    int histSize[] =  {30, 32};
//    int ch[] = {0, 1};

    //calcHist(&imageSrc, 1, 0, cv::noArray(), hist, 1, histSize, ranges, true);
    //normalize(hist, hist, 0, 255, cv::NORM_MINMAX);
    //equalizeHist(imageSrc, imageSrc);


    Mat imageDst;
    //Sobel(imageSrc, imageDst, -1, 1, 1);
    Laplacian(imageSrc, imageDst, -1);



    Mat mean, dev;
    meanStdDev(imageDst, mean, dev);

    threshold(imageDst, imageDst, mean.at<double>(0,0) + mullFactor * dev.at<double>(0,0),
              255, THRESH_BINARY);

    for(int i = 0; i < imageDst.rows; i++)
    {
        for(int j = 0; j < imageDst.cols; j++)
        {
            imageDst.at<uchar>(i,j) = 255 - imageDst.at<uchar>(i,j);
        }
    }

    namedWindow("dst", WINDOW_AUTOSIZE);

    for(;;)
    {
        if(!imageDst.empty())
            imshow("dst", imageDst);

        if(waitKey(10) == 10)
        {
            char *fileName = strdup("../result.png");
            imwrite(fileName, imageDst);
            free(fileName);
            break;
        }
    }

    cout << "Hello World!" << endl;
    return 0;
}
