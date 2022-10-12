#include "productitem.h"

#include <QLabel>
#include <iostream>

using namespace std;

ProductItem::ProductItem(int id, QString name, QString price, QString stock)
{
    setText(0, QString::number(id));
    setText(1, name);
    setText(2, price);
    setText(3, stock);
}

QString ProductItem::getName() const
{
    return text(1);
}

void ProductItem::setName(QString& name)
{
    setText(1, name);
}

QString ProductItem::getPrice() const
{
    return text(2);
}

void ProductItem::setPrice(QString& phoneNumber)
{
    setText(2, phoneNumber);    // c_str() --> const char*
}

QString ProductItem::getStock() const
{
    return text(3);
}

void ProductItem::setStock(QString& address)
{
    setText(3, address);
}

int ProductItem::id() const
{
    return text(0).toInt();
}

// Define copy assignment operator.
bool ProductItem::operator==(const ProductItem &other) const {
    return (this->text(1) == other.text(1));
}

