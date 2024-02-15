#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Мини ATC");
    setFixedSize(220, 100);

    control_widget = new ControlWidget;

    status_widget = new StatusWidget;

    vbox = new QVBoxLayout;

    btn_control = new QPushButton("Окно управления", this);
    btn_status = new QPushButton("Окно отображения", this);

    connect(btn_control, &QPushButton::pressed, this, &MainWidget::OpenControlWidget);
    connect(btn_status, &QPushButton::pressed, this, &MainWidget::OpenStatusWidget);

    vbox->addWidget(btn_control);
    vbox->addWidget(btn_status);

    setLayout(vbox);
}

MainWidget::~MainWidget()
{
    delete control_widget;
    delete status_widget;
    delete btn_control;
    delete btn_status;
    delete vbox;
}

void MainWidget::OpenControlWidget() {
    control_widget->show();
}

void MainWidget::OpenStatusWidget() {
    status_widget->show();
}
