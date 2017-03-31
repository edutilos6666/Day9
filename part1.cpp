#include "part1.h"
#include "ui_part1.h"

Part1::Part1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Part1)
{
    ui->setupUi(this);
	registerEvents(); 
}

Part1::~Part1()
{
    delete ui;
}


void Part1::registerEvents() {
	QObject::connect(ui->btnChooseP1, SIGNAL(clicked(bool)), this, SLOT(onChooseFile()));
	QObject::connect(ui->btnDetectP1, SIGNAL(clicked(bool)), this, SLOT(onDetectFace())); 
}

void Part1::onChooseFile() {
	QString caption = "Choose Image File"; 
	QString dir = "C:/Users/edutilos/Pictures"; 
	QString fileName = QFileDialog::getOpenFileName(0, caption, dir); 
	if (fileName == "") {
		ui->btnDetectP1->setEnabled(false); 
	}
	else {
		ui->btnDetectP1->setEnabled(true); 
		img = cv::imread(fileName.toStdString()); 
		if (img.empty()) {
			cerr << "img is empty" << endl; 
			return; 
		}

	
		cv::cvtColor(img, dst, cv::COLOR_BGR2RGB);
		QImage qImage((uchar*)dst.data, dst.cols, dst.rows, QImage::Format_RGB888);
		QPixmap pixmap = QPixmap::fromImage(qImage); 
		int w = ui->lblTDisplayP1->width(); 
		int h = ui->lblTDisplayP1->height(); 
		ui->lblTDisplayP1->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio));
		//ui->lblTDisplayP1->setPixmap(pixmap); 
	}
}
void Part1::onDetectFace() {
	QString xmlFile = ui->cbP1->currentText();
	stringstream ss;
	ss << "C:/opencv/data/haarcascades/"
		<< xmlFile.toStdString();
	cv::CascadeClassifier classifier;
	classifier.load(ss.str());
	if (classifier.empty()) {
		cerr << "classifier is empty" << endl;
		return;
	}

	cv::Mat gray; 
	cv::cvtColor(img, gray, CV_BGR2RGB);
	vector<cv::Rect_<int>>  faces;
	classifier.detectMultiScale(gray, faces);

	if (faces.size() <= 0) {
		cerr << "could not find face" << endl;
		return;
	}
	cv::Mat img2;
	img2 = img.clone();
	cv::rectangle(img2, faces[faces.size() - 1], CV_RGB(255, 0, 0), 1);
	
	cv::cvtColor(img2, dst, cv::COLOR_BGR2RGB);
	QImage qImage((uchar*)dst.data, dst.cols, dst.rows, QImage::Format_RGB888);
	QPixmap pixmap = QPixmap::fromImage(qImage);
	int w = ui->lblTDisplayP1->width();
	int h = ui->lblTDisplayP1->height();
	ui->lblTDisplayP1->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio));
}