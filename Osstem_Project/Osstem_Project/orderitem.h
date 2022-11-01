#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <QTreeWidgetItem>

/* 주문정보의 데이터를 관리하는 클래스*/
class OrderItem :public QTreeWidgetItem
{
public:
    /* 주문번호, 고객, 제품, 주문수량, 가격, 총 합, 주소 */
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
