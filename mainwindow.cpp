#include "mainwindow.h"

MainWindow::MainWindow():
    QMainWindow(0)
{
   configureWindow();
   addWidgets();
   registerEvents();
}

MainWindow::~MainWindow()
{

}



void MainWindow::configureWindow()
{
   this->resize(600, 600);
    this->setWindowTitle("Day9");

}

void MainWindow::addWidgets()
{
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    layout = new QVBoxLayout();
    centralWidget->setLayout(layout);
    pageChanger = new QComboBox();
    pageChanger->addItem("Part 1");
    pageChanger->addItem("Part 2");
    pageChanger->addItem("Part 3");
    layout->addWidget(pageChanger);

     stackedWidget = new QStackedWidget();
//     this->setCentralWidget(stackedWidget);
     layout->addWidget(stackedWidget);
   part1 = new Part1();
   stackedWidget->insertWidget(0, part1);
   part2 = new Part2();
   stackedWidget->insertWidget(1, part2);
   part3 = new Part3();
   stackedWidget->insertWidget(2, part3);
}

void MainWindow::registerEvents()
{
    QObject::connect(pageChanger, SIGNAL(activated(int)), stackedWidget, SLOT(setCurrentIndex(int)));
}
