#ifndef QGENDER_H
#define QGENDER_H

#include "basequestion.h"
#include "basequestion.cpp"

class QGender : public BaseQuestion<int>
{
public:
    QGender(QString  question_input, QString subquestion_input, vector<int> data_input);

    QString getCalculation();

};

#endif // QGENDER_H
