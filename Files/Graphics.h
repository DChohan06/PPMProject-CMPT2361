#include <iostream>
#include "PPM.h"
using namespace std;

class Graphics{

	private:

	public:
  static const PPM& ApplyFilter(PPM&, const char*);
	static const PPM& MakeGrayScale(PPM&);
	static const PPM& RotateImage(PPM&,double);
	static const PPM& ScaleImage(PPM&, double);
	static const PPM& TranslateImage(PPM&, int, int);

};
