// By MIstral Théo
// Le 19/10/2022
// 
// TP_TraitImage.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "CTraitementImage.h"


int main()
{
    CTraitementImage 
        traitImg;

    std::string
        imgPath = "annexe/Image9Balles.png";
    
    Mat
        img = imread(imgPath),
        imgBina,
        imgEros,
        imgDila,
        imgGray,
        imgCont;

    VideoCapture
        video("annexe/voiture5.mp4");

    if (img.empty()) return -1;
    if (!video.isOpened()) return -1;

    //---------------------- Traitement Image avec binarisation ----------------------//
    //imgBina = traitImg.binarisation(img,190);
    //imgEros = traitImg.erosion(imgBina);
    //for(int k = 1; k < 2; k++)
    //    imgEros = traitImg.erosion(imgEros);
    //
    //imgDila = traitImg.dilatation(imgEros);
    //for (int k = 1; k < 5; k++)
    //    imgDila = traitImg.dilatation(imgDila);
    
    
    //imshow("Image Origine", img);
    //imshow("Image Erode", imgEros);
    //imshow("Image Binarise", imgBina);
    //imshow("Image Dilatation", imgDila);
    //std::cout << "--------------> Nombre de balles sur l'image: " << traitImg.cptPixBlanc(imgDila) / 4500 << std::endl;


    //---------------------- Traitement Image avec les contours ----------------------//
    //imgCont = traitImg.contour(img);
    //imshow("Image Contour", imgCont);
   


    //---------------------- Traitement Image avec Pixels moyens ----------------------//
    Mat imgMoy = traitImg.pixelMoyen(video);
    imshow("Image Pixel Moyen", imgMoy);

    waitKey(0);
    return 0;
}
