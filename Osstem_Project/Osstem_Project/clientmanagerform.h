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

/* 고객정보관리 클래스 */
class ClientManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientManagerForm(QWidget *parent = nullptr);
    ~ClientManagerForm();
    void loadData();    /* 파일의 데이터 입력하는 메서드 */

private:
    QMenu* menu;    //ContextMenu를 위한 메뉴
    QMap<int, ClientItem*> clientList;  // 등록된 고객 관리를 위한 clientList
    Ui::ClientManagerForm *ui;

    int makeId();   /* ID(키 값) 생성 메서드*/

signals:
    void clientDataSent(ClientItem*);   /* id나 이름에 해당하는 데이터를 보내주는 시그널*/
    void clickClientSent(ClientItem*);  /* id에 해당하는 데이터를 보내주는 시그널*/
    void addClient(int, QString);       /* 채팅서버에서 등록된 고객을 알기 위해 id, 이름을 시그널로 보냄 */
    void remClient(int);                /* 채팅서버에서 삭제된 고객을 알기 위해 id를 시그널로 보냄 */

private slots:
    void on_addPushButton_clicked();        /* 고객정보추가를 위한 슬롯 */
    void on_modifyPushButton_clicked();     /* 고객정보변경을 위한 슬롯 */
    void on_searchPushButton_clicked();     /* 고객정보검색을 위한 슬롯 */
    void on_statePushButton_clicked();      /* 검색결과 창에서 고객정보관리로 돌아오는 슬롯 */
    void showContextMenu(const QPoint &);   /* ContextMenu 슬롯 */
    void removeItem();  /* 고객정보의 데이터(트리위젯)의 리스트 제거 슬롯 */
    void on_clientTreeWidget_itemClicked(QTreeWidgetItem *item, int column);    /* 등록된 고객정보 클릭 시 관련정보 출력 슬롯*/
    void receiveClientName(QString);     /* Order에서 고객 id나 이름을 받아오는 슬롯*/
    void receiveClientKey(int);          /* 고객 id 값을 받아오는 슬롯 */

    void on_clearButton_clicked();       /* 버튼 클릭 시 입력 값 초기화 하는 슬롯 */

};

#endif // CLIENTMANAGERFORM_H
