#include "connection.h"
//test connection git
Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test=false;
  QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
  db.setDatabaseName("projet2A");
  db.setUserName("ahmed");
  db.setPassword("esprit20");

  if (db.open())
      test=true;

  return test ;

}
