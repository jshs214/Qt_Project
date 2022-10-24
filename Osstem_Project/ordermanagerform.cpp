#include "ordermanagerform.h"
#include "ui_ordermanagerform.h"

#include "ordermanagerform.h"

#include <QFile>
#include <QMenu>
#include <QMessageBox>

OrderManagerForm::OrderManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderManagerForm)
{
    ui->setupUi(this);

    /* ContextMenu의 remove 액션, 리스트의 데이터 삭제 */
    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));
    menu = new QMenu;
    menu->addAction(removeAction);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    /* ui의 트리위젯들의 열 너비 설정 */
    ui->clientTreeWidget->QTreeView::setColumnWidth(0,35);
    ui->clientTreeWidget->QTreeView::setColumnWidth(1,70);
    ui->clientTreeWidget->QTreeView::setColumnWidth(2,95);
    ui->productTreeWidget->QTreeView::setColumnWidth(0,35);
    ui->productTreeWidget->QTreeView::setColumnWidth(1,70);
    ui->productTreeWidget->QTreeView::setColumnWidth(2,95);
    ui->treeWidget->QTreeView::setColumnWidth(0,60);
    ui->treeWidget->QTreeView::setColumnWidth(1,100);
    ui->treeWidget->QTreeView::setColumnWidth(2,100);
    ui->treeWidget->QTreeView::setColumnWidth(3,40);

    ui->stockLineEdit->setValidator(new QIntValidator(0, 9999, this) ); //수량에 0~9999 범위의 숫자만 받도록

    connect(ui->searchLineEdit, SIGNAL(returnPressed()), this, SLOT(on_searchPushButton_clicked()));
}

/* 파일의 데이터 입력하는 메서드 */
void OrderManagerForm::loadData()
{
    QFile file("orderlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    /* 파일의 데이터를 ','로 파싱해서 입력 */
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int id = row[0].toInt();
            OrderItem* o = new OrderItem(id, row[1], row[2], row[3], row[4], row[5], row[6]);
            ui->treeWidget->addTopLevelItem(o);
            orderList.insert(id, o);
        }
    }
    file.close( );
}

/* 소멸자에서 파일 출력 */
OrderManagerForm::~OrderManagerForm()
{
    delete ui;

    QFile file("orderlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) //읽기 전용, text가 아닐 경우의 예외처리
        return;

    /* 파일의 데이터를 ','로 파싱해서 저장 */
    QTextStream out(&file);
    for (const auto& v : orderList) {
        OrderItem* o = v;
        out << o->id() << ", " << o->getClient() << ", ";
        out << o->getProduct() << ", ";
        out << o->getStock() << ", ";
        out << o->getPrice() << ", ";
        out << o->getSum() <<", ";
        out << o->getAddress() << "\n";
    }
    file.close( );
}

/* ID(키 값) 생성 메서드*/
int OrderManagerForm::makeId( )
{
    if(orderList.size( ) == 0) {    // ID가 중복되면 +1
        return 1000001;
    } else {
        auto id = orderList.lastKey();
        return ++id;
    }
}

/* 고객의 ID나 이름을 입력받아 전달하고 관련 데이터를 받아오는 슬롯 */
void OrderManagerForm::on_clientButton_clicked()
{
    ui->clientTreeWidget->clear();  //버튼이 눌릴때마다 화면 초기화 (중복방지)
    emit clientNameSent(ui->clientLineEdit->text());
}

/* 제품의 ID나 제품명을 입력받아 전달하고 관련 데이터를 받아오는 슬롯 */
void OrderManagerForm::on_productButton_clicked()
{
    ui->productTreeWidget->clear();  //버튼이 눌릴때마다 화면 초기화 (중복방지)
    emit productNameSent(ui->productLineEdit->text());
}

/* 고객 리스트 데이터 클릭 시 출력하는 슬롯 */
void OrderManagerForm::receive_ClientTreewidget_itemclicked(ClientItem* clientList)
{
    ui->clientTreeWidget->clear();

    int id = clientList->id();
    QString name = clientList->getName();
    QString number = clientList->getPhoneNumber();
    QString address = clientList->getAddress();
    ClientItem* item = new ClientItem(id, name, number, address);

    ui->clientTreeWidget->addTopLevelItem(item);
}

/* 제품 리스트 데이터 클릭 시 출력하는 슬롯 */
void OrderManagerForm::receive_ProductTreewidget_itemclicked(ProductItem* productList)
{
    ui->productTreeWidget->clear();

    int id = productList->id();
    QString name = productList->getName();
    QString price = productList->getPrice();
    QString stock = productList->getStock();
    ProductItem* item = new ProductItem(id, name, price, stock);

    ui->productTreeWidget->addTopLevelItem(item);
}

/* 고객정보 데이터를 받아 트리위젯에 출력하는 슬롯 */
void OrderManagerForm::receiveClientData(ClientItem* clientList)
{
    int id = clientList->id();
    QString name = clientList->getName();
    QString number = clientList->getPhoneNumber();
    QString address = clientList->getAddress();
    ClientItem* item = new ClientItem(id, name, number, address);

    ui->clientTreeWidget->addTopLevelItem(item);
}

/* 제품정보 데이터를 받아 트리위젯에 출력하는 슬롯 */
void OrderManagerForm::receiveProductData(ProductItem* productList)
{
    int id = productList->id();
    QString name = productList->getName();
    QString price = productList->getPrice();
    QString stock = productList->getStock();
    ProductItem* item = new ProductItem(id, name, price, stock);

    ui->productTreeWidget->addTopLevelItem(item);
}

/* 고객정보 데이터 클릭 시 입력되는 슬롯 */
void OrderManagerForm::on_clientTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->idLineEdit->clear();
    Q_UNUSED(column);
    QString CLineEdit;
    CLineEdit = item->text(0)+" ("+item->text(1)+")";

    ui->cIdLineEdit->setText(CLineEdit);
    ui->addresslineEdit->setText(item->text(3));
}
/* 제품정보 데이터 클릭 시 입력되는 슬롯 */
void OrderManagerForm::on_productTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->idLineEdit->clear();
    ui->stockLineEdit->clear();
    Q_UNUSED(column);
    QString pLineEdit;
    pLineEdit = item->text(0)+" ("+item->text(1)+")";

    ui->pIdLineEdit->setText(pLineEdit);
    ui->pricelineEdit->setText(item->text(2));
}

/* 주문정보추가를 위한 슬롯 */
void OrderManagerForm::on_addPushButton_clicked()
{
    /* 검색 결과에서 정보 추가 시 경고메시지*/
    if(ui->orderInfoLabel->text() != "OrderManagerInfo")
    {
        QMessageBox::information(this, "Error",
                                 QString("This is Search Info.\nGo to OrderManagerInfo."));
        return;
    }

    QTreeWidgetItem* pItem = ui->productTreeWidget->currentItem();
    QString client, product, stock, price, address;
    QString sum, productKey, productTree_Stock;

    int id = makeId( );
    client = ui->cIdLineEdit->text();
    product = ui->pIdLineEdit->text();
    stock = ui->stockLineEdit->text();
    price = ui->pricelineEdit->text();
    address = ui->addresslineEdit->text();

    productTree_Stock = pItem->text(3); //제품리스트의 재고
    productKey =  ui->pIdLineEdit->text().left(4);   //제품 키값
    /* 총합을 위한 연산 */
    int result = price.toInt() * stock.toInt();
    sum = QString::number(result);

    /* 재고반영을 위해 제품키값과, 수량을 시그널로 보냄 */
    emit productAddKeySent(productKey.toInt(), stock );

    if(pItem == nullptr) return; // 예외

    /* 주문 수량이 재고보다 많을 경우 예외*/
    if(productTree_Stock.toInt() < ui->stockLineEdit->text().toInt()) return;

    /* 주문이 되면 제품리스트의 재고를 변경 */
    QString result_stock = QString::number(productTree_Stock.toInt() - stock.toInt());
    pItem->setText((3), result_stock);

    /* 주문 할 데이터를 다 입력, 재고>=주문수량이면 주문정보 추가 */
    if( client.length() && product.length() && stock.length() &&price.length() && address.length() &&
            productTree_Stock.toInt() >= stock.toInt())
    {
        OrderItem* o = new OrderItem(id, client, product, stock, price, sum, address);
        orderList.insert(id, o);
        ui->treeWidget->addTopLevelItem(o);

        ui->cIdLineEdit->clear();
        ui->pIdLineEdit->clear();
        ui->stockLineEdit->clear();
        ui->addresslineEdit->clear();
        ui->pricelineEdit->clear();
    }
}
/* 주문정보검색을 위한 슬롯 */
void OrderManagerForm::on_searchPushButton_clicked()
{
    ui->orderInfoLabel->setText("Search Info");

    /* 모든 주문 데이터 hidden */
    for (const auto& v : qAsConst(orderList)) {
        OrderItem* o = v;
        o->setHidden(true);
    }
    int i = ui->searchComboBox->currentIndex(); //무엇으로 검색할지 콤보박스의 인덱스를 가져옴

    {   /* 검색과 일치(id) 하거나 포함하는 문자열이 있으면 hidden(false) */
        auto items = ui->treeWidget->findItems(ui->searchLineEdit->text(), Qt::MatchContains, i);
        foreach(auto i, items) {
            OrderItem* o = static_cast<OrderItem*>(i);
            o->setHidden(false);    //검색된 데이터의 리스트만 출력되게
        }
    }
}
/* 검색결과 창에서 주문정보관리로 돌아오는 슬롯 */
void OrderManagerForm::on_statePushButton_clicked()
{
    ui->orderInfoLabel->setText("OrderManagerInfo");
    for (const auto& v : orderList) {
        OrderItem* o = v;
        o->setHidden(false);
    }
}

/* 주문정보변경을 위한 슬롯 */
void OrderManagerForm::on_modifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    QTreeWidgetItem* pItem = ui->productTreeWidget->currentItem();
    /* 변경할 제품이 선택된 경우*/
    if(item != nullptr && pItem != nullptr) {
        int key = item->text(0).toInt();
        OrderItem* o = orderList[key];
        QString client, product, stock, price, sum, address;
        QString productkey, productTree_Stock, orderTree_Stock;
        /* 주문내역의 제품의 ID, 해당하는 재고 ,현재 주문 수량*/
        productkey =  item->text(2).left(4);
        productTree_Stock = pItem->text(3);
        orderTree_Stock =item->text(3);

        client = ui->cIdLineEdit->text();
        product = ui->pIdLineEdit->text();
        stock = ui->stockLineEdit->text();
        address = ui->addresslineEdit->text();
        price = ui->pricelineEdit->text();

        if(stock ==nullptr) return; // 수량 입력 안할 경우 예외처리

        int resultstock = productTree_Stock.toInt() + orderTree_Stock.toInt();
        /* 변경 가능 수량이 많이 입력된 경우 경고메시지*/
        if( resultstock < stock.toInt()) {
            QMessageBox::information(this, "Sold Out",
                                     QString("재고 부족\n%0개 까지 변경 가능합니다.").arg(resultstock));
            return ;
        }
        /* 변경할 제품과 선택한 제품이 다른 경우 경고메시지*/
        if( productkey != pItem->text(0)){
            QMessageBox::information(this, "Error",
                                     QString("오류\n선택한 제품명과 고르신 제품명이 다릅니다."));
            return ;
        }
        /* 재고반영을 위해 키값, 수정할 수량, 입력된 수량을 시그널로 보냄 */
        emit productModKeySent(productkey.toInt(), stock , orderTree_Stock);

        /* 가격 합을 위한 연산*/
        int result = price.toInt() * stock.toInt();
        sum = QString::number(result);

        int up_ptreewidget = productTree_Stock.toInt() + orderTree_Stock.toInt() - ui->stockLineEdit->text().toInt();
        pItem->setText((3), QString::number(up_ptreewidget));   //제품리스트의 재고 변경

        o->setClient(client);
        o->setProduct(product);
        o->setStock(stock);
        o->setPrice(price);
        o->setSum(sum);
        o->setAddress(address);
        orderList[key] = o;
    }
    /* 변경할 제품이 선택되지 않은 경우 경고메시지*/
    else
    {
        QMessageBox::information(this, "Error",
                                 QString("제품리스트의 제품을 선택해주세요."));
        return;
    }

}

/* ContextMenu 슬롯 */
void OrderManagerForm::showContextMenu(const QPoint &pos)
{
    if(ui->treeWidget->currentItem() == nullptr)    return; //에외처리
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

/* 주문정보의 데이터(트리위젯)의 리스트 제거 슬롯 */
void OrderManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    int id = item->text(0).toInt();
    QString ordertree_stock,ordertree_product;

    ordertree_stock = item->text(3);
    ordertree_product=item->text(2);
    /* 데이터 제거 시, 제품 ID와 수량을 시그널로 보냄 */
    emit removedataSent(ordertree_product.left(4).toInt() , ordertree_stock);

    /* 주문정보의 id 값의 데이터를 리스트에서 제거, 데이터 clear */
    if(item != nullptr) {   //예외처리
        orderList.remove(id);
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
        ui->treeWidget->update();

        ui->idLineEdit->clear();
        ui->cIdLineEdit->clear();
        ui->pIdLineEdit->clear();
        ui->stockLineEdit->clear();
        ui->addresslineEdit->clear();
        ui->pricelineEdit->clear();
        ui->clientTreeWidget->clear();
        ui->productTreeWidget->clear();
    }
}
/* 주문내역 클릭 시 관련정보 출력 슬롯*/
void OrderManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    int clientkey, productkey;

    clientkey = item->text(1).left(4).toInt();
    productkey = item->text(2).left(4).toInt();

    ui->idLineEdit->setText(item->text(0));
    ui->cIdLineEdit->setText(item->text(1));
    ui->pIdLineEdit->setText(item->text(2));
    ui->stockLineEdit->setText(item->text(3));
    ui->pricelineEdit->setText(item->text(4));
    ui->addresslineEdit->setText(item->text(6));

    /* 고객, 제품의 리스트를 불러오기 위한 시그널 */
    emit clientKeySent(clientkey);      //클릭 시, 고객, 제품의 리스트를 불러오기 위한 시그널
    emit productKeySent(productkey);

}
/* 버튼 클릭 시 입력 값 초기화 하는 슬롯 */
void OrderManagerForm::on_clearButton_clicked()
{
    ui->clientTreeWidget->clear();
    ui->productTreeWidget->clear();
    ui->cIdLineEdit->clear();
    ui->pIdLineEdit->clear();
    ui->stockLineEdit->clear();
    ui->addresslineEdit->clear();
    ui->pricelineEdit->clear();
    ui->searchLineEdit->clear();
    ui->clientLineEdit->clear();
    ui->productLineEdit->clear();
}

