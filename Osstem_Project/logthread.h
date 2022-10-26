#ifndef LOGTHREAD_H
#define LOGTHREAD_H

#include <QThread>
#include <QList>

class QTreeWidgetItem;

class LogThread : public QThread
{
    Q_OBJECT
public:
    explicit LogThread(QObject *parent = nullptr);

private:
    void run();

    QList<QTreeWidgetItem*> itemList;   /* 로그의 데이터 기록 */
    QString filename;

signals:
    void send(int data);

public slots:
    void appendData(QTreeWidgetItem*);
    void saveData();
};

#endif // LOGTHREAD_H
