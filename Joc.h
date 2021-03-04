#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include <QBrush>
#include <QFont>
#include <vector>
#include <string>

using namespace std;


class Final:public QWidget{

public:
    QVBoxLayout* finalLayout= new QVBoxLayout{};
    QTableWidget* finalTable= new QTableWidget;
    QLabel* msg= new QLabel;
    QPalette p;

    Final(int n, int m, QVector<QPoint> nave_calculator){
        this->setWindowTitle("Jocul a luat sfarsit");
        setLayout(finalLayout);


        finalTable->setRowCount(n);
        finalTable->setColumnCount(m);

        for(int i=0;i<=n;i++)
            for(int j=0;j<=m;j++)
                finalTable->setItem(i,j, new QTableWidgetItem(" "));


        p= finalTable->palette();
        p.setColor(QPalette::Base,QColor(125,186,255));
        finalTable->setPalette(p);

        for(auto const& pct:nave_calculator)
            finalTable->item(pct.x(),pct.y())->setBackground(QColor(219,13,27));


        finalTable->resizeRowsToContents();
        finalTable->resizeColumnsToContents();


        msg->setText( "Calculatorul a castigat. Aceasta a fost tabla calculatorului");
        finalLayout->addWidget(msg);
        finalLayout->addWidget(finalTable);


    }

    ~Final(){
        delete finalTable;
        delete finalLayout;
        delete msg;
    };

};



class Joc: public QWidget{
public:
    Joc(int n, int m, QVector<QPoint> nave_input_utilizator, QVector<QPoint> nave_input_calculator){
        scor_calc=0;
        scor_utilizator=0;
        nrlinii=n;
        nrcoloane=m;
        nave_utilizator=nave_input_utilizator;
        nave_calculator=nave_input_calculator;
        initJoc();
        initConnect();
    };

    ~Joc(){
        delete tbl_utilizator;
        delete tbl_calculator;
        delete label;
        delete label_2;
        delete trdLay;
        delete fthLay;
    }
private:
    int scor_calc;
    int scor_utilizator;
    int nrlinii;
    int nrcoloane;
    QVector<QPoint> calc_move;
    QPalette p;
    QTableWidget* tbl_utilizator= new QTableWidget;
    QTableWidget* tbl_calculator= new QTableWidget;
    QLabel* label= new QLabel{" Jocul inca nu a inceput.. " };
    QLabel* label_2= new QLabel{ };
    QVector<QPoint> nave_utilizator;
    QVector<QPoint> nave_calculator;
    QHBoxLayout* trdLay= new QHBoxLayout{};
    QVBoxLayout* fthLay= new QVBoxLayout{};

    void initJoc(){

        this->setLayout(trdLay);
        tbl_utilizator->setRowCount(nrlinii);
        tbl_utilizator->setColumnCount(nrcoloane);
        tbl_calculator->setRowCount(nrlinii);
        tbl_calculator->setColumnCount(nrcoloane);

        for(int i=0;i<=nrlinii;i++)
            for(int j=0;j<=nrcoloane;j++){
                tbl_utilizator->setItem(i,j, new QTableWidgetItem(" "));
                tbl_calculator->setItem(i,j, new QTableWidgetItem("  "));
}

        p= tbl_utilizator->palette();
        p.setColor(QPalette::Base,QColor(125,186,255));
        tbl_utilizator->setPalette(p);
        p= tbl_calculator->palette();
        p.setColor(QPalette::Base,QColor(125,186,255));
        tbl_calculator->setPalette(p);
        tbl_utilizator->resizeRowsToContents();
        tbl_utilizator->resizeColumnsToContents();
        tbl_calculator->resizeRowsToContents();
        tbl_calculator->resizeColumnsToContents();


        trdLay->addWidget(tbl_utilizator);
        fthLay->addWidget(label);
        fthLay->addWidget(label_2);
        trdLay->addLayout(fthLay);
        trdLay->addWidget(tbl_calculator);
        trdLay->addSpacing(30);

        this->setMaximumSize(1800,2000);
        this->setMinimumSize(800,300);


    };

    bool calc_do_move(){
        QPoint p;
        int x,y;
        if(calc_move.isEmpty()){
            x= rand() % nrlinii;
            y= rand() % nrcoloane;
            p.setX(x);
            p.setY(y);
        }else{
             p = calc_move.back();
             calc_move.pop_back();
        }

        while(tbl_utilizator->item(p.x(),p.y())->background().color()==QColor(219,13,27) || tbl_utilizator->item(p.x(),p.y())->background().color()==Qt::white )
        {
            if(calc_move.isEmpty()){
                x= rand() % nrlinii;
                y= rand() % nrcoloane;
                p.setX(x);
                p.setY(y);
            }else{
                p = calc_move.back();
                calc_move.pop_back();
            }
        }
        if(nave_utilizator.contains(p)==true){
            tbl_utilizator->item(p.x(),p.y())->setBackground(QColor(219,13,27));
            scor_calc+=1;
            label_2->setText(" Calculator: ATINS ");
            if(p.x()+1<nrlinii)
                calc_move.push_back(QPoint(p.x()+1,p.y()));
            if(p.y()+1<nrcoloane)
                calc_move.push_back(QPoint(p.x(),p.y()+1));
            if(p.x()-1>=0)
                calc_move.push_back(QPoint(p.x()-1,p.y()));
            if(p.y()-1>=0)
                calc_move.push_back(QPoint(p.x(),p.y()-1));
        }else{
            tbl_utilizator->item(p.x(),p.y())->setBackground(Qt::white);
            label_2->setText(" Calculator: AER ");
        }

        if (scor_utilizator== nave_calculator.size() && scor_calc==nave_utilizator.size() ){
            QMessageBox::about(this,"Jocul a luat sfarsit", "Jocul s-a sfarsit printr-o egalitate");
            return true;
        }
        else if(scor_calc==nave_utilizator.size())
        {
            Final* f = new Final(nrlinii, nrcoloane, nave_calculator);
            f->show();
            return true;
        }

        return false;
    };

    void initConnect(){
        QObject::connect(tbl_calculator,&QTableWidget::cellClicked,[&](){

            int crtRow= tbl_calculator->currentRow();
            int crtColumn= tbl_calculator->currentColumn();

            QPoint p;
            p.setX(crtRow);

            p.setY(crtColumn);
            if(tbl_calculator->item(p.x(),p.y())->background().color()==QColor(219,13,27) || tbl_calculator->item(p.x(),p.y())->background().color()==Qt::white)
                QMessageBox::warning(this,"Imposibil","Deja ati apasat pe butonul asta");
            else{
                if(nave_calculator.contains(p)==true)
                {
                tbl_calculator->item(crtRow,crtColumn)->setBackground(QColor(219,13,27));
                scor_utilizator+=1;

                label->setText(" Utilizator: ATINS ");

            }else{
                label->setText(" Utillizator: AER ");
                tbl_calculator->item(crtRow,crtColumn)->setBackground(Qt::white);
            }


            bool gata=calc_do_move();

            if(gata==true)
                close();
            else
                if(scor_utilizator==nave_calculator.size())
                {
                    QMessageBox::about(this,"Jocul a luat sfarsit", "Utilizatorul a castigat");
                    close();
                }

            }

        });

    }

};
