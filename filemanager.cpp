#include "filemanager.h"
#include "questiondata.h"
#include "dbmanager.h"

/**
 * TODO:
 *
 * _ASK for name of ORT, save to DB
 * _DATE
 *
 * */

FileManager::FileManager(QString path, int stype_id) : file_path(path), surveytype_id(stype_id)
{
db_man.setpath("/Users/Sebastian/Documents/CPP/AFZ/Feedbacker/Feedbacker_db.db");
ReadCsv();
ReadSurveytypes();
ReadDataToQuestions();
}



void FileManager::ReadCsv(){

    cout << "START READING CSV..." << endl;


    ifstream file;
    file.open(file_path.toStdString().c_str());

   if(!file.is_open()){
   cout << "file could not be opened! error"<< endl;
   assert(0);
   }

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
    if (datamatrix.empty()){
        cout << "ERROR. READING CSV FAILED. STOP." << endl << "Check .csv dialect. "
                                                              "line breakers could be different.  maybe: \r\n " << endl;
    }
    cout << "...CSV SUCESSFULLY READ!" << endl;

    cout << "DATA SUCCESSFULLY READ - ready to go!" << endl;
    }

void FileManager::ReadDataToQuestions(){

// fills CSV Data from vector < vector <T> > datamatrix to questiondata objects.

    int m = datamatrix[0].size();

    questions.resize(m);
    QString result;
    int id=0;

    for(int i=0; i<m;++i){
        questions[i].write_question(QString::fromStdString(datamatrix[0][i]));
        questions[i].write_subquestion(QString::fromStdString(datamatrix[1][i]));
        questions[i].write_data_fromStdString(datamatrix,i);

        if(questions[i].read_question()!="")
            ++id;

        questions[i].write_ID(id);      // a question and its subquestions share the same id


        for (int i=0; i<m;++i){
            questions[i].write_questiontype(questiontypes[surveytype_id][i].toInt());
        }

    }


    cout << "DATA READ INTO SAMPLES" << endl;

}

void FileManager::ReadSurveytypes(){

    int surveytypes_size =0;
    db_man.count_lines("surveys",surveytypes_size);
    question_types.resize(surveytypes_size);

    int questiontypes_size =0;

    for (int i=0; i<surveytypes_size; ++i){
        question_types[i].resize(questiontypes_size);
        db_man.select_single_query("SELECT type FROM qtypes WHERE surveytype_id = " + (i+1),"type",question_types[i] );
    }
}

void FileManager::WriteSurveyToDb(){
    db_man.insert_query("INSERT INTO surveys VALUES (NULL,"+surveytype_id+",'Ort', '02/24/2015' )");

    for (int i=0; i<questions.size();++i){
    db_man.insert_query("INSERT INTO questions VALUES(NULL,last_insert_rowid(), "+questions[i].read_question()+"," + questions[i].read_question_type() + ")");
// NEXT UP: subquestions
    }
}


