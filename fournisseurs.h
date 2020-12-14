#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H
#include <QString>
#include <QSql>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>


class Fournisseurs
{
public:
    QString matricule;
        QString nom;
        QString adresse;
        QString tel;

public:
    Fournisseurs();
    Fournisseurs(const QString &matricule, const QString &nom, const QString &adresse, const QString &tel);
    const QString &getMatricule() const;

    void setMatricule(const QString &matricule);

    const QString &getNom() const;

    void setNom(const QString &nom);

    const QString &getAdresse() const;

    void setAdresse(const QString &adresse);

    const QString &getTel() const;

    void setTel(const QString &tel);
 bool add();
 QSqlQueryModel *list();
 bool delet();
QSqlQueryModel *tri1();
QSqlQueryModel * afficher_matricule();
};

#endif
