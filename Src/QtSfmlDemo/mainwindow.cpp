#include "QtSfmlDemo/mainwindow.h"

#include <memory>
#include <string_view>

#include <QAction>
#include <qmessagebox.h>
#include <qwidget.h>

#include "./ui_mainwindow.h"
#include "QtSfmlDemo/AboutDialog.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeProgram.h"
#include "QtSfmlDemo/Demos/Init/InitProgram.h"
#include "QtSfmlDemo/Demos/TestApp/TestDemo.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	context.controlsWidget = ui->controlsWidget;
	context.canvas = ui->sfmlWindow;
	context.statusBar = ui->statusbar;
	context.timer = &timer;

	connect(ui->actionClose, &QAction::triggered, this, &MainWindow::close);

	connect(
		ui->actionAbout_current_algorithm,
		&QAction::triggered,
		this,
		&MainWindow::aboutCurrentProgram);

	connect(
		ui->actionAbout_this_program,
		&QAction::triggered,
		this,
		&MainWindow::aboutThisProgram);

	registerDemos();
	reset("Maze generator");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::aboutCurrentProgram()
{
	Qsd::AboutDialog* about =
		new Qsd::AboutDialog(this, currentProgram->getDescription());
	about->show();
}

void MainWindow::aboutThisProgram()
{
	auto text = R"(
<h2>QtSfmlDemo</h2>
<p>Simple program created to visualize different algorithms or other stuff I'd like to show.<br />Algorithm menu contains different algorithms implemented in program.<br />Demo menu will contain more interactive things like simple games or other projects made in SFML that does't exactly match algorithm section.</p>
<p>&nbsp;</p>
<h3>External libraries used</h3>
<ul>
<li><strong>Qt5</strong> - <a href="https://www.qt.io/">https://www.qt.io/</a></li>
<li><strong>SFML</strong> - <a href="https://www.sfml-dev.org/">https://www.sfml-dev.org/</a></li>
<li><strong>QSLite</strong> - <a href="https://sqlite.org/index.html">https://sqlite.org/index.html</a></li>
<li><strong>Date</strong> -&nbsp; <a href="https://github.com/HowardHinnant/date">https://github.com/HowardHinnant/date</a></li>
<li><strong>{fmt}</strong> - <a href="https://github.com/fmtlib/fmt">https://github.com/fmtlib/fmt</a></li>
<li><strong>GoogleTest</strong> - <a href="https://github.com/google/googletest">https://github.com/google/googletest</a></li>
</ul>)";

	Qsd::AboutDialog* about = new Qsd::AboutDialog(this, text);
	about->show();
}

template<typename T>
void MainWindow::registerDemo(QMenu* menu, std::string_view name)
{
	demoFactory.registerType(name, [&]() -> std::unique_ptr<Qsd::BaseDemo> {
		return std::make_unique<T>(context);
	});

	auto newAction = menu->addAction(QString(name.data()));
	connect(newAction, &QAction::triggered, [this, name]() { reset(name); });
}

void MainWindow::registerDemos()
{
	registerDemo<Qsd::MazeProgram>(ui->algorithmsMenu, "Maze generator");

	registerDemo<Qsd::InitialProgram>(ui->demosMenu, "Initial program");
	registerDemo<Qsd::TestDemo>(ui->demosMenu, "Controls test");
}

void MainWindow::reset(std::string_view name)
{
	timer.disconnect();
	currentProgram = demoFactory.create(name);
	currentProgram->run();

	// ten show jest wymagany tylko i wyłącznie jeśli przełączamy
	// się między programami. Jeśli program jest wybrany jako
	// pierwszy to wszystko magicznie działa bez tego show
	currentProgram->show();
}