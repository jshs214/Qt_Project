#include "chattingform.h"
#include "ui_chattingform.h"

#include "chattingitem.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QTcpServer>
#include <QTcpSocket>
#include <QApplication>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QDebug>
#include <QMenu>

chattingForm::chattingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chattingForm)
{
    ui->setupUi(this);
    QList<int> sizes;
    sizes << 120 << 500;
    ui->splitter->setSizes(sizes);
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection( )), SLOT(clientConnect( )));
    if (!tcpServer->listen(QHostAddress::Any, 8000)) {
        QMessageBox::critical(this, tr("Chatting Server"), \
                              tr("Unable to start the server: %1.") \
                              .arg(tcpServer->errorString( )));
        close( );
        return;
    }

    QAction* inviteAction = new QAction(tr("&Invite"));
    inviteAction->setObjectName("Invite");
    connect(inviteAction, SIGNAL(triggered()), SLOT(inviteClient()));

    QAction* removeAction = new QAction(tr("&Kick out"));
    connect(removeAction, SIGNAL(triggered()), SLOT(kickOut()));

    menu = new QMenu;
    menu->addAction(inviteAction);
    menu->addAction(removeAction);
    ui->clientTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    qDebug() << tr("The server is running on port %1.").arg(tcpServer->serverPort( ));
}

chattingForm::~chattingForm()
{
    delete ui;

    tcpServer->close( );
}

void chattingForm::clientConnect( )
{
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection( );
    connect(clientConnection, SIGNAL(readyRead( )), SLOT(receiveData( )));
    connect(clientConnection, SIGNAL(disconnected( )), SLOT(removeClient()));
    qDebug("new connection is established...");
}

void chattingForm::receiveData( )
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));
    QByteArray bytearray = clientConnection->read(BLOCK_SIZE);

    chatProtocolType data;
    QDataStream in(&bytearray, QIODevice::ReadOnly);
    in >> data.type;
    in.readRawData(data.data, 1020);

    QString ip = clientConnection->peerAddress().toString();
    QString name = QString::fromStdString(data.data);

    switch(data.type) {
    case Chat_Login:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(1) != "O") {
                item->setText(0, "O");
                clientList.append(clientConnection);        // QList<QTcpSocket*> clientList;
                clientNameHash[ip] = name;
            }
        }
        break;
    case Chat_In:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(1) != "O") {
                item->setText(0, "O");
            }
        }
        break;
    case Chat_Talk: {
        foreach(QTcpSocket *sock, clientList) {
            if(sock != clientConnection) {
                QByteArray data("<font color=red>");
                data.append(name.toStdString().data());
                data.append("</font> : ");
                data.append(bytearray);
                sock->write(data);
            }
        }

        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
        item->setText(0, clientConnection->peerAddress().toString());
        item->setText(1, QString::number(clientConnection->peerPort()));
        item->setText(2, QString::number(clientIDHash[clientNameHash[ip]]));
        item->setText(3, clientNameHash[ip]);
        item->setText(4, QString(data.data));
        item->setText(5, QDateTime::currentDateTime().toString());
        item->setToolTip(4, QString(data.data));

        for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
            ui->messageTreeWidget->resizeColumnToContents(i);

        ui->messageTreeWidget->addTopLevelItem(item);
    }
        break;
    case Chat_Close:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            if(item->text(1) == "O") {
                item->setText(0, "X");
            }
        }
        break;
    case Chat_LogOut:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            if(item->text(1) == "O") {
                item->setText(0, "X");
                clientList.removeOne(clientConnection);        // QList<QTcpSocket*> clientList;
            }
        }
//        ui->inviteComboBox->addItem(name);
        break;
    }
    //    qDebug() << bytearray;
}

void chattingForm::removeClient()
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));
    clientList.removeOne(clientConnection);
    clientConnection->deleteLater();

    QString name = clientNameHash[clientConnection->peerAddress().toString()];
    foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
        item->setText(0, "X");
    }
}

void chattingForm::addClient(int id, QString name)
{
    clientIDList << id;
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->clientTreeWidget);
    item->setText(0, "X");
    item->setText(1, name);
    ui->clientTreeWidget->addTopLevelItem(item);
    clientIDHash[name] = id;
    ui->clientTreeWidget->resizeColumnToContents(0);
}

void chattingForm::on_clientTreeWidget_customContextMenuRequested(const QPoint &pos)
{
    foreach(QAction *action, menu->actions()) {
        if(action->objectName() == "Invite")
            action->setEnabled(ui->clientTreeWidget->currentItem()->text(0) != "O");
        else
            action->setEnabled(ui->clientTreeWidget->currentItem()->text(0) == "O");
    }
    QPoint globalPos = ui->clientTreeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void chattingForm::kickOut()
{
    QString name = ui->clientTreeWidget->currentItem()->text(1);
    QString ip = clientNameHash.key(name);

    chatProtocolType data;
    data.type = Chat_KickOut;
    qstrcpy(data.data, "");
    QByteArray sendArray;
    QDataStream out(&sendArray, QIODevice::WriteOnly);
    out << data.type;
    out.writeRawData(data.data, 1020);

    foreach(QTcpSocket* sock, clientList) {
        if(sock->peerAddress().toString() == ip){
//            sock->disconnectFromHost();
            sock->write(sendArray);
        }
    }
    ui->clientTreeWidget->currentItem()->setText(0, "X");
//    clientIDList.append(clientIDHash[name]);
//    ui->inviteComboBox->addItem(name);
}

void chattingForm::inviteClient()
{
    if(ui->clientTreeWidget->topLevelItemCount()) {
        QString name = ui->clientTreeWidget->currentItem()->text(1);
        QString ip = clientNameHash.key(name, "");

        chatProtocolType data;
        data.type = Chat_Invite;
        qstrcpy(data.data, "");
        QByteArray sendArray;
        QDataStream out(&sendArray, QIODevice::WriteOnly);
        out << data.type;
        out.writeRawData(data.data, 1020);

        foreach(QTcpSocket* sock, clientList) {
            if(sock->peerAddress().toString() == ip){
                sock->write(sendArray);
//                clientList.append(sock);        // QList<QTcpSocket*> clientList;
                foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
                    if(item->text(1) != "O") {
                        item->setText(0, "O");
                        clientList.append(sock);        // QList<QTcpSocket*> clientList;
//                        clientNameHash[ip] = name;
                    }
                }
            }
        }
    }
}

