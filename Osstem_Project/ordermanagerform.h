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
    void loadData();    /* 파일의 데이터 입력하는 메서드 */
private slots:
    void on_clientButton_clicked(); /* 고객의 ID나 이름을 입력받아 전달하고 관련 데이터를 받아오는 슬롯 */
    void on_productButton_clicked(); /* 제품의 ID나 제품명을 입력받아 전달하고 관련 데이터를 받아오는 슬롯 */
    void receive_ClientTreewidget_itemclicked(ClientItem*); /* 고객 리스트 데이터 클릭 시 출력하는 슬롯 */
    void receive_ProductTreewidget_itemclicked(ProductItem*); /* 제품 리스트 데이터 클릭 시 출력하는 슬롯 */

    void receiveClientData(ClientItem*);    /* 고객정보 데이터를 받아 트리위젯에 출력하는 슬롯 */
    void receiveProductData(ProductItem*);  /* 제품정보 데이터를 받아 트리위젯에 출력하는 슬롯 */

    void on_clientTreeWidget_itemClicked(QTreeWidgetItem *item, int column); /* 고객정보 데이터 클릭 시 입력되는 슬롯 */
    void on_productTreeWidget_itemClicked(QTreeWidgetItem *item, int column); /* 제품정보 데이터 클릭 시 입력되는 슬롯 */

    void on_addPushButton_clicked();    /* 주문정보추가를 위한 슬롯 */
    void on_searchPushButton_clicked(); /* 주문정보검색을 위한 슬롯 */
    void on_statePushButton_clicked();  /* 검색결과 창에서 주문정보관리로 돌아오는 슬롯 */
    void on_modifyPushButton_clicked(); /* 주문정보변경을 위한 슬롯 */
    void showContextMenu(const QPoint &);   /* ContextMenu 슬롯 */
    void removeItem();  /* QAction을 위한 데이터 제거 슬롯 */

    void on_orderTreeWidget_itemClicked(QTreeWidgetItem *item, int column); /* 주문내역 클릭 시 관련정보 출력 슬롯*/
    void on_clearButton_clicked();/* 버튼 클릭 시 입력 값 초기화 하는 슬롯 */



private:
    int makeId();   /* ID(키 값) 생성 메서드*/
    QMap<int, OrderItem*> orderList;    // 주문내역 관리를 위한 orderList
    Ui::OrderManagerForm *ui;
    QMenu* menu;    //ContextMenu를 위한 메뉴

signals:
    void clientNameSent(QString); /* 고객의 ID나 이름을 입력받아 전달 */
    void productNameSent(QString); /* 제품의 ID나 이름을 입력받아 전달 */
    void productAddKeySent(int, QString);  /* 재고반영을 위해 제품키값과, 수량을 시그널로 보냄 */
    void productModKeySent(int, QString, QString); /* 재고반영을 위해 키값, 수정할 수량, 입력된 수량을 시그널로 보냄 */
    void removedataSent(int, QString);     /* 재고반영을 위해 데이터 제거 시, 제품 ID와 수량을 시그널로 보냄 */

    /* 고객, 제품의 리스트를 불러오기 위한 시그널 */
    void clientKeySent(int);
    void productKeySent(int);
};

#endif // ORDERMANAGERFORM_H
