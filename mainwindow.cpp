#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "settingsdialog.h"
#include <timediff/timediff.hpp>
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , settingsDialog(nullptr)
    , updateTimer(new QTimer(this))
    , useTime2(false)
{
    ui->setupUi(this);
    setWindowTitle("TimeDiff - UTC Time Difference");
    
    // 初始化time1为当前UTC时间
    timediff::DateTime now = timediff::now_utc();
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << now.year
        << std::setw(2) << now.month
        << std::setw(2) << now.day
        << std::setw(2) << now.hour
        << std::setw(2) << now.minute
        << std::setw(2) << now.second;
    time1Str = QString::fromStdString(oss.str());
    
    // 连接设置按钮
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::onSettingsButtonClicked);
    
    // 设置定时器每秒更新
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateTimeDiff);
    updateTimer->start(50);
    
    // 立即更新一次
    updateTimeDiff();
}

MainWindow::~MainWindow()
{
    delete settingsDialog;
    delete ui;
}

void MainWindow::onSettingsButtonClicked()
{
    if (!settingsDialog) {
        settingsDialog = new SettingsDialog(this);
    }
    
    // 设置当前值
    settingsDialog->setTime1(time1Str);
    settingsDialog->setTime2(time2Str);
    settingsDialog->setUseTime2(useTime2);
    
    // 显示对话框
    if (settingsDialog->exec() == QDialog::Accepted) {
        // 获取新值
        time1Str = settingsDialog->getTime1();
        time2Str = settingsDialog->getTime2();
        useTime2 = settingsDialog->getUseTime2();
        
        // 立即更新显示
        updateTimeDiff();
    }
}

void MainWindow::updateTimeDiff()
{
    try {
        // 解析time1
        if (time1Str.isEmpty()) {
            ui->labelDiff->setText("Time1 is required");
            return;
        }
        
        timediff::DateTime time1 = timediff::parse_utc_string(time1Str.toStdString());
        
        // 获取time2
        timediff::DateTime time2;
        if (useTime2 && !time2Str.isEmpty()) {
            time2 = timediff::parse_utc_string(time2Str.toStdString());
        } else {
            time2 = timediff::now_utc();
        }
        
        // 计算时间差
        timediff::MixedDuration duration = timediff::diff_mixed(time1, time2, false);
        
        // 格式化并显示
        QString displayText = formatMixedDuration(
            duration.years, duration.months, duration.days,
            duration.hours, duration.minutes, duration.seconds
        );
        ui->labelDiff->setText(displayText);
    } catch (...) {
        ui->labelDiff->setText("Error calculating time difference");
    }
}

QString MainWindow::formatDateTime(const QString &timeStr) const
{
    if (timeStr.length() != 14) {
        return timeStr;
    }
    return timeStr.mid(0, 4) + "-" + timeStr.mid(4, 2) + "-" + timeStr.mid(6, 2) + " " +
           timeStr.mid(8, 2) + ":" + timeStr.mid(10, 2) + ":" + timeStr.mid(12, 2);
}

QString MainWindow::formatMixedDuration(int64_t years, int64_t months, int64_t days,
                                        int64_t hours, int64_t minutes, int64_t seconds) const
{
    QStringList parts;
    
    if (years != 0) {
        parts << QString("%1 year").arg(years);
    }
    if (months != 0) {
        parts << QString("%1 month").arg(months);
    }
    if (days != 0) {
        parts << QString("%1 day").arg(days);
    }
    if (hours != 0) {
        parts << QString("%1 hour").arg(hours);
    }
    if (minutes != 0) {
        parts << QString("%1 minute").arg(minutes);
    }
    if (seconds != 0 || parts.isEmpty()) {
        parts << QString("%1 second").arg(seconds);
    }
    
    return parts.join(" ");
}
