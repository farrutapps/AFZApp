#ifndef QAGREEMENT_H
#define QAGREEMENT_H

#include "basequestion.h"
#include "basequestion.cpp"

class QAgreement : public BaseQuestion<int>
{
public:
    QAgreement(QString  question_input, QString subquestion_input, vector<int> &data_input);
    QString getCalculation();
signals:

public slots:
};

#endif // QAGREEMENT_H
