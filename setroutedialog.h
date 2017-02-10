#ifndef SETROUTEDIALOG_H
#define SETROUTEDIALOG_H

#include <QDialog>

class BaseBuilding;
struct Route;

class QString;
class SelectTableWidget;
namespace Ui {
class SetRouteDialog;
}

class SetRouteDialog : public QDialog {
	Q_OBJECT

public:
	SetRouteDialog(QWidget *parent = nullptr);
	~SetRouteDialog();

	void createNewRoute();

	inline void showAndRaise();

public slots:
	void updateDisplay();

private slots:
	void getGoodsName(const QString &);

	void getGoodsVolume(double);

	void getOrig(BaseBuilding *);
	
	void getDest(BaseBuilding *);

	void finishSetting();

signals:
	void sendRoute(Route *);

	void dataChanged();

private:
	Route *route_;

	SelectTableWidget *selectOrigTableWidget_;

	SelectTableWidget *selectDestTableWidget_;

	Ui::SetRouteDialog *ui;
};

inline void SetRouteDialog::showAndRaise() {
	this->show();
	this->raise();
	this->activateWindow();
}

#endif // !SETROUTEDIALOG_H