#include <iostream>
#include <functional>
#include <numeric>
#include <vector>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>


// I've copypasted this part from stackoverflow ;)
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

//So all mine code starts here
cv::Mat img_self = cv::imread("D:/projects/ascii_cpp_project/ascii_cpp_project_self/res/pics/6.jpg");
cv::Mat img_to_convert = cv::imread("D:/projects/ascii_cpp_project/ascii_cpp_project_self/res/pics/6.jpg");

int iHeight = img_self.size().height;
int iWidth = img_self.size().width;

//Feel free to redact. Low font size increase detalisation of ascii
int iFontSize = 12;
int iCharStep = iFontSize * 1;

//Before adding more chars to list be sure to redact the length
const int length = 6;
std::string sChars[length] = { " ", ".", "@", "#" };

int iCoeff = 255 / length - 1;


IotaWrapper<int> n(0, [](const int& n) { return n + iCharStep; });

int main()
{

    std::vector<int> vHeight(iHeight / iCharStep);
    std::iota(vHeight.begin(), vHeight.end(), n);
    std::vector<int> vWidth(iWidth / iCharStep);
    std::iota(vWidth.begin(), vWidth.end(), n);

    //Fill whole image black before ascii convert
    img_to_convert = cv::Mat::zeros(iHeight, iWidth, CV_8UC3);
    
    for (auto i : vHeight)
    {
        for (int j : vWidth)
        {
            //Find out current pixel's rgb value
            cv::Vec3b pixel = img_self.at<cv::Vec3b>(i, j);

            //Fill pixel with char and right rgb
            cv::putText(img_to_convert, sChars[1],
                cv::Point(j, i),
                //Feel free to change font
                cv::FONT_HERSHEY_SIMPLEX,
                1.0,
                CV_RGB(pixel[2], pixel[1], pixel[0], 1.0));
        }
    }

    cv::imshow("Image_self", img_self);
    cv::imshow("Image_converted", img_to_convert);
    cv::waitKey(0);
    //Feel free to change dir, be sure you use right slashes
    cv::imwrite("D:/projects/ascii_cpp_project/ascii_cpp_project_self/res/render/Converted.jpg", 
        img_to_convert);
}