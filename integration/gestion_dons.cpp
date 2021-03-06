#include "gestion_dons.h"
#include "ui_gestion_dons.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include<QMessageBox>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>



gestion_dons::gestion_dons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestion_dons)
{
    ui->setupUi(this);
    //update table don
     ui->tableDon->setModel(tmp1.afficher());
    //update table famille
     ui->table_famille->setModel(tmp2.afficher());
     ui->id_don_ajouter_famille->setModel(tmp1.afficher());
     gestion_dons::afficherStatistique();



}





gestion_dons::~gestion_dons()
{
    delete ui;
}



//------------------------------------------ CRUD DON ----------------------------------------------------//
//ajouter don


void gestion_dons::on_ajoute_don_clicked()
{
    QMessageBox msg;


        int matricule=ui->matricule_ajouter_don->text().toInt();
        int valeur=ui->valeur_ajouter_don->text().toInt();

        QString source=ui->Source_ajouter_don->text();
        QString type;
        QString autre;

    if(ui->argent->isChecked())
    {
        type="argent";
        autre="-";
    }
    else if(ui->autre->isChecked())
    {
        type="autre";
        autre=ui->autre_ajouter_don->currentText();
        valeur=0;
    }
    //don constructor
        Don d(matricule ,valeur ,source ,autre ,type);

    if(d.ajouter())
    {
    ui->tableDon->setModel(tmp1.afficher());
    msg.setText("add succ");
    msg.exec();

    }else
    {
        msg.setText("failed to add");
        msg.exec();
    }
}

void gestion_dons::on_supprimer_don_clicked()
{
    QMessageBox msg;
        Don d;
        int matricule =ui->matricule_supprimer_don->text().toInt();
        if(d.supprimer(matricule)){
            ui->tableDon->setModel(tmp1.afficher());
            msg.setText("element deleted succ");
            msg.exec();

        }
        else
        {
            msg.setText("failed to delete");
            msg.exec();
        }
}



void gestion_dons::on_modifier_don_clicked()
{
    QMessageBox msg;
       int matricule=ui->matricule_modifier_don->text().toInt();
       int valeur=ui->valeur_modifier_don->text().toInt();
       QString source=ui->source_modifier_don->text();
       QString type;
       if(ui->argent_modifier->isChecked()){ type =ui->argent_modifier->text();}
       if(ui->autre_modifier->isChecked()){ type =ui->autre_modifier->text();}
       QString autre;
        autre = ui->autre_modifier_don->currentText();

       if(ui->argent->isChecked())
       {
           type="argent";
           autre="N/A";
       }
       else if(ui->autre->isChecked())
       {
           type="autre";
           autre=ui->autre_modifier_don->currentText();
           valeur=0;
       }

       Don d;
   if(d.modifier(matricule,valeur,source,autre,type))
   {
   ui->tableDon->setModel(tmp1.afficher());
   msg.setText("update succ");
   msg.exec();

   }
   else
   {
       msg.setText("failed to update");
       msg.exec();
    }
}


//-----------------------------------CRUD FAMILLE--------------------------------------------//

void gestion_dons::on_ajouter_famille_clicked()
{
    QMessageBox msg;


            int matricule=ui->matricule_ajouter_famille->text().toInt();
            int nb_membres=ui->nombre_ajouter_famille->text().toInt();
            int don=ui->id_don_ajouter_famille->currentText().toInt();
            QString nom=ui->nom_ajouter_famille->text();
            QString besoin=ui->besoin_ajouter_famille->currentText();
            QString region=ui->region_ajouter_famille->text();



         famille f(matricule,nb_membres,don,nom,besoin,region);
           //famille f(matricule,nb_membres,don,nom,besoin,region);
        if(f.ajouter())
        {
        ui->table_famille->setModel(tmp2.afficher());
        msg.setText("add succ");
        msg.exec();

        }else{
            msg.setText("failed to add");
            msg.exec();
        }
    }


void gestion_dons::on_supprimer_famille_clicked()
{
    QMessageBox msg;
        famille f;
        int matricule =ui->matricule_supprimer_famille->text().toInt();

        if(f.supprimer(matricule)){
    ui->table_famille->setModel(tmp2.afficher());
    msg.setText("famille deleted succ");
            msg.exec();

        }else {
            msg.setText("failed to delete");
            msg.exec();
        }
}



void gestion_dons::on_modifier_famille_clicked()
{
    QMessageBox msg;


        int matricule=ui->matricule_modifier_famille->text().toInt();
        int nb_membres=ui->nombre_modifier_famille->text().toInt();
        int don=ui->id_don_modifier_famille->currentText().toInt();
        QString nom=ui->nom_modifier_famille->text();
        QString besoin=ui->besoin_modifier_famille->currentText();
        QString region=ui->region_modifier_famille->text();



     famille f;
     //(int matricule ,int nbr_membres,int don ,QString nom ,QString besoin ,QString region)
    if(f.modifier(matricule,nb_membres,don,nom,besoin,region))
    {
    ui->table_famille->setModel(tmp2.afficher());
    msg.setText("update succ");
    msg.exec();

    }
    else
    {
        msg.setText("failed to update");
        msg.exec();

}
   }
//----------------------------------------------les metiers--------------------------------//


void gestion_dons::on_afficher_don_trier_clicked()
{

    if(ui->matricule_trie->isChecked())
    {

        ui->tableDon->setModel(tmp1.afficherMatricule());
    }
    else if(ui->type_trie->isChecked())
    {

        ui->tableDon->setModel(tmp1.afficherType());
    }
    else
    {
        ui->tableDon->setModel(tmp1.afficher());
    }
}

void gestion_dons::on_afficher_tri_famille_clicked()
{
    if(ui->besoin_trie_famille->isChecked())
    {
        ui->table_famille->setModel(tmp2.afficherBesoin());

    }
    else if(ui->nbr_trie_famille->isChecked())
    {

        ui->table_famille->setModel(tmp2.afficherNBR());
    }
    else
    {
        ui->table_famille->setModel(tmp2.afficher());
    }
}

//recherche par nom dynamique

void gestion_dons::on_recherche_dynamique_famille_textChanged(const QString &arg1)
{
    ui->table_famille->setModel(tmp2.rechercheDynamic(arg1));
}

//statistique!!!!!!!!!!!!!!!!!
void gestion_dons::afficherStatistique(){


    QSqlQuery query;

    //nombre de dons
            QString nb_don="";
            query.prepare("SELECT COUNT(*) FROM DON");
            query.exec();
            while(query.next()){
            nb_don= query.value(0).toString();}

     //nombre de famille

            QString nb_famille="";
            query.prepare("SELECT COUNT(*) FROM FAMILLES");
            query.exec();
            while(query.next()){
            nb_famille= query.value(0).toString();}



        QBarSet *set0 = new QBarSet("Jane");


           *set0 << nb_don.toInt()  << nb_famille.toInt()   ;
        QBarSeries *series = new QBarSeries();
         series->append(set0);
         QChart *chart = new QChart();
             chart->addSeries(series);
             chart->setTitle("statistique dons");
             chart->setAnimationOptions(QChart::SeriesAnimations);

             QStringList categories;
                categories << "nombre don" <<  "nombre famille" ;
                QBarCategoryAxis *axisX = new QBarCategoryAxis();
                axisX->append(categories);
                chart->addAxis(axisX, Qt::AlignBottom);
                series->attachAxis(axisX);



                chart->legend()->setVisible(true);
                    chart->legend()->setAlignment(Qt::AlignBottom);

                    QChartView *chartView = new QChartView(chart);
                    chartView->setRenderHint(QPainter::Antialiasing);
                    chartView->setParent(ui->horizontalFrame);
}
