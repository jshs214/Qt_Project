#ifndef CHATSERVERFORM_H
#define CHATSERVERFORM_H

#include <QWidget>
#include <QList>
#include <QHash>

class QLabel;
class QTcpServer;
class QTcpSocket;

namespace Ui {
class ChatServerForm;
}

typedef struct {
    int type;
    char data[1020];
} chatProtocolType;

typedef enum {
    Chat_Login,
    Chat_In,
    Chat_Talk,
    Chat_Close,
    Chat_LogOut,
    Chat_Invite,
    Chat_KickOut,
    Chat_FileTransform
} Chat_Status;

class chattingForm : public QWidget
{
    Q_OBJECT

public:
    explicit chattingForm(QWidget *parent = nullptr);
    ~chattingForm();

private:
    const int BLOCK_SIZE = 1024;
    Ui::ChatServerForm *ui;
    QTcpServer *tcpServer;
    QList<QTcpSocket*> clientList;
    QList<int> clientIDList;
    QHash<QString, QString> clientNameHash;
    QHash<QString, int> clientIDHash;
    QMenu* menu;

private slots:
    void clientConnect( );                       /* 채팅 서버 */
    void receiveData( );
    void removeClient( );
    void addClient(int, QString);
    void inviteClient();
    void kickOut();
    void on_clientTreeWidget_customContextMenuRequested(const QPoint &pos);
};

#endif // CHATSERVERFORM_H

