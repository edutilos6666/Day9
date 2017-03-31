#ifndef PART3_H
#define PART3_H

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
#include <shark/Data/CVDatasetTools.h>
#include <shark/ObjectiveFunctions/CrossValidationError.h>
#include <shark/Algorithms/JaakkolaHeuristic.h>
#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <shark/Algorithms/Trainers/AbstractTrainer.h>
#include <shark/Algorithms/AbstractSingleObjectiveOptimizer.h>
#include <shark/ObjectiveFunctions/AbstractCost.h>
namespace Ui {
	class Part3;
}

class Part3 : public QWidget
{
	Q_OBJECT

public:
	explicit Part3(QWidget *parent = 0);
	~Part3();
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
	Ui::Part3 *ui;
	ClassificationDataset *trainData;
	ClassificationDataset *testData;
	GaussianRbfKernel <> kernel;
	CSvmTrainer<RealVector> *trainer;
	KernelClassifier<RealVector> classifier;
	double  error;
};

#endif // PART3_H
