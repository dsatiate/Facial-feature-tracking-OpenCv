/* Demo of modified Lucas-Kanade optical flow algorithm.
   See the printf below */

#ifdef _CH_
#pragma package <opencv>
#endif

#define CV_NO_BACKWARD_COMPATIBILITY

#ifndef _EiC
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <ctype.h>
#endif

IplImage *image = 0, *grey = 0, *prev_grey = 0, *pyramid = 0, *prev_pyramid = 0, *swap_temp;

int win_size = 10;
const int MAX_COUNT = 500;
CvPoint2D32f* points[2] = {0,0}, *swap_points;
char* status = 0;
int count = 0;
int need_to_init = 0;
int night_mode = 0;
int flags = 0;
int add_remove_pt = 0;
CvPoint pt;
int f_length;
int x_ref,mid_y_ref;
int yl_ref,yu_ref,corr;;
bool doit=false;
char *mouth_cascade="C:\\OpenCV-2.1.0\\data\\haarcascades\\haarcascade_mcs_mouth.xml";
char *face_cascade="C:\\OpenCV-2.1.0\\data\\haarcascades\\haarcascade_frontalface_default.xml";
CvHaarClassifierCascade *cascade_mouth,*cascade;

CvMemStorage *storage;

void on_mouse( int event, int x, int y, int flags, void* param )
{
    if( !image )
        return;

    if( image->origin )
        y = image->height - y;

    if( event == CV_EVENT_LBUTTONDOWN )
    {
        //pt = cvPoint(x,y);
        //add_remove_pt = 1;
		doit=true;
    }
	
}


int main( int argc, char** argv )
{
    CvCapture* capture = 0;
	cascade = ( CvHaarClassifierCascade* )cvLoad( face_cascade, 0, 0, 0 );
	cascade_mouth = ( CvHaarClassifierCascade* )cvLoad( mouth_cascade, 0, 0, 0 );

	int dis;
	int pt_count=0;
	CvMemStorage* storage=cvCreateMemStorage(0);
    cvClearMemStorage( storage );

    if( argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
        capture = cvCaptureFromCAM( argc == 2 ? argv[1][0] - '0' : 0 );
    else if( argc == 2 )
        capture = cvCaptureFromAVI( argv[1] );

    if( !capture )
    {
        fprintf(stderr,"Could not initialize capturing...\n");
        return -1;
    }

    
	cvNamedWindow( "LkDemo", 0 );
    cvSetMouseCallback( "LkDemo", on_mouse, 0 );

    for(;;)
    {
        IplImage* frame = 0;
        int i, k, c;
		CvSeq *mouth;
		CvSeq *faces;
		CvRect *r;

        frame = cvQueryFrame( capture );
        if( !frame )
            break;

        if( !image )
        {
            /* allocate all the buffers */
            image = cvCreateImage( cvGetSize(frame), 8, 3 );
            image->origin = frame->origin;
            grey = cvCreateImage( cvGetSize(frame), 8, 1 );
            prev_grey = cvCreateImage( cvGetSize(frame), 8, 1 );
            pyramid = cvCreateImage( cvGetSize(frame), 8, 1 );
            prev_pyramid = cvCreateImage( cvGetSize(frame), 8, 1 );
            points[0] = (CvPoint2D32f*)cvAlloc(MAX_COUNT*sizeof(points[0][0]));
            points[1] = (CvPoint2D32f*)cvAlloc(MAX_COUNT*sizeof(points[0][0]));
            status = (char*)cvAlloc(MAX_COUNT);
            flags = 0;
        }

        cvCopy( frame, image, 0 );
        cvCvtColor( image, grey, CV_BGR2GRAY );
//------------------------------------------------------

		if(image)
		{

			faces = cvHaarDetectObjects(image,cascade, storage, 1.2, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize(20, 20));
		
			if(faces->total>0)
			{
				/* for each face found, draw a red box */
				for(int i = 0 ; i < 1/*( faces ? faces->total : 0 )*/ ; i++ )
				{       
					r = ( CvRect* )cvGetSeqElem( faces, i );
					cvRectangle( image,cvPoint( r->x, r->y ),cvPoint( r->x + r->width, r->y + r->height ),
								 CV_RGB( 255, 0, 0 ), 1, 8, 0 ); 

					corr=r->height;
					f_length=r->height;
					x_ref=r->x+r->width/2;
					yl_ref=r->y+r->height;
					yu_ref=(int)r->y+r->height/2;
					//printf("yl=%d yu=%d\n",yl_ref,yu_ref);

						cvSetImageROI(image,/* the source image */
							cvRect(r->x,            /* x = start from leftmost */
								r->y+(r->height *2/3), /* y = a few pixels from the top */
								r->width,        /* width = same width with the face */
								r->height/3    /* height = 1/3 of face height */
							   )
						);

						mouth = cvHaarDetectObjects(image,/* the source image, with the estimated location defined */
                                cascade_mouth,      
                                storage,        /* memory buffer */
                                1.15, 4, 0,     /* tune for your app */
                                cvSize(25, 15)  /* minimum detection scale */
                               );
						//cvNamedWindow( "Mouth", 1 );

						if(mouth->total>0)
						{
							for( int i = 0; i < 1/*(mouth ? mouth->total : 0)*/; i++ )
							{
					     
							  CvRect *mouth_cord = (CvRect*)cvGetSeqElem(mouth, i);
							  if(doit)
							  {
							  if(pt_count==0)
							  {
							  pt = cvPoint(r->x+mouth_cord->x+mouth_cord->width/2,r->y+mouth_cord->y+r->height-20-2*mouth_cord->height/3);
							  add_remove_pt = 1;
							  pt_count=1;
							  
							  }
							  else if(pt_count==1)
							  {
							  pt = cvPoint(r->x+mouth_cord->x+mouth_cord->width/2,r->y+mouth_cord->y+r->height-mouth_cord->height-20);
							  add_remove_pt = 1;
							  pt_count++;
							  
							  
							  }
							 /* else if(pt_count==2)
							  {
							  pt = cvPoint(r->x+mouth_cord->x,r->y+mouth_cord->y+r->height-3*mouth_cord->height/4-20);
							  add_remove_pt = 1;
							  pt_count++;
							  
							  
							  }
							  else if(pt_count==3)
							  {
							  pt = cvPoint(r->x+mouth_cord->x+mouth_cord->width,r->y+mouth_cord->y+r->height-3*mouth_cord->height/4-20);
							  add_remove_pt = 1;
							  pt_count++;
							  
							  
							  }*/
							  mid_y_ref=r->y+mouth_cord->y+r->height-3*mouth_cord->height/4-20;
							  
							  }
							 
							  /* draw a red rectangle */
							 cvRectangle(image,
										  cvPoint(mouth_cord->x, mouth_cord->y),
										  cvPoint(mouth_cord->x + mouth_cord->width, mouth_cord->y + mouth_cord->height),
										  CV_RGB(255,255, 255),
										  1, 8, 0
										);
							  

							}
						}

						cvResetImageROI(image);
				
				}
			}
			else
		{
			pt_count=0;
			add_remove_pt=0;
			//doit=false;
		
		}
			
					
			
		}
		

//------------------------------------------------------      


         if( count > 0 )
        {
            cvCalcOpticalFlowPyrLK( prev_grey, grey, prev_pyramid, pyramid,
                points[0], points[1], count, cvSize(win_size,win_size), 3, status, 0,
                cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03), flags );
            flags |= CV_LKFLOW_PYR_A_READY;
            for( i = k = 0; i < count; i++ )
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

			points[1][0].x=x_ref;
			points[1][1].x=x_ref;
			if(points[1][0].y>=yl_ref+10 || points[1][0].y<=mid_y_ref)
				points[1][0].y=mid_y_ref+10;
			if(points[1][1].y>=mid_y_ref || points[1][1].y<=yu_ref)
				points[1][1].y=mid_y_ref-10;
			dis=(points[1][0].y-points[1][1].y)*21/f_length;
			printf("distance=%d cm\n",dis);

            count = k;
        }

        if( add_remove_pt && count < MAX_COUNT )
        {
            points[1][count++] = cvPointTo32f(pt);
            cvFindCornerSubPix( grey, points[1] + count - 1, 1,
                cvSize(win_size,win_size), cvSize(-1,-1),
                cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03));
            add_remove_pt = 0;
        }

        CV_SWAP( prev_grey, grey, swap_temp );
        CV_SWAP( prev_pyramid, pyramid, swap_temp );
        CV_SWAP( points[0], points[1], swap_points );
        need_to_init = 0;
        cvShowImage( "LkDemo", image );

        c = cvWaitKey(10);
        if( (char)c == 27 )
            break;
      
    }

    cvReleaseCapture( &capture );
    cvDestroyWindow("LkDemo");

    return 0;
}

#ifdef _EiC
main(1,"lkdemo.c");
#endif
