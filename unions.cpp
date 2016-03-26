#include "unions.h"
#include "ui_unions.h"
#include <QUdpSocket>

    struct packetHeader{
        unsigned short type;
        unsigned short reserved16bit;
        unsigned long  size;
    };

    struct CRCFooter{
        // If demand..
    };

    struct entry{
        quint32 x;
        qint32  y;   // 64 bits
        quint16 z;
        quint16 v;
        quint16 n;
        quint16 t;   // 64 bits
            // Total : 128 bits
    };

    union entryUnion{
        entry e;
        packetHeader header;
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

void unions::deserialize(QByteArray* source){
    entryUnion flyWheel;    // Someone likes to give strange names to variables..
    int typemini    = 0;    //  0 - standart, 1 - mini pack (x, y choords. only)
    int entrySize   = 16;   // 16 - standart, 8 - mini
    quint16 offset  = 0; // позиция чтения, 0 - начало тела UDP пакета
    quint16 pointer;     // позиция чтения, кол-во entries начиная от offset.

    // посмотрим, какой тип.

    flyWheel.header.type = 0;
    flyWheel.header.size = 2;
    memcpy(flyWheel.packed, source, 8);

    typemini    = flyWheel.header.type;
    p("\nType: " + QString::number(typemini));

    int packetSize  = flyWheel.header.size;
    p("\npacket size: " + QString::number(packetSize));
    int ss = source->size();

    // отсекаем ошибочные значения

    // длина внутреннего пакета не может превышать длину тела UDP
    if (packetSize > ss) packetSize = ss;

    if(typemini) entrySize = 8;
    p("\nentry size: " + QString::number(entrySize));

    unsigned int entriesCount = packetSize/entrySize;

    for(pointer = 0; pointer < entriesCount; pointer++){

        // memcpy(flyWheel.mini, source, 8);
        memcpy(flyWheel.mini, source, 8);
        unsigned long x = flyWheel.e.x;
        unsigned long y = flyWheel.e.y;


        p(QString::number(pointer) + ": x=" + QString::number(x)+ " y= "+ QString::number(y));
    }

    p(QString::number(source->size()) + "\n");
    p("\n");
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

        p("\n\n");

        QString TH = datagram.toHex();
        QString THR;
        int THi;

        for(THi=0; THi<TH.size()/8; THi++){

            THR.append(TH.mid(THi*8, 8));
            THR.append("  ");
            if(THi%4 == 3) THR.append("\n");
        }

        p(THR);
        //p(datagram.toHex());


        deserialize(&datagram);
    }
}

void unions::bindUdpPort()
{
    quint16 port = ui->lineEdit->text().toInt();
    if (udpServerSocket.bind(port)) { ui->pushButton->setEnabled(false);
     ui->plainTextEdit->appendPlainText("Сервер запущен.");}
    else {      ui->plainTextEdit->appendPlainText("Ошибка запуска сервера");     }

    connect(&udpServerSocket, SIGNAL(readyRead()),
               this, SLOT(readUdpDatagrams()));
}

unions::~unions()
{
    delete ui;
}

void unions::on_pushButton_clicked()
{
    bindUdpPort();
}
