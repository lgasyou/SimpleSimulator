#ifndef SELECTTABLEWIDGET_H
#define SELECTTABLEWIDGET_H

#include <QTableWidget>
#include <QString>
#include <vector>

class BaseBuilding;
class TableWidgetPushButton;

class SelectTableWidget : public QTableWidget {
	Q_OBJECT

public:
	enum { 
		None = 0, 
		UnusedLand = 1, 
		Factory = 2, Mine = 4 };

	SelectTableWidget(QWidget *parent = nullptr);

	~SelectTableWidget();

	void init();

	void updateDisplay();

	void updateEachLine(int indexInWidget, int indexInManager, BaseBuilding *);

	// Sets type(s) which will be displayed later.
	// Uses '|' to add multiple objects.
	void setSelector(int type);

public slots:
	void getDestAndSendBuilding(int index);

signals:
	void sendBuilding(BaseBuilding *);

private:
	std::vector<QString> typeNames_;
};

#endif // !SELECTTABLEWIDGET_H