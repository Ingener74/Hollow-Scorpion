//
// Created by pavel on 17.03.16.
//

#ifndef PROJECT_MEDIAN_H
#define PROJECT_MEDIAN_H

#include <opencv2/core/core.hpp>
#include <QtGui/QImage>

class Median {
public:
    typedef QImage result_type;

    Median(int size = 3);
    virtual ~Median() = default;

    QImage operator()(const cv::Mat& a);

    int size;
};

#endif //PROJECT_MEDIAN_H
