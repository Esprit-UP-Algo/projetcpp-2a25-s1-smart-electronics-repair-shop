#ifndef ARDUINO_H
#define ARDUINO_H

#include <QByteArray>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>

class Arduino
{
public:
    Arduino();                      // Default constructor
    ~Arduino();                     // Destructor
    int connect_arduino();          // Connect to Arduino
    int close_arduino();            // Close connection
    void write_to_arduino(QByteArray data);  // Send data
    QByteArray read_from_arduino();         // Read data
    QSerialPort* getserial() { return serial; }
    QString getarduino_port_name() { return arduino_port_name; }

private:
    QSerialPort *serial;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;
};

#endif // ARDUINO_H
