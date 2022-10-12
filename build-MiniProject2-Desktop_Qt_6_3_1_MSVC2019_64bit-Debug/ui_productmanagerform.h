/********************************************************************************
** Form generated from reading UI file 'productmanagerform.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTMANAGERFORM_H
#define UI_PRODUCTMANAGERFORM_H

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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProductManagerForm
{
public:
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *clearbutton;
    QPushButton *ProductManagement;
    QFormLayout *clientFormLayout;
    QLabel *idLabel;
    QLineEdit *idLineEdit;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *priceLabel;
    QLineEdit *priceLineEdit;
    QLabel *stockLabel;
    QLineEdit *stockLineEdit;
    QHBoxLayout *addHorizontalLayout;
    QPushButton *addPushButton;
    QPushButton *modifyPushButton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QComboBox *searchComboBox;
    QLineEdit *searchLineEdit;
    QPushButton *searchPushButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_3;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *ProductManagerForm)
    {
        if (ProductManagerForm->objectName().isEmpty())
            ProductManagerForm->setObjectName(QString::fromUtf8("ProductManagerForm"));
        ProductManagerForm->resize(603, 418);
        horizontalLayout_3 = new QHBoxLayout(ProductManagerForm);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(ProductManagerForm);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        clearbutton = new QPushButton(ProductManagerForm);
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

        horizontalLayout_2->addWidget(clearbutton);


        verticalLayout_4->addLayout(horizontalLayout_2);

        ProductManagement = new QPushButton(ProductManagerForm);
        ProductManagement->setObjectName(QString::fromUtf8("ProductManagement"));

        verticalLayout_4->addWidget(ProductManagement);

        clientFormLayout = new QFormLayout();
        clientFormLayout->setObjectName(QString::fromUtf8("clientFormLayout"));
        idLabel = new QLabel(ProductManagerForm);
        idLabel->setObjectName(QString::fromUtf8("idLabel"));

        clientFormLayout->setWidget(0, QFormLayout::LabelRole, idLabel);

        idLineEdit = new QLineEdit(ProductManagerForm);
        idLineEdit->setObjectName(QString::fromUtf8("idLineEdit"));
        idLineEdit->setReadOnly(true);

        clientFormLayout->setWidget(0, QFormLayout::FieldRole, idLineEdit);

        nameLabel = new QLabel(ProductManagerForm);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        clientFormLayout->setWidget(1, QFormLayout::LabelRole, nameLabel);

        nameLineEdit = new QLineEdit(ProductManagerForm);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        clientFormLayout->setWidget(1, QFormLayout::FieldRole, nameLineEdit);

        priceLabel = new QLabel(ProductManagerForm);
        priceLabel->setObjectName(QString::fromUtf8("priceLabel"));

        clientFormLayout->setWidget(2, QFormLayout::LabelRole, priceLabel);

        priceLineEdit = new QLineEdit(ProductManagerForm);
        priceLineEdit->setObjectName(QString::fromUtf8("priceLineEdit"));

        clientFormLayout->setWidget(2, QFormLayout::FieldRole, priceLineEdit);

        stockLabel = new QLabel(ProductManagerForm);
        stockLabel->setObjectName(QString::fromUtf8("stockLabel"));

        clientFormLayout->setWidget(3, QFormLayout::LabelRole, stockLabel);

        stockLineEdit = new QLineEdit(ProductManagerForm);
        stockLineEdit->setObjectName(QString::fromUtf8("stockLineEdit"));

        clientFormLayout->setWidget(3, QFormLayout::FieldRole, stockLineEdit);

        addHorizontalLayout = new QHBoxLayout();
        addHorizontalLayout->setObjectName(QString::fromUtf8("addHorizontalLayout"));
        addPushButton = new QPushButton(ProductManagerForm);
        addPushButton->setObjectName(QString::fromUtf8("addPushButton"));

        addHorizontalLayout->addWidget(addPushButton);

        modifyPushButton = new QPushButton(ProductManagerForm);
        modifyPushButton->setObjectName(QString::fromUtf8("modifyPushButton"));

        addHorizontalLayout->addWidget(modifyPushButton);


        clientFormLayout->setLayout(4, QFormLayout::SpanningRole, addHorizontalLayout);


        verticalLayout_4->addLayout(clientFormLayout);

        groupBox = new QGroupBox(ProductManagerForm);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        searchComboBox = new QComboBox(groupBox);
        searchComboBox->addItem(QString());
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

        verticalSpacer_2 = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        pushButton = new QPushButton(ProductManagerForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_4->addWidget(pushButton);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(2, 7);
        verticalLayout_4->setStretch(3, 6);
        verticalLayout_4->setStretch(4, 1);

        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        treeWidget = new QTreeWidget(ProductManagerForm);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setRootIsDecorated(false);

        verticalLayout_3->addWidget(treeWidget);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 6);

        horizontalLayout_3->addLayout(horizontalLayout);

#if QT_CONFIG(shortcut)
        idLabel->setBuddy(idLineEdit);
        nameLabel->setBuddy(nameLineEdit);
        priceLabel->setBuddy(priceLineEdit);
        stockLabel->setBuddy(stockLineEdit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(ProductManagerForm);

        QMetaObject::connectSlotsByName(ProductManagerForm);
    } // setupUi

    void retranslateUi(QWidget *ProductManagerForm)
    {
        ProductManagerForm->setWindowTitle(QCoreApplication::translate("ProductManagerForm", "Client Info", nullptr));
        label->setText(QCoreApplication::translate("ProductManagerForm", "\354\240\234\355\222\210\354\240\225\353\263\264\352\264\200\353\246\254", nullptr));
        clearbutton->setText(QString());
        ProductManagement->setText(QCoreApplication::translate("ProductManagerForm", "\354\240\234\355\222\210\354\240\225\353\263\264\352\264\200\353\246\254", nullptr));
        idLabel->setText(QCoreApplication::translate("ProductManagerForm", "I&D", nullptr));
        idLineEdit->setPlaceholderText(QCoreApplication::translate("ProductManagerForm", "Auto-generated", nullptr));
        nameLabel->setText(QCoreApplication::translate("ProductManagerForm", "&Name", nullptr));
        priceLabel->setText(QCoreApplication::translate("ProductManagerForm", "&Price", nullptr));
        priceLineEdit->setPlaceholderText(QCoreApplication::translate("ProductManagerForm", "Only Number", nullptr));
        stockLabel->setText(QCoreApplication::translate("ProductManagerForm", "&Stock", nullptr));
        stockLineEdit->setPlaceholderText(QCoreApplication::translate("ProductManagerForm", "Only Number", nullptr));
        addPushButton->setText(QCoreApplication::translate("ProductManagerForm", "&Add", nullptr));
        modifyPushButton->setText(QCoreApplication::translate("ProductManagerForm", "&Modify", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ProductManagerForm", "&Search", nullptr));
        searchComboBox->setItemText(0, QCoreApplication::translate("ProductManagerForm", "ID", nullptr));
        searchComboBox->setItemText(1, QCoreApplication::translate("ProductManagerForm", "Name", nullptr));
        searchComboBox->setItemText(2, QCoreApplication::translate("ProductManagerForm", "Price", nullptr));
        searchComboBox->setItemText(3, QCoreApplication::translate("ProductManagerForm", "Stock", nullptr));

        searchPushButton->setText(QCoreApplication::translate("ProductManagerForm", "S&earch", nullptr));
        pushButton->setText(QCoreApplication::translate("ProductManagerForm", "Quit", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("ProductManagerForm", "Stock", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("ProductManagerForm", "Price", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("ProductManagerForm", "Name", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ProductManagerForm", "ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProductManagerForm: public Ui_ProductManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTMANAGERFORM_H
