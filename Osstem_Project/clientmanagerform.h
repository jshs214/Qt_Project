#ifndef CLIENTMANAGERFORM_H
#define CLIENTMANAGERFORM_H

#include <QWidget>
#include <QHash>

#include <QTcpSocket>

#include "clientitem.h"

class QMenu;
class QTreeWidgetItem;

namespace Ui {
class ClientManagerForm;
}

class ClientManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientManagerForm(QWidget *parent = nullptr);
    ~ClientManagerForm();
    void loadData();

private slots:

    /* QTreeWidget을 위한 슬롯 */
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void showContextMenu(const QPoint &);
    void removeItem();              /* QAction을 위한 슬롯 */
    void on_addPushButton_clicked();
    void on_modifyPushButton_clicked();
    void on_searchPushButton_clicked();

    void receiveClientName(QString);
    void receiveClientKey(int);
    void on_ClientManagement_clicked();
    void on_clearButton_clicked();

private:
    int makeId();

    QMap<int, ClientItem*> clientList;
    Ui::ClientManagerForm *ui;
    QMenu* menu;


signals:
    void clientDataSent(ClientItem*);
    void clickClientSent(ClientItem*);
    void addClient(int, QString);
    void remClient(int);
};

#endif // CLIENTMANAGERFORM_H
