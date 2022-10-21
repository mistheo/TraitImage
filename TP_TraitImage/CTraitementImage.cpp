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

			if (cptNbNoir > 1) 
				setPixel(imgRetour, i, j, NOIR);
			else 
				setPixel(imgRetour, i, j, BLANC);

			cptNbNoir = 0;
		}
	}
	return imgRetour;
}

Mat CTraitementImage::contour(Mat& imgOri)
{
	Mat imgDebase = imgOri.clone();
	cvtColor(imgOri, imgDebase, COLOR_RGB2GRAY);//converti l'image en grisée (1octet qui definit le niveau de gris)
	Mat imgRetour = imgDebase.clone();

	int resPixel = 0;

	for (int i = 1; i < imgRetour.rows - 1; i++)//pour chaque ligne
	{
		for (int j = 1; j < imgRetour.cols - 1; j++)//pour chaque colonne
		{
			//std::cout << "--------------------------------------" << std::endl;
			resPixel += getPixel(imgDebase, i-1, j)*1;//haut
			resPixel += getPixel(imgDebase, i+1, j)*1;//bas
			resPixel += getPixel(imgDebase, i, j)*-4;//pixel actuel
			resPixel += getPixel(imgDebase, i, j-1)*1;//gauche
			resPixel += getPixel(imgDebase, i, j+1)*1;//droite
			// noubeau pixel = case du haut +  case du bas + case de droite + case de guache + case actuel*-4

			if (resPixel > BLANC) resPixel = BLANC;//le pixel ne peut pas etre plus blanc que blanc
			if (resPixel < NOIR) resPixel = NOIR;//le pixel ne peut pas etre plus noir que noir
			
			setPixel(imgRetour, i, j, resPixel); //std::cout << "Pixel mis en place: " << i << ',' << j << " resPixel: " << resPixel << std::endl;
			resPixel = 0;
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
