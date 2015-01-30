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
#include "Image.h"
#include <opencv2/core/core.hpp>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

Mat apply88Dct(Mat img)
{
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
//                planes[k].convertTo(planes[k], CV_32FC1);
                dct(planes[k], outplanes[k]);
//                outplanes[k].convertTo(outplanes[k], CV_8UC1);
            }
            merge(outplanes, block);
        }
    }

//    int x = 0;
//    int y = 0;
//    namedWindow("dctBlockImage");
//    moveWindow("dctBlockImage", x, y);
//    imshow("dctBlockImage", dctImage);
//    x += 100; y += 100;
    
    return dctImage;
}

void applyDct(Mat img, Mat out)
{
    vector<Mat> planes;
    split(img, planes);
    vector<Mat> outplanes(planes.size());
    
    for (size_t i = 0; i < planes.size(); i++)
    {
//        planes[i].convertTo(planes[i], CV_32FC1);
        dct(planes[i], outplanes[i]);
    }
    
    merge(outplanes, out);
    
//    int x = 0; int y = 0;
//    x += 100; y += 100;
//    namedWindow("DCT Image[0]", CV_WINDOW_AUTOSIZE);
//    moveWindow("DCT Image[0]", x, y);
//    imshow("DCT Image[0]", outplanes[0]); x += 100; y += 100;
//    
//    namedWindow("DCT Image[1]", CV_WINDOW_AUTOSIZE);
//    moveWindow("DCT Image[1]", x, y);
//    imshow("DCT Image[1]", outplanes[1]); x += 100; y += 100;
//    
//    namedWindow("DCT Image[2]", CV_WINDOW_AUTOSIZE);
//    moveWindow("DCT Image[2]", x, y);
//    imshow("DCT Image[2]", outplanes[2]);
}

int main(int argc, const char * argv[])
{
    Mat img1 = imread("flower1.png", 0);
    img1.convertTo(img1, CV_32FC1);
    Mat img2 = imread("flower2.png", 0);
    img2.convertTo(img2, CV_32FC1);
    Mat img3 = imread("flower3.png", 0);
    img3.convertTo(img3, CV_32FC1);
    Mat img4 = imread("flower4.png", 0);
    img4.convertTo(img4, CV_32FC1);
    Mat img5 = imread("flower5.png", 0);
    img5.convertTo(img5, CV_32FC1);
    Mat avg(img1.size(), img1.type());
    add(img1, img2, avg);
    add(avg, img3, avg);
    add(avg, img4, avg);
    add(avg, img5, avg);
    avg = avg / 5;
    
    subtract(img1, avg, img1);
    subtract(img3, avg, img3);
    subtract(img2, avg, img2);
    subtract(img4, avg, img4);
    subtract(img5, avg, img5);
    
    Mat dctavg(img1.size(), img1.type()), out1(img1.size(), img1.type()), out2(img1.size(), img1.type()), out3(img1.size(), img1.type()), out4(img1.size(), img1.type()), out5(img1.size(), img1.type());
    applyDct(avg, dctavg);
    applyDct(img1, out1);
    applyDct(img2, out2);
    applyDct(img3, out3);
    applyDct(img4, out4);
    applyDct(img5, out5);
    Mat dct8avg = apply88Dct(avg);
    Mat dct81 = apply88Dct(img1);
    Mat dct82 = apply88Dct(img2);
    Mat dct83 = apply88Dct(img3);
    Mat dct84 = apply88Dct(img4);
    Mat dct85 = apply88Dct(img5);
    avg.convertTo(avg, CV_8UC1);
    img1.convertTo(img1, CV_8UC1);
    img2.convertTo(img2, CV_8UC1);
    img3.convertTo(img3, CV_8UC1);
    img4.convertTo(img4, CV_8UC1);
    img5.convertTo(img5, CV_8UC1);
    dctavg.convertTo(dctavg, CV_8UC1);
    out1.convertTo(out1, CV_8UC1);
    out2.convertTo(out2, CV_8UC1);
    out3.convertTo(out3, CV_8UC1);
    out4.convertTo(out4, CV_8UC1);
    out5.convertTo(out5, CV_8UC1);
    dct8avg.convertTo(dct8avg, CV_8UC1);
    dct81.convertTo(dct81, CV_8UC1);
    dct82.convertTo(dct82, CV_8UC1);
    dct83.convertTo(dct83, CV_8UC1);
    dct84.convertTo(dct84, CV_8UC1);
    dct85.convertTo(dct85, CV_8UC1);
    imwrite("avg1.pgm", img1);
    imwrite("avg3.pgm", img3);
    imwrite("avg2.pgm", img2);
    imwrite("avg4.pgm", img4);
    imwrite("avg5.pgm", img5);
    imwrite("avg.pgm", avg);
    imwrite("dctavg.pgm", dctavg);
    imwrite("dct1.pgm", out1);
    imwrite("dct2.pgm", out2);
    imwrite("dct3.pgm", out3);
    imwrite("dct4.pgm", out4);
    imwrite("dct5.pgm", out5);
    imwrite("dct8avg.pgm", dct8avg);
    imwrite("dct81.pgm", dct81);
    imwrite("dct82.pgm", dct82);
    imwrite("dct83.pgm", dct83);
    imwrite("dct84.pgm", dct84);
    imwrite("dct85.pgm", dct85);
//    Mat merged;
//    applyDct(img1, merged);
//    
//    apply88Dct(img1, merged);
//    waitKey(0);
//    imwrite("dct.pgm", a);

//    Image img1("face1.png");
//    Image img2("face2.png");
//    Image img3("face3.png");
//    Image img4("face4.png");
//    Image avg;
//
//    avg = img1 + img2 + img3 + img4;
//    imshow("a",avg.img);
//    waitKey(0);
//    imshow("1",img1.img);
//    waitKey(0);
//    avg /= 4;
//    imshow("a/4",avg.img);
//    waitKey(0);
//    imshow("1",img1.img);
//    img1 -= avg;
//    imshow("r1",img1.img);
//    waitKey(0);
//    imshow("2",img2.img);
//    img2 -= avg;
//    imshow("r2",img2.img);
//    waitKey(0);
//    imshow("3",img3.img);
//    img3 -= avg;
//    imshow("r3",img3.img);
//    waitKey(0);
//    imshow("4",img4.img);
//    img4 -= avg;
//    imshow("r4",img4.img);
//    waitKey(0);
//    //    subtract(img2, avg, img2);
//    //    subtract(img4, avg, img4);
//    
//    img1.save("avg1.pgm");
//    img3.save("avg3.ppm");
//    //    imwrite("avg2.ppm", img2);
//    //    imwrite("avg4.ppm", img4);
//    avg.save("avg.ppm");
//    
////    Mat merged;
////    applyDct(img1, merged);
////    
////    apply88Dct(img1, merged);
////    waitKey(0);
//    //    imwrite("dct.pgm", a);
    return 0;
}
