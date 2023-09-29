#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>



int main()
{
    cv::Mat img = cv::imread("D:/projects/3D_Graph/Graph_project_self/res/pics/1.jpg", cv::);
    cv::Mat img1 = cv::imread("D:/projects/3D_Graph/Graph_project_self/res/pics/1.jpg");
    int iHeight = img1.size().height;
    int iWidth = img1.size().width;
    
    int iFontSize = 12;
    const int l = 5;

    char cChars[l] = ".o@#";
    std::string sChars[] = { ".", "#"};
    std::cout << sChars[0] << "\n";
    int iCoeff = 255 / strlen(cChars) - 1;
     
    for (int i = 0; i < iHeight; i++) 
    {
        for (int j = 0; j < iWidth; j++)
        {
            if (i % 10 == 0 || j % 10 == 0)
                cv::putText(img1, sChars[0],
                    cv::Point(j, i),
                    cv::FONT_HERSHEY_SIMPLEX,
                    1.0,
                    CV_RGB(160, 160, 160), false);
            //else 
            //    cv::putText(img1, sChars[1],
              //  cv::Point(j, i),
                //cv::FONT_HERSHEY_SIMPLEX,
              //  0.01,
//                CV_RGB(60, 60, 60), false);
        }
    }

    cv::imshow("window_second", img1);
    
    printf("%d\n", iHeight);
    printf("%d\n", iWidth);
    printf(cChars);
    printf("%d\n", iCoeff);
    cv::waitKey(0);


}

int draw()
{
    
    char cArray[1];
    return 0;
}

int convert()
{
    return 0;
}

int draw_converted()
{
    return 0;
}