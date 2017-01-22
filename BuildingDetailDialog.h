#ifndef BUILDINGDETAILDIALOG_H
#define BUILDINGDETAILDIALOG_H

class BaseBuilding;
class Company;
class FactoryCargoTableWidget;
#include <QDialog>
namespace Ui {
class BuildingDetailDialog;
}

class BuildingDetailDialog : public QDialog {
    Q_OBJECT

public:
    BuildingDetailDialog(QWidget *parent);
    ~BuildingDetailDialog();

    inline void setBuilding(BaseBuilding *building) { this->building_ = building; }
    inline void setVisitor(Company *visitor) { this->visitor_ = visitor; }

public slots:
	void updateDisplay();

signals:
    void buySignal(BaseBuilding *);
    void sellSignal(BaseBuilding *);
    void changeTypeSignal(BaseBuilding *, const QString &buildingType);
    void manageSignal(BaseBuilding *, const QString &cmd);

private slots:
    void on_pushButton_Buy_clicked();
    void on_pushButton_Sell_clicked();

    void on_pushButton_Manage_clicked();
    void on_pushButton_Dismantle_clicked();

	void on_pushButton_Build_clicked();
    void on_pushButton_Build_IronMine_clicked();
	void on_pushButton_Build_CoalMine_clicked();
	void on_pushButton_Build_SteelFactory_clicked();
    void on_pushButton_Build_residence_clicked();

private:
	// transforms double into QString
	QString toString(double value);

    BaseBuilding *building_;
    Company *visitor_;

    FactoryCargoTableWidget *factoryCargoTableWidget;
    Ui::BuildingDetailDialog *ui;
};

#endif // BUILDINGDETAILDIALOG_H
