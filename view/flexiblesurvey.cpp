#include "view/flexiblesurvey.h"
#include "ui_flexiblesurvey.h"

flexiblesurvey::flexiblesurvey(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::flexiblesurvey)
{
    ui->setupUi(this);
/*
    ReadCsv("Data.csv");
    ExtractHeaders();
    ExtractNumbers();
    BuildMathCombo();
    BuildList();

*/
    connect(ui->CalculateButton,SIGNAL(clicked()),this,SLOT(NewCalculation()));


}

flexiblesurvey::~flexiblesurvey()
{
    delete ui;
}


void flexiblesurvey::NewCalculation(){

    ui->ShowBox->appendPlainText("");

    double display;
    bool found=0;
    int q_index=0;

    foreach(QListWidgetItem* item, ui->QuestionList->selectedItems()){
        q_index=0;
        found=0;
        while (!found){
            if (item->text()==QString::fromStdString(fb_headers[q_index])){
                found=1;
            }
            else
                ++q_index;


            if (q_index>=fb_headers.size())
            {
                cout << "ERROR: Something went wrong selecting the items" << endl;
                ui->ShowBox->appendPlainText("ERROR: something went wrong selecting the items");
                break;
            }

        }

        switch (ui->MathsCombo->currentIndex()){
        case 0:
            display=MeanValue(q_index);
            ui->ShowBox->appendPlainText(item->text());
            ui->ShowBox->appendPlainText(QString::number(qRound(display*100.0)/100.0));
            break;
        case 1:
            display=ShareOfNonZeros(q_index);
            ui->ShowBox->appendPlainText(item->text());
            ui->ShowBox->appendPlainText(QString::number(qRound(display*10000.0)/100.0)+" %");
            break;
        }

    }

}

void flexiblesurvey::ReadCsv(string filename){

    cout << "START READING CSV..." << endl;

    filename ="a";
    ifstream file;
    file.open("/Users/Sebastian/Documents/CPP/AFZ/Feedbacker/datanew.csv");

   if(!file.is_open()){
   cout << "file could not be opened! error"<< endl;
   assert(0);
   }

    string value;


    vector <string> dataset;

    string delimiter = "\r";
    string token1;
    string token2;

    while (getline(file,value,';'))
    {
        // check if row delimiter is part of value. if yes, eliminate it and jump to next line.


        if (value.find(delimiter) != std::string::npos) {
        token1 = value.substr(0, value.find(delimiter));
        token2 = value.substr(value.find(delimiter)+delimiter.size(),value.size());

        token1.push_back('"');


        dataset.push_back(token1);
        datamatrix.push_back(dataset);
        dataset.clear();
        dataset.push_back(token2);
        }
        else dataset.push_back(value);

    }
    if (datamatrix.empty()){
        cout << "ERROR. READING CSV FAILED. STOP." << endl << "Check .csv dialect. "
                                                              "line breakers could be different.  maybe: \r\n " << endl;
    }
    cout << "...CSV SUCESSFULLY READ!" << endl;


    }

void flexiblesurvey::ExtractHeaders(){
    // extracts headers from datamatrix and puts them into one single array



    for (int i=0; i<datamatrix[0].size();++i){

        if(datamatrix[0][i]=="")
        {

            fb_headers.push_back(datamatrix[1][i]);

        }
        else{
            if (datamatrix[1][i]=="locker")   {    //workaround for "locker" problem
                fb_headers.push_back(datamatrix[1][i]);
            }
            else{
            fb_headers.push_back(datamatrix[0][i]);

            }
        }
    }
    cout << "HEADERS SUCCESSFULLY BUILT" << endl;


}

void flexiblesurvey::BuildList(){
    QString str;

    ui->QuestionList->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QStringList Questions;
     for(int i=0; i<fb_headers.size()-1;++i)
         Questions.append(str.fromStdString(fb_headers[i]));

     foreach(const QString &item, Questions){
         ui->QuestionList->addItem(new QListWidgetItem(item));
     }

     cout << "LIST SUCCESSFULLY BUILT" << endl;
}

void flexiblesurvey::ExtractNumbers(){
// extracts number-strings from datamatrix and converts them to doubles. returns a new matrix.

    fb_values.resize(datamatrix.size()-2,vector <double>(datamatrix[2].size()));

    // go through datasets
    for(int i=0; i<fb_values.size();++i){

        //go through questions
        for (int j=0; j<fb_values[2].size();++j){
            fb_values[i][j]=atoi(datamatrix[i+2][j].c_str());
           // cout << atoi(datamatrix[i+2][j].c_str()) << endl;
        }



    }
   cout << "NUMBERS SUCCESSFULLY EXTRACTED" <<endl;
}

double flexiblesurvey::MeanValue(int q_index){

    double result;
    double sum=0;


    int numberofnd=0;

    for (int i=0; i<fb_values.size();++i)
    {
        if(fb_values[i][q_index]==0)
            ++numberofnd;

        else
        sum+=fb_values[i][q_index];
    }

    result =sum/(double)(fb_values.size()-numberofnd);

    return result;

}

double flexiblesurvey::ShareOfNonZeros(int q_index){
    int counter=0;
    double share=0;


    for (int i=0; i<fb_values.size();++i){
        if(fb_values[i][q_index]==0){}
        else
            ++counter;
    }

    share=((double)counter/(double)fb_values.size());
    cout << "WENT THROUGH" << endl;
    return share;
}

void flexiblesurvey::BuildMathCombo(){
    ui->MathsCombo->addItem("Mittelwert");
    ui->MathsCombo->addItem("so viel % haben das angegeben");


    cout << "COMBO SUCCESSFULLY BUILT" << endl;
}

void flexiblesurvey::on_ClearButton_clicked(){
    ui->ShowBox->clear();
}

