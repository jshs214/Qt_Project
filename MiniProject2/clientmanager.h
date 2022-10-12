#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QWidget>

namespace Ui {
class ClientManager;
}

class ClientManager : public QWidget
{
    Q_OBJECT

public:
    explicit ClientManager(QWidget *parent = nullptr);
    ~ClientManager();

private:
    Ui::ClientManager *ui;
};

#endif // CLIENTMANAGER_H
