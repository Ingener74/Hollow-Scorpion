//
// Created by pavel on 17.03.16.
//

#ifndef PROJECT_CANNY_H
#define PROJECT_CANNY_H

#include <opencv2/core/core.hpp>
#include <QtGui/QImage>

class Canny {
public:
    typedef QImage result_type;

    Canny(int low = 50, int high = 150, int size = 3);
    virtual ~Canny() = default;

    QImage operator()(const cv::Mat& a);

    int low, high, size;
};

#endif //PROJECT_CANNY_H
