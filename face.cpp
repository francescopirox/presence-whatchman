#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cstdio>

using namespace cv;

// Macro declaration
#define FFACE "haarcascade_frontalface_alt.xml"

/** Global variables */
std::vector<Rect> faces(10);
CascadeClassifier face_cascade;

void detectAndDisplay( Mat frame ){
  //-- Rect faces;
  Mat frame_gray;
  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );
  //-- Detect faces
  face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
  Uint8 faces_number =faces.size();
  printf("%d", faces_number);
}

int main(int argc, const char** argv){

  bool continuos;

  if(argv[1] == "-c" || argv[1] == "--continue"){
    continuos = true;
  }else{
    continuos = false;
  }

  CvCapture* capture;
  Mat frame;
  //-- 1. Load the cascades
  if(!face_cascade.load(FFACE)){
    puts("--(!)Error loading\n");
    return -1;
  }
  //-- 2. Read the video stream
  capture = cvCaptureFromCAM( -1 );
  if(capture){
    do{
      frame = cvQueryFrame( capture );
      //-- 3. Apply the classifier to the frame
      if(!frame.empty()){
        detectAndDisplay(frame);
      }else{
         puts(" --(!) No captured frame -- Break!");
         break;
      }
    }while(continuos);
  }
  return 0;
}
