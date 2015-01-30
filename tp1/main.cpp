//
//  main.cpp
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

#include <iostream>
#include <algorithm>
//#include "Image.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

void apply88Dct(Mat img, Mat out)
{
    int x = 0;
    int y = 0;
    
    Mat dctImage = img.clone();
    // Step through the copied image with rectangles size 8x8
    // For each block, split into planes, do dct, and merge back
    // into the block. (This will affect the image from
    // which the block is selected each time.)
    
    int width = img.size().width;
    int height = img.size().height;
    
    for (int j = 0; j < height-8; j += 8)
    {
        for (int i = 0; i < width-8; i+= 8)
        {
            Mat block = dctImage(Rect(i, j, 8, 8));
            vector<Mat> planes; split(block, planes);
            vector<Mat> outplanes(planes.size());
            
            for (size_t k = 0; k < planes.size(); k++)
            {
                planes[k].convertTo(planes[k], CV_32FC1);
                dct(planes[k], outplanes[k]);
                outplanes[k].convertTo(outplanes[k], CV_8UC1);
            }
            merge(outplanes, block);
        }
    }
    
    namedWindow("dctBlockImage");
    moveWindow("dctBlockImage", x, y);
    imshow("dctBlockImage", dctImage);
    x += 100; y += 100;
}

void applyDct(Mat img, Mat out)
{
    vector<Mat> planes;
    split(img, planes);
    vector<Mat> outplanes(planes.size());
    
    for (size_t i = 0; i < planes.size(); i++)
    {
        planes[i].convertTo(planes[i], CV_32FC1);
        dct(planes[i], outplanes[i]);
    }
    
    merge(outplanes, out);
    
    int x = 0; int y = 0;
    x += 100; y += 100;
    namedWindow("DCT Image[0]", CV_WINDOW_AUTOSIZE);
    moveWindow("DCT Image[0]", x, y);
    imshow("DCT Image[0]", outplanes[0]); x += 100; y += 100;
    
    namedWindow("DCT Image[1]", CV_WINDOW_AUTOSIZE);
    moveWindow("DCT Image[1]", x, y);
    imshow("DCT Image[1]", outplanes[1]); x += 100; y += 100;
    
    namedWindow("DCT Image[2]", CV_WINDOW_AUTOSIZE);
    moveWindow("DCT Image[2]", x, y);
    imshow("DCT Image[2]", outplanes[2]);

}

int main(int argc, const char * argv[])
{
    Mat img1 = imread("1.pgm");
    Mat img3 = imread("3.ppm");
    Mat avg(img1.size(), img1.type());
    add(img1, img3, avg);
    avg = avg / 2;
    
    subtract(img1, avg, img1);
    subtract(img3, avg, img3);
//    subtract(img2, avg, img2);
//    subtract(img4, avg, img4);
    
    imwrite("avg1.pgm", img1);
    imwrite("avg3.ppm", img3);
//    imwrite("avg2.ppm", img2);
//    imwrite("avg4.ppm", img4);
    imwrite("avg.ppm", avg);
    
    Mat merged;
    applyDct(img1, merged);
    
    apply88Dct(img1, merged);
    waitKey(0);
//    imwrite("dct.pgm", a);
    
    return 0;
}
