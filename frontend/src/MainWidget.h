/*
 * MainWidget.h
 *
 *  Created on: Mar 17, 2016
 *      Author: pavel
 */

#ifndef FRONTEND_SRC_MAINWIDGET_H_
#define FRONTEND_SRC_MAINWIDGET_H_

#include <QtWidgets/QWidget>

#include "ui_mainwidget.h"

class MainWidget: public QWidget, public Ui_MainWidget {
public:
    MainWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~MainWidget();

    virtual void showEvent(QShowEvent *);
    virtual void closeEvent(QCloseEvent *);
    virtual void keyPressEvent(QKeyEvent *);

public slots:
    void onOpenButton();
};

#endif /* FRONTEND_SRC_MAINWIDGET_H_ */
