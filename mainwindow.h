#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSettingsButtonClicked();
    void updateTimeDiff();

private:
    QString formatDateTime(const QString &timeStr) const;
    QString formatMixedDuration(int64_t years, int64_t months, int64_t days,
                                int64_t hours, int64_t minutes, int64_t seconds) const;

    Ui::MainWindow *ui;
    SettingsDialog *settingsDialog;
    QTimer *updateTimer;
    QString time1Str;
    QString time2Str;
    bool useTime2;
};
#endif // MAINWINDOW_H
