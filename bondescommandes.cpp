#include "Bondescommandes.h"
#include<QDebug>
#include<QString>
#include "ui_mainwindow.h"
#include "mainwindow.h"



Bondescommandes::Bondescommandes()
{

}
Bondescommandes::Bondescommandes(const QString &id, const QString &liste, const QString &type, const QString &prix,  const QString &matricule)
        : type(type), prix(prix), id(id), matricule(matricule) {}
 const QString &Bondescommandes::getIDdecommande() const {
  return id ;}

void Bondescommandes::setIDdecommande(const QString &id) {
    Bondescommandes:: id = id;
}
const QString &Bondescommandes::getListedeproduit() const {
    return liste;}
void Bondescommandes::setListedeproduit(const QString &liste) {
    Bondescommandes::liste = liste;
}
const QString &Bondescommandes::getTypedeproduit()  const {
    return type;
}
void Bondescommandes::setTypedeproduit(const QString &type) {
    Bondescommandes::type = type;
}
const QString &Bondescommandes::getPrixtotal() const {
    return prix;
}
void Bondescommandes::setPrixtotal(const QString &prix) {
    Bondescommandes:: prix = prix;
}

const QString &Bondescommandes::getMatricule() const {
    return matricule;}
void Bondescommandes::setMatricule(const QString &matricule) {
    Bondescommandes::matricule = matricule;
}
bool Bondescommandes::add()
{
    QSqlQuery query;

        query.prepare("INSERT INTO bondescommandes (ID_DE_COMMANDE, PRIX_TOTAL, TYPE_DE_PRODUIT, MATRICULE_DE_FOURNISSEUR, LISTE_DE_PRODUIT) "
                      "VALUES (?, ?, ?, ?,?)");
        query.bindValue(0, this->id);
        query.bindValue(1, this->prix);
        query.bindValue(2, this->type);
        query.bindValue(3, this->matricule);
        query.bindValue(4, this->liste);
        return query.exec();
}
QSqlQueryModel *Bondescommandes::list()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from bondescommandes");


    return model;

}
bool Bondescommandes::delet()

{
QSqlQuery query;
    query.prepare("delete from bondescommandes where ID_DE_COMMANDE =:todelete");
            query.bindValue(":todelete",id);
            return query.exec();

}
QSqlQueryModel *Bondescommandes::tri()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from bondescommandes order by Prix_total desc");


    return model;

}
