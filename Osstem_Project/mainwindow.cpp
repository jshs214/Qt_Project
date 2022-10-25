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
    clientForm->setWindowTitle(tr("Client Info"));
    connect(clientForm, SIGNAL(destroyed()),
            clientForm, SLOT(deleteLater()));

    productForm = new ProductManagerForm(this);
    productForm->setWindowTitle(tr("Product Info"));
    connect(productForm, SIGNAL(destroyed()),
            productForm, SLOT(deleteLater()));

    orderForm = new OrderManagerForm(this);
    orderForm->setWindowTitle(tr("Order Info"));
    connect(orderForm, SIGNAL(destroyed()),
            orderForm, SLOT(deleteLater()));

    serverForm = new ChatServerForm(this);
    serverForm->setWindowTitle(tr("Chatting Server"));
    connect(serverForm, SIGNAL(destroyed()),
            serverForm, SLOT(deleteLater()));


    connect(orderForm, SIGNAL(clientNameSent(QString)),   //검색 후 고객리스트 출력을 위한 시그널 슬롯
            clientForm, SLOT(receiveClientName(QString)));
    connect(clientForm,SIGNAL(clientDataSent(ClientItem*)),
            orderForm, SLOT(receiveClientData(ClientItem*)));
    connect(orderForm, SIGNAL(productNameSent(QString)),  //검색 후 제품리스트 출력을 위한 시그널 슬롯
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
    connect(orderForm, SIGNAL(productAddKeySent(int, QString)),       //주문 시.
            productForm, SLOT(receiveAddStock(int, QString)));
    connect(orderForm, SIGNAL(productModKeySent(int,QString,QString)),//주문 변경 시.
            productForm, SLOT(receiveModStock(int, QString, QString)));
    connect(orderForm, SIGNAL(removedataSent(int, QString)),        //주문 삭제 시.
            productForm, SLOT(receiveDelStock(int, QString)));

    //ui->stackedWidget->setActiveSubWindow(cw);    //없으면 마지막으로 추가한 subWindow가 열림

    connect(clientForm, SIGNAL(addClient(int, QString) ),   //고객관리에서 데이터 추가 시 채팅서버에 고객리스트 추가
            serverForm, SLOT(addClient(int, QString)));
    connect(clientForm, SIGNAL(remClient(int) ),        //고객관리에서 데이터 삭제 시 채팅서버에 고객리스트 삭제
            serverForm, SLOT(remClient(int)) );

    clientForm->loadData();
    productForm->loadData();
    orderForm->loadData();

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
void MainWindow::on_actionClient_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_actionproduct_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_actionOrder_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionServer_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_actionChat_triggered()
{
    chattingForm = new ChattingForm;
    chattingForm->show();
}


