#include "chattingitem.h"

chattingitem::chattingitem(QString status, QString name,
                           QString id, QString phonenum, QString address)
{
    setText(0, status);
    setText(1, name);
    setText(2, id);
    setText(3, phonenum);
    setText(4, address);
}
QString chattingitem::getStatus() const
{
    return text(0);
}
QString chattingitem::getName() const
{
    return text(1);
}

QString chattingitem::getID() const
{
    return text(2);
}

QString chattingitem::getPhoneNum() const
{
    return text(3);
}
QString chattingitem::getAddress() const
{
    return text(4);
}

