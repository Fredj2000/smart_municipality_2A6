#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class arduino_code
{
private:
QSerialPort * serial ;  // cet objet rassemble des info ( vitesse , bit ) sur ce qu'est  une voie série pour arduino
static const quint16 arduino_uno_vendor_id=9025;
static const quint16 arduino_uno_producy=67;
QString arduino_port_name ;
bool arduino_is_available ;
QByteArray data; // contien les donnes lues  a partire d'arduino



public:
arduino_code();
int connect_arduino(); //connecter pc et arduino
int close_arduino();   // fermer connection
int write_to_arduino(QByteArray);//envoyer des donneés vers arduino
QByteArray read_from_arduino(); //recevoir des donnees de arduino
QSerialPort *getserial(); //accesseur
QString getarduino_port_name();

};
#endif // ARDUINO_H
