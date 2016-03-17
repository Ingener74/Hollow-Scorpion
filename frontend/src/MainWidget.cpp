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

#include "QtAndOpenCvTools.h"

#include "MainWidget.h"

using namespace std;
using namespace cv;

class Median {
public:
    typedef QImage result_type;

    Median(int size = 3) :
        size(size) {
    }
    virtual ~Median() = default;

    QImage operator()(const Mat& input) {
        try {
            Mat a = input, b, c, d;
            cvtColor(a, b, CV_RGB2GRAY);
            medianBlur(b, c, size);
            cvtColor(c, d, CV_GRAY2RGB);
            return QtAndOpenCvTools::Mat2QImage(d);
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

    QImage operator()(const Mat& a) {
        try {
            Mat b;
            cvtColor(a, b, CV_RGB2GRAY);

            Mat c;
            medianBlur(b, c, size);

            Mat d;
            cv::Canny(c, d, low, high, size);

            Mat e;
            cvtColor(d, e, CV_GRAY2RGB);

            return QtAndOpenCvTools::Mat2QImage(e);
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

    connect(saveSaltAntPepperPushButton, SIGNAL(clicked()), SLOT(saveMedian()));
    connect(saveContourPushButton, SIGNAL(clicked()), SLOT(saveCanny()));

    _medianFuture.reset(new QFutureWatcher<QImage>(this));
    connect(_medianFuture.get(), SIGNAL(resultReadyAt(int)), SLOT(showSaltPepper(int)));
    connect(_medianFuture.get(), SIGNAL(finished()), SLOT(saltPepperFinished()));

    _cannyFuture.reset(new QFutureWatcher<QImage>(this));
    connect(_cannyFuture.get(), SIGNAL(resultReadyAt(int)), SLOT(showCanny(int)));
    connect(_cannyFuture.get(), SIGNAL(finished()), SLOT(cannyFinished()));

    if(!fileName.empty()){
        _input = QtAndOpenCvTools::QImage2Mat(QImage(QString::fromStdString(fileName)));
    }
}

MainWidget::~MainWidget() {
}

void MainWidget::closeEvent(QCloseEvent*) {
}

void MainWidget::showEvent(QShowEvent*) {
    if (_input.empty()) {
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
    _input = QtAndOpenCvTools::QImage2Mat(QImage(QFileDialog::getOpenFileName(nullptr, "Open image file", "/home", "Images (*.png *.xpm *.jpg)")));
    recalcMedian();
    recalcCanny();
}

void MainWidget::recalcMedian() {
    QList<Mat> images;
    images << _input;
    Median median(saltPepperSpinBox->value());
    _medianFuture->setFuture(QtConcurrent::mapped(images, median));
}

void MainWidget::showSaltPepper(int int1) {
    saltPepperInputLabel->setPixmap(QPixmap::fromImage(QtAndOpenCvTools::Mat2QImage(_input)));
    saltPepperOutputLabel->setPixmap(QPixmap::fromImage(_medianFuture->resultAt(int1)));
}

void MainWidget::saltPepperFinished() {
}

void MainWidget::recalcCanny() {
    QList<Mat> images;
    images << _input;
    ::Canny canny(lowThresholdSlider->value(), highThresholdSlider->value(), cannySpinBox->value());
    _cannyFuture->setFuture(QtConcurrent::mapped(images, canny));
}

void MainWidget::showCanny(int int1) {
    cannyInputLabel->setPixmap(QPixmap::fromImage(QtAndOpenCvTools::Mat2QImage(_input)));
    cannyOutputLabel->setPixmap(QPixmap::fromImage(_cannyFuture->resultAt(int1)));
}

void MainWidget::cannyFinished() {
}

void MainWidget::saveMedian() {
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save median image", "/home", "Png (*.png)");
    saltPepperOutputLabel->pixmap()->save(fileName + ".png", "PNG", 100);
}

void MainWidget::saveCanny() {
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save canny image", "/home", "Png (*.png)");
    cannyOutputLabel->pixmap()->save(fileName + ".png", "PNG", 100);
}
