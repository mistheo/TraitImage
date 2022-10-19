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
        imgPath = "annexe/Image6Balles.png";
    
    Mat
        img = imread(imgPath),
        imgBina,
        imgEros,
        imgDila;

    if (img.empty()) return -1;

    imgBina = traitImg.binarisation(img,190);

    imgEros = traitImg.erosion(imgBina);
    for(int k = 1; k < 2; k++)
        imgEros = traitImg.erosion(imgEros);

    imgDila = traitImg.dilatation(imgEros);
    for (int k = 1; k < 5; k++)
        imgDila = traitImg.dilatation(imgDila);

    
    imshow("Image Origine", img);
    //imshow("Image Binarise", imgBina);
    //imshow("Image Erode", imgEros);
    //imshow("Image Dilatation", imgDila);


    std::cout << "-------------------> Nombre de balle.s dans l'image: " << traitImg.cptPixBlanc(imgDila) / 4000 << std::endl;
    waitKey(0);


    return 0;
}
