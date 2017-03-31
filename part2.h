#ifndef PART2_H
#define PART2_H

#include <QWidget>
#include <shark/Data/Csv.h>
#include <shark/Algorithms/Trainers/LDA.h>
#include <shark/Algorithms/DirectSearch/GridSearch.h>
using namespace shark; 
#include <iostream>
#include <string>
#include <memory>
using namespace std; 

#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QFileInfoList>
#include <QVector>
#include <QTextStream>

#include <opencv2/core.hpp>
//#include <opencv2/face.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include <shark/Models/Kernels/GaussianRbfKernel.h>
#include <shark/Algorithms/Trainers/CSvmTrainer.h>
#include <shark/Models/Kernels/KernelExpansion.h>
#include <shark/ObjectiveFunctions/Loss/ZeroOneLoss.h>

#include <QFileDialog>
#include <fstream>
#include <QMessageBox>

namespace Ui {
class Part2;
}

class Part2 : public QWidget
{
    Q_OBJECT

public:
    explicit Part2(QWidget *parent = 0);
    ~Part2();
	void loadTestData(); 
	void loadTrainData(); 
	unsigned int findLabel(QString dirName, QString fileName); 
	RealVector generateVector(QString dirName, QString fileName); 
	void registerEvents(); 
signals: 
	void loadDataCompleted(); 
	void trainCompleted(); 
	void testCompleted(double); 
	void testImageCompleted(unsigned int); 
	void loadClassifierCompleted(); 
	void saveClassifierCompleted(); 
	void loadDataFailed();
	void trainFailed();
	void testFailed();
	void testImageFailed();
	void loadClassifierFailed();
	void saveClassifierFailed();

	public slots :
    void onLoadData(); 
	void onTrain(); 
	void onTest(); 
	void onTestImage(); 
	void onLoadClassifier(); 
	void onSaveClassifier(); 
	void onLoadDataCompleted();
	void onTrainCompleted();
	void onTestCompleted(double);
	void onTestImageCompleted(unsigned int);
	void onLoadClassifierCompleted();
	void onSaveClassifierCompleted();
	void onLoadDataFailed();
	void onTrainFailed();
	void onTestFailed();
	void onTestImageFailed();
	void onLoadClassifierFailed();
	void onSaveClassifierFailed();

private:
    Ui::Part2 *ui;
	ClassificationDataset *trainData;
	ClassificationDataset *testData;
	GaussianRbfKernel <> kernel;
	CSvmTrainer<RealVector> *trainer; 
	KernelClassifier<RealVector> classifier; 
	double  error; 
};

#endif // PART2_H
