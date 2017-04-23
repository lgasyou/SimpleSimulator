/*
 *  Copyright 2017 Li Zeqing
 *
 *  This file is part of World Simulator.
 *  
 *  World Simulator is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  World Simulator is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAPUI_H
#define MAPUI_H

#include <QWidget>
#include <QImage>

namespace Ui { 
class MainUI; 
}

class MainUI : public QWidget {
    Q_OBJECT

public:
    MainUI(QWidget *parent = nullptr);

    ~MainUI();

    enum PaintMode{ Map, Building };

    // TODO: Reset colors of Map Node.
    void init();

    QSize sizeHint() const;

    void setImage(const QImage &image) { this->image_ = image; }
    const QImage &image() const { return image_; }

    void setMode(int mode);

    void setZoom(int zoom) { this->zoom_ = zoom; }
    int zoom() const { return zoom_; }

signals:
    void sendPosition(int x, int y);

protected:
    void mousePressEvent(QMouseEvent *) override;

    void paintEvent(QPaintEvent *)      override;

private:
    QRect pixelRect(int i, int j) const;

    void paintMap(QPaintEvent *);

    void paintBuilding(QPaintEvent *);

private:
    QImage image_;

    int mode_;

    int zoom_;

    Ui::MainUI *ui;
};

#endif // !MAPUI_H