
//class PPM - On Ki Tom (Angel)

#ifndef PPM_hpp
#define PPM_hpp

#include <vector>
#include <string>
#include <fstream>
#include "Pixel.h"


class PPM{

private:
        
    string magic;
    string comment;
    unsigned int width;
    unsigned int height;
    unsigned int maxColor;
    vector<Pixel> pixels;
    
public:
    
    //constructors and destructor
    PPM();
    PPM(const PPM& other); //copy constructor
    PPM(PPM&& other); //move constructor
    PPM(ifstream& inputFile);
    ~PPM();
    
    //Getters
    string getMagic() const;
    string getComment() const;
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    unsigned int GetMaxColor() const;
    unsigned int GetSize() const;
    
    //Setters
    void SetMagic( const string& newMagic);
    void SetComment( const string& newComment);
    void SetWidth( unsigned int newWidth);
    void SetHeight (unsigned int newHeight);
    void SetMaxColor( unsigned int newMaxColor);
    
    //Operators
    PPM& operator= (const PPM& other);
    PPM& operator= (PPM&& other);
    Pixel& operator[](unsigned int index);
    const Pixel& operator[](unsigned int index) const;
    
    //resize
    void resize(unsigned int newSize);
    
    //save image
    void saveImageToFile( const string& filename) const;
    
};

#endif
