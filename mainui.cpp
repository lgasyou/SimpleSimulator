/*
 *	Copyright 2017 Li Zeqing
 *
 *	This file is part of World Simulator.
 *	
 *	World Simulator is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	World Simulator is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainui.h"
#include "ui_mainui.h"
#include "mapmanager.h"

#include <QPainter>
#include <QMouseEvent>

MainUI::MainUI(QWidget *parent) : 
	QWidget(parent) {
	image_ = QImage(16, 16, QImage::Format_ARGB32);
	image_.fill(qRgba(0, 0, 0, 0));

	mode_ = PaintMode::Map;

	zoom_ = 40;

	this->setMinimumSize(sizeHint());
	this->setMaximumSize(sizeHint());

	ui = new Ui::MainUI;
	ui->setupUi(this);
}

MainUI::~MainUI() {
	delete ui;
}

void MainUI::init() {
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

QSize MainUI::sizeHint() const {
	QSize size = image_.size() * zoom_;
	size += QSize(1, 1);
	return size;
}

void MainUI::setMode(int mode) {
	if (mode_ != mode) {
		mode_ = mode;
		update();
	}
}

void MainUI::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		QPoint pos = event->pos();
		int x = pos.x() / zoom_;
		int y = pos.y() / zoom_;

		if (image_.rect().contains(x, y)) {
			emit sendPosition(x, y);
		}
	}
}

void MainUI::paintEvent(QPaintEvent *event) {
	switch (mode_) {
	case PaintMode::Map:
		paintMap(event);
		break;

	case PaintMode::Building:
		paintBuilding(event);
		break;

	default:
		break;
	}


}

QRect MainUI::pixelRect(int i, int j) const {
	return QRect(zoom_ * i + 1, zoom_ * j + 1, zoom_ - 1, zoom_ - 1);
}

void MainUI::paintMap(QPaintEvent *event) {
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

void MainUI::paintBuilding(QPaintEvent *) {
	QPainter painter(this);
}
