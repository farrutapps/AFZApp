#ifndef FLEXIBLESURVEY_H
#define FLEXIBLESURVEY_H
using namespace std;
#include <iostream>
#include <QWidget>

#include <fstream>
#include <cassert>
#include <vector>

namespace Ui {
class flexiblesurvey;
}

class flexiblesurvey : public QWidget
{
    Q_OBJECT

public:
    explicit flexiblesurvey(QWidget *parent = 0);
    ~flexiblesurvey();

    void ReadCsv (string);
    void ExtractHeaders();
    void ExtractNumbers();

    void BuildMathCombo();
    void BuildList();
    //math functions
    double MeanValue(int);
    double ShareOfNonZeros(int);


private:
    Ui::flexiblesurvey *ui;

    vector<vector <string> > datamatrix;
    vector <vector <double> > fb_values;
    vector <string> fb_headers;


private slots:
    void NewCalculation();
    void on_ClearButton_clicked();
};

#endif // FLEXIBLESURVEY_H
