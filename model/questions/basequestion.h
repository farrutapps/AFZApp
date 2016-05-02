#ifndef BASEQUESTION_H
#define BASEQUESTION_H

#include <QWidget>
#include <vector>
#include <iostream>

using namespace std;

template<class T>
class BaseQuestion
{
protected:
    QString question;
    QString subQuestion;
    int questionType;

    vector <T> data;
    QString calculation;

public:
    BaseQuestion(QString  question_input, QString subquestion_input, vector <T> & data_input);

    QString getQuestion() const;
    void setQuestion(const QString &value);

    QString getSubQuestion() const;
    void setSubQuestion(const QString &value);

    int getQuestionType() const;
    void setQuestionType(int value);

    // statistical methods
    double meanValue();
    double shareOfNonZeros();
    double shareOfInput(int answer);

    virtual void setDataFromStdStringMatrix(vector <vector <string> >  &datamat, int q_index);
    virtual QString getCalculation() =0;

};

#endif // BASEQUESTION_H
