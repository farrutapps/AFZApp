#include "classes/questiondata.h"


questiondata::questiondata()
{
}

questiondata::questiondata(QString  question_input, QString subquestion_input, vector <int> & data_input, int questiontype_input) : question(question_input), subquestion(subquestion_input),questiontype(questiontype_input)
{
    data=data_input;
}

double questiondata::read_stat_val(){
    calc_stat_val();
    return statistical_value;
}

void questiondata::write_data(vector <int>  &data_input){
    // reads in the data of question with index q_index

    data=data_input;

}


void questiondata::write_data_fromStdString_matrix(vector<vector<string> > & datamat, int q_index){


    data.resize(datamat.size());

    for (int i=0; i<datamat.size(); ++i){

        data[i]=atoi(datamat[i][q_index].c_str());

    }

}

void questiondata::write_questiontype(int question_type){

    questiontype=question_type;
}

void questiondata::write_question(QString  header){

    question=header;

}

void questiondata::calc_stat_val(){

    switch (questiontype) {

    /** see README in Database folder for explanation of questiontype index. **/

    case 1: //mean value
        statistical_value= qRound(mean_value()*100.0)/100.0;
        stat_val_string=QString::number(statistical_value);
        break;

    case 2: //how many agree
        statistical_value=qRound(share_of_non_zeros()*10000.0)/100.0;
        stat_val_string=QString::number(statistical_value)+"%";
        break;

   case 3: // age
        double res;
        for (int i=0; i<3;++i){

            res=qRound(share_of_input(i+1)*10000.0)/100.0;

            switch(i+1){
            case 1: stat_val_string.append("12-14 Jahre:\n"); break;
            case 2: stat_val_string.append("15-17 Jahre:\n"); break;
            case 3: stat_val_string.append("18-21 Jahre:\n"); break;
            case 4: stat_val_string.append("älter als 21 Jahre:\n"); break;
            }

            stat_val_string.append(QString::number(res)+"%\n\n");

        }

            stat_val_string.chop(2);
        break;

    case 4: // gender
         res=0;
        for (int i=0; i<2;++i){

            res=qRound(share_of_input(i+1)*10000.0)/100.0;

            switch(i+1){
            case 1: stat_val_string.append("männlich:\n"); break;
            case 2: stat_val_string.append("weiblich:\n"); break;

            }

            stat_val_string.append(QString::number(res)+"%\n\n");

        }

            stat_val_string.chop(2);
        break;

     case 5: //Schultyp

        res=0;
        int min=5;
        for (int i=0; i<12;++i){

            res=qRound(share_of_input(i+1)*10000.0)/100.0;

            switch(i+1){
            case 1:
                if(res>min)
                    stat_val_string.append("Förderschule\n");
                break;
            case 2:
                 if(res>min)
                     stat_val_string.append("Hauptschule:\n");
                break;
            case 3:
                 if(res>min)
                     stat_val_string.append("Realschule:\n");
                break;
            case 4:
                 if(res>min)
                     stat_val_string.append("Regelschule:\n");
                break;
            case 5:
                 if(res>min)
                     stat_val_string.append("Sekundarschule:\n");
                break;
            case 6:  if(res>min)
                    stat_val_string.append("Gesamtschule:\n");
                break;
            case 7: if(res>min)
                    stat_val_string.append("Gymnasium:\n");
                break;
            case 8: if(res>min)
                    stat_val_string.append("Hochschule:\n");
                break;
            case 9: if(res>min)
                    stat_val_string.append("Berufsschule:\n");
                break;
            case 10: if(res>min)
                    stat_val_string.append("Sonstiges:\n");
                break;
            case 11: if(res>min)
                    stat_val_string.append("Keine:\n");
                break;

            }
            if(res>min)
            stat_val_string.append(QString::number(res)+"%\n\n");

        }

        break;



/*
    default:
        cout << "ERROR, Question type not implemented!" <<  endl;
        statistical_value=0;
        stat_val_string="error, question type not implemented";
        break;
        */
    }

}

double questiondata::mean_value(){
    double result;
    double sum=0;


    int numberofnd=0;

    for (int i=0; i<data.size();++i)
    {
        if(data[i]==0)
            ++numberofnd;

        else
        sum+=data[i];
    }

    result =sum/(double)(data.size()-numberofnd);
    return result;

}

double questiondata::share_of_non_zeros(){

    int counter=0;
    double share=0;


    for (int i=0; i<data.size();++i){
        if(data[i]==0){}
        else
            ++counter;
    }

    share=((double)counter/(double)data.size());

    return share;
}

int questiondata::read_question_type(){
    return questiontype;
}

QString questiondata::read_question(){
    return question;
}

QString questiondata::read_stat_val_string(){
    calc_stat_val();
    return stat_val_string;

}

double questiondata::share_of_input(int answer){
    int counter=0;

    for (int i=0; i<data.size();++i){
        if(data[i]==answer)
            ++counter;
        else{}
    }

    return (double)counter/(double)data.size();
}

void questiondata::write_subquestion(QString input){
     subquestion=input;
}

void questiondata::push_back_datamatrix(vector <int> vec){
    datamatrix.push_back(vec);
}

vector <int> questiondata::read_data(){
    return data;
}

int questiondata::read_ID(){
    return ID;
}

void questiondata::write_ID(int id){
    ID=id;
}

QString questiondata::read_subquestion(){
    return subquestion;
}
