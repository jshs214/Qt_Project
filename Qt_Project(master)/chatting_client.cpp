#include "chatting_client.h"
#include "ui_chatting_client.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDataStream>
#include <QTcpSocket>
#include <QApplication>
#include <QThread>
#include <QMessageBox>
#include <QSettings>

#define BLOCK_SIZE      1024

Chatting_Client::Chatting_Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chatting_Client)
{
    ui->setupUi(this);

    ui->serverAddress->setText("127.0.0.1");
    //ui->serverAddress->setInputMask("999.999.999.999;_");
    QRegularExpression re("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                          "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                          "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                          "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    QRegularExpressionValidator validator(re);
    ui->serverAddress->setPlaceholderText("Server IP Address");
    ui->serverAddress->setValidator(&validator);

    ui->serverPort->setText("8000");
    ui->serverPort->setInputMask("00000;_");
    ui->serverPort->setPlaceholderText("Server Port No");

    connect(ui->connectButton, &QPushButton::clicked,
            [=]{
        if(ui->connectButton->text() == tr("Log In")) {
            clientSocket->connectToHost(ui->serverAddress->text( ),
                                                 ui->serverPort->text( ).toInt( ));
            connectToServer( );
            ui->connectButton->setText(tr("Chat in"));
        } else {
            QByteArray bytearray;
            chatProtocolType data;
            data.type = Chat_In;
            qstrcpy(data.data, ui->name->text().toStdString().data());

            QByteArray sendArray;
            QDataStream out(&sendArray, QIODevice::WriteOnly);
            out << data.type;
            out.writeRawData(data.data, 1020);
            clientSocket->write(sendArray);
        }
        ui->connectButton->setDisabled(true);
        ui->inputLine->setEnabled(true);
        ui->sentButton->setEnabled(true);
    } );

    ui->message->setReadOnly(true);

    connect(ui->inputLine, SIGNAL(returnPressed( )), SLOT(sendData( )));
    connect(ui->inputLine, SIGNAL(returnPressed( )), ui->inputLine, SLOT(clear( )));

    connect(ui->sentButton, SIGNAL(clicked( )), SLOT(sendData( )));
    connect(ui->sentButton, SIGNAL(clicked( )), ui->inputLine, SLOT(clear( )));
    ui->inputLine->setEnabled(false);
    ui->sentButton->setEnabled(false);

    connect(ui->quitButton, SIGNAL(clicked( )), qApp, SLOT(quit( )));

    clientSocket = new QTcpSocket(this);			// 클라이언트 소켓 생성
    connect(clientSocket, &QAbstractSocket::errorOccurred,
            [=]{ qDebug( ) << clientSocket->errorString( ); });
    connect(clientSocket, SIGNAL(readyRead( )), SLOT(receiveData( )));
    connect(clientSocket, SIGNAL(disconnected( )), SLOT(disconnect( )));
    setWindowTitle(tr("Chat Client"));
    QSettings settings("ChatClient", "Chat Client");
    ui->name->setText(settings.value("ChatClient/ID").toString());

}

Chatting_Client::~Chatting_Client()
{
    clientSocket->close( );
    QSettings settings("ChatClient", "Chat Client");
    settings.setValue("ChatClient/ID", ui->name->text());
    delete ui;
}
void Chatting_Client::closeEvent(QCloseEvent*)
{
    chatProtocolType data;
    data.type = Chat_LogOut;
    qstrcpy(data.data, ui->name->text().toStdString().data());

    QByteArray sendArray;
    QDataStream out(&sendArray, QIODevice::WriteOnly);
    out << data.type;
    out.writeRawData(data.data, 1020);
    clientSocket->write(sendArray);

    clientSocket->disconnectFromHost();
    while(clientSocket->waitForDisconnected(1000))
        QThread::usleep(10);
}

void Chatting_Client::receiveData( )
{
    QTcpSocket *clientSocket = dynamic_cast<QTcpSocket *>(sender( ));
    if (clientSocket->bytesAvailable( ) > BLOCK_SIZE) return;
    QByteArray bytearray = clientSocket->read(BLOCK_SIZE);
    chatProtocolType data;
    QDataStream in(&bytearray, QIODevice::ReadOnly);
    in >> data.type;
    in.readRawData(data.data, 1020);

    qDebug( ) << data.type;
    switch(data.type) {
    case Chat_In:
        ui->message->append(QString(data.data));
        break;
        ui->inputLine->setEnabled(true);
        ui->sentButton->setEnabled(true);
        ui->connectButton->setDisabled(true);
    case Chat_KickOut:
        QMessageBox::critical(this, tr("Chatting Client"), \
                              tr("Kick out from Server"));
        ui->inputLine->setEnabled(false);
        ui->sentButton->setEnabled(false);
        ui->connectButton->setEnabled(true);
        break;
    case Chat_Invite:
        QMessageBox::critical(this, tr("Chatting Client"), \
                              tr("Invited from Server"));
        ui->inputLine->setEnabled(true);
        ui->sentButton->setEnabled(true);
        ui->connectButton->setDisabled(true);
        break;
    default:
        break;
    };
}

void Chatting_Client::sendData(  )
{
    QString str = ui->inputLine->text( );
    if(str.length( )) {
        QByteArray bytearray;
        bytearray = str.toUtf8( );
        ui->message->append("<font color=red>나</font> : " + str);

        chatProtocolType data;
        data.type = Chat_Talk;
        qstrcpy(data.data, bytearray.data());

        QByteArray sendArray;
        QDataStream out(&sendArray, QIODevice::WriteOnly);
        out << data.type;
        out.writeRawData(data.data, 1020);
        clientSocket->write(sendArray);
    }
}

void Chatting_Client::connectToServer( )
{
    chatProtocolType data;
    data.type = Chat_Login;
    qstrcpy(data.data, ui->name->text().toStdString().data());

    QByteArray sendArray;
    QDataStream out(&sendArray, QIODevice::WriteOnly);
    out << data.type;
    out.writeRawData(data.data, 1020);
    clientSocket->write(sendArray);
}

void Chatting_Client::disconnect( )
{
    QMessageBox::critical(this, tr("Chatting Client"), \
                          tr("Disconnect from Server"));
    ui->inputLine->setEnabled(false);
    ui->sentButton->setEnabled(false);
//    close( );
}

