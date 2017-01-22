#ifndef FACTORYCARGOTABLEWIDGET_H
#define FACTORYCARGOTABLEWIDGET_H

class FactoryCargo;
#include <QTableWidget>

class FactoryCargoTableWidget : public QTableWidget {
    Q_OBJECT

public:
	FactoryCargoTableWidget(QWidget *parent = nullptr, FactoryCargo *cargo = nullptr);

	void updateDisplay();

	void setCargo(FactoryCargo *cargo) { this->cargo_ = cargo; }

	QString toString(double value);

private:
	FactoryCargo *cargo_;
};

#endif // FACTORYCARGOTABLEWIDGET_H
