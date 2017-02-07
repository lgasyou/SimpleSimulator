#ifndef SELECTINDUSTRYDIALOG_H
#define SELECTINDUSTRYDIALOG_H

#include <QDialog>

class BaseIndustry;

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

	inline void showAndRaise();

	void updateDisplay();

	void displayTableWidget(int indexInWidget, int indexInManager, BaseIndustry *);

signals:
	void sendSelectedBaseIndustry(BaseIndustry *);

private:
	Ui::SelectIndustryDialog *ui;
};

inline void SelectIndustryDialog::showAndRaise() {
	this->show();
	this->raise();
	this->activateWindow();
}

#endif // !SELECTINDUSTRYDIALOG_H
