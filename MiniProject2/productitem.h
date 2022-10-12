#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include <QTreeWidgetItem>

class ProductItem : public QTreeWidgetItem
{
public:
    explicit ProductItem(int id = 0, QString = "", QString = "", QString = "");

    QString getName() const;
    void setName(QString&);
    QString getPrice() const;
    void setPrice(QString&);
    QString getStock() const;
    void setStock(QString&);
    int id() const;
    bool operator==(const ProductItem &other) const;
};

#endif // PRODUCTITEM_H
