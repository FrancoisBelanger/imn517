//
//  image.cpp
//  tp1
//
//  Created by François Bélanger on 2015-01-22.
//  Copyright (c) 2015
//
//  François Bélanger   94 245 437.
//  Roxane Martel       10 215 000
//  Pavlo Minko
//
//  All rights reserved.
//


#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Image.h"

using namespace std;

Image::Image()// : w(0), h(0), pixels(0x0)
{ /* empty image */ }

//Image::Image(const unsigned int &_w, const unsigned int &_h, const Pixel &c ) : w(_w), h(_h), pixels(0x0)
//{
//    pixels = new Pixel[w * h];
//    for (int i = 0; i < w * h; ++i) pixels[i] = c;
//}

Image::Image(const char* filename)
{
    read(filename);
}

Image::~Image()
{ 
//	if (pixels != 0x0) 
//	{
//		delete [] pixels; 
//	}
}

Image Image::operator+(const Image& other)
{
    Image retVal;
    retVal.img = cv::Mat(other.img.size(), other.img.type());
    cv::add(img, other.img, retVal.img);
    return retVal;
    
//    Image* retVal = new Image(w, h);
//    
//    for(int j = 0; j< h; ++j)
//    {
//        for(int i = 0; i < w; ++i)
//        {
//            int idx = j*w+i;
//            retVal->pixels[idx] = pixels[idx] + other.pixels[idx];
//        }
//    }
//    
//    return *retVal;
}

Image& Image::operator-=(const Image& other)
{
    cv::subtract(img, other.img, img);
    return *this;
//    for(int j = 0; j< h; ++j)
//    {
//        for(int i = 0; i < w; ++i)
//        {
//            int idx = j*w+i;
//            pixels[idx] -= other.pixels[idx];
//        }
//    }
//    
//    return *this;
}


//Image& Image::operator /= (const float& zapper)
Image& Image::operator/=(const float &zapper)
{
    img = img / zapper;
    return *this;
//    for(int j = 0; j< h; ++j)
//    {
//        for(int i = 0; i < w; ++i)
//        {
//            int idx = j*w+i;
//            pixels[idx] /= zapper;
//        }
//    }
//    
//    return *this;
}

Image& Image::operator=(const Image& other)
{
    
    img = cv::Mat(other.img);
    return *this;
}

void Image::read(const char *filename)
{
    img = cv::imread(filename, 0);
}

void Image::save(const char *filename)
{
    cv::imwrite(filename, img);
}
