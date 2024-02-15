#include "controlwidget.h"

ControlWidget::ControlWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Окно управления");
    setFixedSize(600, 300);

    QRegularExpression rx("\\d+");
    validator = new QRegularExpressionValidator(rx);

    vbox = new QVBoxLayout;

    abonents.clear();
    grid = new QGridLayout;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 5; j++) {
            abonents.push_back(new QPushButton("Абонент №" + QString::number(i * 5 + j + 1), this));
            grid->addWidget(abonents.last(), i, j);

            connect(abonents.last(), &QPushButton::pressed, this, &ControlWidget::getAbonent);
        }
    vbox->addLayout(grid);

    hbox_abonent = new QHBoxLayout;
    name = new QLabel("Абонент:", this);
    hbox_abonent->addWidget(name);
    number = new QLineEdit(this);
    number->setValidator(validator);
    hbox_abonent->addWidget(number);
    status = new QLabel("не готов", this);
    hbox_abonent->addWidget(status);
    save = new QPushButton("сохранить", this);
    save->setDisabled(true);

    connect(save, &QPushButton::pressed, this, &ControlWidget::setAbonent);

    hbox_abonent->addWidget(save);

    vbox->addLayout(hbox_abonent);

    output_abonents = new QLabel("Выберите абонента", this);
    output_abonents->setAlignment(Qt::AlignCenter);
    vbox->addWidget(output_abonents);

    hbox_lines = new QHBoxLayout;
    for (int i = 0; i < 4; i++) {
        lines.push_back(new QPushButton("Линия №" + QString::number(i + 1)));
        hbox_lines->addWidget(lines.last());

        connect(lines.last(), &QPushButton::pressed, this, &ControlWidget::getLine);
    }

    vbox->addLayout(hbox_lines);

    output_lines = new QLabel(this);
    output_lines->setAlignment(Qt::AlignCenter);
    vbox->addWidget(output_lines);

    setLayout(vbox);
}

ControlWidget::~ControlWidget()
{
    for (int i = 0; i < abonents.size(); i++)
        delete abonents[i];
    delete grid;
    delete vbox;
    delete number;
    delete name;
    delete status;
    delete output_abonents;
    delete save;
    delete validator;
    for (int i = 0; i < lines.size(); i++) {
        delete lines[i];
    }
    delete output_lines;
}

void ControlWidget::getAbonent() {
    QString msg;
    QPushButton *btn = (QPushButton*)sender();
    msg << QString::number(ABONENT_INFO_REQUEST);
    msg << btn->text().split("№")[1];

    emit request(msg);
}

void ControlWidget::setAbonent() {
    QString msg;
    msg << QString::number(SET_NUMBER_REQUEST);
    msg << name->text().replace(":", "").split("№")[1];
    msg << number->text();

    emit request(msg);
}

void ControlWidget::getLine() {
    QString msg;
    QPushButton *btn = (QPushButton*)sender();
    msg << QString::number(LINE_INFO_REQUEST);
    msg << btn->text().split("№")[1];

    emit request(msg);
}

void ControlWidget::answer(QString msg)
{
    QStringList arr = msg.split(separator);
    int m = arr[0].toInt();
    if (m == ABONENT_INFO_ANSWER) {
        name->setText("Абонент №" + arr[1] + ":");
        number->setText(arr[2]);
        status->setText(getModeName(arr[3].toInt()));
        if (arr[3].toInt() == CALL)
            save->setDisabled(true);
        else
            save->setDisabled(false);
        output_abonents->setText("");
    } else if (m == SET_NUMBER_ANSWER) {
        if (arr[1].toInt() == 2)
            output_abonents->setText("Абонент с таким номером уже есть!");
        else if (arr[1].toInt() == 0)
            output_abonents->setText("Номер должен состоять из 11 цифр!");
        else
            output_abonents->setText("Сохранено");
        status->setText(getModeName(arr[2].toInt()));
    } else if (m == LINE_INFO_ANSWER) {
        output_lines->setText(arr[1] + " " + arr[2] + " - " + arr[3]);
    }
}
