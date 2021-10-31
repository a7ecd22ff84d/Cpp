#include "QtSfmlDemo.h"

#include <cmath>

#include <QComboBox>
#include <QResizeEvent>
#include <QSlider>
#include <QSpinBox>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#include "QtSfml/QtSfmlCanvas.h"
#include "ui_QtSfmlDemo.h"

namespace Visualization
{
const auto backgroundSize = 600.0f;
const auto workAreaSize = 1000.0f;
const auto boundariesThickness = -5.0f;

QtSfmlDemo::QtSfmlDemo(const Qsd::DemoContext& context)
	: BaseDemo(context)
	, ui(new Ui::QtSfmlDemo)
{
	ui->setupUi(this);

	displayTimer->setInterval(std::chrono::milliseconds(1000 / 60));
	connect(displayTimer, &QTimer::timeout, this, &QtSfmlDemo::update);

	connect(ui->resetButton, &QPushButton::clicked, this, &QtSfmlDemo::resetView);
	ui->rectBackground->setChecked(true);

	initResizeControls();
	initZoomControls();
	initViewAreaControls();

	initBackground();
	initViewAreaBoundaries();
	initAntiAliasingBackground();
}

QtSfmlDemo::~QtSfmlDemo()
{
	delete ui;
}

void QtSfmlDemo::run()
{
	canvas->setResizingPolicy(QtSfml::ResizingPolicy::keepAspectRato);
	updateViewArea();
	displayTimer->start();
}

auto QtSfmlDemo::getDescription() const -> QString
{
	return "";
}

void QtSfmlDemo::updateViewArea(int x)
{
	Q_UNUSED(x);

	sf::Vector2f centerPoint{
		static_cast<float>(ui->centerPointX->value()),
		static_cast<float>(ui->centerPointY->value())};
	sf::Vector2f viewArea{
		static_cast<float>(ui->sizeHorizontal->value()),
		static_cast<float>(ui->sizeVertical->value())};

	viewAreaBoundaries.setSize(viewArea);
	viewAreaBoundaries.setPosition(
		{centerPoint.x - viewArea.x / 2, centerPoint.y - viewArea.y / 2});

	canvas->setViewArea(viewArea, centerPoint);
}

void QtSfmlDemo::resetView()
{
	ui->zoomSlider->setValue(100);
	ui->zoomSlider->sliderMoved(100);
	ui->sizeHorizontal->setValue(backgroundSize);
	ui->sizeVertical->setValue(backgroundSize);
	ui->centerPointX->setValue(backgroundSize / 2);
	ui->centerPointY->setValue(backgroundSize / 2);
}

void QtSfmlDemo::initResizeControls()
{
	ui->resizeTypeCombo->addItem(
		"Keep aspect ratio",
		QVariant::fromValue(QtSfml::ResizingPolicy::keepAspectRato));
	ui->resizeTypeCombo->addItem(
		"Keep zoom level",
		QVariant::fromValue(QtSfml::ResizingPolicy::keepZoomLevel));
	ui->resizeTypeCombo->addItem(
		"Stretch", QVariant::fromValue(QtSfml::ResizingPolicy::stretch));

	connect(
		ui->resizeTypeCombo,
		QOverload<int>::of(&QComboBox::currentIndexChanged),
		[&](int index) {
			auto data = ui->resizeTypeCombo->currentData();
			canvas->setResizingPolicy(data.value<QtSfml::ResizingPolicy>());
			canvas->refreshViewArea();
		});
}

void QtSfmlDemo::initZoomControls()
{
	ui->zoomSlider->setMinimum(25);
	ui->zoomSlider->setMaximum(400);
	connect(ui->zoomSlider, &QSlider::sliderMoved, [&](int zoom) {
		auto zoomPercentage = zoom / 100.0;
		canvas->setZoomLevel(zoomPercentage);
		ui->zoomLabel->setText(QString("Zoom level: %1%").arg(zoom));
	});

	ui->zoomSlider->setValue(100);
	ui->zoomSlider->sliderMoved(100);
}

void QtSfmlDemo::initViewAreaControls()
{
	auto initSpinBox = [this](QSpinBox* sp, int min, int max, int initialValue) {
		sp->setMinimum(min);
		sp->setMaximum(max);
		sp->setValue(initialValue);
		sp->setSingleStep(5);

		connect(
			sp,
			QOverload<int>::of(&QSpinBox::valueChanged),
			this,
			&QtSfmlDemo::updateViewArea);
	};

	initSpinBox(ui->sizeHorizontal, workAreaSize / 10, workAreaSize, backgroundSize);
	initSpinBox(ui->sizeVertical, workAreaSize / 10, workAreaSize, backgroundSize);

	auto centerLimit = workAreaSize / 2;
	initSpinBox(ui->centerPointX, -centerLimit, centerLimit, backgroundSize / 2);
	initSpinBox(ui->centerPointY, -centerLimit, centerLimit, backgroundSize / 2);
}

void QtSfmlDemo::update()
{
	canvas->clear();

	if (ui->rectBackground->isChecked())
	{
		for (const auto& rect : background)
			canvas->draw(rect);
	}

	if (ui->antiAliasBackground->isChecked())
	{
		for (const auto& rect : antialiasingBg)
			canvas->draw(rect);
	}

	if (ui->viewAreaBoundaries->isChecked())
		canvas->draw(viewAreaBoundaries);

	canvas->display();
}

void QtSfmlDemo::initBackground()
{
	auto addRectangle = [this](float size) {
		auto& rect = background.emplace_back(sf::Vector2f{size, size});
		rect.setFillColor(sf::Color(0, 0, size / backgroundSize * 255));
		auto pos = (backgroundSize - size) / 2.0f;
		rect.setPosition({pos, pos});
	};

	addRectangle(600);
	addRectangle(500);
	addRectangle(400);
	addRectangle(300);
	addRectangle(200);
	addRectangle(100);
}

void QtSfmlDemo::initAntiAliasingBackground()
{
	auto addTriangle = [this](double startAngle, double endAngle, bool color) {
		const auto pi = 3.1416;
		const auto radius = backgroundSize / sqrt(2);
		const auto center = backgroundSize / 2;

		auto& triangle =
			antialiasingBg.emplace_back(sf::VertexArray(sf::Triangles, 3));

		triangle[0].position = {0.0f + center, 0.0f + center};

		triangle[1].position = {
			static_cast<float>(radius * cos(startAngle * pi / 180)) + center,
			static_cast<float>(radius * sin(startAngle * pi / 180)) + center};

		triangle[2].position = {
			static_cast<float>(radius * cos(endAngle * pi / 180)) + center,
			static_cast<float>(radius * sin(endAngle * pi / 180)) + center};

		if (color)
			triangle[0].color = sf::Color::White;
		else
			triangle[0].color = sf::Color::Black;

		triangle[1].color = sf::Color::Black;
		triangle[2].color = sf::Color::Black;
	};

	auto summary = 0.0;
	auto angle = 60.0;
	auto decreaseFactor = 0.835;
	bool color = true;

	while (summary < 360.0)
	{
		addTriangle(summary, summary + angle, color);
		summary += angle;
		angle = std::max(angle * decreaseFactor, 1.0);
		color = !color;
	}
}

void QtSfmlDemo::initViewAreaBoundaries()
{
	viewAreaBoundaries = sf::RectangleShape({backgroundSize, backgroundSize});
	viewAreaBoundaries.setFillColor(sf::Color::Transparent);
	viewAreaBoundaries.setOutlineThickness(boundariesThickness);
	viewAreaBoundaries.setOutlineColor(sf::Color::Red);
}

} // namespace Visualization