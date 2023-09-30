#include <iostream>
#include <fstream>

#include <functional>
#include <numeric>
#include <vector>

#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>



//Star this rep if you see it ;)

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
std::string sFontPath = "res/font/Lack.otf";
std::string sPath = "res/pics/1.jpg";

cv::Mat img_self = cv::imread(sPath);
cv::Mat img_to_convert = cv::imread(sPath);
cv::Mat img_to_gray = cv::imread(sPath);

int iHeight = img_self.size().height;
int iWidth = img_self.size().width;


//Feel free to redact. Low font size increase detalisation of ascii
int iFontSize = 12;
int iCharStep = iFontSize * 0.8;

//Before adding more chars to list be sure to redact the length
const int length = 12;
std::string sChars[length] = { " ", "*", "!", "?", "2", "X", "F", "W", "A", "&", "%", "@"};
std::string sAsciiText;
int iCoeff = 255 / length + 1;


IotaWrapper<int> n(0, [](const int& n) { return n + iCharStep; });

int main()
{
    std::ofstream oAsciiText;
    oAsciiText.open("res/txt/Converted.txt");


    std::vector<int> vHeight(iHeight / iCharStep);
    std::iota(vHeight.begin(), vHeight.end(), n);
    std::vector<int> vWidth(iWidth / iCharStep);
    std::iota(vWidth.begin(), vWidth.end(), n);



    //Make gray image
    cv::cvtColor(img_to_gray, img_to_gray, cv::COLOR_BGR2GRAY);
   
    //I don't know why, but code just crash at rgb value check without converting it back. I have no clue, it have same value still.
    cv::cvtColor(img_to_gray, img_to_gray, cv::COLOR_GRAY2RGB);
    
    //Fill whole convertated image in black before ascii convert
    img_to_convert = cv::Mat::zeros(iHeight, iWidth, CV_8UC3);
    
    for (auto i : vHeight)
    {
        for (int j : vWidth)
        {
            //Find out current pixel's rgb value
            cv::Vec3b pixel = img_self.at<cv::Vec3b>(i, j);

            cv::Vec3b pixel_gray = img_to_gray.at<cv::Vec3b>(i, j);

            int iCharCoeff = 1;

            iCharCoeff = pixel_gray[0] / iCoeff;
            //Fill pixel with char and right rgb
            if (iCharCoeff <= length)
                cv::putText(img_to_convert, sChars[iCharCoeff],
                    cv::Point(j, i),
                    //Feel free to change font
                    cv::FONT_HERSHEY_PLAIN,
                    1.0,
                    CV_RGB(pixel[2], pixel[1], pixel[0], 1.0));
            
            sAsciiText += sChars[iCharCoeff];
        }

        sAsciiText += "\n";
    }
    
    cv::imshow("Image_self", img_self);
    cv::imshow("Image_converted", img_to_convert);
    //cv::imshow("Image_gray", img_to_gray);

    oAsciiText << sAsciiText;
    cv::waitKey(0);
    
    oAsciiText.close();
    //cv::imwrite("res/render/Converted.jpg", img_to_convert);

}
