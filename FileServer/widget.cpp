#include "widget.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QByteArray>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QProgressDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    infoLabel = new QLabel("Hello, World", this);
    QPushButton* button = new QPushButton("Server Start", this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(infoLabel);
    layout->addWidget(button);

    progressDialog = new QProgressDialog(this);
    progressDialog->hide();
    connect(button, SIGNAL(clicked()), SLOT(clickButton()));
}

Widget::~Widget()
{
}

void Widget::acceptConnection()
{
    infoLabel->setText(tr("Connected, preparing to receive files!"));

    receivedSocket = server->nextPendingConnection();
    connect(receivedSocket, SIGNAL(readyRead()), this, SLOT(readClient()));
}

void Widget::readClient()
{
    infoLabel->setText(tr("Receiving file ..."));

    if (byteReceived == 0) { // just started to receive data, this data is file information
        progressDialog->setValue(0);

        QDataStream in(receivedSocket);
        in >> totalSize >> byteReceived >> filename;
        QFileInfo info(filename);
        QString currentFileName = info.fileName();
        newFile = new QFile(currentFileName);
        newFile->open(QFile::WriteOnly);
        progressDialog->show();
    } else { // Officially read the file content
        inBlock = receivedSocket->readAll();

        byteReceived += inBlock.size();
        newFile->write(inBlock);
        newFile->flush();
    }

    progressDialog->setMaximum(totalSize);
    progressDialog->setValue(byteReceived);

    if (byteReceived == totalSize) {
        infoLabel->setText(tr("%1 receive completed").arg(filename));

        inBlock.clear();
        byteReceived = 0;
        totalSize = 0;
        progressDialog->hide();
        newFile->close();
    }
}

void Widget::clickButton()
{
    totalSize = 0;
    byteReceived = 0;

    server = new QTcpServer(this);
    server->listen(QHostAddress("127.0.0.1"), 8000);

    connect(server, SIGNAL(newConnection()), SLOT(acceptConnection()));

    progressDialog->setValue(0);
    progressDialog->hide();
    infoLabel->setText(tr("Start listening ..."));
}
