#include "part3.h"
#include "ui_part3.h"

Part3::Part3(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Part3)
{
	ui->setupUi(this);
	registerEvents();
}

Part3::~Part3()
{
	delete ui;
}

void Part3::registerEvents() {

	ui->btnTrainP3->setEnabled(false);
	ui->btnTestP3->setEnabled(false);
	ui->btnTestOnImgP3->setEnabled(false);
	ui->btnLoadClassifierP3->setEnabled(false);
	ui->btnSaveClassifierP3->setEnabled(false);

	QObject::connect(ui->btnLoadDataP3, SIGNAL(clicked(bool)), this, SLOT(onLoadData()));
	QObject::connect(ui->btnTrainP3, SIGNAL(clicked(bool)), this, SLOT(onTrain()));
	QObject::connect(ui->btnTestP3, SIGNAL(clicked(bool)), this, SLOT(onTest()));
	QObject::connect(ui->btnTestOnImgP3, SIGNAL(clicked(bool)), this, SLOT(onTestImage()));
	QObject::connect(ui->btnLoadClassifierP3, SIGNAL(clicked(bool)), this, SLOT(onLoadClassifier()));
	QObject::connect(ui->btnSaveClassifierP3, SIGNAL(clicked(bool)), this, SLOT(onSaveClassifier()));
	/*
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

	onLoadDataCompleted
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
	*/

	QObject::connect(this, SIGNAL(loadDataCompleted()), this, SLOT(onLoadDataCompleted()));
	QObject::connect(this, SIGNAL(trainCompleted()), this, SLOT(onTrainCompleted()));
	QObject::connect(this, SIGNAL(testCompleted(double)), this, SLOT(onTestCompleted(double)));
	QObject::connect(this, SIGNAL(testImageCompleted(unsigned int)), this, SLOT(onTestImageCompleted(unsigned int)));
	QObject::connect(this, SIGNAL(loadClassifierCompleted()), this, SLOT(onLoadClassifierCompleted()));
	QObject::connect(this, SIGNAL(saveClassifierCompleted()), this, SLOT(onSaveClassifierCompleted()));
	QObject::connect(this, SIGNAL(loadDataFailed()), this, SLOT(onLoadDataFailed()));
	QObject::connect(this, SIGNAL(trainFailed()), this, SLOT(onTrainFailed()));
	QObject::connect(this, SIGNAL(testFailed()), this, SLOT(onTestFailed()));
	QObject::connect(this, SIGNAL(testImageFailed()), this, SLOT(onTestImageFailed()));
	QObject::connect(this, SIGNAL(loadClassifierFailed()), this, SLOT(onLoadClassifierFailed()));
	QObject::connect(this, SIGNAL(saveClassifierFailed()), this, SLOT(onSaveClassifierFailed()));
}


void Part3::onLoadDataCompleted() {
	ui->btnLoadDataP3->setEnabled(true);
	ui->btnTrainP3->setEnabled(true);
	ui->btnTestP3->setEnabled(false);
	ui->btnTestOnImgP3->setEnabled(false);
	ui->btnLoadClassifierP3->setEnabled(true);
	ui->btnSaveClassifierP3->setEnabled(false);
}
void Part3::onTrainCompleted() {
	ui->btnLoadDataP3->setEnabled(true);
	ui->btnTrainP3->setEnabled(true);
	ui->btnTestP3->setEnabled(true);
	ui->btnTestOnImgP3->setEnabled(false);
	ui->btnLoadClassifierP3->setEnabled(true);
	ui->btnSaveClassifierP3->setEnabled(false);
}
void Part3::onTestCompleted(double error) {
	ui->btnLoadDataP3->setEnabled(true);
	ui->btnTrainP3->setEnabled(true);
	ui->btnTestP3->setEnabled(true);
	ui->btnTestOnImgP3->setEnabled(true);
	ui->btnLoadClassifierP3->setEnabled(true);
	ui->btnSaveClassifierP3->setEnabled(true);

	QMessageBox *msgBox = new QMessageBox();
	msgBox->setWindowTitle("Test Result");
	QString msg;
	QTextStream out(&msg);
	out << "ZeroOneLoss error = " << error;
	msgBox->setText(msg);
	msgBox->show();
}
void Part3::onTestImageCompleted(unsigned int label) {
	QString msg;
	QTextStream out(&msg);
	if (label == 0) {
		out << "Gender = Male";
	}
	else if (label == 1) {
		out << "Gender = Female";
	}

	QMessageBox *msgBox = new QMessageBox();
	msgBox->setWindowTitle("TestImage Result");
	msgBox->setText(msg);
	msgBox->show();
}
void Part3::onLoadClassifierCompleted() {

}
void Part3::onSaveClassifierCompleted() {

}
void Part3::onLoadDataFailed() {
	ui->btnLoadDataP3->setEnabled(true);
	ui->btnTrainP3->setEnabled(false);
	ui->btnTestP3->setEnabled(false);
	ui->btnTestOnImgP3->setEnabled(false);
	ui->btnLoadClassifierP3->setEnabled(true);
	ui->btnSaveClassifierP3->setEnabled(false);
}
void Part3::onTrainFailed() {
	ui->btnLoadDataP3->setEnabled(true);
	ui->btnTrainP3->setEnabled(true);
	ui->btnTestP3->setEnabled(false);
	ui->btnTestOnImgP3->setEnabled(false);
	ui->btnLoadClassifierP3->setEnabled(true);
	ui->btnSaveClassifierP3->setEnabled(false);
}
void Part3::onTestFailed() {
	ui->btnLoadDataP3->setEnabled(true);
	ui->btnTrainP3->setEnabled(true);
	ui->btnTestP3->setEnabled(true);
	ui->btnTestOnImgP3->setEnabled(false);
	ui->btnLoadClassifierP3->setEnabled(true);
	ui->btnSaveClassifierP3->setEnabled(false);
}
void Part3::onTestImageFailed() {

}
void Part3::onLoadClassifierFailed() {

}
void Part3::onSaveClassifierFailed() {

}



void Part3::onLoadData() {
	loadTrainData();
	loadTestData();
	emit loadDataCompleted();
}

void Part3::onTrain() {
	//editCP3, editGammeP3

	try {

		/*
			ClassificationDataset *trainData;
	ClassificationDataset *testData;
	GaussianRbfKernel <> kernel;
	CSvmTrainer<RealVector> *trainer;
	KernelClassifier<RealVector> classifier;
		*/
		bool bias = true;
		bool unconstrained = true;

		KernelClassifier<RealVector> svm;

		kernel = GaussianRbfKernel<>(0.5, unconstrained);
		trainer = new CSvmTrainer<RealVector>(&kernel, 1.0, bias, unconstrained);


		//const unsigned int K = 5;
		const unsigned int K = ui->editFoldsP3->text().toUInt(); 
		CVFolds<ClassificationDataset> folds = createCVSameSizeBalanced(*trainData, K);

		ZeroOneLoss<unsigned int> loss;
		/*
			CrossValidationError(
		FoldsType const& dataFolds,
		IParameterizable* meta,
		ModelType* model,
		TrainerType* trainer,
		CostType* cost)*/
		CrossValidationError<KernelClassifier<RealVector>, unsigned int> cvError(folds, trainer, &svm, trainer, &loss);


		JaakkolaHeuristic ja(*trainData);
		double ljg = log(ja.gamma());

		GridSearch grid; // gamma C
		//vector<double> min = { ljg - 4., 0.0 };
		//vector<double> max = { ljg + 4., 10.0 };
		//vector<size_t> sections = { 9, 11 };
		  
		double minGamma = ui->lblMinGammeP3->text().toDouble(),
			minC = ui->lblMinCP3->text().toDouble(),
			maxGamma = ui->lblMaxGammeP3->text().toDouble(),
			maxC = ui->lblMaxCP3->text().toDouble(); 

		size_t	sectionGamma = ui->lblSectionGammeP3->text().toUInt(),
			sectionC = ui->lblSectionCP3->text().toUInt(); 
		vector<double> min = { ljg - minGamma , minC }; 
		vector<double> max = { ljg - maxGamma, maxC }; 
		vector<size_t> sections = { sectionGamma, sectionC }; 
		grid.configure(min, max, sections);
		grid.step(cvError);


		trainer->setParameterVector(grid.solution().point);
		trainer->train(classifier, *trainData);
		emit trainCompleted();
	}
	catch (exception &ex) {
		cerr << ex.what() << endl;
		emit trainFailed();
	}

}
void Part3::onTest() {
	try {

		Data<unsigned int> output = classifier((*testData).inputs());
		ZeroOneLoss<unsigned int> loss;
		error = loss.eval((*testData).labels(), output);
		emit testCompleted(error);
	}
	catch (exception &ex) {
		cerr << ex.what() << endl;
		emit testFailed();
	}
}
void Part3::onTestImage() {
	try {
		QString caption = "Open Image File";
		QString dir = "C:/Users/edutilos/Pictures";
		QString fileName = QFileDialog::getOpenFileName(0, caption, dir);
		cv::Mat img = cv::imread(fileName.toStdString());
		if (img.empty()) {
			cerr << "img is empty" << endl;
			emit testImageFailed();
			return;
		}
		cv::Mat imgClone = img.clone(); 
		RealVector vector;
		cv::resize(img, img, cv::Size(30, 30));
		cout << img.cols << " , " << img.rows << endl;
		for (int i = 0; i < img.rows; ++i) {
			for (int j = 0; j < img.cols; ++j) {
				vector.push_back((double)img.at<unsigned char>(i, j));
			}
		}

		cv::Mat dst; 
		cv::cvtColor(imgClone, dst, cv::COLOR_BGR2RGB);
		QImage qImage((uchar*)dst.data, dst.cols, dst.rows, QImage::Format_RGB888);
		QPixmap pixmap = QPixmap::fromImage(qImage);
		int w = ui->lblDisplayP3->width();
		int h = ui->lblDisplayP3->height();
		ui->lblDisplayP3->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio));

		unsigned int estimatedLabel = classifier(vector);
		emit testImageCompleted(estimatedLabel);

	}
	catch (exception &ex) {
		cerr << ex.what() << endl;
		emit testImageFailed();
	}
}
void Part3::onLoadClassifier() {
	try {
		GaussianRbfKernel<> loadedKernel; // IMPORTANT!
		classifier = KernelClassifier<RealVector>(&loadedKernel);

		std::ifstream ifs("svm.model");
		boost::archive::polymorphic_text_iarchive ia(ifs);
		classifier.read(ia);
		ifs.close();
		emit loadClassifierCompleted();
	}
	catch (exception &ex) {
		cerr << ex.what() << endl;
		emit loadClassifierFailed();
	}
}
void Part3::onSaveClassifier() {
	try {
		ofstream ofs("svm.model");
		boost::archive::polymorphic_text_oarchive oa(ofs);
		classifier.write(oa);
		ofs.close();
		emit saveClassifierCompleted();
	}
	catch (exception &ex) {
		cerr << ex.what() << endl;
		emit saveClassifierFailed();
	}
}


void Part3::loadTestData() {
	testData = new ClassificationDataset();
	QString dirName = "C:/a/RUB/3 semester/anwendungsprogrammierung in c++/tag-9/material01/test";
	QDir dir(dirName);
	QVector<QString> fileNames;
	QFileInfoList list = dir.entryInfoList();
	int i = 0, upper = 20;
	foreach(QFileInfo file, list) {
		QString str;
		QTextStream out(&str);

		//int i = 0, upper = 10; //	out << file.absolutePath() << QString("/") << file.fileName()<< endl;
		if (file.fileName().endsWith(".ppm.jpg")) {
			if (i++ >= upper) continue;
			out << file.fileName();
			fileNames.append(str);
		}
	}



	vector<RealVector>  data;
	vector<unsigned int> labels;
	for (QString fileName : fileNames) {
		data.push_back(generateVector(dirName, fileName));
		labels.push_back(findLabel(dirName, fileName));
	}

	//for (auto d : data) {
	//	for (auto b : d) cout << b << ", "; 
	//	cout << endl; 
	//}

	//for (auto l : labels) {
	//	cout << l << ", "; 
	//}
	//cout << endl; 

	LabeledData<RealVector, unsigned int> lData =
		createLabeledDataFromRange(data, labels);
	testData->append(lData);

}
void Part3::loadTrainData() {
	trainData = new ClassificationDataset();
	QString dirName = "C:/a/RUB/3 semester/anwendungsprogrammierung in c++/tag-9/material01/training";
	QDir dir(dirName);
	QVector<QString> fileNames;
	QFileInfoList list = dir.entryInfoList();
	int i = 0, upper = 20;
	foreach(QFileInfo file, list) {
		QString str;
		QTextStream out(&str);


		//	out << file.absolutePath() << QString("/") << file.fileName()<< endl;
		if (file.fileName().endsWith(".ppm.jpg")) {
			if (i++ >= upper) continue;
			out << file.fileName();
			fileNames.append(str);
		}
	}



	vector<RealVector>  data;
	vector<unsigned int> labels;

	for (QString fileName : fileNames) {
		data.push_back(generateVector(dirName, fileName));
		labels.push_back(findLabel(dirName, fileName));
	}

	//for (auto l : labels) {
	//	cout << l << ", "; 
	//}
	//cout << endl; 

	cout << data.size() << ", " << labels.size() << endl;
	LabeledData<RealVector, unsigned int> lData =
		createLabeledDataFromRange(data, labels);
	trainData->append(lData);

}

unsigned int Part3::findLabel(QString dirName, QString fileName) {
	QString str;
	QTextStream out(&str);
	out << dirName << "/" << "labels" << "/" << fileName.mid(0, 5) << "/" << fileName.mid(0, 5) << ".txt";
	//cout << str.toStdString() << endl; 

	QFile file(str);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		cerr << str.toStdString() << endl;
		return -1;
	}
	QTextStream stream(&file);
	while (!stream.atEnd()) {
		QString line = stream.readLine();
		//	cout << line.toStdString() << endl; 
		QStringList splitted = line.split("=");

		if (splitted.at(0) == "gender") {
			if (splitted.at(1) == "Male") return 0;
			else if (splitted.at(1) == "Female") return 1;
		}
	}

	return -1;
}


RealVector  Part3::generateVector(QString dirName, QString fileName) {
	QString str;
	QTextStream out(&str);
	out << dirName << "/" << fileName;
	RealVector vector;
	cv::Mat img;
	img = cv::imread(str.toStdString());
	if (img.empty()) {

	}
	else {
		cv::resize(img, img, cv::Size(30, 30));
		//cout << img.cols << " , " << img.rows << endl;
		for (int i = 0; i < img.rows; ++i) {
			for (int j = 0; j < img.cols; ++j) {
				vector.push_back((double)img.at<unsigned char>(i, j));
			}
		}
	}

	return vector;
}