#ifndef BUILDINGDETAILDIALOG_H
#define BUILDINGDETAILDIALOG_H

class BuildingBase;
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

    inline void setBuilding(BuildingBase *building) { this->building_ = building; }
    inline void setVisitor(Company *visitor) { this->visitor_ = visitor; }

public slots:
	void updateDisplay();

signals:
    void buySignal(BuildingBase *);
    void sellSignal(BuildingBase *);
    void changeTypeSignal(BuildingBase *, const QString &buildingType);
    void manageSignal(BuildingBase *, const QString &cmd);

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

    BuildingBase *building_;
    Company *visitor_;

    FactoryCargoTableWidget *factoryCargoTableWidget;
    Ui::BuildingDetailDialog *ui;
};

#endif // BUILDINGDETAILDIALOG_H
