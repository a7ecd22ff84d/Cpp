#include "mainwindow.h"

#include <QtSfml/QtSfmlCanvas.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qsize.h>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()   
{
	delete ui;
}
