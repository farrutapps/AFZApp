#include "import.h"
#include "model/dbmanager.h"
#include "question.h"

#include <QMessageBox>

Import::Import(DbManager *databaseMan, QString location, QString date, int surveyTypeId, vector<QString> &questionTypesIn, QString filePath) : questionTypes(questionTypesIn), dbMan(databaseMan)
{
    success = false;
    if(csvToDatamatrix(filePath))
        if(datamatrixToQuestions())
            if(questionsToDb(location,date, surveyTypeId))
                success=true;
}

bool Import::csvToDatamatrix(QString filePath){
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
    success = true;

    if (success==true && dataMatrix.empty()){
        cout << "ERROR. READING CSV FAILED. " << endl << "Check .csv dialect. "
                                                              "line breakers could be different. check FileMangager::CsvToDatamatrix() maybe: \r\n " << endl;
        QMessageBox msgBox;
        msgBox.setText("FEHLER: Mit der .CSV Datei stimmt etwas nicht.");
        msgBox.setInformativeText("Die Datei darf nicht verändert worden sein. Die Umfrage muss dem Surveymonkey Vorlagenformat entsprechen.");
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        success = false;
    }


    return success;
}



bool Import::datamatrixToQuestions(){
    bool success = false;

    cout << "START READING DATA TO QUESTION OBJECTS" << endl;
// fills CSV Data from vector < vector <...> > datamatrix to questiondata objects.

    int m = dataMatrix[0].size();

    // check dimensions of datamatix
    if(m!=questionTypes.size()){


        cout << "ERROR: number of survey questions != number of questiontypes" << endl;

        QMessageBox msgBox;
        msgBox.setText("FEHLER: Der ausgewählte Ausstellungstyp passt nicht zur .CSV Datei.");
        msgBox.setInformativeText("Bitte richtigen Ausstellungstyp wählen.");
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        success = false;
        return success;
    }

    int id=0;

    for(int i=0; i<m;++i){


        if(questionTypes[i].toInt()!=0){

            Question *tempQuestion = new Question;

            tempQuestion->setQuestiontype(questionTypes[i].toInt());
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


bool Import::questionsToDb(QString location, QString date, int surveyTypeId){
    cout << "START WRITING SURVEY TO DATABASE!" << endl;
    bool success;
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
    success=true;
    return success;

}

bool Import::getSuccess() const
{
    return success;
}

