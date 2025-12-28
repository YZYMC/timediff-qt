#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    setWindowTitle("Settings - TimeDiff");
    connect(ui->checkBoxUseTime2, &QCheckBox::toggled, this, &SettingsDialog::onUseTime2Toggled);
    ui->Time2Edit->setEnabled(false);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

QString SettingsDialog::getTime1() const
{
    return ui->Time1Edit->text();
}

void SettingsDialog::setTime1(const QString &time1)
{
    ui->Time1Edit->setText(time1);
}

QString SettingsDialog::getTime2() const
{
    return ui->Time2Edit->text();
}

void SettingsDialog::setTime2(const QString &time2)
{
    ui->Time2Edit->setText(time2);
}

bool SettingsDialog::getUseTime2() const
{
    return ui->checkBoxUseTime2->isChecked();
}

void SettingsDialog::setUseTime2(bool use)
{
    ui->checkBoxUseTime2->setChecked(use);
    ui->Time2Edit->setEnabled(use);
}

void SettingsDialog::onUseTime2Toggled(bool checked)
{
    ui->Time2Edit->setEnabled(checked);
}
