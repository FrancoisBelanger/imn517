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

#include "Image.h"

using namespace std;

Image::Image() : w(0), h(0), pixels(0x0)
{ /* empty image */ }

Image::Image(const unsigned int &_w, const unsigned int &_h, const Pixel &c ) : w(_w), h(_h), pixels(0x0)
{
    pixels = new Pixel[w * h];
    for (int i = 0; i < w * h; ++i) pixels[i] = c;
}

Image::Image(const char* filename)
{
    readPPM(filename);
}

Image::~Image()
{ 
	if (pixels != 0x0) 
	{
		delete [] pixels; 
	}
}

Image& Image::operator+(const Image& other)
{
    Image* retVal = new Image(w, h);
    
    for(int j = 0; j< h; ++j)
    {
        for(int i = 0; i < w; ++i)
        {
            int idx = j*w+i;
            retVal->pixels[idx] = pixels[idx] + other.pixels[idx];
        }
    }
    
    return *retVal;
}

Image& Image::operator-=(const Image& other)
{
    for(int j = 0; j< h; ++j)
    {
        for(int i = 0; i < w; ++i)
        {
            int idx = j*w+i;
            pixels[idx] -= other.pixels[idx];
        }
    }
    
    return *this;
}


Image& Image::operator /= (const float& zapper)
{
    for(int j = 0; j< h; ++j)
    {
        for(int i = 0; i < w; ++i)
        {
            int idx = j*w+i;
            pixels[idx] /= zapper;
        }
    }
    
    return *this;
}

void Image::readPPM(const char *filename)
{
    std::ifstream ifs;
    ifs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users

    try {
        if (ifs.fail())
        {
            throw("Can't open input file");
        }
        
        std::string header;
        int width, height, b;
        ifs >> header;
        
        if (strcmp(header.c_str(), "P6") != 0)
            throw("Can't read input file");
        
        ifs >> width >> height >> b;
        w = width;
        h = height;
        pixels = new Image::Pixel[w * h]; // this is throw an exception if bad_alloc
        ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data
        unsigned char pix[3];
        
        // read each pixel one by one and convert bytes to floats
        for (int i = 0; i < w * h; ++i)
        {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            pixels[i].r = pix[0];
            pixels[i].g = pix[1];
            pixels[i].b = pix[2];
        }
        ifs.close();
    }
    
    catch (const char *err)
    {
        fprintf(stderr, "%s\n", err);
        ifs.close();
    }
}

void Image::savePPM(const char *filename)
{
    if (w == 0 || h == 0)
    {
        fprintf(stderr, "Can't save an empty image\n");
        return;
    }
    
    std::ofstream ofs;
    try
    {
        ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users
        if (ofs.fail())
            throw("Can't open output file");
        
        ofs << "P6\n" << w << " " << h << "\n255\n";
        unsigned char r, g, b;
        // loop over each pixel in the image, clamp and convert to byte format
        
        for (int i = 0; i < w * h; ++i)
        {
            r = static_cast<unsigned char>(pixels[i].r);
            g = static_cast<unsigned char>(pixels[i].g);
            b = static_cast<unsigned char>(pixels[i].b);
            ofs << r << g << b;
        }
        ofs.close();
    }
    
    catch (const char *err)
    {
        fprintf(stderr, "%s\n", err);
        ofs.close();
    }
}
