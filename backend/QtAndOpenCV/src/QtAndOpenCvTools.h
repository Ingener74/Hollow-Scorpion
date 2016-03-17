/*
 * QtAndOpenCvTools.h
 *
 *  Created on: Mar 17, 2016
 *      Author: pavel
 */

#ifndef BACKEND_QTANDOPENCV_SRC_QTANDOPENCVTOOLS_H_
#define BACKEND_QTANDOPENCV_SRC_QTANDOPENCVTOOLS_H_

#include <QtGui/QImage>
#include <opencv2/core/core.hpp>

class QtAndOpenCvTools {
public:
    static QImage Mat2QImage(const cv::Mat &src);

    static cv::Mat QImage2Mat(const QImage &src);

    QtAndOpenCvTools();

    virtual ~QtAndOpenCvTools();
};

#endif /* BACKEND_QTANDOPENCV_SRC_QTANDOPENCVTOOLS_H_ */
