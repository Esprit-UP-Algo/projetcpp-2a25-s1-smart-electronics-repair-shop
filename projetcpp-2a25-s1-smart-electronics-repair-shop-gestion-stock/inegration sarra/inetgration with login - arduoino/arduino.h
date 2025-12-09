#ifndef ARDUINO_H
#define ARDUINO_H

#include <QByteArray>
#include <QSerialPort>
#include <QSerialPortInfo>

class Arduino
{
public:
    Arduino();
    ~Arduino();
    int connect_arduino();
    int close_arduino();
    void write_to_arduino(QByteArray);
    QByteArray read_from_arduino();
    QSerialPort* getserial() { return serial; }
    QString getarduino_port_name() { return arduino_port_name; }
    bool isConnected() { return (serial && serial->isOpen()); } // ADDED

private:
    QSerialPort *serial;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_producy_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;
};

#endif // ARDUINO_H
