#include "controller/controller.h"
#include "model/questions/question.h"
#include "model/dbmanager.h"
#include "view/dbwindow.h"
#include "QFileDialog"

/**
 * TODO:
 *
 * SEE TEXT FILE
 *
 * */



Controller::Controller()
{
                          
}


DbManager *Controller::dbMan = new DbManager("/Users/Sebastian/Documents/CPP/AFZ/Feedbacker/database/fb_database.db");

vector <Survey> Controller::surveys;

Survey *Controller::currentSurvey=NULL;


void Controller::getSurveyTypes(vector <QString> &surveyTypes){
    dbMan->selectSingleQuery("SELECT surveytype_name FROM surveytypes", "surveytype_name", surveyTypes);
}

void Controller::getQuestionTypesFromDb(vector<QString> &questionTypes,  int surveyTypeId, bool cutUseless){
    cout << "START READING SURVEYTYPES FROM DB" << endl;
    
        dbMan->selectSingleQuery("SELECT qtype FROM qtypes WHERE surveytype_id = " + QString::number(surveyTypeId),"qtype",questionTypes );

        if(cutUseless){ // cuts out questiontipes == zero
            for(int i=questionTypes.size()-1; i>-1;--i){
                if(questionTypes[i].toInt()==0)
                    questionTypes.erase(questionTypes.begin()+i);
            }
        }
    
}



void Controller::questionsToTextFile(QString filePath, QString text){

     ofstream myfile;
     myfile.open (filePath.toStdString().c_str());
     myfile << text.toStdString().c_str();
     myfile.close();
}

void Controller::fillSurveyFromDb(Survey &survey){

    vector<QString> questionTypes;
    getQuestionTypesFromDb(questionTypes, survey.getSurveyTypeId(), true);

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


    Question *tempQuestion;

   dbMan->selectQuery("SELECT question_id, question_name FROM questions WHERE survey_id="+QString::number(survey.getDbId()),q_column_names, question_data);

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
                tempQuestion = new Question(question_data[1][i],subquestion_data[1][j],data,questionTypes[k].toInt());

                else tempQuestion = new Question(question_data[1][i],subquestion_data[1][j],text_answers,questionTypes[k].toInt());
            }

            else {
                if(!data.empty())
                    tempQuestion = new Question("",subquestion_data[1][j],data,questionTypes[k].toInt());

                else tempQuestion = new Question("",subquestion_data[1][j],text_answers,questionTypes[k].toInt());
            }
            
            survey.pushBackQuestions(*tempQuestion);
            delete tempQuestion;
            ++k;
        }

    }

    cout << "FINISHED FILLING QUESTIONS FROM DB" << endl;

}

void Controller::getSurveyFacts(vector <QString> &surveyFacts, int surveyId ){

   if(!surveyFacts.empty())
   cout << "WARNING: surveyFacts is not empty!" << endl;

 cout << "WHAPPAAAA" << endl;
    for (int i=0; i<surveys.size();++i){
        cout << "123123123" <<endl;
        if (surveys[i].getDbId()==surveyId){

            surveyFacts.push_back(surveys[i].getSurveyTypeName());
            surveyFacts.push_back(surveys[i].getLocation());
            surveyFacts.push_back(surveys[i].getDate());
            surveyFacts.push_back(QString::number(surveys[i].getQuestionDataSize()));
            surveyFacts.push_back(QString::number(surveys[i].getDbId()));



        }
    }


}

void Controller::getSurveyFacts(vector <vector<QString> > &surveyFacts)
{

    if(!surveyFacts.empty())
    cout << "WARNING: surveyFacts is not empty!" << endl;

    vector <QString> tempFacts;
     for (int i=0; i<surveys.size();++i){


             tempFacts.push_back(surveys[i].getSurveyTypeName());
             tempFacts.push_back(surveys[i].getLocation());
             tempFacts.push_back(surveys[i].getDate());
             tempFacts.push_back(QString::number(surveys[i].getQuestionDataSize()));
             tempFacts.push_back(QString::number(surveys[i].getDbId()));

             surveyFacts.push_back(tempFacts);
             tempFacts.clear();
         }
     }







bool Controller::surveysFromDbToModel(int &numberOfSurveys){

    bool success=false;

    vector <vector <QString> > surveyData;
    vector <QString> columnNames;

    columnNames.push_back("surveytype_name");
    columnNames.push_back("survey_name");
    columnNames.push_back("survey_date");
    columnNames.push_back("survey_datasize");
    columnNames.push_back("survey_id");
    columnNames.push_back("surveytype_id");

    dbMan->selectQuery("SELECT survey_name, survey_date, survey_datasize, survey_id, surveytype_name, surveys.surveytype_id "
                         "FROM surveys INNER JOIN surveytypes "
                         "ON surveys.surveytype_id=surveytypes.surveytype_id",columnNames,surveyData);

    numberOfSurveys=surveyData[0].size();

    vector <QString> surveyTypeIds;

    if (!surveyData.empty()){

        surveys.resize(numberOfSurveys);

            for (int j=0; j<numberOfSurveys;++j){
                surveys[j].setSurveyTypeName(surveyData[0][j]);
                surveys[j].setLocation(surveyData[1][j]);
                surveys[j].setDate(surveyData[2][j]);
                surveys[j].setQuestionDataSize(surveyData[3][j].toInt());
                surveys[j].setDbId(surveyData[4][j].toInt());
                surveys[j].setSurveyTypeId(surveyData[5][j].toInt());

        }

        success = true;
    }

    else {
        cout << "Error reading database. Maybe empty." <<endl;
        success = false;
    }


    return success;
    
}


bool Controller::ImportFile(QString location, QString date, int surveyTypeId, QString filePath){
    bool success=false;

    vector <QString> questionTypes;
    getQuestionTypesFromDb(questionTypes,surveyTypeId, false);


    Import *import = new Import(dbMan, location, date, surveyTypeId, questionTypes, filePath);
    success = import-> getSuccess();

    return success;
}

void Controller::deleteSurveyFromDb(QString surveyId)
{
    dbMan->deleteQuery("DELETE FROM surveys WHERE survey_id="+ surveyId);
}

bool Controller::newCalculation(int surveyId){

    bool success = false;


    // find survey with surveyID
    for (int i=0; i<surveys.size(); ++i){
        if(surveys[i].getDbId()==surveyId)
            currentSurvey=&surveys[i];
    }

    if (!currentSurvey->getIsFilled())
        fillSurveyFromDb(*currentSurvey);

    CalcWindow *calcWindow = new CalcWindow();

    calcWindow->show();
}

Survey *Controller::getCurrentSurvey()
{
    return currentSurvey;
}







