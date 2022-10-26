#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include <QTreeWidgetItem>

/* 제품정보의 데이터를 관리하는 클래스*/
class ProductItem : public QTreeWidgetItem
{
public:
    /* 제품명, 제품ID, 가격, 재고 */
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
