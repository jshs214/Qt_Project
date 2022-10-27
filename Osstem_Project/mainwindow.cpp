#include "mainwindow.h"
#include "qmenubar.h"
#include "ui_mainwindow.h"

#include "chattingform.h"
#include "clientmanagerform.h"
#include "productmanagerform.h"
#include "ordermanagerform.h"
#include "chatserverform.h"
#include "chattingform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* ui 툴바 및 액션 설정 */
    ui->toolBar->setAllowedAreas(Qt::RightToolBarArea);
    ui->actionClient->setIcon(QIcon(":/images/client.png"));
    ui->actionproduct->setIcon(QIcon(":/images/product.png"));
    ui->actionOrder->setIcon(QIcon(":/images/order.png"));
    ui->actionServer->setIcon(QIcon(":/images/server.png"));
    ui->actionChat->setIcon(QIcon(":/images/chat.png"));
    ui->actionQuit->setIcon(QIcon(":/images/quit.png"));
    ui->toolBar->setIconSize(QSize(66, 66));
    setContextMenuPolicy (Qt::NoContextMenu);

    clientForm = new ClientManagerForm(this);
    connect(clientForm, SIGNAL(destroyed()),
            clientForm, SLOT(deleteLater()));
    productForm = new ProductManagerForm(this);
    connect(productForm, SIGNAL(destroyed()),
            productForm, SLOT(deleteLater()));
    orderForm = new OrderManagerForm(this);
    connect(orderForm, SIGNAL(destroyed()),
            orderForm, SLOT(deleteLater()));
    serverForm = new ChatServerForm(this);
    connect(serverForm, SIGNAL(destroyed()),
            serverForm, SLOT(deleteLater()));

    /* 고객,제품의 데이터를 주문정보로 넘겨주는 시그널 슬롯 */
    connect(orderForm, SIGNAL(clientNameSent(QString)),
            clientForm, SLOT(receiveClientName(QString)));
    connect(clientForm,SIGNAL(clientDataSent(ClientItem*)),
            orderForm, SLOT(receiveClientData(ClientItem*)));
    connect(orderForm, SIGNAL(productNameSent(QString)),
            productForm, SLOT(receiveProductName(QString)));
    connect(productForm,SIGNAL(productDataSent(ProductItem*)),
            orderForm, SLOT(receiveProductData(ProductItem*)));

    /*클릭시 리스트 출력을 위한 시그널 슬롯*/
    connect(orderForm, SIGNAL(clientKeySent(int)),
            clientForm, SLOT(receiveClientKey(int)));
    connect(clientForm, SIGNAL( clickClientSent(ClientItem*)),
            orderForm, SLOT(receive_ClientTreewidget_itemclicked(ClientItem*)));
    /*클릭시 리스트 출력을 위한 시그널 슬롯*/
    connect(orderForm, SIGNAL(productKeySent(int)),
            productForm, SLOT(receiveProductKey(int)));
    connect(productForm, SIGNAL( clickProductSent(ProductItem*)),
            orderForm, SLOT(receive_ProductTreewidget_itemclicked(ProductItem*)));

    /*키값(재고)를 위한 시그널 슬롯 */
    connect(orderForm, SIGNAL(productAddKeySent(int, QString)),       //주문 추가
            productForm, SLOT(receiveAddStock(int, QString)));
    connect(orderForm, SIGNAL(productModKeySent(int,QString,QString)),//주문 변경
            productForm, SLOT(receiveModStock(int, QString, QString)));
    connect(orderForm, SIGNAL(removedataSent(int, QString)),        //주문 삭제
            productForm, SLOT(receiveDelStock(int, QString)));

    /* 고객정보를 채팅서버로 넘겨주는 시그널 슬롯 */
    connect(clientForm, SIGNAL(addClient(int, QString) ),
            serverForm, SLOT(addClient(int, QString)));
    connect(clientForm, SIGNAL(remClient(int) ),
            serverForm, SLOT(remClient(int)) );

    /* 파일의 데이터 입력하는 메서드 */
    clientForm->loadData();
    productForm->loadData();
    orderForm->loadData();

    /* ui 설정 */
    ui->stackedWidget->insertWidget(0, clientForm);
    ui->stackedWidget->insertWidget(1, productForm);
    ui->stackedWidget->insertWidget(2, orderForm);
    ui->stackedWidget->insertWidget(3, serverForm);
    clientForm->showMaximized();
    ui->stackedWidget->setCurrentIndex(0);
    this->setWindowTitle("Qt_Project");
}

MainWindow::~MainWindow()
{
    delete clientForm;
    delete productForm;
    delete orderForm;
    delete serverForm;
    delete chattingForm;
    delete ui;
}

/* 고객정보 슬롯 */
void MainWindow::on_actionClient_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/* 제품정보 슬롯 */
void MainWindow::on_actionproduct_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/* 주문정보 슬롯 */
void MainWindow::on_actionOrder_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

/* 채팅서버 슬롯 */
void MainWindow::on_actionServer_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

/* 채팅창 open하는 슬롯 */
void MainWindow::on_actionChat_triggered()
{
    chattingForm = new ChattingForm;
    chattingForm->show();
}


