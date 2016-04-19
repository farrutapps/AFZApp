#include "model/filemanager.h"
#include "model/question.h"
#include "model/dbmanager.h"
#include "view/dbwindow.h"

/**
 * TODO:
 *
 * SEE TEXT FILE
 *
 * */

FileManager::FileManager(){isReady=false;}

FileManager::FileManager(int surveyId, int stype_id, DbManager *databaseMan) : dbMan(databaseMan), surveyTypeId(stype_id)
{
    isReady=false;
    getSurveytypes(true);
    dbToQuestions(surveyId);
    isReady=true;

}

FileManager::FileManager(QString path, int stypeId, DbManager *databaseMan) : filePath(path), surveyTypeId(stypeId), dbMan(databaseMan)
{
isReady=false;
getSurveytypes();

if(csvToDatamatrix()){
    if(datamatrixToQuestions())
        isReady=true;
}
else{
    QMessageBox msgBox;
    msgBox.setText("FEHLER: Mit der .CSV Datei stimmt etwas nicht.");
    msgBox.setInformativeText("Die Datei darf nicht verändert worden sein. Die Umfrage muss dem Surveymonkey Vorlagenformat entsprechen.");
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
}

}

bool FileManager::csvToDatamatrix(){
    bool success = false;

    cout << "START READING CSV" << endl;

    ifstream file;
    file.open(filePath.toStdString().c_str());

    if(!file.is_open()){
        cout << "WARNING: file has not been opened!"<< endl;
        success = false;
    }

    else {success = true;}

    string value;

    vector <string> dataset;

    string delimiter = "\r\n";      // \r for mac. \r\n for view csv
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
            dataMatrix.push_back(dataset);
            dataset.clear();
            dataset.push_back(token2);
        }
        else dataset.push_back(value);
    }

    if (success==true && dataMatrix.empty()){
        cout << "ERROR. READING CSV FAILED. " << endl << "Check .csv dialect. "
                                                              "line breakers could be different. check FileMangager::CsvToDatamatrix() maybe: \r\n " << endl;
    success = false;
    }


    return success;
}

bool FileManager::datamatrixToQuestions(){
    bool success = false;

    cout << "START READING DATA TO QUESTION OBJECTS" << endl;
// fills CSV Data from vector < vector <...> > datamatrix to questiondata objects.

    int m = dataMatrix[0].size();

    // check dimensions of datamatix
    if(m!=questionTypes[surveyTypeId].size()){


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


        if(questionTypes[surveyTypeId][i].toInt()!=0){

            Question *tempQuestion = new Question;

            tempQuestion->setQuestiontype(questionTypes[surveyTypeId][i].toInt());
            tempQuestion->setQuestion(QString::fromStdString(dataMatrix[0][i]));
            tempQuestion->setSubquestion(QString::fromStdString(dataMatrix[1][i]));

            if(tempQuestion->getQuestionType()!=6)
                tempQuestion->setDataFromStdStringMatrix(dataMatrix,i);

            else
                tempQuestion->setTextAnswersFromStdStringMatrix(dataMatrix,i);

            if(tempQuestion->getQuestion()!="")
                ++id;


            tempQuestion->write_ID(id);      // a question and its subquestions share the same id

            questions.push_back(*tempQuestion);
            delete tempQuestion;
            }

        }

    success=true;
    return success;
}

void FileManager::getSurveytypes(bool cutUseless){
    cout << "START READING SURVEYTYPES FROM DB" << endl;

    int surveyTypesSize =0;
    dbMan->countLines("surveytypes",surveyTypesSize);
    questionTypes.resize(surveyTypesSize);

    for (int i=0; i<surveyTypesSize; ++i){
        dbMan->selectSingleQuery("SELECT qtype FROM qtypes WHERE surveytype_id = " + QString::number(i),"qtype",questionTypes[i] );

        if(cutUseless){ // cuts out questiontipes == zero
            for(int j=questionTypes[i].size()-1; j>-1;--j){
                if(questionTypes[i][j].toInt()==0)
                    questionTypes[i].erase(questionTypes[i].begin()+j);
            }
        }
    }


}

void FileManager::questionsToDb(QString location, QString date){
    cout << "START WRITING SURVEY TO DATABASE!" << endl;

    // INSERT SURVEY
    int survey_id=0;
    int question_id=0;
    int subquestion_id=0;
    vector <int> temp_data_numeric;
    vector <QString> temp_data_qstring;

    dbMan->insertQuery("INSERT INTO surveys(surveytype_id, survey_name, survey_date, survey_datasize) VALUES (" + QString::number(surveyTypeId) + ",'" +
                         location +"', '"+ date + "' , "+ QString::number(questions[0].getData().size()) + ") RETURNING survey_id","survey_id",survey_id);


    // INSERT QUESTIONS WITH SUBQUESTIONS
    for (int i=0; i<questions.size();++i){

        if (questions[i].getQuestion() != ""){

            dbMan->insertQuery("INSERT INTO questions(survey_id, question_name) VALUES(" + QString::number(survey_id) +", '"+ questions[i].getQuestion()+"') RETURNING question_id", "question_id", question_id);
        }

        dbMan->insertQuery("INSERT INTO subquestions(question_id, subquestion_name) VALUES (" + QString::number(question_id) +", '"+ questions[i].getSubQuestion()+"') RETURNING subquestion_id","subquestion_id",subquestion_id); //

         // NOW INSERT DATA CONNECTED TO SUBQUESTIONS

        if(questions[i].getQuestionType()!=6){
            temp_data_numeric.clear();
            temp_data_numeric=questions[i].getData();
            for (int j=0; j<temp_data_numeric.size(); ++j){
                dbMan->insertQuery("INSERT INTO data_numeric(subquestion_id, answer_numeric) VALUES(" + QString::number(subquestion_id) + ", " + QString::number(temp_data_numeric[j]) +")");
            }
        }
        else{
            temp_data_qstring.clear();
            temp_data_qstring=questions[i].getTextAnswers();
            for (int j=0; j<temp_data_qstring.size(); ++j){
                dbMan->insertQuery("INSERT INTO data_text(subquestion_id, answer_text) VALUES(" + QString::number(subquestion_id) + ", '" + temp_data_qstring[j] +"')");
            }

        }

    }

    questions.clear();
    dataMatrix.clear();

}

vector <Question> FileManager::getQuestions(){
    if(!isReady)
    cout << "WARNING: FILEMANAGER WAS NOT SET UP. RETURNING EMPTY QUESTION OBJECTS" << endl;

    return questions;
}

void FileManager::questionsToTextFile(QString filePath, QString text){

     ofstream myfile;
     myfile.open (filePath.toStdString().c_str());
     myfile << text.toStdString().c_str();
     myfile.close();
}

void FileManager::dbToQuestions(int surveyId){

    vector < vector <QString> > survey_data;
    vector <QString> column_names;
    column_names.push_back("surveytype_name");
    column_names.push_back("survey_name");
    column_names.push_back("survey_date");

    dbMan->selectQuery("SELECT surveytype_name, survey_name, survey_date "
                         "FROM surveys INNER JOIN surveytypes "
                         "ON surveys.surveytype_id=surveytypes.surveytype_id "
                         "WHERE survey_id = "+ QString::number(surveyId),column_names,survey_data);


    surveyFacts.push_back(survey_data[0][0]);
    surveyFacts.push_back(survey_data[1][0]);
    surveyFacts.push_back(survey_data[2][0]);

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
    Question *temp_question;

   dbMan->selectQuery("SELECT question_id, question_name FROM questions WHERE survey_id="+QString::number(surveyId),q_column_names, question_data);

    int k=0;
    for (int i=0; i<question_data[0].size();++i){
        subquestion_data.clear();
        dbMan->selectQuery("SELECT subquestion_id, subquestion_name FROM subquestions WHERE question_id ="+question_data[0][i],sq_col_names,subquestion_data);

        for (int j =0; j<subquestion_data[0].size();++j){


            data.clear();
            dbMan->selectSingleQuery("SELECT answer_numeric FROM data_numeric WHERE subquestion_id ="+ subquestion_data[0][j], "answer_numeric",data);

            text_answers.clear();
            dbMan->selectSingleQuery("SELECT answer_text FROM data_text WHERE subquestion_id ="+ subquestion_data[0][j], "answer_text",text_answers);

            if (j==0){
                if(!data.empty())
                temp_question = new Question(question_data[1][i],subquestion_data[1][j],data,questionTypes[surveyTypeId][k].toInt());

                else temp_question = new Question(question_data[1][i],subquestion_data[1][j],text_answers,questionTypes[surveyTypeId][k].toInt());
            }

            else {
                if(!data.empty())
                    temp_question = new Question("",subquestion_data[1][j],data,questionTypes[surveyTypeId][k].toInt());

                else temp_question = new Question("",subquestion_data[1][j],text_answers,questionTypes[surveyTypeId][k].toInt());
            }
            questions.push_back(*temp_question);
            delete temp_question;
        ++k;
        }

    }

    cout << "FINISHED READING DB TO QUESTIONS" << endl;

}

vector<QString> FileManager::getSurveyFacts(){
    cout << surveyFacts[0].toStdString() << " " << surveyFacts[1].toStdString() << endl;
    return surveyFacts;
}


bool FileManager::getIsReady(){
    return isReady;
}
















