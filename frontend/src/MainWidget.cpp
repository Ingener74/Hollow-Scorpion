/*
 * MainWidget.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: pavel
 */

#include <iostream>

#include <QtGui/QKeyEvent>
#include <QtConcurrent/QtConcurrentMap>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "QtAndOpenCvTools.h"

#include "MainWidget.h"

using namespace std;
using namespace cv;

MainWidget::MainWidget(const string& fileName, QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    setupUi(this);

    connect(openImagePushButton, SIGNAL(clicked()), SLOT(onOpenButton()));

    connect(saltPepperSpinBox, SIGNAL(editingFinished()), SLOT(recalcMedian()));
    connect(saltPepperSpinBox, SIGNAL(valueChanged(int)), SLOT(recalcMedian(int)));

    connect(lowThresholdSlider, SIGNAL(sliderReleased()), SLOT(recalcCanny()));
    connect(highThresholdSlider, SIGNAL(sliderReleased()), SLOT(recalcCanny()));
    connect(cannySpinBox, SIGNAL(editingFinished()), SLOT(recalcCanny()));
    connect(cannySpinBox, SIGNAL(valueChanged(int)), SLOT(recalcCanny(int)));

    connect(saveSaltAntPepperPushButton, SIGNAL(clicked()), SLOT(saveMedian()));
    connect(saveContourPushButton, SIGNAL(clicked()), SLOT(saveCanny()));

    saveSaltAntPepperPushButton->setEnabled(false);
    saveContourPushButton->setEnabled(false);

    saltPepperSpinBox->setEnabled(false);
    lowThresholdSlider->setEnabled(false);
    highThresholdSlider->setEnabled(false);
    cannySpinBox->setEnabled(false);

    _medianFuture.reset(new QFutureWatcher<QImage>(this));
    connect(_medianFuture.get(), SIGNAL(resultReadyAt(int)), SLOT(showSaltPepper(int)));

    _cannyFuture.reset(new QFutureWatcher<QImage>(this));
    connect(_cannyFuture.get(), SIGNAL(resultReadyAt(int)), SLOT(showCanny(int)));

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
        _enableOpen = 2;
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
    auto fileName = QFileDialog::getOpenFileName(nullptr, "Open image file", "/home", "Images (*.png *.xpm *.jpg *.bmp)");
    if(fileName.isEmpty())
        return;
    _input = QtAndOpenCvTools::QImage2Mat(QImage(fileName));
    
    openImagePushButton->setEnabled(false);
    saveSaltAntPepperPushButton->setEnabled(false);
    saveContourPushButton->setEnabled(false);
    _enableOpen = 2;
    recalcMedian();
    recalcCanny();
}

void MainWidget::recalcMedian() {
    _medianFuture->setFuture(QtConcurrent::mapped(QList<Mat>{} << _input,
                                                  std::bind(&MainWidget::median, this, std::placeholders::_1,
                                                            saltPepperSpinBox->value())));
}

void MainWidget::showSaltPepper(int int1) {
    saltPepperInputLabel->setPixmap(QPixmap::fromImage(_input.empty() ? QImage(":/error.png") : QtAndOpenCvTools::Mat2QImage(_input)));
    saltPepperOutputLabel->setPixmap(QPixmap::fromImage(_medianFuture->resultAt(int1)));
    saveSaltAntPepperPushButton->setEnabled(true);
    saltPepperSpinBox->setEnabled(true);
    if(!--_enableOpen)
        openImagePushButton->setEnabled(true);
}

void MainWidget::recalcCanny() {
    _cannyFuture->setFuture(QtConcurrent::mapped(QList<Mat>{} << _input,
                                                 std::bind(&MainWidget::canny, this, std::placeholders::_1,
                                                           lowThresholdSlider->value(), highThresholdSlider->value(),
                                                           cannySpinBox->value())));
}

void MainWidget::showCanny(int int1) {
    cannyInputLabel->setPixmap(QPixmap::fromImage(_input.empty() ? QImage(":/error.png") : QtAndOpenCvTools::Mat2QImage(_input)));
    cannyOutputLabel->setPixmap(QPixmap::fromImage(_cannyFuture->resultAt(int1)));
    saveContourPushButton->setEnabled(true);
    lowThresholdSlider->setEnabled(true);
    highThresholdSlider->setEnabled(true);
    cannySpinBox->setEnabled(true);
    if(!--_enableOpen)
        openImagePushButton->setEnabled(true);
}

void MainWidget::saveMedian() {
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save median image", "/home", "Png (*.png)");
    if(fileName.isEmpty())
        return;
    saltPepperOutputLabel->pixmap()->save(fileName + ".png", "PNG", 100);
}

void MainWidget::saveCanny() {
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save canny image", "/home", "Png (*.png)");
    if(fileName.isEmpty())
        return;
    cannyOutputLabel->pixmap()->save(fileName + ".png", "PNG", 100);
}

QImage MainWidget::median(const cv::Mat & a, int size) {
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

QImage MainWidget::canny(const cv::Mat &a, int low, int high, int size) {
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

