#include "mainwindow.h"

#include "connection.h"
#include <QMessageBox>
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Connection c ;
      ;

    bool test =c.createconnect();
    if (test)
     {
MainWindow w;
w.showNormal();
  return a.exec();
       QMessageBox::information(nullptr,QObject::tr("data base is open"),
               QObject::tr("connection succesful.\n"),QMessageBox::Cancel);
     }
    else
        QMessageBox::critical(nullptr,QObject::tr("data base is not  open"),
                QObject::tr("connection failed.\n"),QMessageBox::Cancel);


    return a.exec();
}
