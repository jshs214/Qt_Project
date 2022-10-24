#include "productmanagerform.h"
#include "ui_productmanagerform.h"
#include "productitem.h"

#include <QFile>
#include <QMenu>
#include <QMessageBox>

ProductManagerForm::ProductManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductManagerForm)
{
    ui->setupUi(this);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));

    ui->priceLineEdit->setValidator( new QIntValidator(0, 99999999, this) );    //숫자만 받도록
    ui->stockLineEdit->setValidator( new QIntValidator(0, 9999, this) );        //숫자만 받도록


}
void ProductManagerForm::loadData()
{
    QFile file("productlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int id = row[0].toInt();
            ProductItem* c = new ProductItem(id, row[1], row[2], row[3]);
            ui->treeWidget->addTopLevelItem(c);
            productList.insert(id, c);
        }
    }
    file.close( );
}
ProductManagerForm::~ProductManagerForm()
{
    delete ui;

    QFile file("productlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const auto& v : productList) {
        ProductItem* p = v;
        out << p->id() << ", " << p->getName() << ", ";
        out << p->getPrice() << ", ";
        out << p->getStock() << "\n";
    }
    file.close( );
}

int ProductManagerForm::makeId( )
{
    if(productList.size( ) == 0) {
        return 5000;
    } else {
        auto id = productList.lastKey();
        return ++id;
    }
}

void ProductManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {
        productList.remove(item->text(0).toInt());
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
        ui->treeWidget->update();
    }
}

void ProductManagerForm::showContextMenu(const QPoint &pos)
{
    if(ui->treeWidget->currentItem() == nullptr)    return;
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void ProductManagerForm::on_searchPushButton_clicked()
{
    ui->productInfoLabel->setText("Search Info");

    int i = ui->searchComboBox->currentIndex();
    for (const auto& v : productList) {
        ProductItem* p = v;
        p->setHidden(true); //검색 시, 기존 고객리스트 히든
    }
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->treeWidget->findItems(ui->searchLineEdit->text(), flag, i);
        foreach(auto i, items) {
            i->setHidden(false);
            ProductItem* p = static_cast<ProductItem*>(i);
            p->id();
            QString name = p->getName();
            QString price = p->getPrice();
            QString stock = p->getStock();

        }
    }
}

void ProductManagerForm::on_modifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {
        int key = item->text(0).toInt();
        ProductItem* p = productList[key];
        QString name, price, stock;
        name = ui->nameLineEdit->text();
        price = ui->priceLineEdit->text();
        stock = ui->stockLineEdit->text();
        p->setName(name);
        p->setPrice(price);
        p->setStock(stock);
        productList[key] = p;
    }
}

void ProductManagerForm::on_addPushButton_clicked()
{
    if(ui->productInfoLabel->text() != "ProductInfoManager")
    {
        QMessageBox::warning(this, "Error",
                             QString("This is Search Info.\nGo to ProductInfoManager."));
        return;
    }
    QString name, price, stock;
    int id = makeId( );
    name = ui->nameLineEdit->text();
    price = ui->priceLineEdit->text();
    stock = ui->stockLineEdit->text();
    if(name.length() && price.length() && stock.length()) {
        ProductItem* p = new ProductItem(id, name, price, stock);
        productList.insert(id, p);
        ui->treeWidget->addTopLevelItem(p);

        ui->nameLineEdit->clear();
        ui->priceLineEdit->clear();
        ui->stockLineEdit->clear();
    }
}

void ProductManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->idLineEdit->setText(item->text(0));
    ui->nameLineEdit->setText(item->text(1));
    ui->priceLineEdit->setText(item->text(2));
    ui->stockLineEdit->setText(item->text(3));
}


void ProductManagerForm::receiveProductName(QString str)
{
    QMap<int,ProductItem*> searchList;

    auto flag =  Qt::MatchCaseSensitive|Qt::MatchContains;

    auto id = ui->treeWidget->findItems(str, flag,0);        //키값비교, 0
    foreach(auto i, id) {
        ProductItem* p = static_cast<ProductItem*>(i);
        int id = p->id();
        QString name = p->getName();
        QString price = p->getPrice();
        QString stock = p->getStock();
        ProductItem* item = new ProductItem(id, name, price, stock);
        searchList.insert(p->id(), item);
    }

    auto items = ui->treeWidget->findItems(str, flag,1);        //이름이므로 1
    foreach(auto i, items) {
        ProductItem* p = static_cast<ProductItem*>(i);
        int id = p->id();
        QString name = p->getName();
        QString price = p->getPrice();
        QString stock = p->getStock();
        ProductItem* item = new ProductItem(id, name, price, stock);
        searchList.insert(p->id(), item);
    }

    for(const auto&v : searchList){
        ProductItem* p = v;
        emit productDataSent(p);
    }
}

void ProductManagerForm::receiveAddStock(int key, QString Instock) //추가 시 재고 변경
{
    ProductItem* p = productList[key];
    if(p->getStock().toInt() < Instock.toInt()) {   // 재고부족을 위한 메시지 박스
        QMessageBox::information(this, "Sold Out",
                                 QString("재고 부족\n %0개 까지 주문 가능합니다.").arg(p->getStock()));
        return; }
    QString stock = QString::number(p->getStock().toInt() - Instock.toInt() );
    p->setStock(stock);

}

void ProductManagerForm::receiveModStock(int key, QString upstock, QString stock)
{                                                  //업데이트할 수량, 기존 수량
    ProductItem* p = productList[key];
    QString result = QString::number(p->getStock().toInt() + stock.toInt() - upstock.toInt() );
    p->setStock(result);

}
void ProductManagerForm::receiveDelStock(int key, QString instock)  //지울 때 재고추가를 위한 슬롯
{
    ProductItem* p = productList[key];
    int stock = p->getStock().toInt() + instock.toInt();   //기존재고에 지운 재고 수량 추가
    QString result = QString::number(stock);
    p->setStock(result);

}
void ProductManagerForm::receiveProductKey(int key) //키값에 해당하는 리스트 행 시그널.
{
    ProductItem* p = productList[key];

    int id = p->id();
    QString name = p->getName();
    QString price = p->getPrice();
    QString stock = p->getStock();
    ProductItem* item = new ProductItem(id, name, price, stock);

    emit clickProductSent(item);

}

void ProductManagerForm::on_clearbutton_clicked()
{
    ui->idLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->priceLineEdit->clear();
    ui->stockLineEdit->clear();
    ui->searchLineEdit->clear();
}


void ProductManagerForm::on_ProductManagement_clicked()
{
    ui->productInfoLabel->setText("ProductInfoManager");
    for (const auto& v : productList) {
        ProductItem* p = v;
        p->setHidden(false);
    }
}

