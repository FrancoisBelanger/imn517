//
//  image.h
//  tp1
//
//  Created by François Bélanger on 2015-01-22.
//  Copyright (c) 2015
//
//  François Bélanger   94 245 437.
//  Roxane Martel       10 215 000
//  Pavlo
//
//  All rights reserved.
//

#ifndef _Image_h
#define _Image_h

#include <opencv2/core/core.hpp>

class Image
{
public:    
    struct Pixel
    {
        Pixel() : r(0), g(0), b(0)  {}
        Pixel(float c) : r(c), g(c), b(c) {}
        Pixel(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
        
        bool operator != (const Pixel &c) const
		{ 
            return c.r != r || c.g != g || c.b != b;
		}
        
        Pixel& operator *= (const Pixel &rgb)
		{ 
			r *= rgb.r, g *= rgb.g, b *= rgb.b; return *this; 
		}
        
        Pixel& operator += (const Pixel &rgb)
		{ 
			r += rgb.r, g += rgb.g, b += rgb.b; return *this; 
		}
        
        Pixel& operator -= (const Pixel &rgb)
        {
            r -= rgb.r, g -= rgb.g, b -= rgb.b; return *this;
        }
        
        Pixel& operator /= (const float& zapper)
        {
            r /= zapper; g /= zapper; b /= zapper; return *this;
        }
        
        Pixel operator+(const Pixel& other)
        {
            return Pixel(r+other.r, g+other.g, b+other.b);
        }
        
        friend float& operator += (float &f, const Pixel rgb)
        { 
			f += (rgb.r + rgb.g + rgb.b) / 3.f; return f; 
		}
        float r, g, b;
    };
    
    cv::Mat img;
    Image();
    Image(const char* filename);
//    Image(const unsigned int &_w, const unsigned int &_h, const Pixel &c = Pixel(0));
	~Image();

//    const Pixel& operator [] (const unsigned int &i) const { return pixels[i]; }
//    Pixel& operator [] (const unsigned int &i) { return pixels[i]; }
//
//    unsigned int w, h; // image resolution
//    Pixel *pixels; // 1D array of pixels
    
//    Image& operator+(const Image& other);
//    Image& operator-=(const Image& other);
//    Image& operator /= (const float& zapper);

    Image operator+(const Image& other);
    Image& operator-=(const Image& other);
    Image& operator/= (const float& zapper);
    Image& operator=(const Image& other);
    
    void read(const char* filename);
    void save(const char* filename);
};

#endif //_Image_h