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

	void init();

	QSize sizeHint() const;

	inline void setImage(const QImage &image) { this->image_ = image; }
	inline const QImage &image() const { return this->image_; }

	void setMode(int mode);

	inline void setZoom(int zoom) { this->zoom_ = zoom; }
	inline int zoom() const { return this->zoom_; }

signals:
	void sendPosition(int x, int y);

protected:
	void mousePressEvent(QMouseEvent *)	override;

	void paintEvent(QPaintEvent *)		override;

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