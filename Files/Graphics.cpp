#include "Graphics.h"

//Gray Scale function
const PPM& Graphics:: MakeGrayScale(PPM& img){
    cout<<"MakeGrayScale is called\n";
    

    for (unsigned int i=0;i<img.GetWidth()*img.GetHeight();i++){
        Pixel& pixel=img[i];
        unsigned int gray=(pixel["red"]+pixel["green"]+pixel["blue"])/3;
        pixel=Pixel(gray,gray,gray);
    }
    return img;
}

//Translated Image function
const PPM& Graphics:: TranslateImage(PPM& img, int dx, int dy){
    int height=img.GetHeight();
    int width=img.GetWidth();
    //shift right, start from bottom right corner
    if (dx>0){
        for (int y=height-1;y>=0;y--){
            for (int x=width-1;x>=0;x--){
                int newX=x+dx;
                if (newX<width){
                    img[y*width+newX]=img[y*width+x];
                }
            }
        }
    }
    //shift left, start from top left corner
    else if (dx<0){
        for (int y=0;y<height;y++){
            for (int x=0;x<width;x++){
                if (x>=abs(dx)){
                    int newX=x+dx;
                    img[y*width+newX]=img[y*width+x];
                }
            }
        }
    }
    //shift down, start from bottom right corner
    if (dy>0){
        for (int y=height-1;y>=0;y--){
            for (int x=width-1;x>=0;x--){
                int newY=y+dy;
                if(newY<height){
                    img[newY*width+x]=img[y*width+x];
                }
            }
        }
    }
    //shift up, start from top left corner
    else if (dy<0){
        for (int y=0;y<height;y++){
            for (int x=0;x<width;x++){
                if (y>=abs(dy)){
                    int newY=y+dy;
                    img[newY*width+x]=img[y*width+x];
                }
            }
        }
    }
    
    //fill the unmoved pixels with black
    for (int y=0;y<height;y++){
        for (int x=0;x<width;x++){
            int originalX=x-dx;
            int originalY=y-dy;
            if (originalX<0||originalX>=width||originalY<0||originalY>=height){
                img[y*width+x]=Pixel(0,0,0);
            }
        }
    }

    return img;
}

//Scale Image Function
const PPM& Graphics:: ScaleImage(PPM& img, double scaleFactor){

    //new dimension
    unsigned int newWidth=img.GetWidth()*scaleFactor;
    unsigned int newHeight=img.GetHeight()*scaleFactor;

    //create temp object
    PPM scaledImage;
    scaledImage.SetHeight(newHeight);
    scaledImage.SetWidth(newWidth);
    scaledImage.resize(newHeight*newWidth);

    for (unsigned int y=0;y<newHeight;y++){
        for (unsigned int x=0;x<newWidth;x++){
            unsigned int originalX=x/scaleFactor;
            unsigned int originalY=y/scaleFactor;
                
            //make sure don't go out of bounds
            originalX=originalX>=img.GetWidth()?img.GetWidth()-1:originalX;
            originalY=originalY>=img.GetHeight()?img.GetHeight()-1:originalY;

            //nearest neighbor pixel mapping
            Pixel nearestPixel=img[originalY*img.GetWidth()+originalX];
            scaledImage[y*newWidth+x]=nearestPixel;
        }
    }

    //swap contents instead of returning a reference to temp object
    img = scaledImage;
    return img;
}

const PPM& Graphics:: RotateImage(PPM& img, double angle){
    
    unsigned int width=img.GetWidth();
    unsigned int height=img.GetHeight();
    double cx=(width-1)/2; //x-center of the image
    double cy=(height-1)/2; //y-center of the image
    double cosTheta=cos(angle);
    double sinTheta=sin(angle);
    
    // Calculate dimensions of bounding box for rotated image
    // For a full rotation, we need to find the maximum distance from center
    // to any corner, then double it to get the diameter
    double cornerX = max(cx, width - 1 - cx);
    double cornerY = max(cy, height - 1 - cy);
    double radius = sqrt(cornerX * cornerX + cornerY * cornerY);
    unsigned int newWidth = ceil(2 * radius);
    unsigned int newHeight = ceil(2 * radius);
        
    // New center coordinates
    double newCx = (newWidth - 1) / 2.0;
    double newCy = (newHeight - 1) / 2.0;

    PPM rotatedImage;
    rotatedImage.SetWidth(newWidth);
    rotatedImage.SetHeight(newHeight);
    rotatedImage.resize(newWidth*newHeight);

    for (unsigned int y=0;y<newHeight;y++){
        for (unsigned int x=0;x<newWidth;x++){
            //because the rotation matrix rotates around the 0,0, so we have to do this make the midpoint applicable to the rotation matrix
            double translatedX=x-newCx;
            double translatedY=y-newCy;

            //apply rotation
            double rotatedX=translatedX*cosTheta-translatedY*sinTheta;
            double rotatedY=translatedX*sinTheta+translatedY*cosTheta;

            //go back to reality adding the cx and cy after subtracting it to make the algorithm works for mid point rotation
            double srcX=rotatedX+cx;
            double srcY=rotatedY+cy;
                
            // Check bounds
            if (srcX >= 0 && srcX < width && srcY >= 0 && srcY < height) {
            // Use nearest neighbor interpolation
                int nearestX = round(srcX);
                int nearestY = round(srcY);
                                
                // Ensure we're within bounds
                nearestX = min(nearestX, (int)width - 1);
                nearestY = min(nearestY, (int)height - 1);
                                
                // Copy the pixel directly
                rotatedImage[y * newWidth + x] = img[nearestY * width + nearestX];
            }
        }
    }
    //swap contents instead of returning a reference to temp object
    img = rotatedImage;
    return img;
}

const PPM& Graphics::BlurImage(PPM& img, unsigned int radius) {
    unsigned int width = img.GetWidth();
    unsigned int height = img.GetHeight();
    
    // Create a temporary copy of the image to read from
    // (We need this to avoid reading from pixels we've already modified)
    PPM originalImg = img;
    
    // Apply box blur algorithm
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            unsigned int totalRed = 0;
            unsigned int totalGreen = 0;
            unsigned int totalBlue = 0;
            unsigned int count = 0;
            
            // Sum the values in the neighborhood (kernel)
            for (int dy = -static_cast<int>(radius); dy <= static_cast<int>(radius); dy++) {
                for (int dx = -static_cast<int>(radius); dx <= static_cast<int>(radius); dx++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    
                    // Only take into account the pixels that are within bounds
                    if (nx >= 0 && nx < static_cast<int>(width) && ny >= 0 && ny < static_cast<int>(height)) {
                        Pixel& p = originalImg[ny * width + nx];
                        totalRed += p["red"];
                        totalGreen += p["green"];
                        totalBlue += p["blue"];
                        count++;
                    }
                }
            }
            
            // Calculate average color values
            unsigned int avgRed = (count > 0) ? totalRed / count : 0;
            unsigned int avgGreen = (count > 0) ? totalGreen / count : 0;
            unsigned int avgBlue = (count > 0) ? totalBlue / count : 0;
            
            // Modify the pixel in the original image
            img[y * width + x] = Pixel(avgRed, avgGreen, avgBlue);
        }
    }
    
    return img;
}
