#include "arduino.h"
#include <QDebug>

Arduino::Arduino()
{
    serial = new QSerialPort(); // no parent
    arduino_is_available = false;
    arduino_port_name = "";
}

Arduino::~Arduino()
{
    if (serial->isOpen())
        serial->close();
    delete serial;
}

int Arduino::connect_arduino()
{
    // Set COM port directly
    arduino_port_name = "COM7";
    serial->setPortName(arduino_port_name);

    if(serial->open(QIODevice::ReadWrite)) {
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        arduino_is_available = true;
        qDebug() << "Arduino connected on:" << arduino_port_name;
        return 0; // success
    } else {
        qDebug() << "Failed to open Arduino port:" << arduino_port_name;
        return 1; // failed
    }
}

int Arduino::close_arduino()
{
    if(serial->isOpen()) {
        serial->close();
        return 0;
    }
    return 1;
}

QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable()) {
        data = serial->readAll();
        return data;
    }
    return QByteArray();
}

void Arduino::write_to_arduino(QByteArray d)
{
    if(serial->isWritable()) {
        serial->write(d);
    } else {
        qDebug() << "Can't write to Arduino serial";
    }
}
