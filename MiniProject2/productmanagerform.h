#ifndef PRODUCTMANAGERFORM_H
#define PRODUCTMANAGERFORM_H

#include <QWidget>
#include <QHash>
#include "productitem.h"

class QMenu;
class QTreeWidgetItem;

namespace Ui {
class ProductManagerForm;
}

class ProductManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductManagerForm(QWidget *parent = nullptr);
    ~ProductManagerForm();

private slots:
    /* QTreeWidget을 위한 슬롯 */
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void showContextMenu(const QPoint &);
    void removeItem();              /* QAction을 위한 슬롯 */
    void on_addPushButton_clicked();
    void on_modifyPushButton_clicked();
    void on_searchPushButton_clicked();
    void on_pushButton_clicked();

    void receiveProductName(QString);
    void receiveAddStock(int, QString);
    void receiveModStock(int, QString, QString);
    void receiveDelStock(int, QString);

    void receiveProductKey(int);
    void on_clearbutton_clicked();

    void on_ProductManagement_clicked();

private:
    int makeId();

    QMap<int, ProductItem*> productList;
    Ui::ProductManagerForm *ui;
    QMenu* menu;

signals:
    void productdataSent(ProductItem*);
    void clickProductSent(ProductItem*);
};

#endif // CLIENTMANAGERFORM_H
