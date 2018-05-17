#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <math.h>
 
int FALSE =0;

int main()
{
    int x=50;
    int y=50;
    int i,j,nIdx;
    IplImage* image = 0;
    IplImage* img1 = cvLoadImage("/home/yeongjin/study_cv/right5.png");
    IplImage* img2 = cvLoadImage("/home/yeongjin/study_cv/left5.png");
    
    IplImage *limage = cvCreateImage(\
    cvSize(img1->width, img1->height),img1->depth,1);
    cvCvtColor(img1, limage,CV_RGB2GRAY);

    IplImage *rimage = cvCreateImage(\
    cvSize(img2->width, img2->height),img2->depth,1);
    cvCvtColor(img2, rimage,CV_RGB2GRAY);

    IplImage *m_disparity_img = cvCreateImage(\
    cvSize(img1->width,img1->height),IPL_DEPTH_8U,1);
  
    CvMat *disparity = cvCreateMat(img1->height,img1->width,CV_16SC1);

 
    cvNamedWindow( "limage", 0 );
    cvResizeWindow( "limage", 320, 240 );

    cvNamedWindow( "rimage", 0 );
    cvResizeWindow( "rimage", 320, 240 );

    cvNamedWindow("depthmap", 0);
    cvResizeWindow("depthmap", 320, 240);
 
    CvStereoBMState *BMState = cvCreateStereoBMState();
    BMState->preFilterSize=21; 
    BMState->preFilterCap=31;
    BMState->SADWindowSize=21;
    BMState->minDisparity=0;
    BMState->numberOfDisparities=64;
    BMState->textureThreshold=10;
    BMState->uniquenessRatio=15;
    cvFindStereoCorrespondenceBM(limage,rimage,disparity,BMState);
    cvNormalize(disparity,m_disparity_img,0,255,CV_MINMAX);
   // printf("%f",m_disparity_img);
   
   /* for(i=0;i<m_disparity_img->width;i++){
      for(j=0;j<m_disparity_img->height;j++){
	     nIdx = i+j*m_disparity_img->widthStep;
         unsigned char value=m_disparity_img->imageData[nIdx];
         printf("%d\n",value);
      }
   }*/
   nIdx = 521+768*m_disparity_img->widthStep;
         unsigned char value=m_disparity_img->imageData[nIdx];
         printf("\n%d\n",value);

    while(1) { 
        
        cvShowImage( "limage", limage ); 
        cvShowImage( "rimage", rimage );
        cvShowImage("depthmap", m_disparity_img); 
        
        if( cvWaitKey(10) >= 0 )
            break;
    }

    cvDestroyWindow( "camera" );

	return 0;
}
