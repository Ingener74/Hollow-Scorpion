/*
 * QtAndOpenCvTools.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: pavel
 */

#include <iostream>

#include "QtAndOpenCvTools.h"

#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

/*
 QImage QtAndOpenCvTools::Mat2QImage(const cv::Mat& src) {
 Mat temp;
 cvtColor(src, temp, CV_BGR2RGB);
 QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
 dest.bits();
 return dest;
 }

 cv::Mat QtAndOpenCvTools::QImage2Mat(const QImage& src) {
 Mat tmp(src.height(), src.width(), CV_8UC3, (uchar*) src.bits(), src.bytesPerLine());
 Mat result;
 cvtColor(tmp, result, CV_BGR2RGB);
 return result;
 }
 */

QImage QtAndOpenCvTools::Mat2QImage(const cv::Mat& src) {
    switch (src.type()) {
    // 8-bit, 4 channel
    case CV_8UC4: {
        QImage image(src.data, src.cols, src.rows, src.step, QImage::Format_RGB32);
        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3: {
        QImage image(src.data, src.cols, src.rows, src.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1: {
        static QVector<QRgb> sColorTable;

        // only create our color table once
        if (sColorTable.isEmpty()) {
            for (int i = 0; i < 256; ++i)
                sColorTable.push_back(qRgb(i, i, i));
        }

        QImage image(src.data, src.cols, src.rows, src.step, QImage::Format_Indexed8);

        image.setColorTable(sColorTable);

        return image;
    }

    default:
        cerr << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << endl; // src.type();
        break;
    }

    return QImage();
}

cv::Mat QtAndOpenCvTools::QImage2Mat(const QImage& src) {
    bool inCloneImageData = true;
    switch (src.format()) {
    // 8-bit, 4 channel
    case QImage::Format_RGB32: {
        cv::Mat mat(src.height(), src.width(), CV_8UC4, const_cast<uchar*>(src.bits()), src.bytesPerLine());
        return (inCloneImageData ? mat.clone() : mat);
    }

        // 8-bit, 3 channel
    case QImage::Format_RGB888: {
        if (!inCloneImageData)
            cout << "ASM::QImageToCvMat() - Conversion requires cloning since we use a temporary QImage";
        QImage swapped = src.rgbSwapped();
        return cv::Mat(swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()),
            swapped.bytesPerLine()).clone();
    }
        // 8-bit, 1 channel
    case QImage::Format_Indexed8: {
        cv::Mat mat(src.height(), src.width(), CV_8UC1, const_cast<uchar*>(src.bits()), src.bytesPerLine());

        return (inCloneImageData ? mat.clone() : mat);
    }

    default:
        cerr << "ASM::QImageToCvMat() - QImage format not handled in switch:" << endl; // src.format();
        break;
    }

    return cv::Mat();
}

QtAndOpenCvTools::QtAndOpenCvTools() {
}

QtAndOpenCvTools::~QtAndOpenCvTools() {
}

