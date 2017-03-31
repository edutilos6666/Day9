#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "part1.h"
#include "part2.h"
#include "part3.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QWidget>
class MainWindow: public QMainWindow
{
public:
    MainWindow();
    ~MainWindow();
    void configureWindow();
    void addWidgets();
    void registerEvents();
signals:
public slots:
public:
    Part1 *part1;
    Part2 *part2;
    Part3 *part3;
    QStackedWidget *stackedWidget;
    QWidget *centralWidget ;
    QVBoxLayout *layout ;
    QComboBox *pageChanger;
};

#endif // MAINWINDOW_H
