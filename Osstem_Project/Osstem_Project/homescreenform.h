#ifndef HOMESCREENFORM_H
#define HOMESCREENFORM_H

#include <QWidget>

namespace Ui {
class HomeScreenForm;
}

class HomeScreenForm : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreenForm(QWidget *parent = nullptr);
    ~HomeScreenForm();

private:
    Ui::HomeScreenForm *ui;
};

#endif // HOMESCREENFORM_H
