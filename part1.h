#ifndef PART1_H
#define PART1_H

#include <QWidget>
#include <opencv2/core.hpp>
//#include <opencv2/face.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include <QString>
#include <string>
#include <iostream>
#include <QFileDialog>
#include <sstream> 
#include <string>
#include <vector>
#include <QImage>
#include <QPixmap>
using namespace std; 

namespace Ui {
class Part1;
}

class Part1 : public QWidget
{
    Q_OBJECT

public:
    explicit Part1(QWidget *parent = 0);
    ~Part1();
	void registerEvents(); 

public slots: 
void onChooseFile(); 
void onDetectFace(); 
private:
    Ui::Part1 *ui;
	cv::Mat img; 
	cv::Mat dst; 
};

#endif // PART1_H
