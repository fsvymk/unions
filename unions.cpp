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

void unions::readUdpDatagrams()
{

}

unions::unions(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::unions)
{
    ui->setupUi(this);
}

unions::~unions()
{
    delete ui;
}
