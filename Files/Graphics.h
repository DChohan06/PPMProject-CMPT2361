#include <iostream>
#include "PPM.h"
using namespace std;

class Graphics{

	private:

	public:
	static const PPM& MakeGrayScale(PPM&);
	static const PPM& RotateImage(PPM&,double);
	static const PPM& ScaleImage(PPM&, double);
	static const PPM& TranslateImage(PPM&, int, int);
    
    //filters
    static const PPM& BlurImage(PPM& img, unsigned int radius);
    static const PPM& SharpenImage(PPM& img, unsigned int radius);
    static const PPM& EdgeDetectedImage(PPM& img, unsigned int radius);
    static const PPM& EmbossImage(PPM& img, unsigned int radius);
    static const PPM& HighContrastImage(PPM& img, unsigned int radius);
    
    //helper function
    static unsigned int Clamp(int value);

};
