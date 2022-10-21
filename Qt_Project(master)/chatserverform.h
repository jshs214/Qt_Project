#ifndef CHATSERVERFORM_H
#define CHATSERVERFORM_H

#include <QWidget>
#include <QList>
#include <QHash>

#include "Chat_Status.h"

class QLabel;
class QTcpServer;
class QTcpSocket;
class QFile;
class QProgressDialog;
class LogThread;

namespace Ui {
class ChatServerForm;
}

class ChatServerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatServerForm(QWidget *parent = nullptr);
    ~ChatServerForm();

private:
    const int BLOCK_SIZE = 1024;
    const int PORT_NUMBER = 8000;

    Ui::ChatServerForm *ui;

    QTcpServer *chatServer;
    QTcpServer *fileServer;
    QHash<quint16, QString> clientNameHash;     // port, name
    QHash<QString, QTcpSocket*> clientSocketHash;// name, socket
    QHash<QString, int> clientIDHash;           // name, id
    QMenu* menu;
    QFile* file;
    QProgressDialog* progressDialog;
    qint64 totalSize;
    qint64 byteReceived;
    QByteArray inBlock;
    LogThread* logThread;


private slots:
    void acceptConnection();                /* 파일 서버 */
    void readClient();

    void clientConnect( );                  /* 채팅 서버 */
    void receiveData( );
    void removeClient( );
    void addClient(int, QString);
    void inviteClient();
    void kickOut();
    void on_clientTreeWidget_customContextMenuRequested(const QPoint &pos);
    void remClient(QString);
};

#endif // CHATSERVERFORM_H
