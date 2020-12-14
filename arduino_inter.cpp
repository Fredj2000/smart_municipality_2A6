#include "arduino_inter.h"
#include "ui_arduino_inter.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include<QObject>
arduino_inter::arduino_inter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::arduino_inter)
{
    ui->setupUi(this);
    int ret=A.connect_arduino();    //lancer arduino

        switch(ret)
        {
        case(0):qDebug()<<"arduino is connected and availeble"<<A.getarduino_port_name();   break;
        case(1):qDebug()<<"arduino is not connected and is availeble"<<A.getarduino_port_name();    break;
        case(-1):qDebug()<<"arduino is not available";
}
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT( update_lable()));
        }

arduino_inter::~arduino_inter()
{
    delete ui;
}

void arduino_inter::on_pushButton_clicked()
{
    A.write_to_arduino("1"); // alumer
}

void arduino_inter::on_pushButton_2_clicked()
{
    A.write_to_arduino("0");

}
void arduino_inter::update_label()
{

 data=A.read_from_arduino();
 if (data=="1")
 {
     ui->label_2->setText("mouvement detecter");
 }
 else if (data=="2")
 {
     ui->label_2->setText(("lampe et buzzeur allumé"));
 }
 else if (data=="3")
 {
     ui->label_2->setText(("OFF"));
 }

}
