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

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    //clienttreeWidget 열 너비 설정
    ui->clienttreeWidget->QTreeView::setColumnWidth(0,35);
    ui->clienttreeWidget->QTreeView::setColumnWidth(1,70);
    ui->clienttreeWidget->QTreeView::setColumnWidth(2,95);
    //producttreeWidget 열 너비 설정
    ui->producttreeWidget->QTreeView::setColumnWidth(0,35);
    ui->producttreeWidget->QTreeView::setColumnWidth(1,70);
    ui->producttreeWidget->QTreeView::setColumnWidth(2,95);
    //treeWidget의 열 너비 설정
    ui->treeWidget->QTreeView::setColumnWidth(0,60);
    ui->treeWidget->QTreeView::setColumnWidth(1,100);
    ui->treeWidget->QTreeView::setColumnWidth(2,100);
    ui->treeWidget->QTreeView::setColumnWidth(3,40);

    ui->StockLineEdit->setValidator( new QIntValidator(0, 9999, this) );    //수량에 숫자만 받도록

    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));

    QFile file("orderlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

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

OrderManagerForm::~OrderManagerForm()
{
    delete ui;

    QFile file("orderlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

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


int OrderManagerForm::makeId( )
{
    if(orderList.size( ) == 0) {
        return 100;
    } else {
        auto id = orderList.lastKey();
        return ++id;
    }
}

void OrderManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();

    QString o_stock, p_stock;
    o_stock = item->text(3);

    emit removedataSent(item->text(2).left(4).toInt() , o_stock);

    if(item != nullptr) {
        orderList.remove(item->text(0).toInt());
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
        ui->treeWidget->update();

        ui->idLineEdit->clear();
        ui->CIDlineEdit->clear();
        ui->PIDlineEdit->clear();
        ui->StockLineEdit->clear();
        ui->addresslineEdit->clear();
        ui->pricelineEdit->clear();
        ui->clienttreeWidget->clear();
        ui->producttreeWidget->clear();
    }
}

void OrderManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void OrderManagerForm::on_searchPushButton_clicked()
{
    ui->label_2->setText("검색 결과");

    for (const auto& v : orderList) {
        OrderItem* o = v;
        o->setHidden(true); //고객리스트 히든
    }

    int i = ui->searchComboBox->currentIndex();
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->treeWidget->findItems(ui->searchLineEdit->text(), flag, i);

        foreach(auto i, items) {
            OrderItem* o = static_cast<OrderItem*>(i);
            o->setHidden(false);    //검색된 리스트만 출력되게
            o->id();
            QString client = o->getClient();
            QString product = o->getProduct();
            QString stock = o->getStock();
            QString price = o->getPrice();
            QString sum = o->getSum();
            QString address = o->getAddress();

        }
    }
}


void OrderManagerForm::on_modifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    QTreeWidgetItem* pitem = ui->producttreeWidget->currentItem();

    if(item != nullptr && pitem != nullptr) {

        int key = item->text(0).toInt();
        OrderItem* o = orderList[key];
        QString client, product, stock, price, sum, address;

        client = ui->CIDlineEdit->text();
        product = ui->PIDlineEdit->text();
        stock = ui->StockLineEdit->text();
        address = ui->addresslineEdit->text();
        price = ui->pricelineEdit->text();

        if(stock ==nullptr) return; // 수량 입력 안할 경우 예외처리

        int resultstock = pitem->text(3).toInt() + item->text(3).toInt();
        if( resultstock < stock.toInt()) {
            QMessageBox::information(this, "Sold Out",
                                     QString("재고 부족\n%0개 까지 변경 가능합니다.").arg(resultstock));
            return ;
        }
        QString prdocutkey =  item->text(2).left(4);
        if( prdocutkey != pitem->text(0)){
            QMessageBox::information(this, "Error",
                                     QString("오류\n선택한 제품명과 고르신 제품명이 다릅니다."));
            return ;
        }
        emit productModKeySent(prdocutkey.toInt(), stock , item->text(3));
        // 키값, 수정할 수량, 입력된 수량

        int result = price.toInt() * stock.toInt();
        sum = QString::number(result);

        int up_ptreewidget = pitem->text(3).toInt() + item->text(3).toInt() - ui->StockLineEdit->text().toInt();
        pitem->setText((3), QString::number(up_ptreewidget));

        o->setClient(client);
        o->setProduct(product);
        o->setStock(stock);
        o->setPrice(price);
        o->setSum(sum);
        o->setAddress(address);
        orderList[key] = o;
    }

    else
    {
        QMessageBox::information(this, "Error",
                                 QString("제품리스트의 제품을 선택해주세요."));
        return;
    }

}


void OrderManagerForm::on_addPushButton_clicked()
{
    if(ui->label_2->text() != "주문정보관리")
    {
        QMessageBox::information(this, "오류",
                                 QString("검색창입니다.\n주문정보관리창으로 이동하세요."));
        return;
    }

    QString client, product, stock,price, address;
    int id = makeId( );
    client = ui->CIDlineEdit->text();
    product = ui->PIDlineEdit->text();
    stock = ui->StockLineEdit->text();
    price = ui->pricelineEdit->text();
    address = ui->addresslineEdit->text();

    int result = price.toInt() * stock.toInt(); //총합을 위한 연산
    QString sum = QString::number(result);

    QString key =  ui->PIDlineEdit->text().left(4);
    emit productAddKeySent( key.toInt(), stock );

    QTreeWidgetItem* pitem = ui->producttreeWidget->currentItem();

    if(pitem == nullptr) return;


    if(  pitem->text(3).toInt() < ui->StockLineEdit->text().toInt()) return;

    QString treewidgetstock = pitem->text(3); // 재고
    //주문이 되면 제품리스트의 재고를 변경
    QString pstock = QString::number(pitem->text(3).toInt() - stock.toInt());
    pitem->setText((3), pstock);

    // 트리위젯에서 선택되고, 모든 요소가 입력 되고 재고>=입력값이면.
    if( client.length() && product.length() && stock.length() &&price.length() && address.length() &&
            treewidgetstock.toInt() >= stock.toInt())
    {
        OrderItem* o = new OrderItem(id, client, product, stock, price, sum, address);
        orderList.insert(id, o);
        ui->treeWidget->addTopLevelItem(o);

        ui->CIDlineEdit->clear();
        ui->PIDlineEdit->clear();
        ui->StockLineEdit->clear();
        ui->addresslineEdit->clear();
        ui->pricelineEdit->clear();
    }
}

void OrderManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->idLineEdit->setText(item->text(0));
    ui->CIDlineEdit->setText(item->text(1));
    ui->PIDlineEdit->setText(item->text(2));
    ui->StockLineEdit->setText(item->text(3));
    ui->pricelineEdit->setText(item->text(4));
    ui->addresslineEdit->setText(item->text(6));

    int clientkey = item->text(1).left(4).toInt();
    int productkey = item->text(2).left(4).toInt();
    emit clientKeySent(clientkey);      //클릭 시, 고객, 제품의 리스트를 불러오기 위한 시그널
    emit productKeySent(productkey);

}
void OrderManagerForm::receive_ClientTreewidget_itemclicked(ClientItem* clientList)
{
    ui->clienttreeWidget->clear();

    int id = clientList->id();
    QString name = clientList->getName();
    QString number = clientList->getPhoneNumber();
    QString address = clientList->getAddress();
    ClientItem* item = new ClientItem(id, name, number, address);

    ui->clienttreeWidget->addTopLevelItem(item);
}

void OrderManagerForm::receive_ProductTreewidget_itemclicked(ProductItem* productList)
{
    ui->producttreeWidget->clear();

    int id = productList->id();
    QString name = productList->getName();
    QString price = productList->getPrice();
    QString stock = productList->getStock();

    ProductItem* item = new ProductItem(id, name, price, stock);

    ui->producttreeWidget->addTopLevelItem(item);
}

void OrderManagerForm::on_pushButton_clicked()
{
    qApp->quit();
}

void OrderManagerForm::on_cbutton_clicked()
{
    ui->clienttreeWidget->clear();  //버튼이 눌릴때마다 화면 초기화 (중복방지)
    emit clientNameSent(ui->ClientLineEdit->text());
}

void OrderManagerForm::on_pbutton_clicked()
{
    ui->producttreeWidget->clear();  //버튼이 눌릴때마다 화면 초기화 (중복방지)
    emit productNameSent(ui->ProductLineEdit->text());
}


void OrderManagerForm::receiveClientData(ClientItem* clientList)
{
    int id = clientList->id();
    QString name = clientList->getName();
    QString number = clientList->getPhoneNumber();
    QString address = clientList->getAddress();
    ClientItem* item = new ClientItem(id, name, number, address);

    ui->clienttreeWidget->addTopLevelItem(item);
}

void OrderManagerForm::receiveProductData(ProductItem* productList)
{
    int id = productList->id();
    QString name = productList->getName();
    QString price = productList->getPrice();
    QString stock = productList->getStock();
    ProductItem* item = new ProductItem(id, name, price, stock);

    ui->producttreeWidget->addTopLevelItem(item);
}

void OrderManagerForm::on_clienttreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->idLineEdit->clear();
    Q_UNUSED(column);
    QString CLineEdit;
    CLineEdit = item->text(0)+" ("+item->text(1)+")";

    ui->CIDlineEdit->setText(CLineEdit);
    ui->addresslineEdit->setText(item->text(3));
}

void OrderManagerForm::on_producttreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->idLineEdit->clear();
    ui->StockLineEdit->clear();
    Q_UNUSED(column);
    QString pLineEdit;
    pLineEdit = item->text(0)+" ("+item->text(1)+")";

    ui->PIDlineEdit->setText(pLineEdit);
    ui->pricelineEdit->setText(item->text(2));
}

void OrderManagerForm::on_clearbutton_clicked() //지우개버튼 클릭 시 화면 초기화
{
    ui->clienttreeWidget->clear();
    ui->producttreeWidget->clear();
    ui->CIDlineEdit->clear();
    ui->PIDlineEdit->clear();
    ui->StockLineEdit->clear();
    ui->addresslineEdit->clear();
    ui->pricelineEdit->clear();
    ui->searchLineEdit->clear();
}

void OrderManagerForm::on_pushButton_2_clicked()
{
    ui->label_2->setText("주문정보관리");
    for (const auto& v : orderList) {
        OrderItem* o = v;
        o->setHidden(false);
    }
}

