#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>

namespace Ui {
class widget;
}

class widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = nullptr);
    ~widget();
    void changeMoney(int m);
    void initsystem();
private slots:

    void on_pb_10_clicked();

    void on_pb_50_clicked();

    void on_pb_100_clicked();

    void on_pb_500_clicked();


    void on_pb_coffee_clicked();

    void on_pb_icetea_clicked();

    void on_pb_cocoa_clicked();

    void on_pb_return_clicked();

private:
    Ui::widget *ui;
    int money{0};
};

#endif // WIDGET_H
