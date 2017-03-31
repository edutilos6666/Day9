#include "mainwindow.h"
#include <QApplication>
#include <shark/Data/Csv.h>
#include <shark/Algorithms/Trainers/LDA.h>
#include <shark/Algorithms/DirectSearch/GridSearch.h>

#include <opencv2/core.hpp>
//#include <opencv2/face.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
using namespace shark;


#include <iostream>
#include <string> 
#include <sstream>
using namespace std;

#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QFileInfoList>

void test0() {
	//create a Dataset from the file "quickstartData"
	/*if (argc < 2) {
	cerr << "usage: " << argv[0] << " (filename)" << endl;
	exit(EXIT_FAILURE);
	}*/


	string fileName = "C:/QtNew/myProjects/Day9Example1/quickstartData.csv";

	ClassificationDataset data;
	try {
		importCSV(data, fileName, LAST_COLUMN, ' ');
	}
	catch (...) {
		cerr << "unable to read data from file " << fileName << endl;
		exit(EXIT_FAILURE);
	}

	//create a test and training partition of the data
	ClassificationDataset test = splitAtElement(data, static_cast<std::size_t>(0.8*data.numberOfElements()));

	//create a classifier for the problem
	LinearClassifier<> classifier;
	//create the lda trainer
	LDA lda;
	//train the classifier using the training portion of the Data
	lda.train(classifier, data);


	//classifier.save(); 

	//now use the test data to evaluate the model
	//loop over all points of the test set
	//be aware that in this example a single point consists of an input and a label
	//this code here is just for illustration purposes
	unsigned int correct = 0;
	for (auto point : test.elements()) {
		unsigned int result = classifier(point.input);
		if (result == point.label) {
			correct++;
		}
	}
	//print results
	cout << "RESULTS: " << endl;
	cout << "========\n" << endl;
	cout << "test data size: " << test.numberOfElements() << endl;
	cout << "correct classification: " << correct << endl;
	cout << "error rate: " << 1.0 - double(correct) / test.numberOfElements() << endl;
}


string fileName = "C:/QtNew/myProjects/Day9Example1/quickstartData.csv";
void test2() {
	//string fileName = "C:/QtNew/myProjects/Day9Example1/quickstartData.csv";

	ClassificationDataset data;
	try {
		importCSV(data, fileName, LAST_COLUMN, ' ');
	}
	catch (exception &ex) {
		cerr << ex.what() << endl;
		exit(EXIT_FAILURE);
	}

	ClassificationDataset test = splitAtElement(data, static_cast<size_t>(0.8* data.numberOfElements()));

	LinearClassifier <> classifier;
	LDA trainer;
	trainer.train(classifier, data);

	int correct = 0;

	for (auto elem : test.elements()) {
		unsigned int expected = elem.label;
		unsigned int predicted = classifier(elem.input);
		if (expected == predicted)  correct++;
	}


	cout << "Number of test elements  = " << test.numberOfElements() << endl
		<< "Number of correct predictions = " << correct << endl
		<< "Error Rate = " << (1.0 - (double)correct / test.numberOfElements()) << endl;

}




void test3() {
	ClassificationDataset data;

	try {
		importCSV(data, fileName, LAST_COLUMN, ' ');
	}
	catch (exception &ex) {
		cerr << ex.what() << endl;
		exit(EXIT_FAILURE);
	}

	//0.2 of data for test, 0.8 for training 
	ClassificationDataset test = splitAtElement(data, static_cast<size_t>(0.8* data.numberOfElements()));
	//classifier 
	LinearClassifier <> classifier;
	//trainer 
	LDA lda;
	lda.train(classifier, data);

	int correct = 0;
	for (auto elem : test.elements()) {
		unsigned int actual = elem.label;
		unsigned int predicted = classifier(elem.input);
		if (predicted == actual)
			correct++;
	}


	cout << "Number of trained data = " << data.numberOfElements() << endl
		<< "Number of test data = " << test.numberOfElements() << endl
		<< "Number of correct predictions = " << correct << endl
		<< "Error rate = " << (1.0 - correct / (double)test.numberOfElements())
		<< endl;
}


void testOpenCVFace() {
	cv::String fileName = "C:/Users/edutilos/Pictures/person4.ppm.jpg";
	cv::Mat img = cv::imread(fileName);
	if (img.empty()) {
		cerr << "img is empty" << endl;
		return;
	}
	cv::CascadeClassifier classifier;
	cv::String haarFile = "C:/opencv/data/haarcascades/haarcascade_frontalface_default.xml";
	classifier.load(haarFile);
	vector<cv::Rect_<int>>  faces;
	cv::Mat gray;
	cv::cvtColor(img, gray, CV_BGR2GRAY);
	classifier.detectMultiScale(gray, faces);
	cout << "faces size = " << faces.size() << endl;
	for (int i = 0; i < faces.size(); ++i) {
		cv::rectangle(img, faces[faces.size() - 1], CV_RGB(0, 255, 0), 1);
	}

	cv::imshow("face", img);
	cv::waitKey(2000);
}

void testFace2() {
	string baseDirFaces = "C:/Users/edutilos/Pictures/";
	string baseDirXml = "C:/opencv/data/haarcascades/";

	vector<string> faces;

	for (int i = 0; i < 4; ++i) {
		stringstream ss;
		ss << baseDirFaces << "person" << (i + 1) << ".ppm.jpg";
		string path = ss.str();
		ss.flush();

		cout << path << endl;
		faces.push_back(path);
	}

	cv::String xml = baseDirXml + "haarcascade_frontalface_default.xml";
	//cv::String xml = baseDirXml + "haarcascade_frontalface_alt_tree.xml"; 
	cv::CascadeClassifier classifier;
	classifier.load(xml);
	if (classifier.empty()) {
		cerr << "classifier is empty" << endl;
		exit(EXIT_FAILURE);
	}

	cout << faces.size() << endl;

	for (int i = 0; i < 4; ++i) {
		cv::Mat img = cv::imread(faces[i]);

		if (img.empty()) {
			cerr << "img is empty" << endl;
			exit(EXIT_FAILURE);
		}


		cv::Mat gray;
		cv::cvtColor(img, gray, CV_BGR2RGB);

		vector<cv::Rect_<int>> detections;
		classifier.detectMultiScale(gray, detections);
		if (detections.size() == 0) {
			cout << "could not detect face" << endl;
			continue;
		}
		cv::Rect_<int> lastOne = detections[detections.size() - 1];
		cv::rectangle(img, lastOne, CV_RGB(255, 0, 0), 2);
		//cv::resize(img, img, cv::Size(30, 30), 1.0, 1.0, CV_INTER_CUBIC);
		cv::imshow("Detections", img);
		cv::waitKey(2000);
	}


}

int testMainWindow(int argc , char *argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}


void testLoadFiles() {
	QString dirName = "C:/a/RUB/3 semester/anwendungsprogrammierung in c++/tag-9/material01/training"; 
	QDir dir(dirName);
	QFileInfoList list = dir.entryInfoList(); 
	foreach(QFileInfo file, list) {
		cout << file.absolutePath().toStdString() <<  "/" << file.fileName().toStdString() <<  endl; 
	}

}
int main(int argc, char *argv[])
{ 
	int res = 0; 
	res = testMainWindow(argc, argv); 
	//testLoadFiles(); 
	return res ; 
}
