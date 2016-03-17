#include "unions.h"
#include "ui_unions.h"
#include <QUdpSocket>

    struct entry{
        quint32 x;
        qint32  y;   // 64 bits
        quint16 z;
        quint16 v;
        quint16 n;
        quint16 t;   // 64 bits
            // Total : 128 bits
    };

    union eu{
        entry e;
        char packed[16];
        char mini[8];
    };

    QUdpSocket udpServerSocket;

unions::unions(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::unions)
{
    ui->setupUi(this);
}

void unions::p(QString str){
    ui->plainTextEdit->appendPlainText(str);
}

void unions::bindUdpPort()
{
    quint16 port = ui->lineEdit->text().toInt();
    if (udpServerSocket.bind(port)) { ui->pushButton->setEnabled(false);}
    else {      ui->plainTextEdit->appendPlainText("Ошибка запуска сервера");     }
}

void unions::readUdpDatagrams()
{
    while (udpServerSocket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpServerSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpServerSocket.readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        QString current = sender.toString();


    }
}


unions::~unions()
{
    delete ui;
}

void unions::on_pushButton_clicked()
{
    bindUdpPort();
}
