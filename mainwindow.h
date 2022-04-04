#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qosc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onOscMessage(const QOscMessage& msg);  // Can't use "on_osc_message" - because Qt treats two "_" specially

    void on_pushButton_SendString_clicked();

    void on_pushButton_SendFloat_clicked();

private:
    Ui::MainWindow *ui;

    QOscInterface osc_iface;

    void osc_send(QString address, const QOscValue &value);
};
#endif // MAINWINDOW_H
