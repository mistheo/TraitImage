#pragma once
// By MIstral Théo
// Le 19/10/2022
// 
// CTraitImage.h : Ce fichier contient les declarations de la class CTraitementImage
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;

class CTraitementImage
{
	public:
		CTraitementImage();
		~CTraitementImage();

		Mat binarisation(Mat& imgOrig,int seuil);
		Mat erosion(Mat&);
		Mat contour(Mat&);
		Mat pixelMoyen(VideoCapture&);
		Mat dilatation(Mat&);
		int cptPixBlanc(Mat&);
		void setPixel(Mat& imgOrig, int l, int c, int color);
		uchar getPixel(Mat& imgOrig, int l, int c);


};

