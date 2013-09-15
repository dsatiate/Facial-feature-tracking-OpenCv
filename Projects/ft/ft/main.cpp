
#include <stdio.h>
//#include<conio.h>
#include "cv.h"
#include "highgui.h"
#include "cvaux.h"
#include <cstdio>
#include <math.h>


using namespace std;
using namespace cv;

CvHaarClassifierCascade *cascade,*cascade_e,*cascade_nose,*cascade_mouth;
CvMemStorage *storage;
char *face_cascade="C:\\OpenCV-2.1.0\\data\\haarcascades\\haarcascade_frontalface_default.xml";
char *eye_cascade="C:\\OpenCV-2.1.0\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml";
char *nose_cascade="C:\\OpenCV-2.1.0\\data\\haarcascades\\haarcascade_mcs_nose.xml";
char *mouth_cascade="C:\\OpenCV-2.1.0\\data\\haarcascades\\haarcascade_mcs_mouth.xml";

IplImage *image = 0, *grey = 0, *prev_grey = 0, *pyramid = 0, *prev_pyramid = 0, *swap_temp;

int win_size = 10;
const int MAX_COUNT = 500;
CvPoint2D32f* points[2] = {0,0}, *swap_points;
char* status = 0;
int count1 = 0;
int need_to_init = 0;
int night_mode = 0;
int flags = 0;
int add_remove_pt = 0;
CvPoint pt;
int i,k;

void on_mouse( int event, int x, int y, int flags, void* param )
{
    if( !image )
        return;

    if( image->origin )
        y = image->height - y;

    if( event == CV_EVENT_LBUTTONDOWN )
    {
        pt = cvPoint(x,y);
        add_remove_pt = 1;
    }
}

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

/*Mouth detect ion*/
void detectMouth( IplImage *img,CvRect *r)
{
   CvSeq *mouth;
   //mouth detecetion - set ROI
   cvSetImageROI(img,/* the source image */
                 cvRect(r->x,            /* x = start from leftmost */
                        r->y+(r->height *2/3), /* y = a few pixels from the top */
                        r->width,        /* width = same width with the face */
                        r->height/3    /* height = 1/3 of face height */
                       )
                );
    mouth = cvHaarDetectObjects(img,/* the source image, with the estimated location defined */
                                cascade_mouth,      /* the eye classifier */
                                storage,        /* memory buffer */
                                1.15, 4, 0,     /* tune for your app */
                                cvSize(25, 15)  /* minimum detection scale */
                               );
	cvNamedWindow( "Mouth", 1 );

        for( int i = 0; i < (mouth ? mouth->total : 0); i++ )
        {
     
          CvRect *mouth_cord = (CvRect*)cvGetSeqElem(mouth, i);

		  //if(((mouth_cord->x+mouth_cord->width/2) <= (r->x + r->width+mouth_cord->width/15))&&((mouth_cord->x+mouth_cord->width/2) <= (r->x + r->width-mouth_cord->width/10)))
		  {
		  /* draw a red rectangle */
          cvRectangle(img,
                      cvPoint(mouth_cord->x, mouth_cord->y),
                      cvPoint(mouth_cord->x + mouth_cord->width, mouth_cord->y + mouth_cord->height),
                      CV_RGB(255,255, 255),
                      1, 8, 0
                    );
		  }
		  cvShowImage( "Mouth", img );
        }
     //end mouth detection
         
}

/*Nose detection*/
void detectNose( IplImage *img,CvRect *r)
{
  CvSeq *nose;
 
  //nose detection- set ROI
  cvSetImageROI(img,                    /* the source image */
                cvRect(r->x,            /* x = start from leftmost */
                       r->y+(r->height *1/2) , /* y = a few pixels from the top */
                       r->width,        /* width = same width with the face */
                       r->height/2  /* height = 1/3 of face height */
                      )
               );
         

  nose = cvHaarDetectObjects(img, /* the source image, with the estimated location defined */
                             cascade_nose,      /* the eye classifier */
                             storage,        /* memory buffer */
                             1.15, 3, 0,     /* tune for your app */
                             cvSize(25, 15)  /* minimum detection scale */
                            );

  for( int i = 0; i < (nose ? nose->total : 0); i++ )
      {
          CvRect *nose_cord = (CvRect*)cvGetSeqElem(nose, i);

          /* draw a red rectangle */
          cvRectangle(img,
                      cvPoint(nose_cord->x, nose_cord->y),
                      cvPoint(nose_cord->x + nose_cord->width, nose_cord->y + nose_cord->height),
                      CV_RGB(0,255, 0),
                      1, 8, 0
                    );

      }
}

/*Eyes detection*/
void detectEyes( IplImage *img,CvRect *r)
{	int i;
    char *eyecascade;
    CvSeq *eyes;
    int eye_detect=0;

	CvFont font;
	double hScale=0.5;
	double vScale=0.5;
	int    lineWidth=1;
   

   //eye detection starts
  /* Set the Region of Interest: estimate the eyes' position */
   
    cvSetImageROI(img,                    /* the source image */
          cvRect
          (
              r->x,            /* x = start from leftmost */
              r->y + (r->height/5.5), /* y = a few pixels from the top */
              r->width,        /* width = same width with the face */
              r->height/3.0    /* height = 1/3 of face height */
          )
      );

      /* detect the eyes */
      eyes = cvHaarDetectObjects( img,            /* the source image, with the estimated location defined */
                                  cascade_e,      /* the eye classifier */
                                  storage,        /* memory buffer */
                                  1.15, 3, 0,     /* tune for your app */
                                  cvSize(25, 15)  /* minimum detection scale */
                                );
   
      printf("\no of eyes detected are %d",eyes->total);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	  if(eyes->total==0)
		{
			cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);
			cvPutText (img,"Eye-closed",cvPoint(10,10), &font, cvScalar(255,0,0));
		}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
     cvNamedWindow( "Eye1", 1 );
	 //cvNamedWindow( "Eye2", 1 );
        /* draw a rectangle for each detected eye */
        for(  i = 0; i < (eyes ? eyes->total : 0); i++ )
          {
              eye_detect++;
              /* get one eye */
              CvRect *eye = (CvRect*)cvGetSeqElem(eyes, i);
              /* draw a blue rectangle */
			  int x,y,width,height;
			  x=eye->x;
			  y=eye->y;
			  width=eye->width;
			  height=eye->height;

                        cvRectangle(img,
                                    cvPoint(eye->x, eye->y),
                                    cvPoint(eye->x + eye->width, eye->y + eye->height),
                                    CV_RGB(0, 0, 255),
                                    1, 8, 0
                                   );
			 //cvResetImageROI(img);
			//cvSetImageROI(img,cvRect(x,y,width,height));
		//if(i==0)
				cvShowImage( "Eye1", img );
			//else
			//	cvShowImage("Eye2",img);

           }
		cvResetImageROI(img);
		
		
		

           
}
int detectFacialFeatures( IplImage *img,IplImage *temp_img,int img_no)
{
   
    char image[100],msg[100],temp_image[100];
    float m[6];
    double factor = 1;
    CvMat M = cvMat( 2, 3, CV_32F, m );
    int w = (img)->width;
    int h = (img)->height;
    CvSeq* faces;
    CvRect *r;

    m[0] = (float)(factor*cos(0.0));
    m[1] = (float)(factor*sin(0.0));
    m[2] = w*0.5f;
    m[3] = -m[1];
    m[4] = m[0];
    m[5] = h*0.5f;
   
    cvGetQuadrangleSubPix(img, temp_img, &M);
    CvMemStorage* storage=cvCreateMemStorage(0);
    cvClearMemStorage( storage );
   
    if( cascade )
        faces = cvHaarDetectObjects(img,cascade, storage, 1.2, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize(20, 20));
    else
        printf("\nFrontal face cascade not loaded\n");

    printf("\n no of faces detected are %d",faces->total);
   
	if(faces->total>0)
    {
    /* for each face found, draw a red box */
    for(int i = 0 ; i < ( faces ? faces->total : 0 ) ; i++ )
    {       
        r = ( CvRect* )cvGetSeqElem( faces, i );
        cvRectangle( img,cvPoint( r->x, r->y ),cvPoint( r->x + r->width, r->y + r->height ),
                     CV_RGB( 255, 0, 0 ), 1, 8, 0 );   
   
        printf("\n face_x=%d face_y=%d wd=%d ht=%d",r->x,r->y,r->width,r->height);
       
        detectEyes(img,r);
        /* reset region of interest */
        cvResetImageROI(img);
        detectNose(img,r);
        cvResetImageROI(img);
        detectMouth(img,r);
        cvResetImageROI(img);
    }
    /* reset region of interest */
      cvResetImageROI(img);

      
            sprintf(image,"C:\\Users\\admin\\Documents\\Visual Studio 2008\\Projects\\ft\\out_img\\%d.jpg",img_no);
            //cvSaveImage( image, img );
			return faces->total;
        }
	  else 
		  return 0;
}

int main( int argc, char** argv )
{
	Mat frame, frameCopy;
    CvCapture *capture;
    IplImage  *img,*temp_img;
    int       key;
	int angle=0;
    char image1[100],temp_image[100];
	IplImage* t_img;
   
	

    /* load the classifier
       note that I put the file in the same directory with
       this code */
    storage = cvCreateMemStorage( 0 );
    cascade = ( CvHaarClassifierCascade* )cvLoad( face_cascade, 0, 0, 0 );
    cascade_e = ( CvHaarClassifierCascade* )cvLoad( eye_cascade, 0, 0, 0 );
    cascade_nose = ( CvHaarClassifierCascade* )cvLoad( nose_cascade, 0, 0, 0 );
    cascade_mouth = ( CvHaarClassifierCascade* )cvLoad( mouth_cascade, 0, 0, 0 );


   
    if( !(cascade || cascade_e ||cascade_nose||cascade_mouth) )
        {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        return -1;
        }
   /*
    for(int j=1;j<=8;j++)
    {

        sprintf(image,"C:\\Users\\admin\\Documents\\Visual Studio 2008\\Projects\\test_img\\%d.jpg",j);
       
        img=cvLoadImage(image);
        temp_img=cvLoadImage(image);
       
        if(!img)
        {
        printf("Could not load image file and trying once again: %s\n",image);
        }
        printf("\n curr_image = %s",image);
     
        detectFacialFeatures(img,temp_img,j);
		
  cvNamedWindow( "Example1", 1 );
  cvShowImage( "Example1", img );
  cvWaitKey(10);
  //cvReleaseImage( &img );
  //cvDestroyWindow( "Example1" );

    }*/
	//capture=cvCreateFileCapture("C:\\Users\\admin\\Downloads\\Video\\test.flv");
	capture = cvCreateCameraCapture(0);
	if( capture )
    {   int j=0;
        for(;;)
        {
            IplImage* iplImg = cvQueryFrame( capture );
            /*frame = iplImg;
            if( frame.empty() )
                break;
            if( iplImg->origin == IPL_ORIGIN_TL )
                frame.copyTo( frameCopy );
            else
                flip( frame, frameCopy, 0 );
			*/

			image = cvCreateImage( cvGetSize(iplImg), 8, 3 );
            image->origin = iplImg->origin;
            grey = cvCreateImage( cvGetSize(iplImg), 8, 1 );
            prev_grey = cvCreateImage( cvGetSize(iplImg), 8, 1 );
            pyramid = cvCreateImage( cvGetSize(iplImg), 8, 1 );
            prev_pyramid = cvCreateImage( cvGetSize(iplImg), 8, 1 );
            points[0] = (CvPoint2D32f*)cvAlloc(MAX_COUNT*sizeof(points[0][0]));
            points[1] = (CvPoint2D32f*)cvAlloc(MAX_COUNT*sizeof(points[0][0]));
            status = (char*)cvAlloc(MAX_COUNT);
            flags = 0;

			img=iplImg;
			temp_img=iplImg;
			cvNamedWindow( "Example1", 1 );
			cvNamedWindow( "xyz", 0 );
    cvSetMouseCallback( "xyz", on_mouse, 0 );

cvCopy( iplImg, image, 0 );
        cvCvtColor( image, grey, CV_BGR2GRAY );

			for(angle=0;angle<=0;angle+=30)
			{
				t_img=rotateimg(img,angle);
				if(detectFacialFeatures(t_img,temp_img,j))
				{	t_img=rotateimg(t_img,-angle);
					break;
				}
				t_img=rotateimg(t_img,-angle);
				
			}

if( count1 > 0 )
        {
            cvCalcOpticalFlowPyrLK( prev_grey, grey, prev_pyramid, pyramid,
                points[0], points[1], count1, cvSize(win_size,win_size), 3, status, 0,
                cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03), flags );
            flags |= CV_LKFLOW_PYR_A_READY;
            for(  i = k = 0; i < count1; i++ )
            {
                if( add_remove_pt )
                {
                    double dx = pt.x - points[1][i].x;
                    double dy = pt.y - points[1][i].y;

                    if( dx*dx + dy*dy <= 25 )
                    {
                        add_remove_pt = 0;
                        continue;
                    }
                }

                if( !status[i] )
                    continue;

                points[1][k++] = points[1][i];
                cvCircle( image, cvPointFrom32f(points[1][i]), 3, CV_RGB(0,255,0), -1, 8,0);
            }
            count1 = k;
        }

 if( add_remove_pt && count1 < MAX_COUNT )
        {
            points[1][count1++] = cvPointTo32f(pt);
            cvFindCornerSubPix( grey, points[1] + count1 - 1, 1,
                cvSize(win_size,win_size), cvSize(-1,-1),
                cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03));
            add_remove_pt = 0;
        }





CV_SWAP( prev_grey, grey, swap_temp );
        CV_SWAP( prev_pyramid, pyramid, swap_temp );
        CV_SWAP( points[0], points[1], swap_points );
        need_to_init = 0;
        cvShowImage( "xyz", image );



			cvShowImage( "Example1", t_img );
			//img=rotateimg(t_img,-angle);
			j++;		
			
			
            //detectAndDraw( frameCopy, cascade, nestedCascade, scale );

            if( cvWaitKey( 33 ) >= 0 )
               break;
        }

        //cvWaitKey(0);

        cvReleaseCapture( &capture );
    }
	else {
		return -1;
	}


    cvReleaseHaarClassifierCascade( &cascade );
    cvReleaseHaarClassifierCascade( &cascade_e );
   
    cvReleaseHaarClassifierCascade( &cascade_nose );
    cvReleaseHaarClassifierCascade( &cascade_mouth );
    cvReleaseMemStorage( &storage );
   
     cvReleaseImage(&img);
     cvReleaseImage(&temp_img);
   

    return 0;
}