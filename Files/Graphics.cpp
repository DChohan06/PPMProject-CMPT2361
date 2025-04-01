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

//Rotate - angle in radians
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
    unsigned int newWidth = ceil(2 * radius); //ceiling function
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

//Filters

const PPM& Graphics::ApplyFilter(PPM& img, const char* filterName) {
    
    //get width and height of image
    unsigned int width = img.GetWidth();
    unsigned int height = img.GetHeight();
    
    //create copy for transformation
    PPM originalImg = img;
    
    //blur filter
    if (strcmp(filterName, "blur") == 0) {
        //define length for bluring from each pixel for kernel
        int radius = 1; //use int to prevent static_cast
        
        //for every pixel in the image - use int to prevent static_cast
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int totalRed = 0, totalGreen = 0, totalBlue = 0, count = 0;
                
                //loop over neighboring pixels within length
                for (int dy = -radius; dy <= radius; dy++) {
                    for (int dx = -radius; dx <= radius; dx++) {
                        
                        //find neighbour coordinates
                        int nx = x + dx, ny = y + dy;
                        
                        //check if neighbour is within bounds of image width and height
                        if (nx >= 0 && nx < static_cast<int>(width) && ny >= 0 && ny < static_cast<int>(height)) {
                            
                            //add neighbour pixels color values to total
                            Pixel& p = originalImg[ny * width + nx];
                            totalRed += p["red"];
                            totalGreen += p["green"];
                            totalBlue += p["blue"];
                            count++;
                        }
                    }
                }
                //set current pixel to average color value of its neighbours
                img[y * width + x] = Pixel(totalRed / count, totalGreen / count, totalBlue / count);
            }
        }
    
    // sharpen filter
    } else if (strcmp(filterName, "sharpen") == 0) {
        
        //use 3x3 kernel to enhance edge
        int kernel[3][3] = {{  0, -1,  0 }, { -1,  5, -1 }, {  0, -1,  0 }};
        
        //loop through pixels of image, excluding border
        for (unsigned int y = 1; y < height - 1; y++) {
            for (unsigned int x = 1; x < width - 1; x++) {
                int totalRed = 0, totalGreen = 0, totalBlue = 0;
                
                //apply kernel to surrounding pixels
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        Pixel& p = originalImg[(y + dy) * width + (x + dx)];
                        totalRed += p["red"] * kernel[dy + 1][dx + 1];
                        totalGreen += p["green"] * kernel[dy + 1][dx + 1];
                        totalBlue += p["blue"] * kernel[dy + 1][dx + 1];
                    }
                }
                
                //make sure color values are within 0 and 255
                totalRed = (totalRed < 0) ? 0 : (totalRed > 255 ? 255 : totalRed);
                totalGreen = (totalGreen < 0) ? 0 : (totalGreen > 255 ? 255 : totalGreen);
                totalBlue = (totalBlue < 0) ? 0 : (totalBlue > 255 ? 255 : totalBlue);
                
                //set pixel to new sharpen color
                img[y * width + x] = Pixel(totalRed, totalGreen, totalBlue);
            }
        }
        
    // Edge detect filter
    } else if (strcmp(filterName, "edgeDetect") == 0) {
        
        //use kernel for edge detecting make edge brighter
        int kernel[3][3] = {{ 0, 1, 0 }, { 1, -4, 1 }, { 0, 1, 0 }};
        
        //loop through pixels of image, excluding border
        for (unsigned int y = 1; y < height - 1; y++) {
            for (unsigned int x = 1; x < width - 1; x++) {
                int totalRed = 0, totalGreen = 0, totalBlue = 0;
                
                //apply kernel to surrounding pixels
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        Pixel& p = originalImg[(y + dy) * width + (x + dx)];
                        totalRed += p["red"] * kernel[dy + 1][dx + 1];
                        totalGreen += p["green"] * kernel[dy + 1][dx + 1];
                        totalBlue += p["blue"] * kernel[dy + 1][dx + 1];
                    }
                }
                
                //make sure color values are within 0 and 255
                totalRed = (totalRed < 0) ? 0 : (totalRed > 255 ? 255 : totalRed);
                totalGreen = (totalGreen < 0) ? 0 : (totalGreen > 255 ? 255 : totalGreen);
                totalBlue = (totalBlue < 0) ? 0 : (totalBlue > 255 ? 255 : totalBlue);
                
                //set pixel to new color
                img[y * width + x] = Pixel(totalRed, totalGreen, totalBlue);
            }
        }
    } else if (strcmp(filterName, "emboss") == 0) {
        
        //use kernel for emboss -similar to 3D effect
        int kernel[3][3] = {{ -2, -1,  0 }, { -1,  1,  1 }, {  0,  1,  2 }};
        
        //loop through pixels of image, excluding border
        for (unsigned int y = 1; y < height - 1; y++) {
            for (unsigned int x = 1; x < width - 1; x++) {
                int totalRed = 128, totalGreen = 128, totalBlue = 128;
                
                //apply kernel to surrounding pixels
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        Pixel& p = originalImg[(y + dy) * width + (x + dx)];
                        totalRed += p["red"] * kernel[dy + 1][dx + 1];
                        totalGreen += p["green"] * kernel[dy + 1][dx + 1];
                        totalBlue += p["blue"] * kernel[dy + 1][dx + 1];
                    }
                }
                
                //make sure color values are within 0 and 255
                totalRed = (totalRed < 0) ? 0 : (totalRed > 255 ? 255 : totalRed);
                totalGreen = (totalGreen < 0) ? 0 : (totalGreen > 255 ? 255 : totalGreen);
                totalBlue = (totalBlue < 0) ? 0 : (totalBlue > 255 ? 255 : totalBlue);
                
                //set pixel to new color
                img[y * width + x] = Pixel(totalRed, totalGreen, totalBlue);
            }
        }
        
    //customed filter - high contrast
    } else if (strcmp(filterName, "highContrast") == 0) {
        
        //use kernel to enhance contrast
        int kernel[3][3] = {{ -1, -1,  -1 }, { -1,  8,  -1 }, {  -1,  -1,  -1 }};
        
        //loop through pixels of image, excluding border
        for (unsigned int y = 1; y < height - 1; y++) {
            for (unsigned int x = 1; x < width - 1; x++) {
                int totalRed = 128, totalGreen = 128, totalBlue = 128;
                
                //apply kernel to surrounding pixels
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        Pixel& p = originalImg[(y + dy) * width + (x + dx)];
                        totalRed += p["red"] * kernel[dy + 1][dx + 1];
                        totalGreen += p["green"] * kernel[dy + 1][dx + 1];
                        totalBlue += p["blue"] * kernel[dy + 1][dx + 1];
                    }
                }
                
                //make sure color values are within 0 and 255
                totalRed = (totalRed < 0) ? 0 : (totalRed > 255 ? 255 : totalRed);
                totalGreen = (totalGreen < 0) ? 0 : (totalGreen > 255 ? 255 : totalGreen);
                totalBlue = (totalBlue < 0) ? 0 : (totalBlue > 255 ? 255 : totalBlue);
                
                //set pixel to new color
                img[y * width + x] = Pixel(totalRed, totalGreen, totalBlue);
            }
        }
    }
    
    //return a modified img
    return img;
}
