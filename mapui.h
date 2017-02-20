#ifndef MAPUI_H
#define MAPUI_H

#include <QWidget>
#include <QImage>

namespace Ui { class MapUI; }

class MapUI : public QWidget {
	Q_OBJECT

public:
	MapUI(QWidget *parent = nullptr);

	~MapUI();

	void init();

	QSize sizeHint() const;

	inline void setImage(const QImage &image) { this->image_ = image; }
	inline const QImage &image() const { return this->image_; }

	inline void setZoom(int zoom) { this->zoom_ = zoom; }
	inline int zoom() const { return this->zoom_; }

signals:
	void sendPosition(int x, int y);

protected:
	void mousePressEvent(QMouseEvent *)	override;

	void paintEvent(QPaintEvent *)		override;

private:
	QRect pixelRect(int i, int j) const;

private:
	QImage image_;

	int zoom_;

	Ui::MapUI *ui;
};

#endif // !MAPUI_H