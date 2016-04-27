#include "model/filemanager.h"
#include "model/question.h"
#include "model/dbmanager.h"
#include "view/dbwindow.h"
#include "QFileDialog"

/**
 * TODO:
 *
 * SEE TEXT FILE
 *
 * */

FileManager::FileManager()
{

                          
}

QString FileManager::filePath="";

DbManager *FileManager::dbMan = NULL;

vector <Survey> FileManager::surveys = ;
//vector <Survey> FileManager::surveys;
Survey *FileManager::currentSurvey=NULL;



void FileManager::getQuestionTypesFromDb(vector<QString> &questionTypes,  int surveyTypeId, bool cutUseless){
    cout << "START READING SURVEYTYPES FROM DB" << endl;
    
        dbMan->selectSingleQuery("SELECT qtype FROM qtypes WHERE surveytype_id = " + QString::number(surveyTypeId),"qtype",questionTypes );

        if(cutUseless){ // cuts out questiontipes == zero
            for(int i=questionTypes.size()-1; i>-1;--i){
                if(questionTypes[i].toInt()==0)
                    questionTypes.erase(questionTypes.begin()+i);
            }
        }
    
}



void FileManager::questionsToTextFile(QString filePath, QString text){

     ofstream myfile;
     myfile.open (filePath.toStdString().c_str());
     myfile << text.toStdString().c_str();
     myfile.close();
}

void FileManager::fillSurveyFromDb(Survey &survey){

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

vector<QString> FileManager::getSurveyFacts(vector <QString> &surveyFacts, int surveyId ){

   if(!surveyFacts.empty())
   cout << "WARNING: surveyFacts is not empty!" << endl;


    for (int i=0; i<surveys.size();++i){
        if (surveys[i].getDbId()==surveyId){

            surveyFacts.push_back(surveys[i].getSurveyTypeName());
            surveyFacts.push_back(surveys[i].getLocation());
            surveyFacts.push_back(surveys[i].getDate());
            surveyFacts.push_back(QString::number(surveys[i].getQuestionDataSize()));
            surveyFacts.push_back(QString::number(surveys[i].getDbId()));

        }
    }

    return surveyFacts;
}




bool FileManager::surveysFromDbToModel(int &numberOfSurveys){

    bool success=false;

    vector <vector <QString> > surveydata;
    vector <QString> column_names;

    column_names.push_back("surveytype_name");
    column_names.push_back("survey_name");
    column_names.push_back("survey_date");
    column_names.push_back("survey_datasize");
    column_names.push_back("survey_id");
    column_names.push_back("surveytypes.surveytype_id");

    dbMan->selectQuery("SELECT survey_name, survey_date, survey_datasize, survey_id, surveytype_name, surveytypes.surveytype_id  "
                         "FROM surveys INNER JOIN surveytypes "
                         "ON surveys.surveytype_id=surveytypes.surveytype_id",column_names,surveydata);

    numberOfSurveys=surveydata[0].size();

    if (!surveydata.empty()){

        surveys.resize(numberOfSurveys);

            for (int j=0; j<numberOfSurveys;++j){

                surveys[j].setSurveyTypeName(surveydata[0][j]);
                surveys[j].setLocation(surveydata[1][j]);
                surveys[j].setDate(surveydata[2][j]);
                surveys[j].setQuestionDataSize(surveydata[3][j].toInt());
                surveys[j].setDbId(surveydata[4][j].toInt());
                surveys[j].setSurveyTypeId(surveydata[5][j].toInt());

        }

        success = true;
    }

    else {
        cout << "Error reading database. Maybe empty." <<endl;
        success = false;
    }


    return success;
    
}





bool FileManager::newImport(QString location, QString date, int surveyTypeId, QString filePath){
    bool success=false;

    vector <QString> questionTypes;
    getQuestionTypesFromDb(questionTypes,surveyTypeId, false);

    Import *import = new Import(dbMan, location,date,surveyTypeId,questionTypes, filePath);
    success = import-> getSuccess();

    return success;


}


bool FileManager::newCalculation(int surveyId){

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

Survey *FileManager::getCurrentSurvey()
{
    return currentSurvey;
}







