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

    explicit unions(QWidget *parent = 0);
    void bindUdpPort();
    void p(QString str);

    ~unions();

private slots:
    void on_pushButton_clicked();
    void readUdpDatagrams();
    void deserialize(QByteArray *source);

private:
    Ui::unions *ui;
};

#endif // UNIONS_H
