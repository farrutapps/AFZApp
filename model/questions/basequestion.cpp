#include "basequestion.h"

BaseQuestion::BaseQuestion()
{

}

template <class T>
double BaseQuestion<T>::meanValue(vector <int> &data){
    double result;
    double sum=0;

    // dont count empty cells
    int numberofnd=0;

    for (int i=0; i<data.size();++i)
    {
        if(data[i]==0)
            ++numberofnd;

        else
        sum+=data[i];
    }

    result =sum/(double)(data.size()-numberofnd);
    return result;

}

template <class T>
double BaseQuestion<T>::shareOfNonZeros(vector <int> &data){

    int counter=0;
    double share=0;


    for (int i=0; i<data.size();++i){
        if(data[i]==0){}
        else
            ++counter;
    }

    share=((double)counter/(double)data.size());

    return share;
}

template <class T>
double BaseQuestion<T>::shareOfInput(vector<int> &data, int answer){
    int counter=0;

    for (int i=0; i<data.size();++i){
        if(data[i]==answer)
            ++counter;
        else{}
    }

    return (double)counter/(double)data.size();
}

template <class T>
void BaseQuestion<T>::setDataFromStdStringMatrix(vector<vector<string> > & datamat, int q_index){




    for (int i=2; i<datamat.size(); ++i){


        data.push_back(atoi(datamat[i][q_index].c_str()));
    }

}

template <class T>
QString BaseQuestion<T>::getQuestion() const
{
    return question;
}

template <class T>
void BaseQuestion<T>::setQuestion(const QString &value)
{
    question = value;
}

template <class T>
QString BaseQuestion<T>::getSubQuestion() const
{
    return subQuestion;
}

template <class T>
void BaseQuestion<T>::setSubQuestion(const QString &value)
{
    subQuestion = value;
}

template <class T>
int BaseQuestion<T>::getQuestionType() const
{
    return questionType;
}

template <class T>
void BaseQuestion<T>::setQuestionType(int value)
{
    questionType = value;
}




