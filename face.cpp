#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
//#include <iostream>
using namespace std;
using namespace cv;


/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
std::vector<Rect> faces;
String face_cascade_name = "haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;
string window_name = "Capture - Face detection";
//RNG rng(12345);

/** @function main */
int main(int argc, const char** argv )
{
  //cout<<"ciao";
//  printf("1- ");
  CvCapture* capture;
  Mat frame;
int n=0;
  //-- 1. Load the cascades
  if( !face_cascade.load( face_cascade_name ) )
  {
    printf("--(!)Error loading\n"); return -1;
  }

  //-- 2. Read the video stream
  capture = cvCaptureFromCAM( -1 );
  if( capture )
  {
    while( true )
    {
    //  printf("2- ");
  frame = cvQueryFrame( capture );

  //-- 3. Apply the classifier to the frame
      if( !frame.empty() )
      {
        //printf("3- " );
        detectAndDisplay( frame );
      }
      else
      {
         printf(" --(!) No captured frame -- Break!"); break;
      }
     }
  }
  return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
  //printf("4- ");

 //Rect faces;
 Mat frame_gray;

 cvtColor( frame, frame_gray, CV_BGR2GRAY );
 equalizeHist( frame_gray, frame_gray );

 //-- Detect faces
 face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );  // vettore
 int a=faces.size();  //numero faccie
 printf("%d ciao",a );
}
