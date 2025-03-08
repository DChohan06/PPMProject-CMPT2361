//
//  Pixel.h
//  Pixel
//
//  Created by Dylan Chohan on 2025-03-06.
//


using namespace std;

#ifndef Pixel_h
#define Pixel_h

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
        const char* returnError();
        const char* returnOffendingIndex();
        
    };
    
};

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
const char* Pixel::InputOutOfBoundsException::returnError(){
    return errorMessage;
}

const char* Pixel::InputOutOfBoundsException::returnOffendingIndex(){
    return offendingIndex;
}

//returns the corrosponding value of arguement passed
unsigned int& Pixel::operator[](const char* colour){
    unsigned int x = 0;
    //check which colour is passed then return corresponding value
    try{
        
        if(string(colour) == "red"){
            return red;
        }
        else if (string(colour) == "green"){
            return green;
        }
        else if(string(colour) == "blue"){
            return blue;
        }
        else{
            throw colour;
        }
        
    }
    //exception handling
    catch (const char* Err){
        InputOutOfBoundsException error("ERROR! INVALID ARGUEMENT PASSED: ", Err);
        cout << error.returnError() << error.returnOffendingIndex() << endl;
    }
    
    return x;
}


//returns the corrosponding value of arguement passed (immutable)
const unsigned int& Pixel::operator[](const char* colour) const{
    //check which colour is passed then return corresponding value
    try{
        
        if(string(colour) == "red"){
            return red;
        }
        else if (string(colour) == "green"){
            return green;
        }
        else if(string(colour) == "blue"){
            return blue;
        }
        else{
            throw colour;
        }
        
    }
    //exception handling
    catch (const char* Err){
        InputOutOfBoundsException error("ERROR! INVALID ARGUEMENT PASSED: ", Err);
        cout << error.returnError() << error.returnOffendingIndex() << endl;
    }
    
    return 0;
}
#endif /* Pixel_h */
