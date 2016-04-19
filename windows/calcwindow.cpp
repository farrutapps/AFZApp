#include "calcwindow.h"

#include "ui_CalcWindow.h"
#include <QFileDialog>
#include <QInputDialog>
#include <classes/question.h>
#include <fstream>
#include <windows/dbwindow.h>
#include <QCloseEvent>

using namespace std;

CalcWindow::CalcWindow(QWidget *parent, DbManager *db_manager, FileManager *file_manager) :
    QWidget(parent),
    ui(new Ui::CalcWindow),
    dbMan(db_manager),
    fMan(file_manager)
{
    ui->setupUi(this);


    ui->ShowWindow->setReadOnly(true);
    questions=fMan->getQuestions();
    displayStatistics();


}

CalcWindow::~CalcWindow()
{
    delete ui;
}


void CalcWindow::on_WriteFile_Button_clicked(){

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);

    QList<QUrl> directory;
    if (dialog.exec())
        directory = dialog.selectedUrls();

    QString text = ui->ShowWindow->toPlainText();

    vector <QString> survey_facts=fMan->getSurveyFacts();
    QString filename="Feedback_Auswertung_"+ survey_facts[0]+ "_" + survey_facts[1]+".txt";

    QString filepath=directory[0].path();
    filepath=filepath+"/"+filename;

    fMan->questionsToTextFile(filepath,text);

}

void CalcWindow::displayStatistics(){

   vector <QString> survey_facts = fMan->getSurveyFacts();

    QString header = "<b>Feedback Auswertung des "+survey_facts[0]+"s in "+survey_facts[1] + " am " + survey_facts[2] +"</b>";


    QString introduction = "<i>Falls nicht anders angegeben, wurden die Mittelwerte der Antworten ermittelt. Möchgliche Antworten waren: 1,2,3,4. In der Regel giltet: 1 bedeutet volle Zusstimmung, 4 gar keine Zustimmung \n \n <\i>" ;

    ui->ShowWindow->append(header);
    ui->ShowWindow->append("");

    ui->ShowWindow->append(introduction);
    ui->ShowWindow->append("");

    ui->ShowWindow->append("<b>Teilnehmende insgesamt:</b>");
    int size = questions[0].getData().size();
    ui->ShowWindow->append(QString::number(size));
    ui->ShowWindow->append("");

    ui->ShowWindow->moveCursor(QTextCursor::End);

    for (int i=0; i<questions.size();++i){
     // display statistical results, if question type is not unknown and is not a text question.
        if(questions[i].getQuestionType()!=0 && questions[i].getQuestionType()!=6  ){

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


ui->ShowWindow->moveCursor(QTextCursor::Start);

}

void CalcWindow::closeEvent (QCloseEvent *event)
{
        delete fMan;
    cout <<"wahahaha HAHA haha HAHAAHAH" << endl;
        event->accept();
    }

