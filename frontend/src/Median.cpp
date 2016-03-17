//
// Created by pavel on 17.03.16.
//

#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>

#include "QtAndOpenCvTools.h"

#include "Median.h"

using namespace std;
using namespace cv;

Median::Median(int size) :
        size(size) {
}

QImage Median::operator()(const Mat &a) {
    try {
        Mat b;
        if (a.channels() > 1) {
            cvtColor(a, b, CV_RGB2GRAY);
        } else {
            b = a.clone();
        }
        Mat c;
        medianBlur(b, c, size);
        Mat d;
        cvtColor(c, d, CV_GRAY2RGB);
        return QtAndOpenCvTools::Mat2QImage(d);
    } catch (const exception &e) {
        cerr << "median error: " << e.what() << endl;
        return QImage(":/error.png");
    }
}

