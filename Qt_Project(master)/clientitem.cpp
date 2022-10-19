#include "clientitem.h"

#include <QLabel>
#include <iostream>

using namespace std;

ClientItem::ClientItem(int id, QString name, QString phoneNumber, QString address)
{
    setText(0, QString::number(id));
    setText(1, name);
    setText(2, phoneNumber);
    setText(3, address);
}

QString ClientItem::getName() const
{
    return text(1);
}

void ClientItem::setName(QString& name)
{
    setText(1, name);
}

QString ClientItem::getPhoneNumber() const
{
    return text(2);
}

void ClientItem::setPhoneNumber(QString& phoneNumber)
{
    setText(2, phoneNumber);    // c_str() --> const char*
}

QString ClientItem::getAddress() const
{
    return text(3);
}

void ClientItem::setAddress(QString& address)
{
    setText(3, address);
}

int ClientItem::id() const
{
    return text(0).toInt();
}

// Define copy assignment operator.
bool ClientItem::operator==(const ClientItem &other) const {
    return (this->text(1) == other.text(1));
}
