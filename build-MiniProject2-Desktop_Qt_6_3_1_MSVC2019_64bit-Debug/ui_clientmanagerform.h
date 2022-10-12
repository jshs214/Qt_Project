/********************************************************************************
** Form generated from reading UI file 'clientmanagerform.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTMANAGERFORM_H
#define UI_CLIENTMANAGERFORM_H

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

class Ui_ClientManagerForm
{
public:
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *clearbutton;
    QPushButton *ClientManagement;
    QFormLayout *clientFormLayout;
    QLabel *idLabel;
    QLineEdit *idLineEdit;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *phoneNumberLabel;
    QLineEdit *phoneNumberLineEdit;
    QLabel *addressLabel;
    QLineEdit *addressLineEdit;
    QHBoxLayout *addHorizontalLayout;
    QPushButton *addPushButton;
    QPushButton *modifyPushButton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QComboBox *searchComboBox;
    QLineEdit *searchLineEdit;
    QPushButton *searchPushButton;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_3;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *ClientManagerForm)
    {
        if (ClientManagerForm->objectName().isEmpty())
            ClientManagerForm->setObjectName(QString::fromUtf8("ClientManagerForm"));
        ClientManagerForm->resize(603, 418);
        horizontalLayout_3 = new QHBoxLayout(ClientManagerForm);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(ClientManagerForm);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        clearbutton = new QPushButton(ClientManagerForm);
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

        ClientManagement = new QPushButton(ClientManagerForm);
        ClientManagement->setObjectName(QString::fromUtf8("ClientManagement"));

        verticalLayout_4->addWidget(ClientManagement);

        clientFormLayout = new QFormLayout();
        clientFormLayout->setObjectName(QString::fromUtf8("clientFormLayout"));
        idLabel = new QLabel(ClientManagerForm);
        idLabel->setObjectName(QString::fromUtf8("idLabel"));

        clientFormLayout->setWidget(0, QFormLayout::LabelRole, idLabel);

        idLineEdit = new QLineEdit(ClientManagerForm);
        idLineEdit->setObjectName(QString::fromUtf8("idLineEdit"));
        idLineEdit->setReadOnly(true);

        clientFormLayout->setWidget(0, QFormLayout::FieldRole, idLineEdit);

        nameLabel = new QLabel(ClientManagerForm);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        clientFormLayout->setWidget(1, QFormLayout::LabelRole, nameLabel);

        nameLineEdit = new QLineEdit(ClientManagerForm);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        clientFormLayout->setWidget(1, QFormLayout::FieldRole, nameLineEdit);

        phoneNumberLabel = new QLabel(ClientManagerForm);
        phoneNumberLabel->setObjectName(QString::fromUtf8("phoneNumberLabel"));

        clientFormLayout->setWidget(2, QFormLayout::LabelRole, phoneNumberLabel);

        phoneNumberLineEdit = new QLineEdit(ClientManagerForm);
        phoneNumberLineEdit->setObjectName(QString::fromUtf8("phoneNumberLineEdit"));

        clientFormLayout->setWidget(2, QFormLayout::FieldRole, phoneNumberLineEdit);

        addressLabel = new QLabel(ClientManagerForm);
        addressLabel->setObjectName(QString::fromUtf8("addressLabel"));

        clientFormLayout->setWidget(3, QFormLayout::LabelRole, addressLabel);

        addressLineEdit = new QLineEdit(ClientManagerForm);
        addressLineEdit->setObjectName(QString::fromUtf8("addressLineEdit"));

        clientFormLayout->setWidget(3, QFormLayout::FieldRole, addressLineEdit);

        addHorizontalLayout = new QHBoxLayout();
        addHorizontalLayout->setObjectName(QString::fromUtf8("addHorizontalLayout"));
        addPushButton = new QPushButton(ClientManagerForm);
        addPushButton->setObjectName(QString::fromUtf8("addPushButton"));

        addHorizontalLayout->addWidget(addPushButton);

        modifyPushButton = new QPushButton(ClientManagerForm);
        modifyPushButton->setObjectName(QString::fromUtf8("modifyPushButton"));

        addHorizontalLayout->addWidget(modifyPushButton);


        clientFormLayout->setLayout(4, QFormLayout::SpanningRole, addHorizontalLayout);


        verticalLayout_4->addLayout(clientFormLayout);

        groupBox = new QGroupBox(ClientManagerForm);
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

        verticalSpacer_3 = new QSpacerItem(165, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        pushButton = new QPushButton(ClientManagerForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_4->addWidget(pushButton);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(2, 7);
        verticalLayout_4->setStretch(3, 6);
        verticalLayout_4->setStretch(4, 1);

        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        treeWidget = new QTreeWidget(ClientManagerForm);
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
        phoneNumberLabel->setBuddy(phoneNumberLineEdit);
        addressLabel->setBuddy(addressLineEdit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(ClientManagerForm);

        QMetaObject::connectSlotsByName(ClientManagerForm);
    } // setupUi

    void retranslateUi(QWidget *ClientManagerForm)
    {
        ClientManagerForm->setWindowTitle(QCoreApplication::translate("ClientManagerForm", "Client Info", nullptr));
        label->setText(QCoreApplication::translate("ClientManagerForm", "\352\263\240\352\260\235\354\240\225\353\263\264\352\264\200\353\246\254", nullptr));
        clearbutton->setText(QString());
        ClientManagement->setText(QCoreApplication::translate("ClientManagerForm", "\352\263\240\352\260\235\354\240\225\353\263\264\352\264\200\353\246\254", nullptr));
        idLabel->setText(QCoreApplication::translate("ClientManagerForm", "I&D", nullptr));
        idLineEdit->setPlaceholderText(QCoreApplication::translate("ClientManagerForm", "Auto-generated", nullptr));
        nameLabel->setText(QCoreApplication::translate("ClientManagerForm", "&Name", nullptr));
        phoneNumberLabel->setText(QCoreApplication::translate("ClientManagerForm", "&Phone Number", nullptr));
        phoneNumberLineEdit->setInputMask(QString());
        addressLabel->setText(QCoreApplication::translate("ClientManagerForm", "&Address", nullptr));
        addPushButton->setText(QCoreApplication::translate("ClientManagerForm", "&Add", nullptr));
        modifyPushButton->setText(QCoreApplication::translate("ClientManagerForm", "&Modify", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ClientManagerForm", "&Search", nullptr));
        searchComboBox->setItemText(0, QCoreApplication::translate("ClientManagerForm", "ID", nullptr));
        searchComboBox->setItemText(1, QCoreApplication::translate("ClientManagerForm", "Name", nullptr));
        searchComboBox->setItemText(2, QCoreApplication::translate("ClientManagerForm", "Phone Number", nullptr));
        searchComboBox->setItemText(3, QCoreApplication::translate("ClientManagerForm", "Address", nullptr));

        searchPushButton->setText(QCoreApplication::translate("ClientManagerForm", "S&earch", nullptr));
        pushButton->setText(QCoreApplication::translate("ClientManagerForm", "Quit", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("ClientManagerForm", "Address", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("ClientManagerForm", "Phone Number", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("ClientManagerForm", "Name", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ClientManagerForm", "ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientManagerForm: public Ui_ClientManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTMANAGERFORM_H
