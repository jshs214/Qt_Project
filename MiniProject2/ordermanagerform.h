#ifndef ORDERMANAGERFORM_H
#define ORDERMANAGERFORM_H

#include "clientitem.h"
#include "productitem.h"
#include "orderitem.h"
#include <QWidget>
#include <QWidget>
#include <QHash>

class QMenu;
class QTreeWidgetItem;

namespace Ui {
class OrderManagerForm;
}

class OrderManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit OrderManagerForm(QWidget *parent = nullptr);
    ~OrderManagerForm();

private slots:
    /* QTreeWidget을 위한 슬롯 */
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void showContextMenu(const QPoint &);
    void removeItem();              /* QAction을 위한 슬롯 */
    void on_addPushButton_clicked();
    void on_modifyPushButton_clicked();
    void on_searchPushButton_clicked();
    void on_pushButton_clicked();
    void on_cbutton_clicked();
    void on_pbutton_clicked();
    void on_clearbutton_clicked();  //clear 버튼

    void on_clienttreeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_producttreeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void receiveClientData(ClientItem*);
    void receiveProductData(ProductItem*);

    void receive_ClientTreewidget_itemclicked(ClientItem*);
    void receive_ProductTreewidget_itemclicked(ProductItem*);



    void on_pushButton_2_clicked();

private:
    int makeId();

    QMap<int, OrderItem*> orderList;
    Ui::OrderManagerForm *ui;
    QMenu* menu;

signals:
    void clientNameSent(QString);
    void productNameSent(QString);
    void removedataSent(int, QString);
    void productAddKeySent(int, QString);
    void productModKeySent(int, QString, QString);

    void clientKeySent(int);
    void productKeySent(int);
};

#endif // ORDERMANAGERFORM_H
