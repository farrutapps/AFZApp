#ifndef QMEANVALUE_H
#define QMEANVALUE_H
#include "basequestion.h"
#include "basequestion.cpp"

#include <vector>

class QMeanValue : public BaseQuestion<int>
{

public:
    QMeanValue(QString  question_input, QString subquestion_input, vector <int> & data_input);

    QString getCalculation();

public slots:
};

#endif // QMEANVALUE_H
