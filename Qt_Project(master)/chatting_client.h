#ifndef CHATTING_CLIENT_H
#define CHATTING_CLIENT_H

#include <QWidget>
#include <QDataStream>

#include "Chat_Status.h"

class QTcpSocket;
class QFile;
class QProgressDialog;

namespace Ui {
class Chatting_Client;
}


class Chatting_Client : public QWidget
{
    Q_OBJECT

public:
    const int PORT_NUMBER = 8000;

    explicit Chatting_Client(QWidget *parent = nullptr);
    ~Chatting_Client();

private slots:
    void receiveData( );			// 서버에서 데이터가 올 때
    void sendData( );               // 서버로 데이터를 보낼 때
    void disconnect( );
    void sendProtocol(Chat_Status, char*, int = 1020);
    void sendFile();
    void goOnSend(qint64);

    void on_logoutButton_clicked();

private:
    Ui::Chatting_Client *ui;

    void closeEvent(QCloseEvent*) override;

    // 서버로 보내는 메시지 입력용
    // 메시지 전송
    QTcpSocket *clientSocket;		// 클라이언트용 소켓
    QTcpSocket *fileClient;
    QProgressDialog* progressDialog;    // 파일 진행 확인
    QFile* file;            // 서버로 보내는 파일
    qint64 loadSize;        // 파일의 크기
    qint64 byteToWrite;     // 보낸 파일의 크기
    qint64 totalSize;       // 전체 파일의 크기
    QByteArray outBlock;    // 전송을 위한 데이터
    bool isSent;            // 파일 서버에 접속되었는지 확인

};

#endif // CHATTING_CLIENT_H
