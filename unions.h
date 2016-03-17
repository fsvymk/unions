#ifndef UNIONS_H
#define UNIONS_H

#include <QMainWindow>

namespace Ui {
class unions;
}

class unions : public QMainWindow
{
    Q_OBJECT

public:
    void readUdpDatagrams();
    explicit unions(QWidget *parent = 0);
    ~unions();

private:
    Ui::unions *ui;
};

#endif // UNIONS_H
