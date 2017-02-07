#ifndef SELECTINDUSTRYDIALOG_H
#define SELECTINDUSTRYDIALOG_H

#include <QDialog>

class Industry;
class MyPushButton;
namespace Ui {
class SelectIndustryDialog;
}

class SelectIndustryDialog : public QDialog {
	Q_OBJECT

public:
	SelectIndustryDialog(QWidget *parent = nullptr);
	~SelectIndustryDialog();

	void init();

	void updateDisplay();

	void displayTableWidget(int indexInWidget, int indexInManager, Industry *);

signals:
	void sendSelectedIndustry(Industry *);

private:
	Ui::SelectIndustryDialog *ui;
};

#endif // !SELECTINDUSTRYDIALOG_H
