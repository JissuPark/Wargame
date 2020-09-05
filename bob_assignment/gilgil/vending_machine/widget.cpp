#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QtWidgets>
widget::widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::widget)
{
    //default setting
    ui->setupUi(this);
    ui->pb_coffee->setEnabled(false);
    ui->pb_icetea->setEnabled(false);
    ui->pb_cocoa->setEnabled(false);
    ui->pb_return->setEnabled(false);
}

widget::~widget()
{
    delete ui;
}

void widget::changeMoney(int m){

    /*int to string
     * QString::number(int n)
     */

    /*string to int
     * QString s;
     * s.toInt();
     */

    money+=m;
    ui->lcdNumber->display(QString::number(money));

    //setenabled by changed money
    if(money>0)
        ui->pb_return->setEnabled(true);
    else
        ui->pb_return->setEnabled(false);
    if(money<100)
        ui->pb_coffee->setEnabled(false);
    else
        ui->pb_coffee->setEnabled(true);
    if(money<200)
        ui->pb_icetea->setEnabled(false);
    else
        ui->pb_icetea->setEnabled(true);
    if(money<300)
        ui->pb_cocoa->setEnabled(false);
    else
        ui->pb_cocoa->setEnabled(true);
}

/*initialize*/
void widget::initsystem(){
    money = 0;
    ui->lcdNumber->display(QString::number(money));
    ui->pb_coffee->setEnabled(false);
    ui->pb_icetea->setEnabled(false);
    ui->pb_cocoa->setEnabled(false);
    ui->pb_return->setEnabled(false);
}
/*coin click event*/
void widget::on_pb_10_clicked()
{
    changeMoney(10);
}

void widget::on_pb_50_clicked()
{
    changeMoney(50);
}

void widget::on_pb_100_clicked()
{
    changeMoney(100);
}

void widget::on_pb_500_clicked()
{
    changeMoney(500);
}


/*menus click event*/
void widget::on_pb_coffee_clicked()
{
    changeMoney(-100);
}

void widget::on_pb_icetea_clicked()
{
    changeMoney(-200);
}

void widget::on_pb_cocoa_clicked()
{
    changeMoney(-300);
}

//calculate changes function
void widget::on_pb_return_clicked()
{
    //define variables
    QMessageBox msg;
    QString retmsg = "";
    int r10=0, r50=0, r100=0, r500=0;

    //add msg for total money
    retmsg += "total changes <"+QString::number(money)+"won>\n";

    //calculate counts by each coins
    while(money!=0){
        qDebug()<<"loop"+QString::number(money);
        if(money>=500){
            r500 += (money/500);
            money = (money%500);
        }
        if(money>=100){
            r100 += (money/100);
            money = (money%100);
        }
        if(money>=50){
            r50 += (money/50);
            money = (money%50);
        }
        if(money>=10){
            r10 += (money/10);
            money = (money%10);
        }
    }

    //add msg for each coins
    retmsg += "10won: "+QString::number(r10)+"\n50won: "+QString::number(r50)+"\n100won: "+QString::number(r100)+"\n500won: "+QString::number(r500);

    //show msgbox
    msg.information(nullptr,"return changes",retmsg);

    //init system cause it's possible to click menu atfer msgbox(money=0)
    initsystem();
}
