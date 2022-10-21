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
        imgCont;

    VideoCapture
        cap("annexe/voitour_dour.mp4");

    if (img.empty()) return -1;
    if (!cap.isOpened()) return -1;

    
   //imgBina = traitImg.binarisation(img,190);
   //imgEros = traitImg.erosion(imgBina);
   //for(int k = 1; k < 2; k++)
   //    imgEros = traitImg.erosion(imgEros);
   //
   //imgDila = traitImg.dilatation(imgEros);
   //for (int k = 1; k < 5; k++)
   //    imgDila = traitImg.dilatation(imgDila);
   //
    
    //imshow("Image Origine", img);
    //imshow("Image Erode", imgEros);
    //imshow("Image Binarise", imgBina);
    //imshow("Image Dilatation", imgDila);
    //imshow("Image Contour", imgCont);

      // Check if camera opened successfully
    if (!cap.isOpened()) {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    do{

        // Capture frame-by-frame
        cap >> img;
        imshow("Films de base", img);

        // Display the resulting frame
        imshow("Films binaire", traitImg.binarisation(img,150));

    } while (waitKey(1)!='q');

    // When everything done, release the video capture object
    cap.release();

    // Closes all the frames
    destroyAllWindows();

    //std::cout << "-------------------> Nombre de balles dans l'image: " << traitImg.cptPixBlanc(imgDila) / 4500 << std::endl;
    waitKey(0);


    return 0;
}
