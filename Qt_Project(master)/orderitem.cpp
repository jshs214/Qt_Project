#include "orderitem.h"

#include <QLabel>
#include <iostream>

using namespace std;

OrderItem::OrderItem(int id, QString client, QString product,
                     QString stock, QString price , QString sum, QString address)
{
    setText(0, QString::number(id));
    setText(1, client);
    setText(2, product);
    setText(3, stock);
    setText(4, price);
    setText(5, sum);
    setText(6, address);
}

QString OrderItem::getClient() const
{
    return text(1);
}

void OrderItem::setClient(QString& client)
{
    setText(1, client);
}

QString OrderItem::getProduct() const
{
    return text(2);
}

void OrderItem::setProduct(QString& product)
{
    setText(2, product);    // c_str() --> const char*
}

QString OrderItem::getStock() const
{
    return text(3);
}

void OrderItem::setStock(QString& stock)
{
    setText(3, stock);
}

QString OrderItem::getPrice() const
{
    return text(4);
}
void OrderItem::setPrice(QString& price)
{
    setText(4, price);
}
QString OrderItem::getSum() const
{
    return text(5);
}
void OrderItem::setSum(QString& sum)
{
    setText(5, sum);
}
QString OrderItem::getAddress() const
{
    return text(6);
}
void OrderItem::setAddress(QString& address)
{
    setText(6, address);
}


int OrderItem::id() const
{
    return text(0).toInt();
}

// Define copy assignment operator.
bool OrderItem::operator==(const OrderItem &other) const {
    return (this->text(1) == other.text(1));
}
