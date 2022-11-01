#ifndef CLIENTITEM_H
#define CLIENTITEM_H

#include <QTreeWidgetItem>

/* 고객정보의 데이터를 관리하는 클래스*/
class ClientItem : public QTreeWidgetItem
{
public:
    /* 고객명, 고객ID, 전화번호, 주소 */
    explicit ClientItem(int id = 0, QString = "", QString = "", QString = "");

    QString getName() const;
    void setName(QString&);
    QString getPhoneNumber() const;
    void setPhoneNumber(QString&);
    QString getAddress() const;
    void setAddress(QString&);
    int id() const;
    bool operator==(const ClientItem &other) const;
};

#endif // CLIENTITEM_H
