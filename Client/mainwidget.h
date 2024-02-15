#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include "controlwidget.h"
#include "statuswidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

    QVBoxLayout *vbox;
    QPushButton *btn_control;
    QPushButton *btn_status;

public:
    ControlWidget *control_widget;
    StatusWidget *status_widget;

    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

public slots:
    void OpenControlWidget();
    void OpenStatusWidget();
};

#endif // MAINWIDGET_H
