#ifndef CHATTINGITEM_H
#define CHATTINGITEM_H

#include <QTreeWidgetItem>

class chattingitem : public QTreeWidgetItem
{
public:
    explicit chattingitem(QString="", QString="" , QString = "", QString = "", QString = "");
    QString getStatus() const;
    QString getName() const;
    QString getID() const;
    QString getPhoneNum() const;
    QString getAddress() const;


};

#endif // CHATTINGITEM_H
