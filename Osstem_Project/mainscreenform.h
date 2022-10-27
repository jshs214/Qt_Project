#ifndef MAINSCREENFORM_H
#define MAINSCREENFORM_H

#include <QWidget>

namespace Ui {
class MainScreenForm;
}

class MainScreenForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainScreenForm(QWidget *parent = nullptr);
    ~MainScreenForm();


private:
    Ui::MainScreenForm *ui;
};

#endif // MAINSCREENFORM_H
