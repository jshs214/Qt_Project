#ifndef CLIENTITEM_H
#define CLIENTITEM_H

#include <QTreeWidgetItem>

class ClientItem : public QTreeWidgetItem
{
public:
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
