/*
 * MainWidget.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: pavel
 */

#include <iostream>

#include <QtGui/QKeyEvent>

#include "MainWidget.h"

using namespace std;

MainWidget::MainWidget(QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent, f) {
    setupUi(this);

    QObject::connect(openImagePushButton, &QPushButton::clicked, this, &MainWidget::onOpenButton);
}

MainWidget::~MainWidget() {
}

void MainWidget::closeEvent(QCloseEvent*) {
}

void MainWidget::showEvent(QShowEvent*) {
//    saltPepperGraphicsView->setBa
}

void MainWidget::keyPressEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Escape) {
        close();
    }
}

void MainWidget::onOpenButton() {
    cout << "test" << endl;
}
