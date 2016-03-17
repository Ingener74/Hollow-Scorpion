/*
 * QtAndOpenCvTools.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: pavel
 */

#include <iostream>

#include "QtAndOpenCvTools.h"

#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

QImage QtAndOpenCvTools::Mat2QImage(const Mat& src) {
    switch (src.type()) {
    case CV_8UC4: {
        QImage image(src.data, src.cols, src.rows, src.step, QImage::Format_RGB32);
        return image;
    }
    case CV_8UC3: {
        QImage image(src.data, src.cols, src.rows, src.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    case CV_8UC1: {
        static QVector<QRgb> sColorTable;

        if (sColorTable.isEmpty())
            for (int i = 0; i < 256; ++i)
                sColorTable.push_back(qRgb(i, i, i));

        QImage image(src.data, src.cols, src.rows, src.step, QImage::Format_Indexed8);

        image.setColorTable(sColorTable);

        return image;
    }

    default:
        cerr << __PRETTY_FUNCTION__ << " Mat image type not handled in switch " << src.type() << endl;
        break;
    }

    return QImage();
}

Mat QtAndOpenCvTools::QImage2Mat(const QImage& src) {
    bool inCloneImageData = true;
    switch (src.format()) {
    case QImage::Format_RGB32: {
        Mat mat(src.height(), src.width(), CV_8UC4, const_cast<uchar*>(src.bits()), src.bytesPerLine());
        return (inCloneImageData ? mat.clone() : mat);
    }
    case QImage::Format_RGB888: {
        if (!inCloneImageData)
            cout << __PRETTY_FUNCTION__ << " conversion requires cloning since we use a temporary QImage";
        QImage swapped = src.rgbSwapped();
        return Mat(swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()),
            swapped.bytesPerLine()).clone();
    }
    case QImage::Format_Indexed8: {
        Mat mat(src.height(), src.width(), CV_8UC1, const_cast<uchar*>(src.bits()), src.bytesPerLine());
        return (inCloneImageData ? mat.clone() : mat);
    }
    case QImage::Format_Grayscale8: {
        Mat mat(src.height(), src.width(), CV_8UC1, const_cast<uchar*>(src.bits()), src.bytesPerLine());
        return (inCloneImageData ? mat.clone() : mat);
    }

    default:
        cerr << __PRETTY_FUNCTION__ << " QImage format not handled in switch " << src.format() << endl;
        break;
    }
    return Mat();
}

QtAndOpenCvTools::QtAndOpenCvTools() {
}

QtAndOpenCvTools::~QtAndOpenCvTools() {
}

