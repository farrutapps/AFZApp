#include "classes/filemanager.h"
#include "classes/questiondata.h"
#include "classes/dbmanager.h"
#include "windows/dbwindow.h"

/**
 * TODO:
 *
 * SEE TEXT FILE
 *
 * */

FileManager::FileManager(){is_ready=false;}

FileManager::FileManager(int survey_id,int stype_id, DbManager *database_man) : db_man(database_man), surveytype_id(stype_id)
{
    is_ready=false;
    ReadSurveytypes(true);
    DbToQuestions(survey_id);
    is_ready=true;

}

FileManager::FileManager(QString path, int stype_id, DbManager *database_man) : file_path(path), surveytype_id(stype_id), db_man(database_man)
{
is_ready=false;
ReadSurveytypes();

if(CsvToDatamatrix()){
    if(DatamatrixToQuestions())
        is_ready=true;
}
else{
    QMessageBox msgBox;
    msgBox.setText("FEHLER: Mit der .CSV Datei stimmt etwas nicht.");
    msgBox.setInformativeText("Die Datei darf nicht verändert worden sein. Die Umfrage muss dem Surveymonkey Vorlagenformat entsprechen.");
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
}

}

bool FileManager::CsvToDatamatrix(){
    bool success = false;

    cout << "START READING CSV" << endl;

    ifstream file;
    file.open(file_path.toStdString().c_str());

    if(!file.is_open()){
        cout << "WARNING: file has not been opened!"<< endl;
        success = false;
    }

    else {success = true;}

    string value;

    vector <string> dataset;

    string delimiter = "\r\n";      // \r for mac. \r\n for windows csv
    string token1;
    string token2;

    while (getline(file,value,';'))
    {
        // check if row delimiter is part of value. if yes, eliminate it and jump to next line.

        if (value.find(delimiter) != std::string::npos) {
            token1 = value.substr(0, value.find(delimiter));
            token2 = value.substr(value.find(delimiter)+delimiter.size(),value.size());

            token1.push_back('"');


            dataset.push_back(token1);
            datamatrix.push_back(dataset);
            dataset.clear();
            dataset.push_back(token2);
        }
        else dataset.push_back(value);
    }

    if (success==true && datamatrix.empty()){
        cout << "ERROR. READING CSV FAILED. " << endl << "Check .csv dialect. "
                                                              "line breakers could be different. check FileMangager::CsvToDatamatrix() maybe: \r\n " << endl;
    success = false;
    }


    return success;
}

bool FileManager::DatamatrixToQuestions(){
    bool success = false;

    cout << "START READING DATA TO QUESTION OBJECTS" << endl;
// fills CSV Data from vector < vector <...> > datamatrix to questiondata objects.

    int m = datamatrix[0].size();

    // check dimensions of datamatix
    if(m!=question_types[surveytype_id].size()){


        cout << "ERROR: number of survey questions != number of questiontypes" << endl;

        QMessageBox msgBox;
        msgBox.setText("FEHLER: Der ausgewählte Ausstellungstyp passt nicht zur .CSV Datei.");
        msgBox.setInformativeText("Bitte richtigen Ausstellungstyp wählen oder Anleitung lesen.");
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        success = false;
        return success;
    }

    int id=0;

    for(int i=0; i<m;++i){


        if(question_types[surveytype_id][i].toInt()!=0){

            questiondata *temp_question = new questiondata;

            temp_question->write_questiontype(question_types[surveytype_id][i].toInt());
            temp_question->write_question(QString::fromStdString(datamatrix[0][i]));
            temp_question->write_subquestion(QString::fromStdString(datamatrix[1][i]));

            if(temp_question->read_question_type()!=6)
                temp_question->write_data_fromStdString_matrix(datamatrix,i);

            else
                temp_question->write_text_answers_fromStdString_matrix(datamatrix,i);

            if(temp_question->read_question()!="")
                ++id;


            temp_question->write_ID(id);      // a question and its subquestions share the same id

            questions.push_back(*temp_question);
            delete temp_question;
            }

        }

    success=true;
    return success;
}

void FileManager::ReadSurveytypes(bool cut_useless){
    cout << "START READING SURVEYTYPES FROM DB" << endl;

    int surveytypes_size =0;
    db_man->count_lines("surveytypes",surveytypes_size);
    question_types.resize(surveytypes_size);

    for (int i=0; i<surveytypes_size; ++i){
        db_man->select_single_query("SELECT qtype FROM qtypes WHERE surveytype_id = " + QString::number(i),"qtype",question_types[i] );

        if(cut_useless){ // cuts out questiontipes == zero
            for(int j=question_types[i].size()-1; j>-1;--j){
                if(question_types[i][j].toInt()==0)
                    question_types[i].erase(question_types[i].begin()+j);
            }
        }
    }


}

void FileManager::QuestionsToDb(QString Location, QString Date){
    cout << "START WRITING SURVEY TO DATABASE!" << endl;

    // INSERT SURVEY
    int survey_id=0;
    int question_id=0;
    int subquestion_id=0;
    vector <int> temp_data_numeric;
    vector <QString> temp_data_qstring;

    db_man->insert_query("INSERT INTO surveys(surveytype_id, survey_name, survey_date, survey_datasize) VALUES (" + QString::number(surveytype_id) + ",'" +
                         Location +"', '"+ Date + "' , "+ QString::number(questions[0].read_data().size()) + ") RETURNING survey_id","survey_id",survey_id);


    // INSERT QUESTIONS WITH SUBQUESTIONS
    for (int i=0; i<questions.size();++i){

        if (questions[i].read_question() != ""){

            db_man->insert_query("INSERT INTO questions(survey_id, question_name) VALUES(" + QString::number(survey_id) +", '"+ questions[i].read_question()+"') RETURNING question_id", "question_id", question_id);
        }

        db_man->insert_query("INSERT INTO subquestions(question_id, subquestion_name) VALUES (" + QString::number(question_id) +", '"+ questions[i].read_subquestion()+"') RETURNING subquestion_id","subquestion_id",subquestion_id); //

         // NOW INSERT DATA CONNECTED TO SUBQUESTIONS

        if(questions[i].read_question_type()!=6){
            temp_data_numeric.clear();
            temp_data_numeric=questions[i].read_data();
            for (int j=0; j<temp_data_numeric.size(); ++j){
                db_man->insert_query("INSERT INTO data_numeric(subquestion_id, answer_numeric) VALUES(" + QString::number(subquestion_id) + ", " + QString::number(temp_data_numeric[j]) +")");
            }
        }
        else{
            temp_data_qstring.clear();
            temp_data_qstring=questions[i].read_text_answers();
            for (int j=0; j<temp_data_qstring.size(); ++j){
                db_man->insert_query("INSERT INTO data_text(subquestion_id, answer_text) VALUES(" + QString::number(subquestion_id) + ", '" + temp_data_qstring[j] +"')");
            }

        }

    }

    questions.clear();
    datamatrix.clear();

}

vector <questiondata> FileManager::get_questions(){
    if(!is_ready)
    cout << "WARNING: FILEMANAGER WAS NOT SET UP. RETURNING EMPTY QUESTION OBJECTS" << endl;

    return questions;
}

void FileManager::QuestionsToTextFile(QString filepath, QString text){

     ofstream myfile;
     myfile.open (filepath.toStdString().c_str());
     myfile << text.toStdString().c_str();
     myfile.close();
}

void FileManager::DbToQuestions(int survey_id){

    vector < vector <QString> > survey_data;
    vector <QString> column_names;
    column_names.push_back("surveytype_name");
    column_names.push_back("survey_name");
    column_names.push_back("survey_date");

    db_man->select_query("SELECT surveytype_name, survey_name, survey_date "
                         "FROM surveys INNER JOIN surveytypes "
                         "ON surveys.surveytype_id=surveytypes.surveytype_id "
                         "WHERE survey_id = "+ QString::number(survey_id),column_names,survey_data);


    survey_facts.push_back(survey_data[0][0]);
    survey_facts.push_back(survey_data[1][0]);
    survey_facts.push_back(survey_data[2][0]);

    vector < vector <QString> > question_data;
    vector < QString > q_column_names;
    q_column_names.push_back("question_id");
    q_column_names.push_back("question_name");


    vector <vector <QString> > subquestion_data;
    vector <QString> sq_col_names;
    sq_col_names.push_back("subquestion_id");
    sq_col_names.push_back("subquestion_name");

    vector <int> data;
    vector <QString> text_answers;

    questions.clear();
    questiondata *temp_question;

   db_man->select_query("SELECT question_id, question_name FROM questions WHERE survey_id="+QString::number(survey_id),q_column_names, question_data);

    int k=0;
    for (int i=0; i<question_data[0].size();++i){
        subquestion_data.clear();
        db_man->select_query("SELECT subquestion_id, subquestion_name FROM subquestions WHERE question_id ="+question_data[0][i],sq_col_names,subquestion_data);

        for (int j =0; j<subquestion_data[0].size();++j){


            data.clear();
            db_man->select_single_query("SELECT answer_numeric FROM data_numeric WHERE subquestion_id ="+ subquestion_data[0][j], "answer_numeric",data);

            text_answers.clear();
            db_man->select_single_query("SELECT answer_text FROM data_text WHERE subquestion_id ="+ subquestion_data[0][j], "answer_text",text_answers);

            if (j==0){
                if(!data.empty())
                temp_question = new questiondata(question_data[1][i],subquestion_data[1][j],data,question_types[surveytype_id][k].toInt());

                else temp_question = new questiondata(question_data[1][i],subquestion_data[1][j],text_answers,question_types[surveytype_id][k].toInt());
            }

            else {
                if(!data.empty())
                    temp_question = new questiondata("",subquestion_data[1][j],data,question_types[surveytype_id][k].toInt());

                else temp_question = new questiondata("",subquestion_data[1][j],text_answers,question_types[surveytype_id][k].toInt());
            }
            questions.push_back(*temp_question);
            delete temp_question;
        ++k;
        }

    }

    cout << "FINISHED READING DB TO QUESTIONS" << endl;

}

vector<QString> FileManager::ReadSurveyFacts(){
    cout << survey_facts[0].toStdString() << " " << survey_facts[1].toStdString() << endl;
    return survey_facts;
}


bool FileManager::IsReady(){
    return is_ready;
}



QDate FileManager::SQLDateToQtDate(QString SQLDate){
    int year;
    int month;
    int day;

    year = SQLDate.mid(0,4).toInt();
    month = SQLDate.mid(1,2).toInt();
    day = SQLDate.mid(1,2).toInt();

    QDate date;
    date.setDate(year,month,day);
    return date;

}












