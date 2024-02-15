#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QVector>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include "../common/common.h"
#include "../common/communicator.h"
#include <QValidator>
#include <QRegularExpression>

class ControlWidget : public QWidget
{
    Q_OBJECT

    QVBoxLayout *vbox;
    QHBoxLayout *hbox_abonent;
    QVector <QPushButton*> abonents;
    QGridLayout *grid;
    QLineEdit *number;
    QLabel *name, *status;
    QLabel *output_abonents;
    QPushButton *save;
    QValidator *validator;
    QVector <QPushButton*> lines;
    QHBoxLayout *hbox_lines;
    QLabel *output_lines;


public:
    ControlWidget(QWidget *parent = nullptr);
    ~ControlWidget();

public slots:
    void getAbonent();
    void setAbonent();
    void getLine();
    void answer(QString);

signals:
    void request(QString);
};

#endif // CONTROLWIDGET_H
