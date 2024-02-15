#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLayout>
#include <QVector>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "../common/common.h"
#include "../common/communicator.h"
#include <QValidator>
#include <QRegularExpression>
#include <QListView>
#include <QStringListModel>

class StatusWidget : public QWidget
{
    Q_OBJECT

    QVBoxLayout *vbox;
    QHBoxLayout *hbox;
    QGridLayout *grid;
    QVector <QPushButton*> abonents;
    QVBoxLayout *vbox_left;
    QVBoxLayout *vbox_right;
    QLabel *name_left;
    QLabel *name_right;
    QLabel *text_left;
    QLineEdit *number_left;
    QValidator *validator;
    QPushButton *btn_call;
    QHBoxLayout *hbox_number_left;
    QLabel *output_left;
    QLabel *output_right;
    QHBoxLayout *hbox_btns;
    QPushButton *btn_accept;
    QPushButton *btn_reject;
    QLabel *msg_left;
    QLabel *msg_right;
    QLabel *text_input_left;
    QLabel *text_input_right;
    QLineEdit *input_left;
    QLineEdit *input_right;
    QPushButton *submit_left;
    QPushButton *submit_right;
    QPushButton *btn_exit_left;
    QPushButton *btn_exit_right;
    QHBoxLayout *hbox_form_left;
    QHBoxLayout *hbox_form_right;



public:
    StatusWidget(QWidget *parent = nullptr);
    ~StatusWidget();

public slots:
    void getAbonentCaller();
    void callRequest();
    void callAnswer();
    void callBreak();
    void sendMsg();
    void answer(QString);

signals:
    void request(QString);
};

#endif // STATUSWIDGET_H
