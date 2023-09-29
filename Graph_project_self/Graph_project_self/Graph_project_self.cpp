#include <iostream>
#include <opencv2\highgui.hpp>

int main()
{
    cv::Mat img = cv::imread("D:/projects/3D_Graph/Graph_project_self/res/pics/1.jpg");
    cv::Mat img1 = cv::imread("D:/projects/3D_Graph/Graph_project_self/res/pics/2.jpg");

    cv::imshow("window", img1);
    cv::imshow("window_second", img1);

    printf("%d\n", img1.size().height);
    printf("%d\n", img1.size().width);
    cv::waitKey(0);
}

int draw()
{
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