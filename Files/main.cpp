// //
// //  main.cpp
// //  PPMProject
// //
// //  Created by Tom On Ki Angel on 8/3/2025.
// //

// #include <iostream>
// #include "Graphics.h"
// int main(int argc, const char * argv[]) {
//     // insert code here...
//     std::cout << "Hello, World!\n";
//     ifstream infile("Shahriar.ppm");
//     PPM img=PPM(infile);
//     PPM rotatedImage=Graphics::RotateImage(img,3.14);
//     rotatedImage.saveImageToFile("RotatedShahriar.ppm");
//     ~rotatedImage;
//     return 0;
// }
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

    // Test rotation (180 degrees)
    const PPM& rotated = Graphics::RotateImage(img, 3.14159); 
    rotated.saveImageToFile("RotatedShahriar.ppm");
    delete &rotated; // Cleanup

    // Test grayscale
    const PPM& grayscale = Graphics::MakeGrayScale(img);
    grayscale.saveImageToFile("GrayShahriar.ppm");

    // Test scaling
    const PPM& scaled = Graphics::ScaleImage(img, 0.5);
    scaled.saveImageToFile("ScaledShahriar.ppm");
    delete &scaled;

    // Test translation
    const PPM& translated = Graphics::TranslateImage(img, 50, 50);
    translated.saveImageToFile("TranslatedShahriar.ppm");

    return 0;
}