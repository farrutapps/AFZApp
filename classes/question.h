#ifndef QUESTION_H
#define QUESTION_H

#include <QWidget>
#include <vector>

#include <iostream>
#include <vector>

using namespace std;

class Question
{
public:
    Question();
    Question(QString question_input, QString subquestion_input, vector<int> &data_input, int questiontype_input);
    Question(QString question_input, QString subquestion_input, vector<QString> &text_answers_input, int questiontype_input);

    //writes
    void setQuestion(QString );
    void setSubquestion(QString);
    void setQuestiontype(int);
    void setData(vector <int>  & data_input);
    void setDataFromStdStringMatrix(vector <vector <string> >  &datamat, int q_index);
    void setTextAnswersFromStdStringMatrix(vector <vector <string> > &datamat,int q_index);

    void write_ID(int id);

    //reads
    QString getQuestion();
    QString getSubQuestion();
    int getQuestionType();
    vector <int> getData();
    QString getStatValString();
    double getStatVal();
    vector<QString> getTextAnswers();

    int getId();




    // statistical methods
    double meanValue();
    double shareOfNonZeros();
    double shareOfInput(int);

    void calcStatVal();

private:

    QString question;
    QString subQuestion;
    int questionType;
    vector<int> data;


    int ID;

    double statisticalValue;
    QString statValString;
    vector <QString> textAnswers;

};

#endif // QUESTION_H
