#include "arduino.h"
#include <QDebug>
#include <QThread>

Arduino::Arduino() :
    serial(nullptr),
    arduino_is_available(false)
{
    serial = new QSerialPort();
}

Arduino::~Arduino()
{
    if (serial) {
        if (serial->isOpen()) {
            serial->close();
        }
        delete serial;
    }
}

int Arduino::connect_arduino()
{
    arduino_is_available = false;
    arduino_port_name = "";

    // If already open, close first
    if (serial && serial->isOpen()) {
        qDebug() << "Closing existing connection...";
        serial->setDataTerminalReady(false);
        serial->setRequestToSend(false);
        serial->close();
        QThread::msleep(100);
    }

    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                break;
            }
        }
    }

    qDebug() << "Arduino port name is:" << arduino_port_name;

    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);

        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);

            // CRITICAL: Prevent Arduino auto-reset
            serial->setDataTerminalReady(false);
            serial->setRequestToSend(false);

            serial->clear();
            serial->flush();

            // Shorter wait time
            QThread::msleep(500);

            qDebug() << "Serial port opened (DTR/RTS disabled)";
            return 0;
        } else {
            qDebug() << "Failed to open:" << serial->errorString();
            return 1;
        }
    }
    return -1;
}

int Arduino::close_arduino()
{
    if (serial && serial->isOpen()) {
        // Don't trigger reset on close
        serial->setDataTerminalReady(false);
        serial->setRequestToSend(false);
        serial->flush();
        QThread::msleep(50);
        serial->close();
        qDebug() << "Connection closed (no reset)";
        return 0;
    }
    return 1;
}

QByteArray Arduino::read_from_arduino()
{
    if (serial && serial->isReadable()) {
        data = serial->readAll();
        return data;
    }
    return QByteArray();
}

void Arduino::write_to_arduino(QByteArray d)
{
    if (serial && serial->isWritable()) {
        serial->write(d);
    }
}
