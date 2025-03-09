
#include "PPM.h"

//Default constructor - std::vector<Pixel automatically initializes as empty.
PPM::PPM(): magic("P3"), comment(""), width(0), height(0), maxColor(255), pixels(){
}

//Copy constructor - deep copy use std::vector copy constructor
PPM::PPM(const PPM& other): magic(other.magic), comment(other. comment), width(other.width), height(other.height), maxColor(other.maxColor), pixels(other.pixels){}

//Move constructor - calls std::vector move constructor
PPM::PPM(PPM&& other): magic(other.magic), comment(other. comment), width(other.width), height(other.height), maxColor(other.maxColor), pixels(std::move(other.pixels)){
    
    //reset others
    other.magic = "P3";
    other.comment = "";
    other.width = 0;
    other.height = 0;
    other.maxColor = 255;
    other.pixels = vector<Pixel>();
}

//Constructor to read from PPM file
PPM::PPM(ifstream& inputFile){
    
    if (!inputFile){
        cout << "Error, unable to open the input file" << endl; //could throw exception
    }else {
        //read PPM file header
        inputFile >> magic;
        getline(inputFile, comment);
        inputFile >> width >> height;
        inputFile >> maxColor;
        
        //resize the pixel vector
        pixels.resize(width * height);
        
        //Read pixel data
        for (unsigned int i = 0; i < width * height; ++i){
            
            unsigned int r, g, b;
            inputFile >> r >> g >> b;
            pixels[i] = Pixel(r,g,b);
        }
        
    }
}

//Destructor
PPM::~PPM(){}


//Getters
string PPM::getMagic() const{ return magic;};
string PPM::getComment() const{return comment;};
unsigned int PPM::GetWidth() const {return width;};
unsigned int PPM::GetHeight() const {return height;};
unsigned int PPM::GetMaxColor() const {return maxColor;};
unsigned int PPM::GetSize() const {return static_cast<unsigned int>(pixels.size());}; //pixels.size() returns unsigned long

//Setters
void PPM::SetMagic( const string& newMagic){ magic = newMagic;}
void PPM::SetComment( const string& newComment){comment = newComment;}
void PPM::SetWidth( unsigned int newWidth){ width = newWidth;}
void PPM::SetHeight (unsigned int newHeight){ height = newHeight;}
void PPM::SetMaxColor( unsigned int newMaxColor){ maxColor = newMaxColor;}


//Overload copy Assignment operator
PPM& PPM::operator=(const PPM &other){
    
    if (this != &other){
        magic = other.magic;
        comment = other.comment;
        width = other.width;
        height = other.height;
        maxColor = other.maxColor;
        pixels = other.pixels; // calls std vector copy constructor
    }
    
    return *this;
}

//Overload move Assignment operator
PPM& PPM::operator=(PPM&& other){
    
    if (this != &other){
        
        std::swap(magic, other.magic);
        std::swap(comment, other.comment);
        std::swap(width, other.width);
        std::swap(height, other.height);
        std::swap(maxColor, other.maxColor);
        std::swap(pixels, other.pixels);
        
    }
    return *this;
}

//Overload write operator [] for vector pixels
Pixel& PPM::operator[](unsigned int index){
    
    if (index >= pixels.size()){
        cout << "pixel vector index out of range" << endl; //can throw out_of_range exception
        cout << "pixel[0] returned" << endl;
        return pixels[0];
    }
    else{
        return pixels[index];
    }
}

//Overload read-only operator [] for vector pixels
const Pixel& PPM::operator[](unsigned int index) const{
    
    if (index >= pixels.size()){
        cout << "pixel vector index out of range" << endl; //can throw out_of_range exception
        cout << "pixel[0] returned" << endl;
        return pixels[0];
    }
    else{
        return pixels[index];
    }
}

// resize vector pixels
void PPM::resize(unsigned int newSize){
    
    pixels.resize(newSize); //use std::vector resize function
}

//Save Image to File
void PPM::saveImageToFile(const string &filename) const {
    
    //create output ofstream file
    ofstream outfile(filename);
    if (! outfile){
        cout << "Unable to create output PPM file" << endl;
    }
    else{
        
        //Write the PPM file header
        outfile << magic << "\n";
        outfile << comment << "\n";
        outfile << width << " " << height << "\n";
        outfile << maxColor << "\n";
        
        //write all pixels to file
        for (unsigned int i = 0; i < (width * height); i++){
            
            //try to access the pixel values with const operator
            try {
                outfile << pixels[i]["red"] << " " << pixels[i]["green"] << " " << pixels[i]["blue"];
                
            }catch(const Pixel::InputOutOfBoundsException& e){
                
                //handle exception
                outfile << "Error: " << e.returnError() << e.returnOffendingIndex() << "\n";
                
                break;
            }
            
            // if reach end of a row, go to next row
            if ((i+1) % width == 0){
                
                outfile << "\n";
            }
            else{
                outfile << " ";
            }
        }
        
        //close the ofstream file
        outfile.close();
    }
}
