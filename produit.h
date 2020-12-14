#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QSql>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>
#include "statistique_produit.h"
#include <QDialog>
#include <QIdentityProxyModel>
#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QAbstractTableModel>
#include <QVariant>
#include <QBrush>
#include <QMouseEvent>

class  produit
{
public:
    QString reference;
        QString nom;
        QString quantite;
        QString prix;

public:
     produit();
     produit(const QString &reference, const QString &nom, const QString &quantite, const QString &prix);
     const QString &getNom() const;

     void setNom(const QString &nom);
     const QString &getreference() const;

    void setreference(const QString &reference);

    const QString &getquantite() const;

    void setquantite(const QString &quantite);

    const QString &getprix() const;

    void setprix(const QString &prix);
 bool add();
 QSqlQueryModel *list();
 bool delet();
 QSqlQueryModel *tri2();
 QSqlQueryModel * afficher_Reference();

};

#endif
