/********************************************************************************
** Form generated from reading UI file 'ordermanagerform.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERMANAGERFORM_H
#define UI_ORDERMANAGERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrderManagerForm
{
public:
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QPushButton *clearbutton;
    QPushButton *pushButton_2;
    QFormLayout *ClientProductSearch;
    QLineEdit *ClientLineEdit;
    QPushButton *cbutton;
    QLineEdit *ProductLineEdit;
    QPushButton *pbutton;
    QVBoxLayout *verticalLayout_3;
    QTreeWidget *clienttreeWidget;
    QTreeWidget *producttreeWidget;
    QFormLayout *OrderformLayout;
    QLabel *idLabel;
    QLineEdit *idLineEdit;
    QLabel *nameLabel;
    QLineEdit *CIDlineEdit;
    QLabel *phoneNumberLabel;
    QLineEdit *PIDlineEdit;
    QLabel *addressLabel;
    QLineEdit *StockLineEdit;
    QLabel *label;
    QLineEdit *pricelineEdit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addPushButton;
    QPushButton *modifyPushButton;
    QLabel *label_3;
    QLineEdit *addresslineEdit;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QComboBox *searchComboBox;
    QLineEdit *searchLineEdit;
    QPushButton *searchPushButton;
    QPushButton *pushButton;
    QVBoxLayout *treewidgetLayout;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *OrderManagerForm)
    {
        if (OrderManagerForm->objectName().isEmpty())
            OrderManagerForm->setObjectName(QString::fromUtf8("OrderManagerForm"));
        OrderManagerForm->resize(675, 525);
        horizontalLayout_4 = new QHBoxLayout(OrderManagerForm);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(OrderManagerForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setPointSize(11);
        label_2->setFont(font);

        horizontalLayout_3->addWidget(label_2);

        clearbutton = new QPushButton(OrderManagerForm);
        clearbutton->setObjectName(QString::fromUtf8("clearbutton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(clearbutton->sizePolicy().hasHeightForWidth());
        clearbutton->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/erase.png"), QSize(), QIcon::Normal, QIcon::Off);
        clearbutton->setIcon(icon);
        clearbutton->setIconSize(QSize(40, 20));

        horizontalLayout_3->addWidget(clearbutton);


        verticalLayout_4->addLayout(horizontalLayout_3);

        pushButton_2 = new QPushButton(OrderManagerForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_4->addWidget(pushButton_2);

        ClientProductSearch = new QFormLayout();
        ClientProductSearch->setObjectName(QString::fromUtf8("ClientProductSearch"));
        ClientLineEdit = new QLineEdit(OrderManagerForm);
        ClientLineEdit->setObjectName(QString::fromUtf8("ClientLineEdit"));

        ClientProductSearch->setWidget(1, QFormLayout::LabelRole, ClientLineEdit);

        cbutton = new QPushButton(OrderManagerForm);
        cbutton->setObjectName(QString::fromUtf8("cbutton"));

        ClientProductSearch->setWidget(1, QFormLayout::FieldRole, cbutton);

        ProductLineEdit = new QLineEdit(OrderManagerForm);
        ProductLineEdit->setObjectName(QString::fromUtf8("ProductLineEdit"));

        ClientProductSearch->setWidget(2, QFormLayout::LabelRole, ProductLineEdit);

        pbutton = new QPushButton(OrderManagerForm);
        pbutton->setObjectName(QString::fromUtf8("pbutton"));

        ClientProductSearch->setWidget(2, QFormLayout::FieldRole, pbutton);


        verticalLayout_4->addLayout(ClientProductSearch);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        clienttreeWidget = new QTreeWidget(OrderManagerForm);
        clienttreeWidget->setObjectName(QString::fromUtf8("clienttreeWidget"));
        clienttreeWidget->setRootIsDecorated(false);

        verticalLayout_3->addWidget(clienttreeWidget);

        producttreeWidget = new QTreeWidget(OrderManagerForm);
        producttreeWidget->setObjectName(QString::fromUtf8("producttreeWidget"));
        producttreeWidget->setRootIsDecorated(false);

        verticalLayout_3->addWidget(producttreeWidget);


        verticalLayout_4->addLayout(verticalLayout_3);

        OrderformLayout = new QFormLayout();
        OrderformLayout->setObjectName(QString::fromUtf8("OrderformLayout"));
        idLabel = new QLabel(OrderManagerForm);
        idLabel->setObjectName(QString::fromUtf8("idLabel"));

        OrderformLayout->setWidget(0, QFormLayout::LabelRole, idLabel);

        idLineEdit = new QLineEdit(OrderManagerForm);
        idLineEdit->setObjectName(QString::fromUtf8("idLineEdit"));
        idLineEdit->setReadOnly(true);

        OrderformLayout->setWidget(0, QFormLayout::FieldRole, idLineEdit);

        nameLabel = new QLabel(OrderManagerForm);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        OrderformLayout->setWidget(1, QFormLayout::LabelRole, nameLabel);

        CIDlineEdit = new QLineEdit(OrderManagerForm);
        CIDlineEdit->setObjectName(QString::fromUtf8("CIDlineEdit"));
        CIDlineEdit->setReadOnly(true);

        OrderformLayout->setWidget(1, QFormLayout::FieldRole, CIDlineEdit);

        phoneNumberLabel = new QLabel(OrderManagerForm);
        phoneNumberLabel->setObjectName(QString::fromUtf8("phoneNumberLabel"));

        OrderformLayout->setWidget(2, QFormLayout::LabelRole, phoneNumberLabel);

        PIDlineEdit = new QLineEdit(OrderManagerForm);
        PIDlineEdit->setObjectName(QString::fromUtf8("PIDlineEdit"));
        PIDlineEdit->setReadOnly(true);

        OrderformLayout->setWidget(2, QFormLayout::FieldRole, PIDlineEdit);

        addressLabel = new QLabel(OrderManagerForm);
        addressLabel->setObjectName(QString::fromUtf8("addressLabel"));

        OrderformLayout->setWidget(3, QFormLayout::LabelRole, addressLabel);

        StockLineEdit = new QLineEdit(OrderManagerForm);
        StockLineEdit->setObjectName(QString::fromUtf8("StockLineEdit"));
        StockLineEdit->setCursorPosition(0);

        OrderformLayout->setWidget(3, QFormLayout::FieldRole, StockLineEdit);

        label = new QLabel(OrderManagerForm);
        label->setObjectName(QString::fromUtf8("label"));

        OrderformLayout->setWidget(5, QFormLayout::LabelRole, label);

        pricelineEdit = new QLineEdit(OrderManagerForm);
        pricelineEdit->setObjectName(QString::fromUtf8("pricelineEdit"));
        pricelineEdit->setReadOnly(true);

        OrderformLayout->setWidget(5, QFormLayout::FieldRole, pricelineEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        addPushButton = new QPushButton(OrderManagerForm);
        addPushButton->setObjectName(QString::fromUtf8("addPushButton"));

        horizontalLayout_2->addWidget(addPushButton);

        modifyPushButton = new QPushButton(OrderManagerForm);
        modifyPushButton->setObjectName(QString::fromUtf8("modifyPushButton"));

        horizontalLayout_2->addWidget(modifyPushButton);


        OrderformLayout->setLayout(6, QFormLayout::SpanningRole, horizontalLayout_2);

        label_3 = new QLabel(OrderManagerForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        OrderformLayout->setWidget(4, QFormLayout::LabelRole, label_3);

        addresslineEdit = new QLineEdit(OrderManagerForm);
        addresslineEdit->setObjectName(QString::fromUtf8("addresslineEdit"));
        addresslineEdit->setReadOnly(true);

        OrderformLayout->setWidget(4, QFormLayout::FieldRole, addresslineEdit);


        verticalLayout_4->addLayout(OrderformLayout);

        groupBox = new QGroupBox(OrderManagerForm);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        searchComboBox = new QComboBox(groupBox);
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->setObjectName(QString::fromUtf8("searchComboBox"));

        verticalLayout_2->addWidget(searchComboBox);

        searchLineEdit = new QLineEdit(groupBox);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));

        verticalLayout_2->addWidget(searchLineEdit);

        searchPushButton = new QPushButton(groupBox);
        searchPushButton->setObjectName(QString::fromUtf8("searchPushButton"));

        verticalLayout_2->addWidget(searchPushButton);


        verticalLayout->addLayout(verticalLayout_2);


        verticalLayout_4->addWidget(groupBox);

        pushButton = new QPushButton(OrderManagerForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_4->addWidget(pushButton);

        verticalLayout_4->setStretch(3, 2);
        verticalLayout_4->setStretch(4, 1);
        verticalLayout_4->setStretch(5, 1);
        verticalLayout_4->setStretch(6, 1);

        horizontalLayout->addLayout(verticalLayout_4);

        treewidgetLayout = new QVBoxLayout();
        treewidgetLayout->setObjectName(QString::fromUtf8("treewidgetLayout"));
        treeWidget = new QTreeWidget(OrderManagerForm);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setRootIsDecorated(false);
        treeWidget->header()->setDefaultSectionSize(75);

        treewidgetLayout->addWidget(treeWidget);

        treewidgetLayout->setStretch(0, 7);

        horizontalLayout->addLayout(treewidgetLayout);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 5);

        horizontalLayout_4->addLayout(horizontalLayout);

#if QT_CONFIG(shortcut)
        idLabel->setBuddy(idLineEdit);
        nameLabel->setBuddy(ClientLineEdit);
        phoneNumberLabel->setBuddy(ProductLineEdit);
        addressLabel->setBuddy(StockLineEdit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(OrderManagerForm);

        QMetaObject::connectSlotsByName(OrderManagerForm);
    } // setupUi

    void retranslateUi(QWidget *OrderManagerForm)
    {
        OrderManagerForm->setWindowTitle(QCoreApplication::translate("OrderManagerForm", "Client Info", nullptr));
        label_2->setText(QCoreApplication::translate("OrderManagerForm", "\354\243\274\353\254\270\354\240\225\353\263\264\352\264\200\353\246\254", nullptr));
        clearbutton->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("OrderManagerForm", "\354\243\274\353\254\270\354\240\225\353\263\264\352\264\200\353\246\254", nullptr));
        cbutton->setText(QCoreApplication::translate("OrderManagerForm", "ClientSearch", nullptr));
        pbutton->setText(QCoreApplication::translate("OrderManagerForm", "ProductSearch", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = clienttreeWidget->headerItem();
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("OrderManagerForm", "Address", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("OrderManagerForm", "Phone Number", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("OrderManagerForm", "Name", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("OrderManagerForm", "ID", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = producttreeWidget->headerItem();
        ___qtreewidgetitem1->setText(3, QCoreApplication::translate("OrderManagerForm", "Stock", nullptr));
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("OrderManagerForm", "Price", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("OrderManagerForm", "Name", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("OrderManagerForm", "ID", nullptr));
        idLabel->setText(QCoreApplication::translate("OrderManagerForm", "&OrderNum", nullptr));
        idLineEdit->setText(QCoreApplication::translate("OrderManagerForm", "Auto-generated", nullptr));
        idLineEdit->setPlaceholderText(QString());
        nameLabel->setText(QCoreApplication::translate("OrderManagerForm", "&Client", nullptr));
        CIDlineEdit->setPlaceholderText(QCoreApplication::translate("OrderManagerForm", "Click_List", nullptr));
        phoneNumberLabel->setText(QCoreApplication::translate("OrderManagerForm", "&Product", nullptr));
        PIDlineEdit->setText(QString());
        PIDlineEdit->setPlaceholderText(QCoreApplication::translate("OrderManagerForm", "Click_List", nullptr));
        addressLabel->setText(QCoreApplication::translate("OrderManagerForm", "&Stock", nullptr));
        StockLineEdit->setInputMask(QString());
        StockLineEdit->setPlaceholderText(QCoreApplication::translate("OrderManagerForm", "Only Number", nullptr));
        label->setText(QCoreApplication::translate("OrderManagerForm", "Price", nullptr));
        pricelineEdit->setPlaceholderText(QCoreApplication::translate("OrderManagerForm", "Click_List", nullptr));
        addPushButton->setText(QCoreApplication::translate("OrderManagerForm", "&Add", nullptr));
        modifyPushButton->setText(QCoreApplication::translate("OrderManagerForm", "&Modify", nullptr));
        label_3->setText(QCoreApplication::translate("OrderManagerForm", "Address", nullptr));
        addresslineEdit->setPlaceholderText(QCoreApplication::translate("OrderManagerForm", "Click_List", nullptr));
        groupBox->setTitle(QCoreApplication::translate("OrderManagerForm", "&Search", nullptr));
        searchComboBox->setItemText(0, QCoreApplication::translate("OrderManagerForm", "OrderNum", nullptr));
        searchComboBox->setItemText(1, QCoreApplication::translate("OrderManagerForm", "Client (Name or ID)", nullptr));
        searchComboBox->setItemText(2, QCoreApplication::translate("OrderManagerForm", "Product (Name or ID)", nullptr));

        searchPushButton->setText(QCoreApplication::translate("OrderManagerForm", "S&earch", nullptr));
        pushButton->setText(QCoreApplication::translate("OrderManagerForm", "Quit", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidget->headerItem();
        ___qtreewidgetitem2->setText(6, QCoreApplication::translate("OrderManagerForm", "Address", nullptr));
        ___qtreewidgetitem2->setText(5, QCoreApplication::translate("OrderManagerForm", "Sum", nullptr));
        ___qtreewidgetitem2->setText(4, QCoreApplication::translate("OrderManagerForm", "Price", nullptr));
        ___qtreewidgetitem2->setText(3, QCoreApplication::translate("OrderManagerForm", "Stock", nullptr));
        ___qtreewidgetitem2->setText(2, QCoreApplication::translate("OrderManagerForm", "Product", nullptr));
        ___qtreewidgetitem2->setText(1, QCoreApplication::translate("OrderManagerForm", "ClientName", nullptr));
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("OrderManagerForm", "OrderNum", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderManagerForm: public Ui_OrderManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERMANAGERFORM_H
