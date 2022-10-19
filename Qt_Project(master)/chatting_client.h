#ifndef CHATTING_CLIENT_H
#define CHATTING_CLIENT_H

#include <QWidget>
#include <QDataStream>
#include "chatserverform.h"

class QTcpSocket;

namespace Ui {
class Chatting_Client;
}


class Chatting_Client : public QWidget
{
    Q_OBJECT

public:
    explicit Chatting_Client(QWidget *parent = nullptr);
    ~Chatting_Client();

private slots:
    void connectToServer( );
    void receiveData( );			// 서버에서 데이터가 올 때
    void sendData( );			// 서버로 데이터를 보낼 때
    void disconnect( );


private:
    Ui::Chatting_Client *ui;

    void closeEvent(QCloseEvent*) override;

    QTcpSocket *clientSocket;		// 클라이언트용 소켓
};

#endif // CHATTING_CLIENT_H
