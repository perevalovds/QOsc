#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int listen_port = 12345;
    osc_iface.setLocalPort(listen_port);
    //osc_iface.connect("*", this, SLOT(on_osc_message(const QOscMessage& msg)));
    connect(&osc_iface, &QOscInterface::messageReceived,
            this, &MainWindow::onOscMessage);


    //connect(&osc_iface, SIGNAL(messageReceived(const QOscMessage&)),
    //        this, SLOT(on_osc_message(const QOscMessage&)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOscMessage(const QOscMessage& msg)
{
    ui->ReceivedEdit->append("OSC received: " + msg.pattern() + " " + msg.at(0).toString());
}

void MainWindow::osc_send(QString address, const QOscValue &value)
{
    QOscInterface iface;
    iface.setRemoteAddr("127.0.0.1"); // For some reason we can't use "localhost" - TODO need name resolving?
    iface.setRemotePort(ui->SendPortEdit->text().toInt());
    iface.send(address, value);
}

void MainWindow::on_pushButton_SendString_clicked()
{
    osc_send("/stringval", QOscValue("SomeText"));
}

void MainWindow::on_pushButton_SendFloat_clicked()
{
    osc_send("/floatval", QOscValue(0.7f));
}
