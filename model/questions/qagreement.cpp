#include "qagreement.h"
#include "model/constants.h"

QAgreement::QAgreement(QString question_input, QString subquestion_input, vector<int> &data_input) : BaseQuestion (question_input, subquestion_input, data_input)
{
questionType=questionTypes::AGREEMENT;
}

QString QAgreement::getCalculation(){
    double res=qRound(shareOfNonZeros()*10000.0)/100.0;
    calculation=QString::number(res)+"%";

    return calculation;
}
