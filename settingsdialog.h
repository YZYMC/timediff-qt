#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    QString getTime1() const;
    void setTime1(const QString &time1);

    QString getTime2() const;
    void setTime2(const QString &time2);

    bool getUseTime2() const;
    void setUseTime2(bool use);

private slots:
    void onUseTime2Toggled(bool checked);

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
