#include "widget.h"

#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QByteArray>
#include <QProgressDialog>
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent), sendTimes(0)
{
    infoLabel = new QLabel("Hello, World", this);
    QPushButton* button = new QPushButton("Send", this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(infoLabel);
    layout->addWidget(button);

    tcpClient = new QTcpSocket(this);
    progressDialog = new QProgressDialog(this);
    progressDialog->hide();

    connect(button, SIGNAL(clicked()), SLOT(sendData()));
    connect(tcpClient, SIGNAL(connected()), SLOT(send())); // When the connection is successful, start to transfer files
    connect(tcpClient, SIGNAL(bytesWritten(qint64)), SLOT(goOnSend(qint64)));
}

Widget::~Widget()
{
}

void Widget::send() // Send file header information
{
    byteToWrite = localFile->size(); // The size of the remaining data
    totalSize = localFile->size();

    loadSize = 4 * 1024; // The size of data sent each time

    QFileInfo info(filename);
    QDataStream out(&outBlock, QIODevice::WriteOnly);
    out << qint64 (0) << qint64 (0) << filename;

    totalSize += outBlock.size(); // The total size is the file size plus the size of the file name and other information
    byteToWrite += outBlock.size();

    out.device ()-> seek (0); // Go back to the beginning of the byte stream to write a qint64 in front, which is the total size and file name and other information size
    out << totalSize << qint64(outBlock.size());

    tcpClient->write(outBlock); // Send the read file to the socket

    progressDialog->setMaximum(totalSize);
    progressDialog->setValue(totalSize-byteToWrite);
    progressDialog->show();
}

void Widget::goOnSend(qint64 numBytes) // Start sending file content
{
    byteToWrite -= numBytes; // Remaining data size
    outBlock = localFile->read(qMin(byteToWrite, loadSize));
    tcpClient->write(outBlock);

    progressDialog->setMaximum(totalSize);
    progressDialog->setValue(totalSize-byteToWrite);

    if (byteToWrite == 0) { // Send completed
        infoLabel->setText(tr("File sending completed!"));
        progressDialog->hide();
    }
}

void Widget::openFile() // Open the file and get the file name (including path)
{
    progressDialog->setValue(0); // Not sent for the first time

    loadSize = 0;
    byteToWrite = 0;
    totalSize = 0;
    outBlock.clear();

    filename = QFileDialog::getOpenFileName(this);
    localFile = new QFile(filename);
    localFile->open(QFile::ReadOnly);

    infoLabel->setText(tr("file %1 is opened").arg(filename));
}

void Widget::sendData()
{
    openFile();
    if (sendTimes == 0) { // Only the first time it is sent, it happens when the connection generates the signal connect
        tcpClient->connectToHost(QHostAddress("127.0.0.1"), 8000);
        sendTimes = 1;
    } else
        send(); // When sending for the first time, connectToHost initiates the connect signal to call send, and you need to call send after the second time

    infoLabel->setText(tr("Sending file %1").arg(filename));
}
