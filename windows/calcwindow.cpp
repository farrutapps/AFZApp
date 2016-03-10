#include "calcwindow.h"

#include "ui_CalcWindow.h"
#include <QFileDialog>
#include <QInputDialog>
#include <classes/questiondata.h>
#include <fstream>
#include <windows/dbwindow.h>

using namespace std;

CalcWindow::CalcWindow(QWidget *parent, DbManager *db_manager, FileManager *file_manager) :
    QWidget(parent),
    ui(new Ui::CalcWindow),
    db_man(db_manager),
    f_man(file_manager)
{
    ui->setupUi(this);


    ui->ShowWindow->setReadOnly(true);
    questions=f_man->get_questions();
    DisplayStatistics();

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

    QString filename = file.fileName();
    filename.chop(4);
    filename+="_Statistik.txt";

    QString filepath=directory[0].path();
    filepath=filepath+"/"+filename;

    f_man->QuestionsToTextFile(filepath,text);

}

void CalcWindow::DisplayStatistics(){

    QString introduction = "<i>Falls nicht anders angegeben, wurden die Mittelwerte der Antworten ermittelt. Möchgliche Antworten waren: 1,2,3,4. Für die Wanderausstellungen giltet: 1 bedeutet volle Zusstimmung, 4 gar keine Zustimmung <\i>" ;
    ui->ShowWindow->append(introduction);
    ui->ShowWindow->append("");

    for (int i=0; i<questions.size();++i){
     // display statistical results, if question type is not unknown and is not a text question.
        if(questions[i].read_question_type()!=0 && questions[i].read_question_type()!=6  ){

            QString MainQuestion="<b>"+questions[i].read_question()+"</b>";
            QString SubQuestion=questions[i].read_subquestion();

            if(questions[i].read_question()!="")
            ui->ShowWindow->append(MainQuestion);

            if(questions[i].read_subquestion()!="")
                ui->ShowWindow->append(SubQuestion);

            ui->ShowWindow->append(questions[i].read_stat_val_string());
            ui->ShowWindow->append("");
        }
    }

    ui->ShowWindow->append("<b>Teilnehmende insgesamt:</b>");
    int size = questions[0].read_data().size();
    ui->ShowWindow->append(QString::number(size));
    ui->ShowWindow->moveCursor(QTextCursor::Start);
}
