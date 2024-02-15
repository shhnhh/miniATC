#include "statuswidget.h"

StatusWidget::StatusWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Окно состояния");
    setFixedSize(800, 500);

    validator = new QRegularExpressionValidator(QRegularExpression("\\d+"));

    vbox = new QVBoxLayout;
    hbox = new QHBoxLayout;

    grid = new QGridLayout;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 5; j++) {
            abonents.push_back(new QPushButton("Абонент №" + QString::number(i * 5 + j + 1), this));
            grid->addWidget(abonents.last(), i, j);

            connect(abonents.last(), &QPushButton::pressed, this, &StatusWidget::getAbonentCaller);
        }
    vbox->addLayout(grid);

    vbox_left = new QVBoxLayout;
    vbox_right = new QVBoxLayout;

    name_left = new QLabel("Выберите абонента", this);
    name_left->setMinimumWidth(this->width() / 2);
    name_left->setAlignment(Qt::AlignCenter);
    vbox_left->addWidget(name_left);

    name_right = new QLabel("Пусто", this);
    name_right->setMinimumWidth(this->width() / 2);
    name_right->setAlignment(Qt::AlignCenter);
    vbox_right->addWidget(name_right);

    output_left = new QLabel(this);
    output_left->setAlignment(Qt::AlignCenter);
    output_left->setHidden(true);
    vbox_left->addWidget(output_left);

    output_right = new QLabel(this);
    output_right->setAlignment(Qt::AlignCenter);
    output_right->setHidden(true);
    vbox_right->addWidget(output_right);

    hbox_number_left = new QHBoxLayout;
    text_left = new QLabel("Номер", this);
    hbox_number_left->addWidget(text_left);
    number_left = new QLineEdit(this);
    number_left->setValidator(validator);
    hbox_number_left->addWidget(number_left);
    btn_call = new QPushButton("Позвонить", this);
    connect(btn_call, &QPushButton::pressed, this, &StatusWidget::callRequest);
    hbox_number_left->addWidget(btn_call);
    vbox_left->addLayout(hbox_number_left);

    hbox_btns = new QHBoxLayout;
    btn_accept = new QPushButton("Принять", this);
    connect(btn_accept, &QPushButton::pressed, this, &StatusWidget::callAnswer);
    hbox_btns->addWidget(btn_accept);
    btn_reject = new QPushButton("Отклонить", this);
    connect(btn_reject, &QPushButton::pressed, this, &StatusWidget::callAnswer);
    hbox_btns->addWidget(btn_reject);
    vbox_right->addLayout(hbox_btns);

    msg_left = new QLabel(this);
    msg_left->setAlignment(Qt::AlignCenter);
    vbox_left->addWidget(msg_left);

    msg_right = new QLabel(this);
    msg_right->setAlignment(Qt::AlignCenter);
    vbox_right->addWidget(msg_right);

    hbox_form_left = new QHBoxLayout;
    text_input_left = new QLabel("Сообщение:", this);
    hbox_form_left->addWidget(text_input_left);
    input_left = new QLineEdit(this);
    hbox_form_left->addWidget(input_left);
    submit_left = new QPushButton("Отправить", this);
    connect(submit_left, &QPushButton::pressed, this, &StatusWidget::sendMsg);
    hbox_form_left->addWidget(submit_left);
    vbox_left->addLayout(hbox_form_left);

    hbox_form_right = new QHBoxLayout;
    text_input_right = new QLabel("Сообщение:", this);
    hbox_form_right->addWidget(text_input_right);
    input_right = new QLineEdit(this);
    hbox_form_right->addWidget(input_right);
    submit_right = new QPushButton("Отправить", this);
    connect(submit_right, &QPushButton::pressed, this, &StatusWidget::sendMsg);
    hbox_form_right->addWidget(submit_right);
    vbox_right->addLayout(hbox_form_right);

    btn_exit_left = new QPushButton("Завершить звонок", this);
    connect(btn_exit_left, &QPushButton::pressed, this, &StatusWidget::callBreak);
    vbox_left->addWidget(btn_exit_left);

    btn_exit_right = new QPushButton("Завершить звонок", this);
    connect(btn_exit_right, &QPushButton::pressed, this, &StatusWidget::callBreak);
    vbox_right->addWidget(btn_exit_right);

    output_left->setHidden(true);
    output_right->setHidden(true);
    text_left->setHidden(true);
    number_left->setHidden(true);
    btn_call->setHidden(true);
    btn_accept->setHidden(true);
    btn_reject->setHidden(true);
    msg_left->setHidden(true);
    msg_right->setHidden(true);
    text_input_left->setHidden(true);
    input_left->setHidden(true);
    submit_left->setHidden(true);
    text_input_right->setHidden(true);
    input_right->setHidden(true);
    submit_right->setHidden(true);
    btn_exit_left->setHidden(true);
    btn_exit_right->setHidden(true);

    hbox->addLayout(vbox_left);
    hbox->addLayout(vbox_right);
    vbox->addLayout(hbox);
    setLayout(vbox);
}

StatusWidget::~StatusWidget()
{
    for (int i = 0; i < abonents.size(); i++)
        delete abonents[i];
    delete name_left;
    delete name_right;
    delete text_left;
    delete number_left;
    delete validator;
    delete btn_call;
    delete output_left;
    delete output_right;
    delete btn_accept;
    delete btn_reject;
    delete msg_left;
    delete msg_right;
    delete text_input_left;
    delete text_input_right;
    delete input_left;
    delete input_right;
    delete submit_left;
    delete submit_right;
    delete btn_exit_left;
    delete btn_exit_right;
    delete hbox_form_left;
    delete hbox_form_right;
    delete hbox_btns;
    delete hbox_number_left;
    delete vbox_right;
    delete vbox_left;
    delete grid;
    delete hbox;
    delete vbox;
}

void StatusWidget::getAbonentCaller() {
    QString msg;
    QPushButton *btn = (QPushButton*)sender();
    msg << QString::number(CALLER_STATUS_REQUEST);
    msg << btn->text().split("№")[1];

    emit request(msg);
}

void StatusWidget::callRequest() {
    QString msg;
    msg << QString::number(CALL_REQUEST_REQUEST);
    msg << name_left->text().replace(":", "").split("№")[1];
    msg << number_left->text();

    emit request(msg);
}

void StatusWidget::callAnswer() {
    QString msg;
    QPushButton *btn = (QPushButton*)sender();
    msg << QString::number(CALL_ANSWER_REQUEST);
    msg << QString::number(btn->text() == "Принять");
    msg << name_left->text().replace(":", "").split("№")[1];
    msg << name_right->text().replace(":", "").split("№")[1];

    emit request(msg);
}

void StatusWidget::callBreak() {
    QString msg;
    msg << QString::number(CALL_BREAK_REQUEST);
    msg << name_left->text().replace(":", "").split("№")[1];
    msg << name_right->text().replace(":", "").split("№")[1];

    emit request(msg);
}

void StatusWidget::sendMsg() {
    QString msg;
    msg << QString::number(SEND_MSG_REQUEST);
    QPushButton *btn = (QPushButton*)sender();
    msg << name_left->text().replace(":", "").split("№")[1];
    msg << name_right->text().replace(":", "").split("№")[1];
    if (btn == submit_left) {
        msg << msg_left->text();
        msg << input_left->text();
    } else {
        msg << input_right->text();
        msg << msg_right->text();
    }

    emit request(msg);
}

void StatusWidget::answer(QString msg)
{
    for (int i = 0; i < abonents.size(); i++)
        abonents[i]->setDisabled(false);
    output_left->setHidden(true);
    output_right->setHidden(true);
    text_left->setHidden(true);
    number_left->setHidden(true);
    btn_call->setHidden(true);
    btn_accept->setHidden(true);
    btn_reject->setHidden(true);
    msg_left->setHidden(true);
    msg_right->setHidden(true);
    text_input_left->setHidden(true);
    input_left->setHidden(true);
    submit_left->setHidden(true);
    text_input_right->setHidden(true);
    input_right->setHidden(true);
    submit_right->setHidden(true);
    btn_exit_left->setHidden(true);
    btn_exit_right->setHidden(true);
    number_left->setText("");
    name_right->setText("Пусто");
    input_left->setText("");
    input_right->setText("");
    msg_left->setText("");
    msg_right->setText("");

    QStringList arr = msg.split(separator);
    int m = arr[0].toInt();
    if (m == CALLER_STATUS_ANSWER) {
        name_left->setText("Абонент №" + arr[1] + ":");
        output_left->setHidden(false);
        if (arr[2].toInt() == NOT_READY) {
            output_left->setText("У абонента нет номера!");
        } else if (arr[2].toInt() == READY) {
            output_left->setText("Наберите номер:");
            text_left->setHidden(false);
            number_left->setHidden(false);
            btn_call->setHidden(false);
            text_left->setText("Номер:");
        } else if (arr[2].toInt() == CALL) {
            name_right->setText("Абонент №" + arr[3] + ":");
            output_right->setHidden(false);
            output_left->setText("Идёт разговор.");
            output_right->setText("Идёт разговор.");
            msg_left->setHidden(false);
            text_input_left->setHidden(false);
            input_left->setHidden(false);
            submit_left->setHidden(false);
            msg_right->setHidden(false);
            text_input_right->setHidden(false);
            input_right->setHidden(false);
            submit_right->setHidden(false);
            btn_exit_left->setHidden(false);
            btn_exit_right->setHidden(false);
        }
    } else if (m == CALL_REQUEST_ANSWER) {
        output_left->setHidden(false);
        switch (arr[1].toInt()) {
            case NOT_READY:
                output_left->setText("Абонента с таким номером не существует!");
                break;
            case BUSY:
                output_left->setText("Все линии заняты.");
                break;
            case CALL:
                output_left->setText("Линия занята.");
                break;
            case SELF:
                output_left->setText("Это ваш номер.");
                break;
            case READY:
                output_left->setText("Ожидание ответа абонента...");
                break;
        }
        if (arr[1].toInt() == READY) {
            for (int i = 0; i < abonents.size(); i++)
                abonents[i]->setDisabled(true);
            name_right->setText("Абонент №" + arr[4] + ":");
            output_right->setHidden(false);
            output_right->setText("Вам звонит номер " + arr[2]);
            btn_accept->setHidden(false);
            btn_reject->setHidden(false);
        }
    } else if (m == CALL_ANSWER_ANSWER) {
        name_right->setText("Абонент №" + arr[3] + ":");
        output_left->setHidden(false);
        output_right->setHidden(false);
        if (arr[1].toInt() == 2) {
            output_left->setText("Все линии заняты.");
            output_right->setText("Все линии заняты.");
        } else if (arr[1].toInt() == 1) {
            output_left->setText("Идёт разговор.");
            output_right->setText("Идёт разговор.");
            msg_left->setHidden(false);
            text_input_left->setHidden(false);
            input_left->setHidden(false);
            submit_left->setHidden(false);
            msg_right->setHidden(false);
            text_input_right->setHidden(false);
            input_right->setHidden(false);
            submit_right->setHidden(false);
            btn_exit_left->setHidden(false);
            btn_exit_right->setHidden(false);
        } else {
            output_left->setText("Абонент отклонил вызов.");
            output_right->setText("Вы отклонили входящий вызов.");
        }
    } else if (m == CALL_BREAK_ANSWER) {
        output_left->setHidden(false);
        output_right->setHidden(false);
        output_left->setText("Звонок завершен.");
        output_right->setText("Звонок завершен.");
    } else if (m == SEND_MSG_ANSWER) {
        name_left->setText("Абонент №" + arr[1] + ":");
        name_right->setText("Абонент №" + arr[2] + ":");
        output_left->setHidden(false);
        output_right->setHidden(false);
        output_left->setText("Идёт разговор.");
        output_right->setText("Идёт разговор.");
        msg_left->setHidden(false);
        text_input_left->setHidden(false);
        input_left->setHidden(false);
        submit_left->setHidden(false);
        msg_right->setHidden(false);
        text_input_right->setHidden(false);
        input_right->setHidden(false);
        submit_right->setHidden(false);
        btn_exit_left->setHidden(false);
        btn_exit_right->setHidden(false);

        msg_left->setText(arr[3]);
        msg_right->setText(arr[4]);
    }
    this->update();
}
