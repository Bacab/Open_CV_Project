#include <string>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp" 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src,inter,dst;
	string filename=argv[1];
	string buffer=filename;
	string finalfile=buffer.insert(filename.length()-4,"_improve");
	bool success=0;
	VideoCapture capture(filename);
	if (!capture.isOpened()) 
	{
		cout<<("Ouverture du flux vidéo impossible !\n"+filename)<<endl;
		return 1;
	}
	success=capture.read(src);
	VideoWriter Video_rec(finalfile, CV_FOURCC('D','I','V','X'), 25,src.size(), false);
		if (!Video_rec.isOpened()) 
	{
		cout<<("Impossible d'écrire la vidéo !\n"+finalfile)<<endl;
		return 1;
	}
	while(success)
	{
		cvtColor( src, inter, CV_BGR2GRAY );
		equalizeHist( inter, dst );
		Video_rec.write(dst);
		success=capture.read(src);
	}
	Video_rec.release();
	return 0;
}

