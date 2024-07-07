#include "ok.h"
#include "ui_ok.h"

ok::ok(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ok)
{
    ui->setupUi(this);
}

ok::~ok()
{
    delete ui;
}

void ok::on_pushButton_4_clicked()
{
    // تایید ایمیل و فرستادن ایمیل برای کاربر
}


void ok::on_pushButton_2_clicked()//دریافت کدی که به ایمیل ارسال شده و صحت سنجی ان و اگر درست بود در قسمت شماره تلفن 1 بنویسد
{
    /*if "3" == ui->lineEdit->text(){
            //در کلاس و فایل برای شماره 3 بویسد
        }else{
        //پیغام خطا بدهد
    }*/
}



