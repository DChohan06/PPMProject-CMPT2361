#include "Graphics.h"
const PPM& Graphics:: MakeGrayScale(PPM& img){
    cout<<"MakeGrayScale is called";

    for (int i=0;i<img.GetWidth()*img.GetHeight();i++){
        Pixel& pixel=img[i];
        unsigned int gray=(pixel["red"]+pixel["green"]+pixel["blue"])/3;
        pixel=Pixel(gray,gray,gray);
    }
    return img;
}
const PPM& Graphics:: TranslateImage(PPM& img, int dx, int dy){
    unsigned int height=img.GetHeight();
    unsigned int width=img.GetWidth();
    //shift right, start from bottom right corner
    if (dx>0){
    for (unsigned int y=height-1;y>=0;y--){
        for (unsigned int x=width-1;x>=0;x--){
            long int newX=x+dx;
            if (newX<width){
                img[y*width+newX]=img[y*width+x];
            }
        }
    }
    }
    //shift left, start from top left corner
    else if (dx<0){
        for (long int y=0;y<height;y++){
            for (long int x=0;x<width;x++){
                if (x>=abs(dx)){
                    long int newX=x+dx;
                    img[y*width+newX]=img[y*width+x];
                }
            }
        }
    }
    //shift down, start from bottom right corner
    if (dy>0){
        for (long int y=height-1;y>=0;y--){
            for (long int x=width-1;x>=0;x--){
                long int newY=y+dy;
                if(newY<height){
                    img[newY*width+x]=img[y*width+x];
                }
            }
        }
    }
    //shift up, start from top left corner
    else if (dy<0){
        for (long int y=0;y<height;y++){
            for (long int x=0;x<width;x++){
                if (y>=abs(dy)){
                    long int newY=y+dy;
                    img[newY*width+x]=img[y*width+x];
                }
            }
        }
    }
    
    //fill the unmoved pixels with black
    for (long int y=0;y<height;y++){
        for (long int x=0;x<width;x++){
            long int originalX=x-dx;
            long int originalY=y-dy;
            if (originalX<0||originalX>=static_cast<long int>(width)||originalY<0||originalY>=static_cast<long int>(height)){
                img[y*width+x]=Pixel(0,0,0);
            }
        }
    }

return img;
}
	 const PPM& Graphics:: ScaleImage(PPM& img, double scaleFactor){

        //new dimension
        unsigned int newWidth=img.GetWidth()*scaleFactor;
        unsigned int newHeight=img.GetHeight()*scaleFactor;

        PPM* scaledImage=new PPM();
        scaledImage->SetHeight(newHeight);
        scaledImage->SetWidth(newWidth);
        scaledImage->resize(newHeight*newWidth);

   

        for (unsigned int y=0;y<newHeight;y++){
            for (unsigned int x=0;x<newWidth;x++){
                unsigned int originalX=x/scaleFactor;
                unsigned int originalY=y/scaleFactor;
                
                //make sure don't go out of bounds
                originalX=originalX>=img.GetWidth()?img.GetWidth()-1:originalX;
                originalY=originalY>=img.GetHeight()?img.GetHeight()-1:originalY;

                //nearest neighbor pixel mapping
                Pixel nearestPixel=img[originalY*img.GetWidth()+originalX];
                (*scaledImage)[y*newWidth+x]=nearestPixel;
            }
        }

        //return a reference to the dynamically allocated PPM object
        //MUST DELETE after use to avoid MEMORY LEAKS
        return *scaledImage;
    }