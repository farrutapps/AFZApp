#ifndef QMEANVALUE_H
#define QMEANVALUE_H
#include "basequestion.h"

#include <vector>

class QMeanValue : public BaseQuestion
{
protected:
    vector<int> data;

public:
    QMeanValue(QString question_input, QString subquestion_input, vector<int> &data_input, int questiontype_input);

    QString getCalculation();



public slots:
};

#endif // QMEANVALUE_H
