/*
 * MainWidget.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: pavel
 */

#include <iostream>

#include <QtGui/QKeyEvent>
#include <QtWidgets/QFileDialog>
#include <QtConcurrent/QtConcurrentMap>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "MainWidget.h"

using namespace std;
using namespace cv;

QImage Mat2QImage(const Mat& src)
{
     Mat temp;
     cvtColor(src, temp,CV_BGR2RGB);
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits();
     return dest;
}

Mat QImage2Mat(const QImage& src)
{
     Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     Mat result;
     cvtColor(tmp, result,CV_BGR2RGB);
     return result;
}

class Median {
public:
    typedef QImage result_type;

    Median(int size = 3) :
        size(size) {
    }
    virtual ~Median() = default;

    QImage operator()(const QString& fileName) {
        try {
            Mat a = QImage2Mat(QImage(fileName)), b, c, d;
            cvtColor(a, b, CV_RGB2GRAY);
            medianBlur(b, c, size);
            cvtColor(c, d, CV_GRAY2RGB);
            return Mat2QImage(d);
        } catch (const exception& e) {
            cerr << "median error: " << e.what() << endl;
            return QImage(":/error.png");
        }
    }

    int size;
};

class Canny {
public:
    typedef QImage result_type;

    Canny(int low = 50, int high = 150, int size = 3) :
        low(low), high(high), size(size) {
    }
    virtual ~Canny() = default;

    QImage operator()(const QString& fileName) {
        try {
            Mat a = QImage2Mat(QImage(fileName)), b, c;

            Mat gray, edge, draw;
            cvtColor(a, gray, CV_RGB2GRAY);

            cv::Canny(gray, edge, low, high, size);

//            edge.convertTo(draw, CV_8U);

            cvtColor(edge, draw, CV_GRAY2RGB);

//            Mat out;
//            cvtColor(draw, out, CV_GRAY2RGB);

            return Mat2QImage(draw);
        } catch (const exception& e) {
            cerr << "canny error: " << e.what() << endl;
            return QImage(":/error.png");
        }
    }

    int low, high, size;
};

MainWidget::MainWidget(const string& fileName, QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    setupUi(this);

    connect(openImagePushButton, SIGNAL(clicked()), SLOT(onOpenButton()));
    connect(saltPepperSpinBox, SIGNAL(editingFinished()), SLOT(recalcMedian()));
    connect(lowThresholdSlider, SIGNAL(sliderReleased()), SLOT(recalcCanny()));
    connect(highThresholdSlider, SIGNAL(sliderReleased()), SLOT(recalcCanny()));

    _medianFuture.reset(new QFutureWatcher<QImage>(this));
    connect(_medianFuture.get(), SIGNAL(resultReadyAt(int)), SLOT(showSaltPepper(int)));
    connect(_medianFuture.get(), SIGNAL(finished()), SLOT(saltPepperFinished()));

    _cannyFuture.reset(new QFutureWatcher<QImage>(this));
    connect(_cannyFuture.get(), SIGNAL(resultReadyAt(int)), SLOT(showCanny(int)));
    connect(_cannyFuture.get(), SIGNAL(finished()), SLOT(cannyFinished()));

    if(!fileName.empty()){
        _fileName = QString::fromStdString(fileName);
        _input = QImage(_fileName);
    }
}

MainWidget::~MainWidget() {
}

void MainWidget::closeEvent(QCloseEvent*) {
}

void MainWidget::showEvent(QShowEvent*) {
    if (_fileName.isEmpty()) {
        saltPepperInputLabel->setPixmap(QPixmap::fromImage(QImage(":/no-image.png")));
        saltPepperOutputLabel->setPixmap(QPixmap::fromImage(QImage(":/no-image.png")));

        cannyInputLabel->setPixmap(QPixmap::fromImage(QImage(":/no-image.png")));
        cannyOutputLabel->setPixmap(QPixmap::fromImage(QImage(":/no-image.png")));
    } else {
        recalcMedian();
        recalcCanny();
    }
}

void MainWidget::keyPressEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Escape) {
        close();
    }
}

void MainWidget::onOpenButton() {
    _fileName = QFileDialog::getOpenFileName(nullptr, "Open image file", "/home", "Images (*.png *.xpm *.jpg)");
    _input = QImage(_fileName);
    recalcMedian();
    recalcCanny();
}

void MainWidget::recalcMedian() {
    QStringList files;
    files << _fileName;
    Median median(saltPepperSpinBox->value());
    _medianFuture->setFuture(QtConcurrent::mapped(files, median));
}

void MainWidget::showSaltPepper(int int1) {
    saltPepperInputLabel->setPixmap(QPixmap::fromImage(_input));
    saltPepperOutputLabel->setPixmap(QPixmap::fromImage(_medianFuture->resultAt(int1)));
}

void MainWidget::saltPepperFinished() {
}

void MainWidget::recalcCanny() {
    QStringList files;
    files << _fileName;
    ::Canny canny(lowThresholdSlider->value(), highThresholdSlider->value(), cannySpinBox->value());
    _cannyFuture->setFuture(QtConcurrent::mapped(files, canny));
}

void MainWidget::showCanny(int int1) {
    cannyInputLabel->setPixmap(QPixmap::fromImage(_input));
    cannyOutputLabel->setPixmap(QPixmap::fromImage(_cannyFuture->resultAt(int1)));
}

void MainWidget::cannyFinished() {
}
