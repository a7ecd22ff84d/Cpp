#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeControls.h"

#include "ui_MazeControls.h"

MazeControls::MazeControls(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::MazeControls)
{
	ui->setupUi(this);
}

MazeControls::~MazeControls()
{
	delete ui;
}
