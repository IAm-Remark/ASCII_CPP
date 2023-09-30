#include <iostream>
#include <functional>
#include <numeric>
#include <vector>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>


template<class T>
struct IotaWrapper
{
    typedef T type;
    typedef std::function<type(const type&)> IncrFunction;

    type value;
    IncrFunction incrFunction;

    IotaWrapper() = delete;
    IotaWrapper(const type& n, const IncrFunction& incrFunction) : value(n), incrFunction(incrFunction) {};

    operator type() { return value; }
    IotaWrapper& operator++() { value = incrFunction(value); return *this; }
};

cv::Mat img = cv::imread("D:/projects/3D_Graph/Graph_project_self/res/pics/3.jpg");
cv::Mat img1 = cv::imread("D:/projects/3D_Graph/Graph_project_self/res/pics/3.jpg");
//cv::Mat img_converted = img;
int iHeight = img.size().height;
int iWidth = img.size().width;


int iFontSize = 12;
int iCharStep = iFontSize * 2;
const int l = 6;


char cChars[l] = " .o@#";
std::string sChars[] = { " ", ".", "@", "#" };
int iCoeff = 255 / strlen(cChars) - 1;

IotaWrapper<int> n(0, [](const int& n) { return n + iCharStep; });

int main()
{

    std::vector<int> vHeight(iHeight / iCharStep);
    std::iota(vHeight.begin(), vHeight.end(), n);
    std::vector<int> vWidth(iWidth / iCharStep);
    std::iota(vWidth.begin(), vWidth.end(), n);

    for (auto i : vHeight)
        std::cout << i << ' ';


    img1 = cv::Mat::zeros(iHeight, iWidth, CV_8UC3);
    
    for (auto i : vHeight)
    {
        for (int j : vWidth)
        {
            cv::Vec3b pixel = img.at<cv::Vec3b>(i, j);

            cv::putText(img1, sChars[2],
                cv::Point(j, i),
                cv::FONT_HERSHEY_SIMPLEX,
                1.0,
                CV_RGB(pixel[2], pixel[1], pixel[0], 1.0));
        }
    }
    cv::imshow("Image_self", img);
    cv::imshow("Image_converted", img1);
    cv::waitKey(0);
}