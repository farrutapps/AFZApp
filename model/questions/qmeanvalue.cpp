#include "qmeanvalue.h"
#include "basequestion.h"

QMeanValue::QMeanValue(QString  question_input, QString subquestion_input, vector <int> & data_input, int questiontype_input) : question(question_input), subQuestion(subquestion_input),questionType(questiontype_input)
{
    data=data_input;
}

QString QMeanValue::getCalculation()
{
    int res = qRound(meanValue(data)*100.0)/100.0;
    calculation=QString::number(statisticalValue);

    return calculation;
}




