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
    /* ContextMenu의 remove 액션, 리스트의 데이터 삭제 */
    QAction* removeAction = new QAction(tr("&Remove"));
    removeAction->setIcon(QIcon(":/images/eraser.png"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));
    menu = new QMenu;
    menu->addAction(removeAction);
    ui->productTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->productTreeWidget, SIGNAL(customContextMenuRequested(QPoint)), this,
                                                        SLOT(showContextMenu(QPoint)));

    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));
    /* 가격 입력 시 0~99999999, 재고 입력 시 0~9999 숫자만 받도록 */
    ui->priceLineEdit->setValidator( new QIntValidator(0, 99999999, this) );    //숫자만 받도록
    ui->stockLineEdit->setValidator( new QIntValidator(0, 9999, this) );        //숫자만 받도록

}
/* 파일의 데이터 입력하는 메서드 */
void ProductManagerForm::loadData()
{
    QFile file("productlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    /* 파일의 데이터를 ','로 파싱해서 입력 */
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int id = row[0].toInt();
            ProductItem* c = new ProductItem(id, row[1], row[2], row[3]);
            ui->productTreeWidget->addTopLevelItem(c);
            productList.insert(id, c);
        }
    }
    file.close( );
}

/* 소멸자에서 파일 출력 */
ProductManagerForm::~ProductManagerForm()
{
    delete ui;

    QFile file("productlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    /* 파일의 데이터를 ','로 파싱해서 저장 */
    QTextStream out(&file);
    for (const auto& v : qAsConst(productList)) {
        ProductItem* p = v;
        out << p->id() << ", " << p->getName() << ", ";
        out << p->getPrice() << ", ";
        out << p->getStock() << "\n";
    }
    file.close( );
}

/* ID(키 값) 생성 메서드*/
int ProductManagerForm::makeId( )
{
    if(productList.size( ) == 0) {      // ID가 중복되면 +1
        return 5000;
    } else {
        auto id = productList.lastKey();
        return ++id;
    }
}

/* 제품정보추가를 위한 슬롯 */
void ProductManagerForm::on_addPushButton_clicked()
{
    /* 검색 결과에서 정보 추가 시 경고메시지 */
    if(ui->productInfoLabel->text() != tr("ProductInfoManager"))
    {
        QMessageBox::warning(this, tr("Error"),
                             QString( tr("This is Search Info.\nGo to ProductInfoManager.")) );
        return;
    }
    QString name, price, stock;
    int id = makeId( );
    name = ui->nameLineEdit->text();
    price = ui->priceLineEdit->text();
    stock = ui->stockLineEdit->text();

    /* 제품의 데이터를 다 입력하면 제품 정보추가 */
    if(name.length() && price.length() && stock.length()) {
        ProductItem* p = new ProductItem(id, name, price, stock);
        productList.insert(id, p);
        ui->productTreeWidget->addTopLevelItem(p);

        ui->nameLineEdit->clear();
        ui->priceLineEdit->clear();
        ui->stockLineEdit->clear();
    }
}

/* 제품정보변경을 위한 슬롯 */
void ProductManagerForm::on_modifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->productTreeWidget->currentItem();
    /* 변경할 제품의 데이터를 입력한 데이터로 정보 수정 */
    if(item != nullptr) {
        int key = item->text(0).toInt();    //id 값을 가져와
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

/* 제품정보검색을 위한 슬롯 */
void ProductManagerForm::on_searchPushButton_clicked()
{
    ui->productInfoLabel->setText(tr("Search Info"));

    /* 모든 제품 데이터 hidden */
    for (const auto& v : qAsConst(productList)) {
        ProductItem* p = v;
        p->setHidden(true);
    }

    int i = ui->searchComboBox->currentIndex(); //무엇으로 검색할지 콤보박스의 인덱스를 가져옴
    {   /* 검색과 일치하거나 포함하는 문자열이 있으면 hidden(false) */
        auto items = ui->productTreeWidget->findItems(ui->searchLineEdit->text(),
                                                               Qt::MatchContains, i);
        foreach(auto i, items) {
            i->setHidden(false);    //검색된 리스트만 출력되게
        }
    }
}

/* 검색결과 창에서 제품정보관리로 돌아오는 슬롯 */
void ProductManagerForm::on_statePushButton_clicked()
{
    ui->productInfoLabel->setText(tr("ProductInfoManager"));
    for (const auto& v : qAsConst(productList)) {
        ProductItem* p = v;
        p->setHidden(false);
    }
}

/* ContextMenu 슬롯 */
void ProductManagerForm::showContextMenu(const QPoint &pos)
{
    if(ui->productTreeWidget->currentItem() == nullptr)    return;
    QPoint globalPos = ui->productTreeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

/* 제품정보의 데이터(트리위젯)의 리스트 제거 슬롯 */
void ProductManagerForm::removeItem()
{   /* 선택된 정보의 리스트를 트리위젯에서 제거 */
    QTreeWidgetItem* item = ui->productTreeWidget->currentItem();
    if(item != nullptr) {   //예외처리
        productList.remove(item->text(0).toInt());
        ui->productTreeWidget->takeTopLevelItem(ui->productTreeWidget->indexOfTopLevelItem(item));
        ui->productTreeWidget->update();
    }
}

/* 등록된 제품정보 클릭 시 관련정보 출력 슬롯*/
void ProductManagerForm::on_productTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->idLineEdit->setText(item->text(0));
    ui->nameLineEdit->setText(item->text(1));
    ui->priceLineEdit->setText(item->text(2));
    ui->stockLineEdit->setText(item->text(3));
}


/* Order에서 제품 id나 제품명을 받아오는 슬롯*/
void ProductManagerForm::receiveProductName(QString str)
{
    QMap<int,ProductItem*> searchList;

    auto flag =  Qt::MatchCaseSensitive|Qt::MatchContains;

    auto id = ui->productTreeWidget->findItems(str, flag,0);        //키값비교, 0
    foreach(auto i, id) {
        ProductItem* p = static_cast<ProductItem*>(i);
        int id = p->id();
        QString name = p->getName();
        QString price = p->getPrice();
        QString stock = p->getStock();
        ProductItem* item = new ProductItem(id, name, price, stock);
        searchList.insert(p->id(), item);
    }

    auto items = ui->productTreeWidget->findItems(str, flag,1);        //이름이므로 1
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
        /* id나 제품명에 해당하는 데이터를 보내주는 시그널*/
        emit productDataSent(p);
    }
}

/* Order에서 주문추가 시, 재고반영을 위한 슬롯 */
void ProductManagerForm::receiveAddStock(int key, QString Instock) //추가 시 재고 변경
{
    ProductItem* p = productList[key];
    /* 주문 시, 재고부족을 위한 메시지 박스 */
    if(p->getStock().toInt() < Instock.toInt()) {
        QMessageBox::information(this, tr("Error"),
                                 QString( tr("out of stock\nYou can order up to %0.") )
                                                                    .arg(p->getStock()));
        return; }

    QString stock = QString::number(p->getStock().toInt() - Instock.toInt() );
    p->setStock(stock);

}

/* Order에서 주문변경 시, 재고반영을 위한 슬롯 */
void ProductManagerForm::receiveModStock(int key, QString upstock, QString stock)
{
    ProductItem* p = productList[key];
    QString result = QString::number(p->getStock().toInt() + stock.toInt() - upstock.toInt() );
    p->setStock(result);

}

/* Order에서 주문내역제거 시, 재고반영을 위한 슬롯 */
void ProductManagerForm::receiveDelStock(int key, QString instock)  //지울 때 재고추가를 위한 슬롯
{
    ProductItem* p = productList[key];
    int stock = p->getStock().toInt() + instock.toInt();   //기존재고에 지운 재고 수량 추가
    QString result = QString::number(stock);
    p->setStock(result);

}

/* 제품 id 값을 받아오는 슬롯 */
void ProductManagerForm::receiveProductKey(int key)
{
    ProductItem* p = productList[key];

    int id = p->id();
    QString name = p->getName();
    QString price = p->getPrice();
    QString stock = p->getStock();
    ProductItem* item = new ProductItem(id, name, price, stock);
    /* id에 해당하는 데이터를 보내주는 시그널*/
    emit clickProductSent(item);
}

/* 버튼 클릭 시 입력 값 초기화 하는 슬롯 */
void ProductManagerForm::on_clearButton_clicked()
{
    ui->idLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->priceLineEdit->clear();
    ui->stockLineEdit->clear();
    ui->searchLineEdit->clear();
}





