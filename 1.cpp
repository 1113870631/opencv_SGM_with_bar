#include <iostream>
#include <opencv2/opencv.hpp>
#include </usr/include/opencv2/calib3d/calib3d_c.h>
#include "omp.h"

  /**
     * @brief 
     * sgbm->setPreFilterCap(32);
    int SADWindowSize = 9;
    int sgbmWinSize = SADWindowSize > 0 ? SADWindowSize : 3;
    sgbm->setBlockSize(sgbmWinSize);
    int cn = grayLeft.channels();
    sgbm->setP1(8 * cn*sgbmWinSize*sgbmWinSize);
    sgbm->setP2(32 * cn*sgbmWinSize*sgbmWinSize);
    sgbm->setMinDisparity(0);  最小视差值。
    //sgbm->setNumDisparities(16);  最大视差减最小
    sgbm->setUniquenessRatio(10);uniquenessRatio 最佳（最小）计算成本函数值应该“赢”第二个最佳值以考虑找到的匹配正确的百分比保证金。通常，5-15范围内的值就足够了。
    sgbm->setSpeckleWindowSize(100);平滑视差区域的最大尺寸，以考虑其噪声斑点和无效。将其设置为0可禁用斑点过滤。否则，将其设置在50-200的范围内
    sgbm->setSpeckleRange(32);每个连接组件内的最大视差变化。如果你做斑点过滤，将参数设置为正值，它将被隐式乘以16.通常，1或2就足够好了。
    preFilterCap 预滤波图像像素的截断值
    sgbm->setDisp12MaxDiff(1);左右视差允许最大差异
      sgbm->setMode(cv::StereoSGBM::MODE_SGBM);mode 将其设置为StereoSGBM :: MODE_HH以运行全尺寸双通道动态编程算法。它将消耗O（W * H * numDisparities）字节，这对640x480立体声很大，对于HD尺寸的图片很大。默认情况下，它被设置为false。
     */
using namespace std;
using namespace cv;
int   setNumDisparities=1;//最大视差
int   setblock=1;//窗口大小
int   setUniquenessRatio,setSpeckleWindowSize,setSpeckleRange,setDisp12MaxDiff,p1=8,p2=32;
cv::Ptr<cv::StereoSGBM> sgbm= cv::StereoSGBM::create(0,9, setblock);


  Mat im3;


  
 Mat grayLeft,grayRight,grayLeft_h,grayRight_h;

void other_Callback(int , void* )
{  
              if(setblock%2==0)
            {setblock=setblock+1;}
            sgbm->setBlockSize(setblock);
            sgbm->setNumDisparities(setNumDisparities);
            sgbm->setP1(p1 * 1*setblock*setblock);
            sgbm->setP2(p2 * 1*setblock*setblock);  
            sgbm->setUniquenessRatio(setUniquenessRatio);
            sgbm->setSpeckleWindowSize(setSpeckleWindowSize);
            sgbm->setSpeckleRange(setSpeckleRange);
            sgbm->setDisp12MaxDiff(setDisp12MaxDiff);

            sgbm->compute(grayLeft_h, grayRight_h, im3);
            im3.convertTo(im3, CV_16S); 
            im3.convertTo(im3,CV_8UC1,255 / (setNumDisparities*16.0));//归一化  十分重要
            imshow("win",im3);
  }

int main()
{
  //l
  Mat im0 = cv::imread("../0.jpg_l.jpg");
  //r
  Mat im1 = cv::imread("../0.jpg_r.jpg");

   cvtColor(im1,grayLeft,COLOR_BGR2GRAY);
   cvtColor(im0,grayRight,COLOR_BGR2GRAY);
   grayLeft_h=grayLeft;
    grayRight_h=grayRight;
    setUniquenessRatio=10;
    setSpeckleWindowSize=100;
    setSpeckleRange=32;
    setDisp12MaxDiff=1;
    p1=8;
    p2=32;

    imshow("im0",im0);


namedWindow("win",WINDOW_FREERATIO);
    createTrackbar("setNumDisparities","win",&setNumDisparities,512,other_Callback);
    createTrackbar("setblock","win",&setblock,21,other_Callback);
    createTrackbar("setUniquenessRatio","win",&setUniquenessRatio,500,other_Callback);
    createTrackbar("setSpeckleWindowSize","win",&setSpeckleWindowSize,500,other_Callback);
    createTrackbar("setSpeckleRange","win",&setSpeckleRange,200,other_Callback);    
    createTrackbar("setDisp12MaxDiff","win",&setDisp12MaxDiff,100,other_Callback);   
    createTrackbar("p1","win",&p1,21,other_Callback);   
    createTrackbar("p1","win",&p1,21,other_Callback);      

    waitKey(0);

  return 0;
}
