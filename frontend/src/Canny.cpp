//
// Created by pavel on 17.03.16.
//

#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "QtAndOpenCvTools.h"

#include "Canny.h"

using namespace cv;
using namespace std;

Canny::Canny(int low, int high, int size) :
        low(low), high(high), size(size) {
}

QImage Canny::operator()(const Mat &a) {
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
        cv::Canny(c, d, low, high, size);

        Mat e;
        cvtColor(d, e, CV_GRAY2RGB);

        return QtAndOpenCvTools::Mat2QImage(e);
    } catch (const exception &e) {
        cerr << "canny error: " << e.what() << endl;
        return QImage(":/error.png");
    }
}
