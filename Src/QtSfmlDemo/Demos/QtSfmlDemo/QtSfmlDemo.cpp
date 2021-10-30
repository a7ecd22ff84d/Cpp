#include "QtSfmlDemo.h"

#include <QComboBox>
#include <QResizeEvent>
#include <QSlider>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "QtSfml/QtSfmlCanvas.h"
#include "ui_QtSfmlDemo.h"

namespace Visualization
{
const auto maxSize = 600.0f;

QtSfmlDemo::QtSfmlDemo(const Qsd::DemoContext& context)
	: BaseDemo(context)
	, ui(new Ui::QtSfmlDemo)
{
	ui->setupUi(this);

	displayTimer->setInterval(std::chrono::milliseconds(1000 / 60));
	connect(displayTimer, &QTimer::timeout, this, &QtSfmlDemo::update);

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

	ui->zoomSlider->setMinimum(25);
	ui->zoomSlider->setMaximum(400);
	connect(ui->zoomSlider, &QSlider::sliderMoved, [&](int zoom) {
		auto zoomPercentage = zoom / 100.0;
		canvas->setZoomLevel(zoomPercentage);
		ui->zoomLabel->setText(QString("Zoom level: %1%").arg(zoom));
	});

	ui->zoomSlider->setValue(100);
	ui->zoomSlider->sliderMoved(100);

	initBackground();
}

QtSfmlDemo::~QtSfmlDemo()
{
	delete ui;
}

void QtSfmlDemo::run()
{
	canvas->setResizingPolicy(QtSfml::ResizingPolicy::keepAspectRato);
	canvas->setViewArea({maxSize, maxSize}, {maxSize / 2, maxSize / 2});
	displayTimer->start();
}

auto QtSfmlDemo::getDescription() const -> QString
{
	return "";
}

void QtSfmlDemo::update()
{
	canvas->clear();

	for (const auto& rect : background)
		canvas->draw(rect);

	canvas->display();
}

void QtSfmlDemo::initBackground()
{
	auto addRectangle = [this](float size) {
		auto& rect = background.emplace_back(sf::Vector2f{size, size});
		rect.setFillColor(sf::Color(0, 0, size / maxSize * 255));
		auto pos = (maxSize - size) / 2.0f;
		rect.setPosition({pos, pos});
	};

	addRectangle(600);
	addRectangle(500);
	addRectangle(400);
	addRectangle(300);
	addRectangle(200);
	addRectangle(100);
}

} // namespace Visualization