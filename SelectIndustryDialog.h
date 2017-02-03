#pragma once
#include <QWidget>
#include "ui_selectindustrydialog.h"

class SelectIndustryDialog : public QWidget {
	Q_OBJECT

public:
	SelectIndustryDialog(QWidget * parent = Q_NULLPTR);
	~SelectIndustryDialog();

signals:


private:
	Ui::SelectIndustryDialog ui;
};
