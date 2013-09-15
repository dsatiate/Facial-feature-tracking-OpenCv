#include <cv.h>
#include <highgui.h>
#include <math.h>


IplImage* crop(IplImage* src, CvPoint c, int r){
	IplImage* res, * roi;
 
    //src = cvLoadImage("x.jpg", 1);
    res = cvCreateImage(cvGetSize(src), 8, 3);
    roi = cvCreateImage(cvGetSize(src), 8, 1);
 
    /* prepare the 'ROI' image */
    cvZero(roi);
 
    /* Note that you can use any shape for the ROI */
    cvCircle(
        roi,
        c,
        r,
        CV_RGB(255, 255, 255),
        -1, 8, 0
    );
 
    /* extract subimage */
    cvAnd(src, src, res, roi);
 
 
    /* 'restore' subimage */
    IplImage* roi_C3 = cvCreateImage(cvGetSize(src), 8, 3);
    cvMerge(roi, roi, roi, NULL, roi_C3);
    cvAnd(res, roi_C3, res, NULL);
 
    return res;
 
   
}

int main(int argc, char** argv) {
	
  IplImage* image = cvLoadImage( 
    "4.jpg"
  );
 //IplImage* src = cvLoadImage("index.jpg");
  IplImage* croped=cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
 IplImage* src = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
 IplImage* canny=cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
 IplImage* rgbcanny=cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,3);
 CvMemStorage* storage = cvCreateMemStorage(0);
 cvCvtColor( image, src, CV_BGR2GRAY );
 cvSmooth(src, src, CV_GAUSSIAN, 5, 5 );

 
 //cvCanny(src,canny,50,200,3);
 
 
 CvSeq* results = cvHoughCircles( 
    src, 
    storage, 
    CV_HOUGH_GRADIENT, 
    2, 
    src->height/4,
	200,
	100
	//src->height/20,
	//src->height/2
  ); 
cvCvtColor(canny,rgbcanny,CV_GRAY2BGR);
printf("%d",results->total);
 for( int i = 0; i < results->total; i++ ) 
 {
    float* p = (float*) cvGetSeqElem( results, i );
    CvPoint pt = cvPoint( cvRound( p[0] ), cvRound( p[1] ) );
	croped=crop(image,pt,cvRound(p[2]));
    cvCircle( 
      image,
      pt, 
      cvRound( p[2] ),
      CV_RGB(255,0,0) 
    );
	
  }
  cvNamedWindow( "HoughCircles", 1 );
  cvShowImage( "HoughCircles", image);
  if(croped){
	cvNamedWindow("crop",1);
	cvShowImage("crop",croped);}
  cvWaitKey(0);
}