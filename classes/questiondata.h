#ifndef QUESTIONDATA_H
#define QUESTIONDATA_H

#include <QWidget>
#include <vector>

#include <iostream>

using namespace std;

class questiondata
{
public:
    questiondata();
    questiondata(QString, vector < vector <double > >&, int, int);

    void write_question(QString );
    void write_subquestion(QString);
    void write_questiontype(int);
    void write_data(vector <vector <double> >  &, int );
    void write_data_fromStdString(vector <vector <string> >  &, int );

    void push_back_datamatrix(vector <int>);
    void write_ID(int id);

    QString read_question();
    QString read_subquestion();
    vector <int> read_data();
    QString read_stat_val_string();
    double read_stat_val();
    int read_question_type();
    int read_ID();


    void calc_stat_val();

    // statistical methods
    double mean_value();
    double share_of_non_zeros();


    double share_of_input(int);

private:
QString question;
QString subquestion;
int questiontype;
vector<int> data;
vector <vector <int> > datamatrix;
int ID;

double statistical_value;
QString stat_val_string;


signals:

public slots:
};

#endif // QUESTIONDATA_H
