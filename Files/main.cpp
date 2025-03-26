// //
// //  main.cpp
// //  PPMProject

#include <iostream>
#include <fstream>
#include "Graphics.h"

using namespace std;


int main() {
    
    ifstream infile("/Users/tomonkiangel/Desktop/Shahriar.ppm");
    if (!infile) {
        cerr << "Error: Failed to open input file." << endl;
        return 1;
    }

    PPM img(infile);
    infile.close();
    
    // Check if the image was loaded correctly
    cout << "Image Loaded - Width: " << img.GetWidth() << ", Height: " << img.GetHeight() << endl;

    // Create separate copies for each transformation
    PPM rotatedImg (img);      // Copy constructor
    PPM grayscaleImg (img);    // Copy constructor
    PPM scaledImg (img);       // Copy constructor
    PPM translatedImg (img);   // Copy constructor
    PPM blurredImg(img); // Copy constructor
    

    // Test rotation (180 degrees)
    rotatedImg = Graphics::RotateImage(rotatedImg, 1.5);
    rotatedImg.saveImageToFile("/Users/tomonkiangel/Desktop/RotatedShahriar.ppm");

    // Test grayscale
    grayscaleImg = Graphics::MakeGrayScale(grayscaleImg);
    grayscaleImg.saveImageToFile("/Users/tomonkiangel/Desktop/GrayShahriar.ppm");
    

    // Test scaling
    scaledImg = Graphics::ScaleImage(scaledImg, 0.5);
    scaledImg.saveImageToFile("/Users/tomonkiangel/Desktop/ScaledShahriar.ppm");

    // Test translation
    translatedImg = Graphics::TranslateImage(translatedImg, 50, 50);
    translatedImg.saveImageToFile("/Users/tomonkiangel/Desktop/TranslatedShahriar.ppm");
    
    //Test blurring
    blurredImg = Graphics::BlurImage(blurredImg, 2);
    blurredImg.saveImageToFile("/Users/tomonkiangel/Desktop/BlurredShahriar.ppm");

    return 0;
    
     
}
