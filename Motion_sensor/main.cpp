#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;
using namespace cv;

int main(int argc,char*const argv[]){
	VideoCapture myWebcam(0);//create the device myWebcam
	myWebcam.read(pres);//take a picture from the device myWebcam
	Mat prev=pres;//at initialization picture n-1=picture n
	Mat next=pres;//at initialization picture n+1=picture n
	cvtColor(prev,prev, CV_RGB2GRAY);
	cvtColor(next,next, CV_RGB2GRAY);
	cvtColor(pres,pres, CV_RGB2GRAY);//to compare pictures we need them to be in b&w
	Mat I1,I2,result;
	int wind=200;
	int x,y;
	bool mouvement;
for(;;)
{
	mouvement=false;
	absdiff(next,pres,I1);
	absdiff(pres,prev,I2);//make the absolute difference between pictures
	bitwise_xor(I1,I2,result);//compare the two differences
//we use two picture to eliminate recurrent movement
	y=result.rows/2;
	x=result.cols/2;
//determine if there is any movement
	threshold(result,result,140,255,CV_THRESH_BINARY);//binarise the picture
	for (int i=x-wind;i<x+wind;i++)
	{
		for (int j=y-wind;j<y+wind;j++)
		{
			if (result.at<int>(j,i)>0)//if there is a pixel different from black (ie diff between image is>0)
			{
			mouvement=true;
			cout<<"true";
			break;
			}
		}
	}
	prev=pres;
	pres=next;
	myWebcam.read(next);//next picture please
	cvtColor(next,next,CV_RGB2GRAY);//make the picture b&w
	}
return 0;
}