#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

class QListWidgetItem;

namespace Ui { class HelpDialog; }

class HelpDialog : public QDialog {
	Q_OBJECT

public:
	HelpDialog(QDialog *parent = nullptr);

	~HelpDialog();

	void init();
	
public slots:
	void showIndustryChain(QListWidgetItem *);

private:
	Ui::HelpDialog *ui;
};


#endif // !HELPDIALOG_H