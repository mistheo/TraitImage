#include "CTraitementImage.h"

const uchar BLANC = 255, NOIR = 0;

CTraitementImage::CTraitementImage()
{
}

CTraitementImage::~CTraitementImage()
{
}

Mat CTraitementImage::binarisation(Mat& imgOrig, int seuil)
{
	Mat imgRetour = imgOrig.clone();

	cvtColor(imgOrig, imgRetour, COLOR_RGB2GRAY);

	for (int l = 0; l < imgRetour.rows; l++)
	{
		for (int c = 0; c < imgRetour.cols; c++)
		{
			if ((int)getPixel(imgRetour, l, c) < seuil)
				setPixel(imgRetour, l, c, NOIR);
			else 
				setPixel(imgRetour, l, c, BLANC);
		}
	}

	return imgRetour;

}
Mat CTraitementImage::erosion(Mat& imgOri)
{
	Mat imgRetour = imgOri.clone();
	int cptNbNoir = 0;
	
	
	//mettre les bordures en noirs
	for (int l = 0; l < imgRetour.rows; l++)
	{
		setPixel(imgRetour, l, 0, NOIR);//colonne gauche
		setPixel(imgRetour, imgRetour.rows - 1, 0, NOIR);//colonne droite
	}

	for (int c = 0; c < imgRetour.cols; c++)
	{
		setPixel(imgRetour, 0, c, NOIR);//ligne dessus
		setPixel(imgRetour, 0, imgRetour.cols - 1, NOIR);//ligne dessous
	}

	for (int i = 1; i < imgOri.rows-1; i++)
	{
		for (int j = 1; j < imgOri.cols-1; j++)
		{
			//carre de 3x3
			for (int x = -1; x < 2; x++)
			{
				for (int y = -1; y < 2; y++)
				{
					if (getPixel(imgOri, i+x, j+y) == NOIR) cptNbNoir++;
				}
			}

			if (cptNbNoir > 1) setPixel(imgRetour, i, j, NOIR);
			else setPixel(imgRetour, i, j, BLANC);

			cptNbNoir = 0;
		}
	}
	return imgRetour;
}

Mat CTraitementImage::dilatation(Mat& imgOri)
{
	Mat imgRetour = imgOri.clone();
	int cptNbNoir = 0;

	for (int i = 1; i < imgOri.rows - 1; i++)
	{
		for (int j = 1; j < imgOri.cols - 1; j++)
		{
			//carre de 3x3
			for (int x = -1; x < 2; x++)
			{
				for (int y = -1; y < 2; y++)
				{
					if (getPixel(imgOri, i + x, j + y) == NOIR) cptNbNoir++;
				}
			}

			if (cptNbNoir > 8) setPixel(imgRetour, i, j, NOIR);
			else setPixel(imgRetour, i, j, BLANC);

			cptNbNoir = 0;
		}
	}

	return imgRetour;
}

int CTraitementImage::cptPixBlanc(Mat& imgOri)
{
	int cpt = 0;
	for (int i = 1; i < imgOri.rows - 1; i++)
	{
		for (int j = 1; j < imgOri.cols - 1; j++)
		{
			if (getPixel(imgOri, i, j) == BLANC) cpt++;
		}
	}

	return cpt;
}


void CTraitementImage::setPixel(Mat& imgOrig, int l, int c, int color)
{
	uchar* ptr = imgOrig.ptr();
	*(ptr + (l * imgOrig.cols + c)) = color;
}

uchar CTraitementImage::getPixel(Mat& imgOrig, int l, int c)
{
	return imgOrig.at<uchar>(l, c);
}
