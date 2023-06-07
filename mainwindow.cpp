#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QtMath>
#include <QString>
#include "poland.h"
#include <iostream>

const double PI = 3.14;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,600);
    button = new QPushButton(this);
    button->setGeometry(width()*0.855, height()*0.0125, width()*0.1375, height()*0.05);
    button->setText("build");
    connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    ui->lineEdit->setGeometry(width()*0.01, height()*0.0125, width()*0.835, height()*0.05);


}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    QPen pen;
    //pen.setColor(Qt::red);
    pen.setColor(0xff0000);
    pen.setWidth(15);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);


    painter.drawLine(0, 0, 100, 100);
    painter.end();
}*/

void MainWindow:: buttonClicked()
{

    QString s = ui->lineEdit->text();

        ui->label->setGeometry(width()*0.01, height()*0.075, width()*0.835, height()*0.9083);
        QPixmap pm(width(), height());
        QPainter painter;
        painter.begin(&pm);
        pm.fill(Qt::white);
        double xmin = -0.001;
        double xmax = 0.0010;
        double ymin = -0.0010;
        double ymax = 0.0010;
        int xgmin = 0;
        int xgmax = pm.width();
        int ygmin = 0;
        int ygmax = pm.height();
        double x, y;
        double xg, yg;
        /*if (error(s)) {
            exit(0);
        }*/

        double kx = (xgmax - xgmin)/(xmax-xmin);
        double ky = (ygmin - ygmax)/(ymax-ymin);
        double xo = xgmin - kx * xmin;
        double yo = ygmin - ky * ymax;
        x = xmin;
        double stepx = (xmax-xmin)/(xgmax - xgmin);
        /*for (int i = 0; i < pm.width(); i++){
            x = xmin;
            y = sin(x);

        }*/
        QPen pen;
        pen.setColor(0x120404);
        painter.setPen(pen);
        painter.drawLine(0, yo, pm.width(), yo);
        painter.drawLine(xo, 0, xo, pm.height());
        pen.setColor(0xad1515);
        painter.setPen(pen);
        QPainterPath qp;

        double ans = 0;
        QString temp_s = s;
        QString xx = "("+ QString::number(x)+")";
        s.replace("x", xx);
        //cout << s.toStdString() << ' ' << temp_s.toStdString();
        calculate(s.toStdString(), ans);
        y = ans;

         //printf("%f\n", ans);
        qp.moveTo(xo + kx*x, yo + ky*y);
        while(x <= xmax){
            x+=stepx;

            QString xx = "("+ QString::number(x)+")";
            s = temp_s;
            s.replace("x", xx);
            for (int i = 0; i < s.length(); i++){
                if (s[i] == 'e'){
                    s = "0.0000";
                }
            }
            cout << "s - " << s.toStdString() << endl;
            calculate(s.toStdString(), ans);

            y = ans;
            if (calculate(s.toStdString(), ans) == -1) continue;
            xg = xo + kx*x;
            yg = yo + ky*y;
            //printf("%f-x, %f-y, %f-ans, %s - s ", xg, yg, ans, s.toStdString());
            qp.lineTo(xg, yg);
            painter.drawPath(qp);

            }
    //painter.drawLine(1,2, 100, 200);
     painter.end();
    ui->label->setPixmap(pm);
}



