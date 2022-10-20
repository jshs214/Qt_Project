#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ClientManagerForm;
class ProductManagerForm;
class OrderManagerForm;
class ChatServerForm;
class Chatting_Client;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionClient_triggered();
    void on_actionproduct_triggered();
    void on_actionOrder_triggered();


    void on_actionChatting_triggered();

    void on_actionChat_triggered();

private:
    bool flag = false;

    Ui::MainWindow *ui;
    ClientManagerForm *clientForm;
    ProductManagerForm *productForm;
    OrderManagerForm *orderForm;
    ChatServerForm *chatForm;
    Chatting_Client *chatClientForm;

signals:
    void clientupdate();

};
#endif // MAINWINDOW_H
