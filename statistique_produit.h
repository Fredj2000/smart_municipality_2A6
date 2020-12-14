#ifndef STATISTIQUE_PRODUIT_H
#define STATISTIQUE_PRODUIT_H
#include <QDialog>
#include <QDialog>
#include <iostream>
#include <QApplication>
#include <QMainWindow>
//#include <QtCharts/QChartView>
//#include <QtCharts/QBarSeries>
//#include <QtCharts/QBarSet>
//#include <QtCharts/QLegend>
//#include <QtCharts/QBarCategoryAxis>
//#include <QtCharts/QHorizontalStackedBarSeries>
//#include <QtCharts/QLineSeries>
//#include <QtCharts/QCategoryAxis>
//#include <QtCharts/QPieSeries>
//#include <QtCharts/QPieSlice>
#include <QPainter>
#include <QSqlQuery>

namespace Ui {
class statistique_produit;
class QPieSlice;
}

class statistique_produit : public QDialog
{
    Q_OBJECT

public:
    explicit statistique_produit(QWidget *parent = nullptr);
    ~statistique_produit();
    int Statistique_partie2() ;
    int Statistique_partie3() ;
    int Statistique_partie4() ;

    void paintEvent(QPaintEvent *) ;
private slots:
    void on_widget_5_customContextMenuRequested(const QPoint &pos);

private:
    Ui::statistique_produit *ui;
};

#endif // STATISQTIQUE_PRODUIT_H

