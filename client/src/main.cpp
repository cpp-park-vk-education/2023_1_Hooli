//
// Created by Алексей on 01.05.2023.
//

#include "mainwindow.h"
#include <QApplication>
#include <iostream>


int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;

  w.show();
  return a.exec();
}
