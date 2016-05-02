#include "model/questions/question.h"


Question::Question()
{
}

Question::Question(QString  question_input, QString subquestion_input, vector <int> & data_input, int questiontype_input) : question(question_input), subQuestion(subquestion_input),questionType(questiontype_input)
{
    data=data_input;
}

Question::Question(QString question_input, QString subquestion_input, vector<QString> & text_answers_input, int questiontype_input) : question(question_input), subQuestion(subquestion_input),questionType(questiontype_input)
{
    textAnswers=text_answers_input;
}

double Question::getStatVal(){
    calcStatVal();
    return statisticalValue;
}

void Question::setData(vector <int>  &data_input){
    // reads in the data of question with index q_index

    data=data_input;

}


void Question::setDataFromStdStringMatrix(vector<vector<string> > & datamat, int q_index){




    for (int i=2; i<datamat.size(); ++i){


        data.push_back(atoi(datamat[i][q_index].c_str()));
    }

}

void Question::setTextAnswersFromStdStringMatrix(vector<vector<string> > &datamat, int q_index){


    for (int i=2; i<datamat.size(); ++i){
        textAnswers.push_back(QString::fromStdString(datamat[i][q_index]));
    }
}

void Question::setQuestiontype(int question_type){

    questionType=question_type;
}

void Question::setQuestion(QString  header){

    question=header;

}

void Question::calcStatVal(){
double res=0;
    switch (questionType) {

    /** see README in Database folder for explanation of questiontype index. **/

    case 1: //mean value
        statisticalValue= qRound(meanValue()*100.0)/100.0;
        statValString=QString::number(statisticalValue);
        break;

    case 2: //how many agree
        statisticalValue=qRound(shareOfNonZeros()*10000.0)/100.0;
        statValString=QString::number(statisticalValue)+"%";
        break;

   case 3: // age

        for (int i=0; i<3;++i){

            res=qRound(shareOfInput(i+1)*10000.0)/100.0;

            switch(i+1){
            case 1: statValString.append("12-14 Jahre:\n"); break;
            case 2: statValString.append("15-17 Jahre:\n"); break;
            case 3: statValString.append("18-21 Jahre:\n"); break;
            case 4: statValString.append("älter als 21 Jahre:\n"); break;
            }

            statValString.append(QString::number(res)+"%\n\n");

        }

            statValString.chop(2);
        break;

    case 4: // gender
         res=0;
        for (int i=0; i<2;++i){

            res=qRound(shareOfInput(i+1)*10000.0)/100.0;

            switch(i+1){
            case 1: statValString.append("männlich:\n"); break;
            case 2: statValString.append("weiblich:\n"); break;

            }

            statValString.append(QString::number(res)+"%\n\n");

        }

            statValString.chop(2);
        break;

     case 5: //Schultyp
     {
        res=0;
        //define minimum percentage to show school
        int min=5;
        for (int i=0; i<12;++i){

            res=qRound(shareOfInput(i+1)*10000.0)/100.0;

            switch(i+1){
            case 1:
                if(res>min)
                    statValString.append("Förderschule\n");
                break;
            case 2:
                 if(res>min)
                     statValString.append("Hauptschule:\n");
                break;
            case 3:
                 if(res>min)
                     statValString.append("Realschule:\n");
                break;
            case 4:
                 if(res>min)
                     statValString.append("Regelschule:\n");
                break;
            case 5:
                 if(res>min)
                     statValString.append("Sekundarschule:\n");
                break;
            case 6:  if(res>min)
                    statValString.append("Gesamtschule:\n");
                break;
            case 7: if(res>min)
                    statValString.append("Gymnasium:\n");
                break;
            case 8: if(res>min)
                    statValString.append("Hochschule:\n");
                break;
            case 9: if(res>min)
                    statValString.append("Berufsschule:\n");
                break;
            case 10: if(res>min)
                    statValString.append("Sonstiges:\n");
                break;
            case 11: if(res>min)
                    statValString.append("Keine:\n");
                break;

            }

            if(res>min)
            statValString.append(QString::number(res)+"%\n\n");

        }

        break;
    }

    case 6: // Text Question
        for (int i=0; i<textAnswers.size();++i){
            if(textAnswers[i]!="" && textAnswers[i]!="-")
            statValString.append(textAnswers[i]+"\n\n");
        }

    break;

    case 7: // E-Learning

        res=0;
       for (int i=0; i<6;++i){

           res=qRound(shareOfInput(i+1)*10000.0)/100.0;

           switch(i+1){
           case 1: statValString.append("Sehr hilfreich:\n"); break;
           case 2: statValString.append("Eher hilfreich:\n"); break;
           case 3: statValString.append("Eher nicht hilfreich:\n"); break;
           case 4: statValString.append("Nicht hilfreich:\n"); break;
           case 5: statValString.append("Kenne ich nicht:\n"); break;
           case 6: statValString.append("Nicht benutzt:\n"); break;


           }

           statValString.append(QString::number(res)+"%\n\n");

       }

           statValString.chop(2);
       break;

           // DA Feedbackseminar: Wie viele Gruppen gemacht
    case 8:
    res=0;
        for (int i=0; i<3;++i){

            res=qRound(shareOfInput(i+1)*10000.0)/100.0;

            switch(i+1){
            case 1: statValString.append("bis zu 2:\n"); break;
            case 2: statValString.append("3-5:\n"); break;
            case 3: statValString.append("6-8:\n"); break;
            case 4: statValString.append("Mehr als 8:\n"); break;
            }

            statValString.append(QString::number(res)+"%\n\n");

        }

            statValString.chop(2);
        break;

    default:
        cout << "ERROR, Question type not implemented!" <<  endl;
        statisticalValue=0;
        statValString="error, question type not implemented";
        break;

    }

}

double Question::meanValue(){
    double result;
    double sum=0;

    // dont count empty cells
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

double Question::shareOfNonZeros(){

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

int Question::getQuestionType(){
    return questionType;
}

QString Question::getQuestion(){
    return question;
}

QString Question::getStatValString(){
    calcStatVal();
    return statValString;

}

double Question::shareOfInput(int answer){
    int counter=0;

    for (int i=0; i<data.size();++i){
        if(data[i]==answer)
            ++counter;
        else{}
    }

    return (double)counter/(double)data.size();
}

void Question::setSubquestion(QString input){
     subQuestion=input;
}

vector <int> Question::getData(){
    return data;
}



QString Question::getSubQuestion(){
    return subQuestion;
}

vector<QString> Question::getTextAnswers(){
    return textAnswers;
}
