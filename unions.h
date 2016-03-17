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
    void readUdpDatagrams();
    ~unions();

private slots:
    void on_pushButton_clicked();

private:
    Ui::unions *ui;
};

#endif // UNIONS_H
