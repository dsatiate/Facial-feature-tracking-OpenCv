#include <cv.h>
#include <highgui.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <vector>

using namespace std;
int detect_faces(IplImage* img);
int detect_eyes(IplImage* img);
CvHaarClassifierCascade* cascade = 0;
CvMemStorage* storage = 0;

IplImage* rotateimg(IplImage* src,int angle)
{
	IplImage* dst = cvCloneImage( src );
	double factor=1;
	float m[6];
    CvMat M = cvMat(2, 3, CV_32F, m);
    int w = src->width;
    int h = src->height;
		m[0] = (float)(factor*cos(-angle*2*CV_PI/180.));
        m[1] = (float)(factor*sin(-angle*2*CV_PI/180.));
        m[3] = -m[1];
        m[4] = m[0];
        m[2] = w*0.5f;  
        m[5] = h*0.5f;  
        
        cvGetQuadrangleSubPix( src, dst, &M);
		return dst;

}
int main( int argc, char** argv ) 
{
  IplImage* img = cvLoadImage("152.jpg", 1);
  
    cvNamedWindow("src", 1);
    cvShowImage("src", img);

    IplImage* dst=rotateimg(img,15);
        cvNamedWindow("dst", 1);
        cvShowImage("dst", dst);
        
  detect_faces(dst);
  detect_eyes(dst);

dst=rotateimg(dst,-15);

  // ...show image...
  cvNamedWindow( "Example1", 1 );
  cvShowImage( "Example1", dst );
  cvWaitKey(0);
  cvReleaseImage( &img );
  cvDestroyWindow( "Example1" );
return 0;
}

int detect_faces(IplImage* img)
{
   IplImage* gray;
   CvHaarClassifierCascade* cascade1 = 0;
   CvMemStorage* storage1 = 0;

  /* Load the face detector and create memory storage
    `cascade` and `storage` are global variables */
  if (!cascade) {
    char* file1 = "C:/OpenCV-2.1.0/data/haarcascades/haarcascade_frontalface_default.xml";
    cascade1 = (CvHaarClassifierCascade*) cvLoad(file1, 0, 0, 0);
    storage1 = cvCreateMemStorage(0);
  }

  /* Convert multichannel to 1-channel for faster processing */
  if (img->nChannels == 1) {
	  gray =(IplImage *)cvClone(img);
	  //gray =img;
  } else {
    gray = cvCreateImage(cvGetSize(img), img->depth, 1);
    cvCvtColor(img, gray, CV_RGB2GRAY);
  }

  /* detect faces */
  CvSeq* faces = cvHaarDetectObjects(
    gray,
    cascade1,
    storage1,
    1.1,
    3,
    CV_HAAR_DO_CANNY_PRUNING,
    cvSize(20, 20)
  );

  int i;

  /* Draw red boxes on the faces found */
  for( i = 0; i < (faces ? faces->total : 0); i++ ) {
    CvRect* r = (CvRect*)cvGetSeqElem(faces, i);

    cvRectangle(
      img,
      cvPoint(r->x, r->y),
      cvPoint(r->x + r->width, r->y + r->height),
      CV_RGB(255, 0, 0),
      1, 8, 0
    );
  }

return faces->total;
 /* for (i = 0; i < faces->total; i++) {
    CvRect* r = (CvRect*)cvGetSeqElem(faces, i);
    cvSetImageROI(img, *r);
    detect_eyes(img);
    cvResetImageROI(img);
  }*/
}

int detect_eyes(IplImage* img)
{
  /* Load the face detector and create empty memory storage */
  if (!cascade) {
    char* file = "C:/OpenCV-2.1.0/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
	//char* file = "C:/OpenCV-2.1.0/data/haarcascades/mouth.xml";
	//char* file = "C:/Users/admin/Downloads/Compressed/FaceFeaturesDetectors_2/FaceFeaturesDetectors/Nosenew18x15/Nariz_nuevo_20stages.xml";
    cascade = (CvHaarClassifierCascade*) cvLoad(file, 0, 0, 0);
    storage = cvCreateMemStorage(0);
  }

  /* Detect objects */
  CvSeq* eyes = cvHaarDetectObjects(
    img,
    cascade,
    storage,
    1.1,
    3,
    CV_HAAR_DO_CANNY_PRUNING,
    cvSize(10, 10)
  );

  int i;

  /* Draw green boxes around the eyes found */
  for( i = 0; i < (eyes ? eyes->total : 0); i++ ) {
    CvRect* r1 = (CvRect*)cvGetSeqElem(eyes, i);
    cvRectangle(
      img,
      cvPoint(r1->x, r1->y),
      cvPoint(r1->x + r1->width, r1->y + r1->height),
      CV_RGB(0, 255, 0),
      2, 8, 0
    );
  }

  return eyes->total;
}
