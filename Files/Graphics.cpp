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

    const PPM& Graphics:: RotateImage(PPM& img, double angle){
        unsigned int width=img.GetWidth();
        unsigned int height=img.GetHeight();
        double cx=(width-1)/2; //x-center of the image
        double cy=(height-1)/2; //y-center of the image
        double cosTheta=cos(angle);
        double sinTheta=sin(angle);

        PPM* rotatedImage= new PPM();
        rotatedImage->SetWidth(width);
        rotatedImage->SetHeight(height);
        rotatedImage->resize(width*height);

        for (unsigned int y=0;y<height;y++){
            for (unsigned int x=0;x<width;x++){
                //because the rotation matrix rotates around the 0,0, so we have to do this make the midpoint applicable to the rotation matrix
                double translatedX=x-cx;
                double translatedY=y-cy;

                //apply rotation
                double rotatedX=translatedX*cosTheta-translatedY*sinTheta;
                double rotatedY=translatedX*sinTheta+translatedY*cosTheta;

                //go back to reality adding the cx and cy after subtracting it to make the algorithm works for mid point rotation
                double srcX=rotatedX+cx;
                double srcY=rotatedY+cy;
                
                //check bounds
                if (srcX>=0 && srcX<=width-1 && srcY>=0 && srcY<=height-1){
                    unsigned int originalX= static_cast<unsigned int>(srcX+0.5);
                    unsigned int originalY=static_cast<unsigned int>(srcY+0.5);

                    //the x and y in the original image that is about to be transferred to rotatedImage in the rotated position
                    originalX=min(originalX,width-1);
                    originalY=min(originalY,height-1);

                    (*rotatedImage)[y*width+x]=img[originalY*width+originalX];

                }else{
                    //set to black if out of bounds
                    (*rotatedImage)[y*width+x]=Pixel(0,0,0);
                }
            }
        }
        //must call the destructor after using this to avoid memory leak
        return *rotatedImage;
    }