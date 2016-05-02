#ifndef CalcWindow_H
#define CalcWindow_H
using namespace std;
#include <iostream>
#include <QWidget>
#include <QUrl>
#include <fstream>
#include <cassert>

#include "model/questions/question.h"
#include "model/survey.h"
# include "model/dbmanager.h"
#include "controller/controller.h"

namespace Ui {
class CalcWindow;
}

class CalcWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CalcWindow(QWidget *parent = 0, int surveyIdIn=0);
    ~CalcWindow();



    void appendText(QString text);
    void displayStatistics();

    void newCalculation();

    void showEvent(QShowEvent *);
public slots:
    void on_WriteFile_Button_clicked();


private:
    Ui::CalcWindow *ui;
    int surveyId;
    QUrl file;
    vector <Question> * questions;
    Survey *survey;


    Controller *fMan;

};

#endif // CalcWindow_H
