#include "calcwindow.h"

#include "ui_CalcWindow.h"
#include <QFileDialog>
#include <QInputDialog>
#include <model/question.h>
#include <fstream>
#include <view/dbwindow.h>
#include <QCloseEvent>

using namespace std;

CalcWindow::CalcWindow(QWidget *parent, int surveyIdIn) :
    QWidget(parent),
    ui(new Ui::CalcWindow),
    surveyId(surveyIdIn)
  
{
    ui->setupUi(this);

    ui->ShowWindow->setReadOnly(true);
    survey = fMan->getCurrentSurvey();
    newCalculation();

}

CalcWindow::~CalcWindow()
{
    delete ui;
}

void CalcWindow::newCalculation(){





    QString header = "<b>Feedback Auswertung des "+ survey->getSurveyTypeName() +"s in "+ survey->getLocation() + " am " + survey->getDate() +"</b>";


    QString introduction = "<i>Falls nicht anders angegeben, wurden die Mittelwerte der Antworten ermittelt. Möchgliche Antworten waren: 1,2,3,4. In der Regel giltet: 1 bedeutet volle Zusstimmung, 4 gar keine Zustimmung \n \n <\i>" ;


    ui->ShowWindow->append(header);
    ui->ShowWindow->append("");

    ui->ShowWindow->append(introduction);
    ui->ShowWindow->append("");

    ui->ShowWindow->append("<b>Teilnehmende insgesamt:</b>");

    int dataSize= survey->getQuestionDataSize();
    ui->ShowWindow->append(QString::number(dataSize));
    ui->ShowWindow->append("");

    //ui->ShowWindow->moveCursor(QTextCursor::End);

    // CHANGE THIS
    vector <Question> questions = survey->getQuestions();

    for (int i=0; i<questions.size();++i){


        if(questions[i].getQuestionType()!=6){

            QString mainQuestion="<b>"+questions[i].getQuestion()+"</b>";
            QString subQuestion=questions[i].getSubQuestion();

            if(questions[i].getQuestion()!="")
            ui->ShowWindow->append(mainQuestion);

            if(questions[i].getSubQuestion()!="")
                ui->ShowWindow->append(subQuestion);

            ui->ShowWindow->append(questions[i].getStatValString());
            ui->ShowWindow->append("");
        }
    }

    for (int i=0; i<questions.size();++i){
        if(questions[i].getQuestionType()==6  ){
            QString mainQuestion="<b>"+questions[i].getQuestion()+"</b>";

            if(questions[i].getQuestion()!="")
            ui->ShowWindow->append(mainQuestion);
            ui->ShowWindow->append("");
            ui->ShowWindow->append(questions[i].getStatValString());

        }

    }
}



void CalcWindow::on_WriteFile_Button_clicked(){

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);

    QList<QUrl> directory;
    if (dialog.exec())
        directory = dialog.selectedUrls();

    QString text = ui->ShowWindow->toPlainText();

    vector <QString> surveyFacts;
    fMan->getSurveyFacts(surveyFacts,survey->getDbId());
    QString filename="Feedback_Auswertung_"+ surveyFacts[0]+ "_" + surveyFacts[1]+".txt";

    QString filepath=directory[0].path();
    filepath=filepath+"/"+filename;

    fMan->questionsToTextFile(filepath,text);

}




void CalcWindow::showEvent(QShowEvent *){
    ui->ShowWindow->moveCursor(QTextCursor::Start);

}
