#ifndef SELECTTABLEWIDGET_H
#define SELECTTABLEWIDGET_H

#include <QTableWidget>
#include <QString>
#include <vector>

class BaseBuilding;
class MyPushButton;
namespace Ui {
class SelectTableWidget;
}

class SelectTableWidget : public QTableWidget {
	Q_OBJECT

public:
	enum { 
		None = 0, 
		Foundation = 1, 
		Factory = 2, SteelFactory = 4, 
		Mine = 8, CoalMine = 16, IronMine = 32 };

	SelectTableWidget(QWidget *parent = nullptr);

	~SelectTableWidget();

	void init();

	void updateDisplay();

	void updateEachLine(int indexInWidget, int indexInManager, BaseBuilding *);

	void setSelector(int type);

public slots:
	void getDestAndSendBuilding(MyPushButton *);

signals:
	void sendBuilding(BaseBuilding *);

private:
	std::vector<QString> typeNames_;

	Ui::SelectTableWidget *ui;
};

#endif // !SELECTTABLEWIDGET_H