#include "gestion_materiaux.h"
#include "ui_gestion_materiaux.h"
#include "connection.h"
#include "materiauxmanq.h"
#include "materiauxposs.h"
#include "matmaint.h"
#include <QMessageBox>
#include <QComboBox>
#include <QPixmap>
#include<QPdfWriter>
#include<QPainter>
#include<QDesktopServices>
#include<QUrl>



gestion_materiaux::gestion_materiaux(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestion_materiaux)
{
    ui->setupUi(this);
    ui->tableView->setModel(tempmatposs.afficher());
       ui->tableView_3->setModel(tempmatmanq.afficher());
       ui->tableView_2->setModel(tempmatmaint.afficher());

       //possessions
       ui->referance_mat_poss_modifier->setModel(tempmatposs.afficher());
       ui->referance_mat_poss_supprimer_combobox1->setModel(tempmatposs.afficher());
       ui->combo_box_recherche_poss->setModel(tempmatposs.afficher());


       //maintenace
       ui->referance_mat_maint_modifier->setModel(tempmatmaint.afficher());
       ui->referance_mat_maint_supprimer_combobox_1->setModel(tempmatmaint.afficher());
       ui->comboBox_rechercher_mat_maint->setModel(tempmatmaint.afficher());
       ui->combo_nom_mat_maint->setModel(tempmatposs.afficher_nom());

       //manquant
       ui->referance_mat_manq_modifier->setModel(tempmatmanq.afficher());
       ui->referance_mat_manq_supprimer_combobox1->setModel(tempmatmanq.afficher());
       ui->comboBox_rechercher_mat_manq->setModel(tempmatmanq.afficher());
}

gestion_materiaux::~gestion_materiaux()
{
    delete ui;
}





//==================================================================materiaux_possession==============================================
void gestion_materiaux::on_ajouterposs_clicked()
{
    QString etat ;
        bool test;
        int referance =ui->referancePoss->text().toInt();
        QString nom =ui->nomPoss->text();

        if(ui->ajouterEtatMateriauxPoss1->isChecked()){ etat =ui->ajouterEtatMateriauxPoss1->text();}
        if(ui->ajouteretatMateriauxposs0->isChecked()){ etat =ui->ajouteretatMateriauxposs0->text();}

        if(nom==""|| etat==""||referance==0||referance>99999999||nom.length()>10||tempmatposs.verif_nom(nom)==false)


                {
                              QMessageBox::critical(nullptr, QObject::tr("vide"),
                              QObject::tr("veuillez saisir tous les champs correctement!\n"), QMessageBox::Cancel);
                              test=false;

                }

        else
            {
         Materiauxposs m(referance,nom,etat);
         test= m.ajouter();

            }



        if (test)
        {

            ui->combo_nom_mat_maint->setModel(tempmatposs.afficher_nom());
            ui->tableView->setModel(tempmatposs.afficher());
            ui->referance_mat_poss_supprimer_combobox1->setModel(tempmatposs.afficher());
            ui->combo_box_recherche_poss->setModel(tempmatposs.afficher());
            ui->referance_mat_poss_modifier->setModel(tempmatposs.afficher());
            QMessageBox::information(nullptr, QObject::tr("Ajouter un materiel en possessions "),
                              QObject::tr("meteriel ajouté.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
                {
              QMessageBox::critical(nullptr, QObject::tr("Ajouter un materiel en possessions"),
                            QObject::tr("Erreur !\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                }
}



void gestion_materiaux::on_Modifier_materiel_possession_clicked()
{
    bool test;
        QString etat ;
        int referance=ui->referance_mat_poss_modifier->currentText().toInt();
        QString nom=ui->mat_poss_nom_mod->text();
        if(ui->mat_poss_etat_b_mod->isChecked()){ etat =ui->mat_poss_etat_b_mod->text();}
        if(ui->mat_poss_m__mod->isChecked()){ etat =ui->mat_poss_m__mod->text();}
        Materiauxposs m ;
        if(nom==""|| etat==""||referance==0||tempmatposs.verif_nom(nom)==false)


                {
                              QMessageBox::critical(nullptr, QObject::tr("vide"),
                              QObject::tr("veuillez saisir tous les champs.\n"), QMessageBox::Cancel);
                              test=false;
                }
        else
            {
         test = m.modifier(referance,nom,etat);
            }

        if (test)
        {
            QMessageBox::information(nullptr, QObject::tr("modifier un materiel en possessions "),
            QObject::tr("meteriel modifier.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(tempmatposs.afficher());
        ui->combo_nom_mat_maint->setModel(tempmatposs.afficher_nom());

        }
        else
                {
              QMessageBox::critical(nullptr, QObject::tr("modifier un materiel en possessions"),
                            QObject::tr("Erreur !\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                }
}



void gestion_materiaux::on_supp_mat_poss1_clicked()
{
    int ref=ui->referance_mat_poss_supprimer_combobox1->currentText().toInt();

        bool test=tempmatposs.supprimer(ref);
        if(test)
        {
            ui->tableView->setModel(tempmatposs.afficher());
            ui->referance_mat_poss_supprimer_combobox1->setModel(tempmatposs.afficher());
            ui->combo_box_recherche_poss->setModel(tempmatposs.afficher());
            ui->referance_mat_poss_modifier->setModel(tempmatposs.afficher());
            ui->combo_nom_mat_maint->setModel(tempmatposs.afficher_nom());
            QMessageBox::information(nullptr, QObject::tr("Supprimer un materiel"),
                        QObject::tr("materiel supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un materiel"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_materiaux::on_combo_box_recherche_poss_activated(int index)
{
    QString ref= QString::number(index);
         QString reff = ui->combo_box_recherche_poss->currentText();
        ui->tableView->setModel(tempmatposs.afficher_rech(reff));
}



void gestion_materiaux::on_comboBox_trier_poss_activated(int index)
{
    QString res = QString::number(index);
      if(ui->comboBox_trier_poss->currentText()=="Nom"){ui->tableView->setModel(tempmatposs.tri_nom());}
      if(ui->comboBox_trier_poss->currentText()=="referance"){ui->tableView->setModel(tempmatposs.tri_ref());}
}

void gestion_materiaux::on_supprimer_mat_poss_tab_clicked()
{
    int ref=ui->tableView->currentIndex().data().toInt();
        bool test=tempmatposs.supprimer(ref);
        if(test)
        {
            ui->combo_nom_mat_maint->setModel(tempmatposs.afficher_nom());
            ui->tableView->setModel(tempmatposs.afficher());
            ui->referance_mat_poss_supprimer_combobox1->setModel(tempmatposs.afficher());
            ui->combo_box_recherche_poss->setModel(tempmatposs.afficher());
            ui->referance_mat_poss_modifier->setModel(tempmatposs.afficher());
            QMessageBox::information(nullptr, QObject::tr("Supprimer un materiel"),
                        QObject::tr("materiel supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un materiel"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}


void gestion_materiaux::on_imprimer_mat_poss_clicked()
{
    int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
     if (reponse == QMessageBox::Yes)
     {
         tempmatposs.imprimer();
     }
     if (reponse == QMessageBox::No)
     {
         QMessageBox::critical(nullptr, QObject::tr("imprimer annuler"),
                     QObject::tr("imprimer annuler.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
     }
}



void gestion_materiaux::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tableView->setModel(tempmatposs.rechercheDynamic(arg1));
}

//===================================================materiaux_manquant=============================================



void gestion_materiaux::on_ajoutermateriauxmanq_clicked()
{
    bool test;
    QString dispo;
    int referance=ui->refmatmanq->text().toInt();
    int prix=ui->prixmanq->text().toInt();
    QString nom =ui->nommanq->text();
    if(ui->dispo_oui->isChecked()){ dispo =ui->dispo_oui->text();}
    if(ui->dispo_non->isChecked()){ dispo =ui->dispo_non->text();}
    if(prix==0|| nom==""||referance==0||dispo==""||tempmatposs.verif_nom(nom)==false)


            {
                          QMessageBox::critical(nullptr, QObject::tr("vide"),
                          QObject::tr("veuillez saisir tous les champs.\n"), QMessageBox::Cancel);
                          test=false;
            }
   else
       {
       Materiauxmanq mq(referance,prix,nom,dispo);
       test= mq.ajouter();
       }
           if (test)
     {

         ui->tableView_3->setModel(tempmatmanq.afficher()); //refraich afich
          ui->referance_mat_manq_supprimer_combobox1->setModel(tempmatmanq.afficher());
          ui->comboBox_rechercher_mat_manq->setModel(tempmatmanq.afficher());
          ui->referance_mat_manq_modifier->setModel(tempmatmanq.afficher());
         QMessageBox::information(nullptr, QObject::tr("Ajouter un materiel en possessions "),
                           QObject::tr("meteriel ajouté.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
     }
           else
             {
           QMessageBox::critical(nullptr, QObject::tr("Ajouter un materiel en possessions"),
                       QObject::tr("Erreur !\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
             }

}



void gestion_materiaux::on_modifier_materiel_manquant_clicked()
{
    bool test;
      QString dispo ;
      int referance=ui->referance_mat_manq_modifier->currentText().toInt();
      int prix =ui->prix_materiel_manquant_modifier->text().toInt();
      QString nom=ui->nom_materiel_manquant_modfier->text();
      if(ui->dispo_oui_materiel_manquant_modifier->isChecked()){ dispo =ui->dispo_oui_materiel_manquant_modifier->text();}
      if(ui->ispo_non_materiel_manquant_modifier->isChecked()){ dispo =ui->ispo_non_materiel_manquant_modifier->text();}

      if(prix==0|| nom==""||referance==0||dispo==""||tempmatposs.verif_nom(nom)==false)


              {
                            QMessageBox::critical(nullptr, QObject::tr("vide"),
                            QObject::tr("veuillez saisir tous les champs.\n"), QMessageBox::Cancel);
                            test=false;
              }

      else
      {
      Materiauxmanq m ;
      test =m.modifier(referance,prix,nom,dispo);
      }


      if (test)

      {   ui->tableView_3->setModel(tempmatmanq.afficher());
          QMessageBox::information(nullptr, QObject::tr("modifier un materiel manquant "),
          QObject::tr("meteriel modifier.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);


      }
      else
              {
            QMessageBox::critical(nullptr, QObject::tr("modifier un materiel manquant"),
                          QObject::tr("Erreur !\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
              }
}




void gestion_materiaux::on_supprimermatmanq1_clicked()
{

    int ref=ui->referance_mat_manq_supprimer_combobox1->currentText().toInt();
    bool test=tempmatmanq.supprimer(ref);
    if(test)
    {
        ui->tableView_3->setModel(tempmatmanq.afficher());
         ui->referance_mat_manq_supprimer_combobox1->setModel(tempmatmanq.afficher());
         ui->comboBox_rechercher_mat_manq->setModel(tempmatmanq.afficher());
         ui->referance_mat_manq_modifier->setModel(tempmatmanq.afficher());
        QMessageBox::information(nullptr, QObject::tr("Supprimer un materiel"),
                    QObject::tr("materiel supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un materiel"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}




void gestion_materiaux::on_comboBox_tri_ma_manq_activated(int index)
{
    QString res = QString::number(index);
    if(ui->comboBox_tri_ma_manq->currentText()=="Nom"){ui->tableView_3->setModel(tempmatmanq.tri_nom());}
    if(ui->comboBox_tri_ma_manq->currentText()=="referance"){ui->tableView_3->setModel(tempmatmanq.tri_ref());}
}



void gestion_materiaux::on_supprimer_mat_manq_tab_clicked()
{
    int ref=ui->tableView_3->currentIndex().data().toInt();
        bool test=tempmatmanq.supprimer(ref);
        if(test)
        {
            ui->tableView_3->setModel(tempmatmanq.afficher());
             ui->referance_mat_manq_supprimer_combobox1->setModel(tempmatmanq.afficher());
             ui->comboBox_rechercher_mat_manq->setModel(tempmatmanq.afficher());
             ui->referance_mat_manq_modifier->setModel(tempmatmanq.afficher());
            QMessageBox::information(nullptr, QObject::tr("Supprimer un materiel"),
                        QObject::tr("materiel supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un materiel"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}



void gestion_materiaux::on_comboBox_rechercher_mat_manq_activated(int index)
{
    QString ref= QString::number(index);
     QString reff = ui->comboBox_rechercher_mat_manq->currentText();
    ui->tableView_3->setModel(tempmatmanq.afficher_rech(reff));
}


//=============================================Materiaux_maintenace=================================================




void gestion_materiaux::on_ajouter_mat_maintenace_clicked()
{
    bool test;
        QString date = ui->dateTimeEdit->text();
        int  referance=ui->ref_mat_maint_a_ajouter->text().toInt();
        QString nom =ui->combo_nom_mat_maint->currentText();
        QString region =ui->region_mat_maint_a_ajouter->text();

        if(date==""|| nom==""||referance==0||region==""||tempmatposs.verif_nom(nom)==false||tempmatposs.verif_nom(region)==false)


                {
                              QMessageBox::critical(nullptr, QObject::tr("vide"),
                              QObject::tr("veuillez saisir tous les champs.\n"), QMessageBox::Cancel);
                              test=false;
                }
        else {
        Matmaint mt(referance,nom,region,date);
        test = mt.ajouter();
             }

        if (test)

        {
            ui->tableView_2->setModel(tempmatmaint.afficher());
            ui->referance_mat_maint_supprimer_combobox_1->setModel(tempmatmaint.afficher());
            ui->comboBox_rechercher_mat_maint->setModel(tempmatmaint.afficher());
            ui->referance_mat_maint_modifier->setModel(tempmatmaint.afficher());
            QMessageBox::information(nullptr, QObject::tr("Ajouter un materiel en maintenace "),
                              QObject::tr("meteriel ajouté.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
                {
              QMessageBox::critical(nullptr, QObject::tr("Ajouter un materiel en maintenace"),
                            QObject::tr("Erreur !\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                }
}





void gestion_materiaux::on_supprimer_mat_maintenace1_clicked()
{
    int ref=ui->referance_mat_maint_supprimer_combobox_1->currentText().toInt();
      bool test=tempmatmaint.supprimer(ref);
      if(test)
      {
          ui->tableView_2->setModel(tempmatmaint.afficher());
          ui->referance_mat_maint_supprimer_combobox_1->setModel(tempmatmaint.afficher());
          ui->comboBox_rechercher_mat_maint->setModel(tempmatmaint.afficher());
          ui->referance_mat_maint_modifier->setModel(tempmatmaint.afficher());
          QMessageBox::information(nullptr, QObject::tr("Supprimer un materiel"),
                      QObject::tr("materiel supprimé.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

      }
      else
          QMessageBox::critical(nullptr, QObject::tr("Supprimer un materiel"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_materiaux::on_modifier_materiaux_maintenance_clicked()
{
    bool test;
      int referance=ui->referance_mat_maint_modifier->currentText().toInt();
      QString date=ui->dure_materiaux_maintance_modifier->text();
      QString nom=ui->nom_materiel_manquant_modfier->text();
      QString region=ui->region_mateiraux_maintance_modifier->text();
      if(date==""|| nom==""||referance==0||region==""||tempmatposs.verif_nom(nom)==false||tempmatposs.verif_nom(region)==false)


              {
                            QMessageBox::critical(nullptr, QObject::tr("vide"),
                            QObject::tr("veuillez saisir tous les champs.\n"), QMessageBox::Cancel);
                            test=false;
              }
      else
        {
      Matmaint m;
      test= m.modifier(referance,nom,region,date);
        }

      if (test)

      {
          ui->tableView_2->setModel(tempmatmaint.afficher());
          QMessageBox::information(nullptr, QObject::tr("modifier un materiel maintenace "),
          QObject::tr("meteriel modifier.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);


      }
      else
              {
            QMessageBox::critical(nullptr, QObject::tr("modifier un materiel maintenace"),
                          QObject::tr("Erreur !\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
              }

}



void gestion_materiaux::on_comboBox_tri_mat_maint_activated(int index)
{
    QString res = QString::number(index);
    if(ui->comboBox_tri_mat_maint->currentText()=="Nom"){ui->tableView_2->setModel(tempmatmaint.tri_nom());}
    if(ui->comboBox_tri_mat_maint->currentText()=="referance"){ui->tableView_2->setModel(tempmatmaint.tri_ref());}
}


void gestion_materiaux::on_supprimer_mat_maint_tab_clicked()
{
    int ref=ui->tableView_2->currentIndex().data().toInt();
      bool test=tempmatmaint.supprimer(ref);
      if(test)
      {
          ui->tableView_2->setModel(tempmatmaint.afficher());
          ui->referance_mat_maint_supprimer_combobox_1->setModel(tempmatmaint.afficher());
          ui->comboBox_rechercher_mat_maint->setModel(tempmatmaint.afficher());
          ui->referance_mat_maint_modifier->setModel(tempmatmaint.afficher());
                      QMessageBox::information(nullptr, QObject::tr("Supprimer un materiel"),
                      QObject::tr("materiel supprimé.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

      }
      else
                      QMessageBox::critical(nullptr, QObject::tr("Supprimer un materiel"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}


void gestion_materiaux::on_comboBox_rechercher_mat_maint_activated(int index)
{
    QString ref= QString::number(index);
        QString reff = ui->comboBox_rechercher_mat_maint->currentText();
       ui->tableView_2->setModel(tempmatmaint.afficher_rech(reff));
}
