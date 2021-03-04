#ifndef TABLESHOW_H
#define TABLESHOW_H

#include "Joc.h"
class TableShow: public QWidget{
public:
    TableShow(int n, int m, int userMaxVase,int userMaxYacht,int userMaxSub){

        nrlinii=n;
        nrcoloane=m;
        crtNrVase=0;
        crtNrYacht=0;
        crtNrSub=0;
        nrMaxVase=userMaxVase;
        nrMaxYacht=userMaxYacht;
        nrMaxSub= userMaxSub;
        initTable();
        initConnect();

    };

    ~TableShow(){
        delete tbl;
        delete btnExist;
        delete btnStart;
        delete scdLay;
    }

private:
    int crtNrVase;
    int crtNrYacht;
    int crtNrSub;
    int nrMaxVase;
    int nrMaxYacht;
    int nrMaxSub;
     int nrlinii;
     int nrcoloane;
     QVBoxLayout* scdLay= new QVBoxLayout{};
     QVector<QPoint> puncte;
     QVector<QPoint> calculator;
     QTableWidget* tbl= new QTableWidget;
     QPalette p;
     QPushButton* btnExist = new QPushButton{ "&Exit" };
     QPushButton* btnStart = new QPushButton{ "&Start Joc" };

    void populate(){

        int nrVase=0;
        int nrYacht=0;
        int nrSub=0;
        bool isPossible;
        int x,y,r;
        QPoint p;


        while(nrVase<nrMaxVase){

            x = rand() % nrlinii;
            y= rand() % nrcoloane;
            r= rand() % 2;
            p.setX(x);
            p.setY(y);
            if(calculator.contains(p)==false)
             {
                if(r==0)
                    isPossible=isPossibleHorizontally(x,y,5,false,calculator);
                else
                    isPossible=isPossibleVertically(x,y,5,false,calculator);

                if(isPossible==true)
                    nrVase++;
            }

        }

        while(nrYacht<nrMaxYacht){

            x = rand() % nrlinii;
            y= rand() % nrcoloane;
            r= rand() % 2;

            p.setX(x);
            p.setY(y);
            if(calculator.contains(p)==false)
            {
                if(r==0)
                    isPossible=isPossibleHorizontally(x,y,3,false,calculator);
                else
                    isPossible=isPossibleVertically(x,y,3,false,calculator);

                if(isPossible==true)
                    nrYacht++;

            }

        }
        while(nrSub<nrMaxSub){

            x = rand() % nrlinii;
            y= rand() % nrcoloane;
            r= rand() % 2;

            p.setX(x);
            p.setY(y);

            if(calculator.contains(p)==false)
            {
                if(r==0)
                    isPossible=isPossibleHorizontally(x,y,2,false,calculator);
                else
                    isPossible=isPossibleVertically(x,y,2,false,calculator);

                if(isPossible==true)
                    nrSub++;

            }

        }

    };



    void initTable(){
        setLayout(scdLay);
        tbl->setRowCount(nrlinii);
        tbl->setColumnCount(nrcoloane);

        for(int i=0;i<nrlinii;i++)
            for(int j=0;j<nrcoloane;j++)
                tbl->setItem(i,j, new QTableWidgetItem(" "));

        tbl->resizeRowsToContents();
        tbl->resizeColumnsToContents();

        p= tbl->palette();
        p.setColor(QPalette::Base,QColor(125,186,255));
        tbl->setPalette(p);
        scdLay->addWidget(tbl);
        scdLay->addWidget(btnExist);
        scdLay->addWidget(btnStart);
        scdLay->setSizeConstraint(QLayout::SizeConstraint());
        this->setMaximumSize(2000,1800);
        this->setMinimumSize(600,500);
    };

    bool isPossibleHorizontally(int row, int column,int nr_celule, bool culoare, QVector<QPoint> &puncteDejaOcupate){

        QPoint p;
        p.setX(row);
        p.setY(column);
        QVector<QPoint> intermediate;
        intermediate.push_back(p);
        int nr_patratele=1;

        int right_column=column + 1;

        while(right_column<nrcoloane){
            p.setY(right_column);
            if(puncteDejaOcupate.contains(p)==true)
                break;
            else{
                intermediate.push_back(p);
                nr_patratele++;
                if(nr_patratele== nr_celule)
                    break;
                right_column++;
            }
        }

        int left_column=column-1;

        while(nr_patratele<nr_celule && left_column>=0){
            p.setY(left_column);
           if(puncteDejaOcupate.contains(p)==true)
               break;
           else{
                intermediate.push_back(p);
                nr_patratele++;
                left_column--;
            }
        }

        if(intermediate.size()!=nr_celule){
            if(culoare==true)
                QMessageBox::critical(this,"Ati apasat gresit","Nu este loc pe tabla pentru aceasta piesa");
            return false;
        }else{
            for(auto const& pct: intermediate){
                puncteDejaOcupate.push_back(pct);
                if(culoare==true)
                    tbl->item(pct.x(),pct.y())->setBackground(QColor(219,13,27));

            }
            return true;
        }
    };

    bool isPossibleVertically(int row, int column,int nr_celule,bool culoare, QVector<QPoint> &puncteDejaOcupate){

        QPoint p;
        p.setX(row);
        p.setY(column);
        QVector<QPoint> intermediate;
        intermediate.push_back(p);
        int nr_patratele=1;

        int right_row=row+1;

        while(right_row<nrlinii && nr_patratele<nr_celule){
            p.setX(right_row);
            if(puncteDejaOcupate.contains(p)==true)
                break;
            else{
                intermediate.push_back(p);
                nr_patratele++;
                right_row++;
            }
        }

        int left_row=row-1;

        while(nr_patratele<nr_celule && left_row>=0){
            p.setX(left_row);
           if(puncteDejaOcupate.contains(p)==true)
               break;
           else{
                intermediate.push_back(p);
                nr_patratele++;
                left_row--;
            }
        }

        if(intermediate.size()!=nr_celule){
            if(culoare==true)
                QMessageBox::critical(this,"Ati apasat gresit","Nu este loc pe tabla pentru aceasta piesa");
            return false;
        }else{
            for(auto const& pct: intermediate){
                puncteDejaOcupate.push_back(pct);
                if(culoare==true)
                    tbl->item(pct.x(),pct.y())->setBackground(QColor(219,13,27));
            }
            return true;

        }
    };

    void initConnect(){

        QObject::connect(btnExist, &QPushButton::clicked , [&](){
            close();
        });

        QObject::connect(btnStart, &QPushButton::clicked , [&](){
            if(crtNrSub!= nrMaxSub || crtNrVase!= nrMaxVase || crtNrYacht!= nrMaxYacht){
                auto rec = QMessageBox::warning(this,"Avertisment","Nu ati introdus toate navele puse la dispozitie, sigur doriti sa continuati? Adversarul va folosi toate navele posibile",QMessageBox::Yes | QMessageBox::No );
                if( rec == QMessageBox::No)
                    return;
            }
            populate();

            Joc* joc= new Joc(nrlinii,nrcoloane,puncte,calculator);

            joc->show();

            close();
        });

        QObject::connect(tbl,&QTableWidget::cellClicked,[&](){

            QTableWidgetItem* item= tbl->currentItem();

            if(item->background().color()==QColor(219,13,27)){
                QMessageBox::critical(this,"Imposibil","Ati incercat sa puneti o nava pe o celula deja ocupata");
            }else{
                auto question = new QMessageBox;
                bool isPossible;
                question->setText("Ce fel de nava vrei sa pui? ");
                QAbstractButton* vas_de_razboi= question->addButton(tr("Vas de razboi"),QMessageBox::YesRole);

                QAbstractButton* yacht= question->addButton(tr("Yacht"),QMessageBox::NoRole);

                QAbstractButton* submarin= question->addButton(tr("Submarin"),QMessageBox::RejectRole);

                question->setStandardButtons(QMessageBox::Cancel);

                question->exec();
                auto optiune = new QMessageBox;

                QAbstractButton* orizontal= optiune->addButton(tr("Orizontal"),QMessageBox::YesRole);
                QAbstractButton* vertical= optiune->addButton(tr("Vertical"),QMessageBox::NoRole);

                if(question->clickedButton()==vas_de_razboi){
                    if(crtNrVase+1>nrMaxVase)
                        QMessageBox::critical(this,"Imposibil","Ati ajuns la nr maxim de vase de razboi permise");
                    else{
                    optiune->setText("Vasul va fi plasat orizontal sau vertical? ");
                    optiune->exec();
                    if(optiune->clickedButton()==orizontal){
                        isPossible=isPossibleHorizontally(tbl->currentRow(),tbl->currentColumn(),5,true,puncte);
                    }else if(optiune->clickedButton()==vertical){
                        isPossible=isPossibleVertically(tbl->currentRow(),tbl->currentColumn(),5,true,puncte);

                    }
                    if(isPossible==true)
                        crtNrVase+=1;
                    }
                }else if(question->clickedButton()==yacht){
                    if(crtNrYacht+1>nrMaxYacht)
                        QMessageBox::critical(this,"Imposibil","Ati ajuns la nr maxim de yacht-uri permise");
                    else{
                    optiune->setText("Yacht-ul va fi plasat orizontal sau vertical? ");
                    optiune->exec();
                    if(optiune->clickedButton()==orizontal){
                        isPossible=isPossibleHorizontally(tbl->currentRow(),tbl->currentColumn(),3,true,puncte);

                    }else if(optiune->clickedButton()==vertical){
                        isPossible=isPossibleVertically(tbl->currentRow(),tbl->currentColumn(),3,true,puncte);

                    }
                    if(isPossible==true)
                        crtNrYacht+=1;
                    }
                }else if(question->clickedButton()==submarin){
                    if(crtNrSub+1>nrMaxSub)
                        QMessageBox::critical(this,"Imposibil","Ati ajuns la nr maxim de submarine permise");
                    else{
                    optiune->setText("Submarinul va fi plasat orizontal sau vertical? ");
                    optiune->exec();
                    if(optiune->clickedButton()==orizontal){
                        isPossible=isPossibleHorizontally(tbl->currentRow(),tbl->currentColumn(),2,true,puncte);
                    }else if(optiune->clickedButton()==vertical){
                        isPossible=isPossibleVertically(tbl->currentRow(),tbl->currentColumn(),2,true,puncte);

                    }
                    if(isPossible==true)
                        crtNrSub+=1;
                    }
                }

                vas_de_razboi->deleteLater();
                yacht->deleteLater();
                submarin->deleteLater();
                orizontal->deleteLater();
                vertical->deleteLater();
                question->deleteLater();
            }


        });
    };
};




#endif // TABLESHOW_H
