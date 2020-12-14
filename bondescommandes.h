#ifndef BONDESCOMMANDES_H
#define BONDESCOMMANDES_H
#include <QString>
#include <QSql>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>



class Bondescommandes
{
public:
    QString liste;
     QString type;
        QString prix;
        QString id;
        QString matricule;

public:
    Bondescommandes();
    Bondescommandes(const QString &id,const QString &liste, const QString &type, const QString &prix,  const QString &matricule);
    const QString &getListedeproduit() const;
    void setListedeproduit(const QString &liste);

    const QString &getTypedeproduit() const;
    void setTypedeproduit(const QString &type);

    const QString &getPrixtotal() const;
    void setPrixtotal(const QString &prix);

    const QString &getIDdecommande() const;
    void setIDdecommande(const QString &id);

    const QString &getMatricule() const;
    void setMatricule(const QString &matricule);

    bool add();
 QSqlQueryModel *list();
 bool delet();
QSqlQueryModel *tri();
QSqlQueryModel *tri1();
};

#endif
