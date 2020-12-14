#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "fournisseurs.h"
#include "Bondescommandes.h"
#include "produit.h"


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_27_clicked();

    void on_on_pb_supprimer_clicked_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_23_clicked();

    void on_lineEdit_12_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_19_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_33_clicked();

    void on_lineEdit_26_cursorPositionChanged(int arg1, int arg2);

    void on_tabWidget_2_currentChanged(int index);

    void on_tabWidget_3_currentChanged(int index);

    void on_tabWidget_4_currentChanged(int index);

    void on_comboBox_4_activated(const QString &arg1);

    void on_comboBox_4_currentIndexChanged(const QString &arg1);

    void on_pushButton_46_clicked();

    void on_pushButton_47_clicked();

private:
    Ui::MainWindow *ui;
    Fournisseurs Fournisseurs;
    Bondescommandes Bondescommandes ;
    produit produit ;
};
#endif // MAINWINDOW_H
