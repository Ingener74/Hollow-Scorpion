/*
 * MainWidget.h
 *
 *  Created on: Mar 17, 2016
 *      Author: pavel
 */

#ifndef FRONTEND_SRC_MAINWIDGET_H_
#define FRONTEND_SRC_MAINWIDGET_H_

#include <memory>

#include <opencv2/core/core.hpp>

#include <QtWidgets/QWidget>
#include <QtCore/QFutureWatcher>
#include <QtGui/QImage>

#include "ui_mainwidget.h"

class MainWidget: public QWidget, public Ui_MainWidget {
    Q_OBJECT
public:
    MainWidget(const std::string& filename = {}, QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~MainWidget();

    virtual void showEvent(QShowEvent *);
    virtual void closeEvent(QCloseEvent *);
    virtual void keyPressEvent(QKeyEvent *);

private:
    cv::Mat _input;
    std::unique_ptr<QFutureWatcher<QImage>> _medianFuture;
    std::unique_ptr<QFutureWatcher<QImage>> _cannyFuture;

    int _enableOpen;

public slots:
    void onOpenButton();

    void recalcMedian();
    void recalcMedian(int){ recalcMedian(); }
    void showSaltPepper(int);
    void saveMedian();
    QImage median(const cv::Mat&, int size);

    void recalcCanny();
    void recalcCanny(int){ recalcCanny(); }
    void showCanny(int);
    void saveCanny();
    QImage canny(const cv::Mat &, int low, int high, int size);
};

#endif /* FRONTEND_SRC_MAINWIDGET_H_ */
