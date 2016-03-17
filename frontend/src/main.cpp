/*
 * main.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: pavel
 */

#include <iostream>
#include <stdexcept>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

#include "MainWidget.h"

using namespace std;

int main(int argc, char **argv) {
    QApplication app { argc, argv };
    try {
        MainWidget mw;
        mw.show();
        return app.exec();
    } catch (exception const& e) {
        QMessageBox::critical(nullptr, "Error", e.what());
    }
}
