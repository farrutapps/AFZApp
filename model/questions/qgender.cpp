#include "qgender.h"
#include "basequestion.h"
#include "model/constants.h"

QGender::QGender(QString questionInput, QString subquestionInput, vector<int> dataInput) : BaseQuestion(questionInput, subquestionInput, dataInput)
{
questionType=questionTypes::GENDER;
}

QString QGender::getCalculation(){
   double res=0.0;

   for (int i=0; i<2;++i){

       res=qRound(shareOfInput(i+1)*10000.0)/100.0;

       switch(i+1){
       case 1: calculation.append("männlich:\n"); break;
       case 2: calculation.append("weiblich:\n"); break;

       }

       calculation.append(QString::number(res)+"%\n\n");

   }

       calculation.chop(2);

       return calculation;
}
