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

/* 제품정보관리 클래스 */
class ProductManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductManagerForm(QWidget *parent = nullptr);
    ~ProductManagerForm();
    void loadData();    /* 파일의 데이터 입력하는 메서드 */

private:
    int makeId();

    QMap<int, ProductItem*> productList;
    QMenu* menu;
    Ui::ProductManagerForm *ui;

signals:
    void productDataSent(ProductItem*);
    void clickProductSent(ProductItem*);

private slots:
    void on_addPushButton_clicked();        /* 제품정보추가를 위한 슬롯 */
    void on_modifyPushButton_clicked();     /* 제품정보변경을 위한 슬롯 */
    void on_searchPushButton_clicked();     /* 제품정보검색을 위한 슬롯 */
    void on_statePushButton_clicked();      /* 검색결과 창에서 제품정보관리로 돌아오는 슬롯 */
    void showContextMenu(const QPoint &);   /* ContextMenu 슬롯 */
    void removeItem();      /* 제품정보의 데이터(트리위젯)의 리스트 제거 슬롯 */
    void on_productTreeWidget_itemClicked(QTreeWidgetItem *item, int column);   /* 등록된 제품정보 클릭 시 관련정보 출력 슬롯*/

    void receiveProductName(QString);       /* Order에서 제품 id나 제품명을 받아오는 슬롯*/

    void receiveAddStock(int, QString);     /* Order에서 주문추가 시, 재고반영을 위한 슬롯 */
    void receiveModStock(int, QString, QString);    /* Order에서 주문변경 시, 재고반영을 위한 슬롯 */
    void receiveDelStock(int, QString);     /* Order에서 주문내역제거 시, 재고반영을 위한 슬롯 */

    void receiveProductKey(int);        /* 제품 id 값을 받아오는 슬롯 */
    void on_clearButton_clicked();      /* 버튼 클릭 시 입력 값 초기화 하는 슬롯 */

};

#endif // CLIENTMANAGERFORM_H
