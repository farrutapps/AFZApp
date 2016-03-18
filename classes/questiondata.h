#ifndef QUESTIONDATA_H
#define QUESTIONDATA_H

#include <QWidget>
#include <vector>

#include <iostream>
#include <vector>

using namespace std;

class questiondata
{
public:
    questiondata();
    questiondata(QString question_input, QString subquestion_input, vector<int> &data_input, int questiontype_input);
    questiondata(QString question_input, QString subquestion_input, vector<QString> &text_answers_input, int questiontype_input);

    //writes
    void write_question(QString );
    void write_subquestion(QString);
    void write_questiontype(int);
    void write_data(vector <int>  & data_input);
    void write_data_fromStdString_matrix(vector <vector <string> >  &datamat, int q_index);
    void write_text_answers_fromStdString_matrix(vector <vector <string> > &datamat,int q_index);

    void write_ID(int id);

    //reads
    QString read_question();
    QString read_subquestion();
    int read_question_type();
    vector <int> read_data();
    QString read_stat_val_string();
    double read_stat_val();
    vector<QString> read_text_answers();

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


    int ID;

    double statistical_value;
    QString stat_val_string;
    vector <QString> text_answers;

};

#endif // QUESTIONDATA_H
