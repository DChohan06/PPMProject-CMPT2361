// //
// //  main.cpp
// //  PPMProject

#include <iostream>
#include <fstream>
#include "Graphics.h"

using namespace std;


int main() {
    
    ifstream infile("Shahriar.ppm");
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
    
    //filter containers
    PPM blurredImg(img); // Copy constructor
    PPM sharpenedImg(img);
    PPM edgedImg(img);
    PPM embossedImg(img);
    PPM customedImg(img);
    

    // Test rotation (angle in radians)
    rotatedImg = Graphics::RotateImage(rotatedImg, 1.5);
    rotatedImg.saveImageToFile("RotatedShahriar.ppm");

    // Test grayscale
    grayscaleImg = Graphics::MakeGrayScale(grayscaleImg);
    grayscaleImg.saveImageToFile("GrayShahriar.ppm");
    

    // Test scaling
    scaledImg = Graphics::ScaleImage(scaledImg, 0.5);
    scaledImg.saveImageToFile("ScaledShahriar.ppm");

    // Test translation
    translatedImg = Graphics::TranslateImage(translatedImg, 50, 50);
    translatedImg.saveImageToFile("TranslatedShahriar.ppm");
    
    //filters - Blur, Sharpen, Edge Detection, Emboss, and one custom-designed filter
    
    //Test blurring
    blurredImg = Graphics::ApplyFilter(blurredImg, "blur");
    blurredImg.saveImageToFile("BlurredShahriar.ppm");
    
    //Test Sharpen
    sharpenedImg = Graphics::ApplyFilter(sharpenedImg, "sharpen");
    sharpenedImg.saveImageToFile("SharpenedShahriar.ppm");
    
    //Test Edge Detection
    edgedImg = Graphics::ApplyFilter(edgedImg, "edgeDetected");
    edgedImg.saveImageToFile("EdgedShahriar.ppm");
    
    //Test Emboss
    embossedImg = Graphics::ApplyFilter(embossedImg, "emboss");
    embossedImg.saveImageToFile("EmbossedShahriar.ppm");
    
    //Custom
    customedImg = Graphics::ApplyFilter(customedImg, "highContrast");
    customedImg.saveImageToFile("HighContrastShahriar.ppm");

    return 0;
    
     
}
