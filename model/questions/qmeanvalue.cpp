#include "qmeanvalue.h"
#include "basequestion.h"
#include "model/constants.h"


QMeanValue::QMeanValue(QString question_input, QString subquestion_input, vector<int> &data_input) : BaseQuestion(question_input, subquestion_input, data_input)
{
    questionType=questionTypes::MEAN_VALUE;
}

QString QMeanValue::getCalculation()
{
    int res = qRound(meanValue()*100.0)/100.0;
    calculation=QString::number(res);

    return calculation;
}




