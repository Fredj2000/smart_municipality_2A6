#ifndef ARDUINO_INTER_H
#define ARDUINO_INTER_H

#include <QDialog>
#include "arduino.h"

namespace Ui {
class arduino_inter;
}

class arduino_inter : public QDialog
{
    Q_OBJECT

public:
    explicit arduino_inter(QWidget *parent = nullptr);
    ~arduino_inter();

private slots:
    void on_pushButton_clicked();
    void update_label();

    void on_pushButton_2_clicked();

private:
    Ui::arduino_inter *ui;
        arduino_code A;
        QByteArray data;
};

#endif // ARDUINO_INTER_H
