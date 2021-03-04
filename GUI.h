#ifndef GUI_H
#define GUI_H

#include "TableShow.h"

class GUI: public QWidget{

public:
    GUI(){
        initGUI();
        initConnect();
    };
    ~GUI(){
        delete label;
        delete btnExist;
        delete btnTabla;
        delete validator;
        delete validator_2;
        delete txtLinii;
        delete txtColoane;
        delete txtVas;
        delete txtYacht;
        delete txtSub;
        delete lyBtns;
        delete lyMain;

    };
private:
    QLabel* label= new QLabel;
    QPushButton* btnExist = new QPushButton{ "&Iesire" };
    QPushButton* btnTabla= new QPushButton{" &Incepe joc nou "};
    QIntValidator * validator= new QIntValidator(1,100,this);
    QIntValidator * validator_2= new QIntValidator(1,10,this);
    QLineEdit * txtLinii= new QLineEdit(this);
    QLineEdit * txtColoane= new QLineEdit(this);
    QLineEdit * txtVas= new QLineEdit(this);
    QLineEdit * txtYacht= new QLineEdit(this);
    QLineEdit * txtSub= new QLineEdit(this);
    QHBoxLayout* lyBtns= new QHBoxLayout{};
    QHBoxLayout* lyMain= new QHBoxLayout{};



    void initConnect(){
        QObject::connect(btnExist, &QPushButton::clicked , [&](){
            close();
        });

        QObject::connect(btnTabla,&QPushButton::clicked,[&](){

            if(txtLinii->text()=="" || txtColoane->text()=="")
                QMessageBox::critical(this,"Eroare","Nu ati introdus cel putin una din masuratori pentru tabela de joc, jocul nu poate incepe");
            else{
                if(txtVas->text()=="" && txtYacht->text()=="" && txtSub->text()=="")
                    QMessageBox::critical(this,"Eroare","Nu ati introdus un numar pentru oricare tip de nava, jocul nu poate incepe pana cand macar una are un nr de nave");
                else{

                    int nrlinii = txtLinii->text().toInt();
                    int nrcol = txtColoane->text().toInt();
                    int nrvas = txtVas->text().toInt();
                    int nryacht = txtYacht->text().toInt();
                    int nrsub = txtSub->text().toInt();
                    auto StartIntermediate= new TableShow(nrlinii,nrcol,nrvas,nryacht,nrsub);
                    StartIntermediate->show();
                    close();

                }
            }
        });

    }

    void initGUI(){



        setLayout(lyMain);
        auto stgLy= new QVBoxLayout{};

        QPixmap pix("C:\\Users\\Larisa\\Downloads\\BATTLESHIP.jpg");
        label->setPixmap(pix.scaled(1000,1000,Qt::KeepAspectRatio));
        lyMain->addWidget(label);
        auto formLy= new QFormLayout;
        formLy->addRow("Nr de linii", txtLinii );
        formLy->addRow("Nr de coloane", txtColoane );
        formLy->addRow("Nr maxim de vase de razboi", txtVas );
        formLy->addRow("Nr maxim de yacht-uri", txtYacht );
        formLy->addRow("Nr maxim de submarine", txtSub );
        txtLinii->setValidator(validator);
        txtColoane->setValidator(validator);
        txtVas->setValidator(validator_2);
        txtYacht->setValidator(validator_2);
        txtSub->setValidator(validator_2);
        stgLy->addLayout(formLy);
        stgLy->addWidget(new QLabel(" Proiect realizat de Coroama Larisa-Gabriela "));

        lyBtns->addWidget(btnTabla);
        lyBtns->addWidget(btnExist);

        stgLy->addLayout(lyBtns);
        lyMain->addLayout(stgLy);
        lyMain->setSpacing(20);



    }

};

#endif // GUI_H
