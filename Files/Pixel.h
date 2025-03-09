//
//  Pixel.h
//  Pixel
//
//  Created by Dylan Chohan on 2025-03-06.
//

#ifndef Pixel_h
#define Pixel_h

#include <cstring>
#include <iostream>

using namespace std;

//Pixel Class
class Pixel{

//The RGB values for each pixel
private:
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    
public:
    Pixel();
    Pixel(const Pixel& p);
    Pixel(unsigned int r, unsigned int g, unsigned int b);
    ~Pixel(){};
    
    //[] operartor overloads
    const unsigned int& operator[](const char* c) const;
    unsigned int& operator[](const char* c);
    
    class InputOutOfBoundsException{
    private:
        const char* errorMessage;
        const char* offendingIndex;
        
    public:
        InputOutOfBoundsException(const char* error, const char* index);
        const char* returnError() const;
        const char* returnOffendingIndex() const;
        
    };
    
};

#endif /* Pixel_h */
