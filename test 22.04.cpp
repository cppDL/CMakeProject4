#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>



using namespace cv;
using namespace std;


class Detector
{
    Mat camera, camera_HSV, camera_threshold_green, camera_threshold_blue;
    VideoCapture cap;
    int hmin_green = 80;
    int smin_green = 100;
    int vmin_green = 100;
    int hmax_green = 120;
    int smax_green = 255;
    int vmax_green = 255;

    int hmin_blue = 80;
    int smin_blue = 100;
    int vmin_blue = 100;
    int hmax_blue = 120;
    int smax_blue = 255;
    int vmax_blue = 255;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    RotatedRect rect;
    int count = 0;

    // we only have one color value because we will put it as the default and any other color value is immediately "GRAFFITTI"
public:
    Detector() {
        cap.open(0);
        while (true) {
            getcamera();
            findObject(camera);
            showcameras();
            getContours(camera_threshold_green, camera);
        }
    }
    void getcamera()
    {
        cap >> camera;
        if (camera.empty())
        {
            throw;
        }
    }
    void findObject(Mat& camera)
    {
        cvtColor(camera, camera_HSV, ColorConversionCodes::COLOR_BGR2HSV);
        inRange(camera_HSV, Scalar(hmin_green, smin_green, vmin_green), Scalar(hmax_green, smax_green, vmax_green), camera_threshold_green);
        inRange(camera_HSV, Scalar(hmin_blue, smin_blue, vmin_blue), Scalar(hmax_blue, smax_blue, vmax_blue), camera_threshold_blue);
    }
    void showcameras()
    {
        imshow("camera", camera);
        imshow("Image Threshold", camera_threshold_green);
        imshow("Image Threshold", camera_threshold_blue);
        waitKey(20);
    }
    void getContours(Mat imgDil, Mat img)
    {

        findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        vector<vector<Point> > contours_poly(contours.size());
        vector<Rect> boundRect(contours.size());


        for (int i = 0; i < (int)contours.size(); i++)
        {
            approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
            boundRect[i] = boundingRect(Mat(contours_poly[i]));

            if ((boundRect[i].width * boundRect[i].height) > 1000)
            {
                drawContours(img, contours, i, Scalar(255, 0, 255), 4);
                //imshow("image", img);
                rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 0, 255), 2, 8, 0);
                //imshow("rectangle", img);
                circle(img, (boundRect[i].tl() + boundRect[i].br()) / 2, 3, Scalar(), 5, 8, 0);
                imshow("circle", img);
                if (i > 1) {

                    line(img, (boundRect[i].tl() + boundRect[i].br()) / 2, (boundRect[i - 1].tl() + boundRect[i - 1].br()) / 2, (0, 255, 0), 2); //пытаюсь чтобы рисовались линии между двумя точками
                }
            }
        }
    }

};

int main()
{
    Detector();

    return 0;
}
