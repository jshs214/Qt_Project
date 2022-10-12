#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <QTreeWidgetItem>

class OrderItem :public QTreeWidgetItem
{
public:
    explicit OrderItem(int id = 0, QString = "", QString = "",
                       QString = "", QString = "", QString="", QString="");

    QString getClient() const;
    void setClient(QString&);
    QString getProduct() const;
    void setProduct(QString&);
    QString getStock() const;
    void setStock(QString&);
    QString getAddress() const;
    void setAddress(QString&);
    QString getPrice() const;
    void setPrice(QString&);
    QString getSum() const;
    void setSum(QString&);


    int id() const;
    bool operator==(const OrderItem &other) const;
};

#endif // ORDERITEM_H
