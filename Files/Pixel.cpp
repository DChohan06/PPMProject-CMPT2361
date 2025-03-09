
#include "Pixel.h"


//Constructors for Pixel class
Pixel::Pixel(){
    red = 0;
    green = 0;
    blue  = 0;
}

Pixel::Pixel(const Pixel& p){
    red = p.red;
    blue = p.blue;
    green = p.green;
}

Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b){
    red = r;
    green = g;
    blue = b;
}

//Contructor for Exeption handling class
Pixel::InputOutOfBoundsException::InputOutOfBoundsException(const char* error, const char* index){
    errorMessage = error;
    offendingIndex = index;
}

//getters for exeption handling
const char* Pixel::InputOutOfBoundsException::returnError() const {
    return errorMessage;
}

const char* Pixel::InputOutOfBoundsException::returnOffendingIndex() const {
    return offendingIndex;
}

//non-const operator[]: allows modification of pixel's values e.g. p["red"] = 200
unsigned int& Pixel::operator[](const char* colour){

    //check which colour is passed then return corresponding value

        if (strcmp(colour,"red") == 0){
            return red;
        }
        else if (strcmp(colour,"green") == 0){
            return green;
        }
        else if (strcmp(colour,"blue") == 0){
            return blue;
        }
        else{
            throw InputOutOfBoundsException("INVALID ARGUEMENT PASSED: ", colour);
        }
}


// Const operator[]: for read-only accessing pixel values e.g. a = p["red"]
const unsigned int& Pixel::operator[](const char* colour) const{
    //check which colour is passed then return corresponding value

        if (strcmp(colour,"red") == 0){
            return red;
        }
        else if (strcmp(colour,"green") == 0){
            return green;
        }
        else if (strcmp(colour,"blue") == 0){
            return blue;
        }
        else{
            throw InputOutOfBoundsException("INVALID ARGUEMENT PASSED: ", colour);
        }

    
}


