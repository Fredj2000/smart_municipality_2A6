#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "fournisseurs.h"
#include "Bondescommandes.h"
#include "produit.h"
#include <QComboBox>
#include<QPdfWriter>
#include<QPainter>
#include<QDesktopServices>
#include<QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox_4->setModel(Fournisseurs.list());
    ui->comboBox_6->setModel(Bondescommandes.list());
    ui->comboBox_5->setModel(Fournisseurs.list());
    ui->comboBox_7->setModel(produit.list());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()//login
{
    QString email = ui->utilisateur->text();
    QString password = ui->motdepasse->text();
    if (email == "ahmed" && password == "test")
    {
        ui->stackedWidget->setCurrentIndex(1);

    }
    else
    {
        QMessageBox::critical (this, "login", "email ou password sont incorrectes");
    }
}

void MainWindow::on_pushButton_3_clicked()//trqnsqtion
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_8_clicked()//ajiuter fil fournisseur
{
    QString matricule = ui->le_Matricule->text();
    QString NOM = ui->le_nom->text();
    QString adresse = ui->le_Adresse->text();
    QString tel = ui->le_Telephone->text();




    Fournisseurs.setMatricule(matricule);
    Fournisseurs.setNom(NOM);
    Fournisseurs.setAdresse(adresse);
    Fournisseurs.setTel(tel);


    if (Fournisseurs.add())
    {
        QMessageBox::information(this, "success ", "ajouter avec success");
        ui->comboBox_4->setModel(Fournisseurs.list());
        ui->comboBox_5->setModel(Fournisseurs.list());


    }

    else
    {
        QMessageBox::critical(this, "failure !", "completer les champs!");
    }

}

void MainWindow::on_pushButton_27_clicked()// affichge fournisseurs
{
    ui->tableView->setModel(Fournisseurs.list());
}

void MainWindow::on_on_pb_supprimer_clicked_clicked()//delete four
{
    QString matricule = ui->le_Matricule_supp->text();
    Fournisseurs.setMatricule(matricule);
    if (Fournisseurs.delet())
    {
        QMessageBox::information(this, "success ", "supprimé avec success");  }

    else
    {
        QMessageBox::critical(this, "failure !", "completer les champs!");
    }
}

void MainWindow::on_pushButton_28_clicked()//1 chercher fel modifer four
{
    QString matricule = ui->comboBox_4->currentText();
    QSqlQuery query;
    query.prepare("Select * from Fournisseurs where matricule=:id");
    query.bindValue(":id", matricule);
    query.exec();
    if(query.next())
    {
        ui->lineEdit_8->setText(query.value(1).toString());
        ui->lineEdit_9->setText(query.value(3).toString());
        ui->lineEdit_10->setText(query.value(2).toString());


    }
}

void MainWindow::on_pushButton_10_clicked()//2 modifer fel fournissuers

{
    QString matricule = ui->comboBox_4->currentText();
    QString NOM = ui->lineEdit->text();
    QString adresse = ui->lineEdit_2->text();
    QString tel = ui->lineEdit_3->text();

    Fournisseurs.setNom(NOM);
    Fournisseurs.setAdresse(adresse);
    Fournisseurs.setTel(tel);
    QSqlQuery query;

    query.prepare("update Fournisseurs set NOM=:nom,TELEPHONE=:TEL,ADRESSE=:ADRESSE where matricule=:matricule");

    query.bindValue(":matricule",matricule);

    query.bindValue(":nom",NOM);
    query.bindValue(":TEL",tel);
    query.bindValue(":ADRESSE",adresse);
    query.exec();
    if(query.exec()){
        QMessageBox::information (this, "update", "client updated");
    }


    else {QMessageBox::critical (this, "Error", "unexpected error");}
}
//////////////////////////////////////////
void MainWindow::on_pushButton_13_clicked()//ajiuter1 fil bon

{
    QString id = ui->le_id->text();
    QString liste = ui->le_liste->text();
    QString type = ui->le_type->text();
    QString prix = ui->le_prix->text();
    QString matricule = ui->comboBox_5->currentText();



    Bondescommandes.setListedeproduit(liste);
    Bondescommandes.setIDdecommande(id);
    Bondescommandes.setTypedeproduit(type);
    Bondescommandes.setPrixtotal(prix);
    Bondescommandes.setMatricule(matricule);


    if (Bondescommandes.add())
    {
        QMessageBox::information(this, "success ", "ajouter avec success");
        ui->comboBox_6->setModel(Bondescommandes.list());

    }

    else
    {
        QMessageBox::critical(this, "failure !", "completer les champs!");
    }

}


void MainWindow::on_pushButton_14_clicked()// affichge2 fil bon

{
    ui->tableView_2->setModel(Bondescommandes.list());
}


void MainWindow::on_pushButton_15_clicked()//delete2fil bon

{
    QString id = ui->le_id_supp->text();
    Bondescommandes.setIDdecommande(id);
    if (Bondescommandes.delet())
    {
        QMessageBox::information(this, "success ", "supprimé avec success");  }

    else
    {
        QMessageBox::critical(this, "failure !", "completer les champs!");
    }
}

void MainWindow::on_pushButton_11_clicked()//chercher fel modifer2fil bon
{
    QString id = ui->comboBox_6->currentText();
    QSqlQuery query;
    query.prepare("Select * from Bondescommandes where Id_de_commande=:id");
    query.bindValue(":id", id);
    query.exec();
    if(query.next())
    {
        ui->lineEdit_6->setText(query.value(2).toString());
        ui->lineEdit_15->setText(query.value(4).toString());



    }
}

void MainWindow::on_pushButton_9_clicked()//2 modifer2 fil bon
{
    QString id = ui->comboBox_6->currentText();
    QString type = ui->lineEdit_16->text();
    QString liste = ui->lineEdit_17->text();

    Bondescommandes.setTypedeproduit(type);
    Bondescommandes.setListedeproduit(liste);

    QSqlQuery query;

    query.prepare("update Bondescommandes set type_de_produit=:type,liste_de_produit=:liste where id_de_commande=:id");

    query.bindValue(":id",id);

    query.bindValue(":type",type);
    query.bindValue(":liste",liste);
    query.exec();
    if(query.exec()){
        QMessageBox::information (this, "update", "client updated");
    }


    else {QMessageBox::critical (this, "Error", "unexpected error");}
}

/////////////////////////
void MainWindow::on_pushButton_21_clicked()//ajiuterpro

{
    QString NOM = ui->le_nomm->text();
    QString reference = ui->le_reference->text();
    QString quantite = ui->le_quantite->text();
    QString prix = ui->le_pri->text();




    produit.setNom(NOM);
    produit.setreference (reference);
    produit.setquantite (quantite);
    produit.setprix(prix);


    if (produit.add())
    {
        QMessageBox::information(this, "success ", "ajouter avec success");
        ui->comboBox_7->setModel(produit.list());
    }

    else
    {
        QMessageBox::critical(this, "failure !", "completer les champs!");
    }

}




void MainWindow::on_pushButton_24_clicked()//deletepro
{
    QString reference = ui->le_ref_supp->text();
    produit.setreference(reference);
    if (produit.delet())
    {
        QMessageBox::information(this, "success ", "supprimé avec success");  }

    else
    {
        QMessageBox::critical(this, "failure !", "completer les champs!");
    }
}

void MainWindow::on_pushButton_29_clicked()// afficher pro
{
    ui->tableView_3->setModel(produit.list());
}
void MainWindow::on_pushButton_22_clicked()// chercher fel modifer pro
{
    QString reference = ui->comboBox_7->currentText();
       QSqlQuery query;
       query.prepare("Select * from produit where reference=:id");
       query.bindValue(":id", reference);
       query.exec();
       if(query.next())
       {
           ui->lineEdit_12->setText(query.value(3).toString());
           ui->lineEdit_26->setText(query.value(2).toString());
           ui->lineEdit_30->setText(query.value(1).toString());


       }
}
void MainWindow::on_pushButton_23_clicked()// modifer pro
{
    QString REFERENCE = ui->comboBox_7->currentText();
    QString NOM = ui->lineEdit_13->text();
    QString quantite = ui->lineEdit_25->text();
    QString prix = ui->lineEdit_31->text();

    produit.setNom(NOM);
    produit.setquantite(quantite);
    produit.setprix(prix);
    QSqlQuery query;

    query.prepare("update Fournisseurs set NOM=:NOM,QUANTITE=:QUANTITE,PRIX=:PRIX where REFERENCE=:REFERENCE");

    query.bindValue(":REFERENCE",REFERENCE);

    query.bindValue(":nom",NOM);
    query.bindValue(":QUANTITE",quantite);
    query.bindValue(":PRIX",prix);
    query.exec();
    if(query.exec()){
        QMessageBox::information (this, "update", "PRODUIT updated");
    }


    else {QMessageBox::critical (this, "Error", "unexpected error");}
}

void MainWindow::on_pushButton_19_clicked() // cherhcer bon des commande
{
    QString ID = ui->lineEdit_18->text();
    QString type = ui->lineEdit_28->text();
    QString MAT = ui->lineEdit_4->text();
    if(ID!="")
    {
        QSqlQuery query;
        query.prepare("Select * from Bondescommandes where Id_de_commande=:id");
        query.bindValue(":id", ID);
        query.exec();
        if(query.next())
        {
            ui->lineEdit_18->setText(query.value(0).toString());
            ui->lineEdit_27->setText(query.value(1).toString());
            ui->lineEdit_28->setText(query.value(2).toString());
            ui->lineEdit_4->setText(query.value(3).toString());
            ui->lineEdit_11->setText(query.value(4).toString());

        }
    }
    else if(type!="")

    {
        QSqlQuery query;
        query.prepare("Select * from Bondescommandes where type_de_PRODUIT=:id");
        query.bindValue(":id", type);
        query.exec();
        if(query.next())
        {

            ui->lineEdit_18->setText(query.value(0).toString());
            ui->lineEdit_27->setText(query.value(1).toString());
            ui->lineEdit_28->setText(query.value(2).toString());
            ui->lineEdit_4->setText(query.value(3).toString());
            ui->lineEdit_11->setText(query.value(4).toString());

        }

    }
    else
    {
        QSqlQuery query;
        query.prepare("Select * from Bondescommandes where matricule_de_fournisseur=:id");
        query.bindValue(":id", MAT);
        query.exec();
        if(query.next())
        {

            ui->lineEdit_18->setText(query.value(0).toString());
            ui->lineEdit_27->setText(query.value(1).toString());
            ui->lineEdit_28->setText(query.value(2).toString());
            ui->lineEdit_4->setText(query.value(3).toString());
            ui->lineEdit_11->setText(query.value(4).toString());

        }
    }
}

void MainWindow::on_pushButton_30_clicked() // triee fil bon
{
 ui->tableView_2->setModel(Bondescommandes.tri());
}

void MainWindow::on_pushButton_20_clicked() // trierr fil fournisseurs
{
    ui->tableView->setModel(Fournisseurs.tri1());
}

void MainWindow::on_pushButton_31_clicked()// cherhcer fil fournisseurs
{

    QString matricule = ui->lineEdit_20->text();
    QSqlQuery query;
    query.prepare("Select * from Fournisseurs where matricule=:id");
    query.bindValue(":id", matricule);
    query.exec();
    if(query.next())
    {
        ui->lineEdit_19->setText(query.value(1).toString());
        ui->lineEdit_21->setText(query.value(3).toString());
        ui->lineEdit_22->setText(query.value(2).toString());


    }

}

void MainWindow::on_pushButton_32_clicked() // charhcer fil produit
{
    QString NOM = ui->lineEdit_32->text();
    QString REF = ui->lineEdit_7->text();
    if(NOM!="")
    {
        QSqlQuery query;
        query.prepare("Select * from PRODUIT where NOM=:id");
        query.bindValue(":id", NOM);
        query.exec();
        if(query.next())
        {
            ui->lineEdit_7->setText(query.value(0).toString());
            ui->lineEdit_14->setText(query.value(1).toString());
            ui->lineEdit_24->setText(query.value(2).toString());
            ui->lineEdit_32->setText(query.value(3).toString());

        }
    }

    else
    {
        QSqlQuery query;
        query.prepare("Select * from PRODUIT where Reference=:id");
        query.bindValue(":id", REF);
        query.exec();
        if(query.next())
        {
            ui->lineEdit_7->setText(query.value(0).toString());
            ui->lineEdit_14->setText(query.value(1).toString());
            ui->lineEdit_24->setText(query.value(2).toString());
            ui->lineEdit_32->setText(query.value(3).toString());

        }
    }

}

void MainWindow::on_pushButton_33_clicked() //trier produit
{
    ui->tableView_3->setModel(produit.tri2());
}


void MainWindow::on_tabWidget_2_currentChanged(int index)
{
    if (index == 3) {
            ui->tableView->setModel(Fournisseurs.list());
        }

}

void MainWindow::on_tabWidget_3_currentChanged(int index)
{
    if (index == 3) {
            ui->tableView_2->setModel(Bondescommandes.list());
        }

}

void MainWindow::on_tabWidget_4_currentChanged(int index)
{
    if (index == 3) {
            ui->tableView_3->setModel(produit.list());
        }
}





void MainWindow::on_pushButton_46_clicked()
{
    QPdfWriter pdf("C:/Users/DELL/Desktop/ahmeddd/Pdf.pdf");
                              QPainter painter(&pdf);
                             int i = 4000;
                                  painter.setPen(Qt::red);
                                  painter.setFont(QFont("Arial Black", 30));
                                  painter.drawText(1100,1200,"Liste des Produits ");
                                  painter.setPen(Qt::black);
                                  painter.setFont(QFont("Arial", 50));

                                  painter.drawRect(100,100,7300,2600);

                                  painter.drawRect(0,3000,9600,500);
                                  painter.setFont(QFont("Arial", 9));
                                  painter.drawText(200,3300,"REFERENCE");
                                  painter.drawText(1700,3300,"QUANTITE");
                                  painter.drawText(3200,3300,"PRIX");
                                  painter.drawText(4900,3300,"NOM");

                                  QSqlQuery query;
                                  query.prepare("select * from produit");
                                  query.exec();
                                  while (query.next())
                                  {
                                      painter.drawText(200,i,query.value(0).toString());
                                      painter.drawText(1700,i,query.value(1).toString());
                                      painter.drawText(3200,i,query.value(2).toString());
                                      painter.drawText(4900,i,query.value(3).toString());

                                     i = i + 500;
                                  }
                                  int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                                      if (reponse == QMessageBox::Yes)
                                      {
                                          QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/DELL/Desktop/ahmeddd/Pdf.pdf"));
                                          painter.end();
                                      }
                                      if (reponse == QMessageBox::No)
                                      {
                                           painter.end();
                                      }
}


