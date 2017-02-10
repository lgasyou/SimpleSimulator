#ifndef SETROUTEDIALOG_H
#define SETROUTEDIALOG_H

#include <QDialog>

class BaseBuilding;
struct Order;

class SelectTableWidget;
namespace Ui {
class SetRouteDialog;
}

class SetRouteDialog : public QDialog {
	Q_OBJECT

public:
	SetRouteDialog(QWidget *parent = nullptr);
	~SetRouteDialog();

	inline void showAndRaise();

	void updateDisplay();

public slots:
	void getOrigin(BaseBuilding *);
	
	void getDest(BaseBuilding *);

	void finishSetting();

signals:
	void sendOrder(Order *);

private:
	Order *order_;

	SelectTableWidget *selectOriginTableWidget_;

	SelectTableWidget *selectDestTableWidget_;

	Ui::SetRouteDialog *ui;
};

inline void SetRouteDialog::showAndRaise() {
	this->show();
	this->raise();
	this->activateWindow();
}

#endif // !SETROUTEDIALOG_H