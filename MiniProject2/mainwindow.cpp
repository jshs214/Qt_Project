#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "clientmanagerform.h"
#include "productmanagerform.h"
#include "ordermanagerform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    clientForm = new ClientManagerForm(this);
    clientForm->setWindowTitle(tr("Client Info"));
    //connect(clientForm, SIGNAL(destroyed()),
    //        clientForm, SLOT(deleteLater()));
    productForm = new ProductManagerForm(this);
    productForm->setWindowTitle(tr("Product Info"));

    orderForm = new OrderManagerForm(this);
    orderForm->setWindowTitle(tr("Order Info"));

    connect(orderForm, SIGNAL(clientNameSent(QString)),   //검색 후 리스트 출력을 위한 시그널 슬롯
            clientForm, SLOT(receiveClientName(QString)));
    connect(clientForm,SIGNAL(clientdataSent(ClientItem*)),
            orderForm, SLOT(receiveClientData(ClientItem*)));
    connect(orderForm, SIGNAL(productNameSent(QString)),  //검색 후 리스트 출력을 위한 시그널 슬롯
            productForm, SLOT(receiveProductName(QString)));
    connect(productForm,SIGNAL(productdataSent(ProductItem*)),
            orderForm, SLOT(receiveProductData(ProductItem*)));

    connect(orderForm, SIGNAL(clientKeySent(int)),      //클릭시 리스트 출력을 위한 시그널 슬롯
            clientForm, SLOT(receiveClientKey(int)));
    connect(clientForm, SIGNAL( clickClientSent(ClientItem*)),
            orderForm, SLOT(receive_ClientTreewidget_itemclicked(ClientItem*)));

    connect(orderForm, SIGNAL(productKeySent(int)), //클릭시 리스트 출력을 위한 시그널 슬롯
            productForm, SLOT(receiveProductKey(int)));
    connect(productForm, SIGNAL( clickProductSent(ProductItem*)),
            orderForm, SLOT(receive_ProductTreewidget_itemclicked(ProductItem*)));

    connect(orderForm, SIGNAL(productAddKeySent(int, QString)),     //키값(재고)를 위한 시그널 슬롯(add)
            productForm, SLOT(receiveAddStock(int, QString)));
    connect(orderForm, SIGNAL(productModKeySent(int,QString,QString)),//키값(재고)를 위한 시그널 슬롯(mod)
            productForm, SLOT(receiveModStock(int, QString, QString)));
    connect(orderForm, SIGNAL(removedataSent(int, QString)),        //키값(재고)를 위한 시그널 슬롯(del)
            productForm, SLOT(receiveDelStock(int, QString)));

    QMdiSubWindow *cw = ui->mdiArea->addSubWindow(clientForm);
    ui->mdiArea->addSubWindow(productForm);
    ui->mdiArea->addSubWindow(orderForm);

    ui->mdiArea->setActiveSubWindow(cw);    //없으면 마지막으로 추가한 subWindow가 열림
}

MainWindow::~MainWindow()
{
    delete clientForm;
    delete productForm;
    delete orderForm;
    delete ui;
}

void MainWindow::on_actionClient_triggered()
{
    if(clientForm != nullptr) {
        clientForm->setFocus();
    }
}


void MainWindow::on_actionproduct_triggered()
{
    if(productForm != nullptr) {
        productForm->setFocus();
    }
}


void MainWindow::on_actionOrder_triggered()
{
    if(orderForm != nullptr) {
        orderForm->setFocus();
    }
}

