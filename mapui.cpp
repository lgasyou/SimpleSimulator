#include "mapui.h"
#include "ui_mapui.h"
#include "mapmanager.h"

#include <QPainter>
#include <QMouseEvent>

MapUI::MapUI(QWidget *parent) : 
	QWidget(parent) {
	image_ = QImage(16, 16, QImage::Format_ARGB32);
	image_.fill(qRgba(0, 0, 0, 0));

	zoom_ = 40;

	this->setMinimumSize(sizeHint());
	this->setMaximumSize(sizeHint());

	ui = new Ui::MapUI;
	ui->setupUi(this);
}

MapUI::~MapUI() {
	delete ui;
}

void MapUI::init() {
	auto map = MapManager::instance().occupiedMap();
	QColor penColor = Qt::black;
	for (int i = 0; i != 16; ++i) {
		for (int j = 0; j != 16; ++j) {
			if (map[i][j]) {
				image_.setPixel(i, j, penColor.rgba());
			}
		}
	}
}

QSize MapUI::sizeHint() const {
	QSize size = image_.size() * zoom_;
	size += QSize(1, 1);
	return size;
}

void MapUI::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		QPoint pos = event->pos();
		int x = pos.x() / zoom_;
		int y = pos.y() / zoom_;

		if (image_.rect().contains(x, y)) {
			emit sendPosition(x, y);
		}
	}
}

void MapUI::paintEvent(QPaintEvent *event) {
	QPainter painter(this);

	for (int i = 0; i <= image_.width(); ++i)
		painter.drawLine(zoom_ * i, 0,
			zoom_ * i, zoom_ * image_.height());
	for (int j = 0; j <= image_.height(); ++j)
		painter.drawLine(0, zoom_ * j,
			zoom_ * image_.width(), zoom_ * j);

	for (int i = 0; i != image_.width(); ++i) {
		for (int j = 0; j != image_.height(); ++j) {
			QRect rect = pixelRect(i, j);
			if (!event->region().intersected(rect).isEmpty()) {
				QColor color = QColor::fromRgba(image_.pixel(i, j));
				painter.fillRect(rect, color);
			}
		}
	}
}

QRect MapUI::pixelRect(int i, int j) const {
	return QRect(zoom_ * i + 1, zoom_ * j + 1, zoom_ - 1, zoom_ - 1);
}
