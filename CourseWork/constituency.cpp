#include "constituency.h"
#include <iostream>
#include <QDebug>
int size = 4;
using namespace std;

Constituency::Constituency()
{
    sName = "ТВО №117";
    iEducation = 1000;
    iObservants = 5;
    iMembers = 10;
}

Constituency::Constituency(string sName, int iEducation, int iObservants, int iMembers)
{
    this->sName = sName;
    this->iEducation = iEducation;
    this->iObservants = iObservants;
    this->iMembers = iMembers;
}

Constituency::Constituency(const Constituency& c1)
{
    this->sName = c1.sName;
    this->iEducation = c1.iEducation;
    this->iObservants = c1.iObservants;
    this->iMembers = c1.iMembers;
}

string Constituency::getName() const
{
    return sName;
}

int Constituency::getEducation() const
{
    return iEducation;
}

int Constituency::getObservants() const
{
    return iObservants;
}

int Constituency::getMembers() const
{
    return iMembers;
}

void Constituency::setName(string name)
{
    sName = name;
}

void Constituency::setEducation(int education)
{
    iEducation = education;
}

void Constituency::setObservants(int observants)
{
    iObservants = observants;
}

void Constituency::setMembers(int members)
{
    iMembers = members;
}

//витрати на навчання на одну людину
int Constituency::avgExpenses() const
{
    return iEducation / (iObservants + iMembers);
}

//перевантажений оператор присвоєння
Constituency& Constituency::operator=(const Constituency &C)
{
    sName = C.sName;
    iEducation = C.iEducation;
    iObservants = C.iObservants;
    iMembers = C.iMembers;
    return *this;
}

//обмін значень двох округів
void Constituency::Swap(Constituency &c1, Constituency &c2)
{
    Constituency temp = c1;
    c1 = c2;
    c2 = temp;
}

//сортування округів за кількістю членів ДВК методом бульбашки
void Constituency::SortByMembers(vector<Constituency>& list)
{
    if (list.size())
    {
        for (size_t i = 0; i < list.size() - 1; ++i)
        {
            for (size_t j = i + 1; j < list.size(); ++j)
            {
                if (list[i].iMembers < list[j].iMembers)
                {
                    Swap(list[i], list[j]);
                }
            }
        }
    }
}

//витрати на навчання на одного члена ДВК
int Constituency::memberExpenses() const
{
    return iEducation / iMembers;
}

//витрати на навчання на одного спостерігача
int Constituency::observantExpenses() const
{
    return iEducation / iObservants;
}

//середні витрати на навчання на одного члена ДВК
int Constituency::avgMemberExpenses(const vector<Constituency> list)
{
    int sum = 0;
    for (size_t i = 0; i < list.size(); ++i)
    {
        sum += list[i].memberExpenses();
    }
    return sum / list.size();
}

//середні витрати на навчання на одного спостерігача
int Constituency::avgObservantExpenses(const vector<Constituency> list)
{
    int sum = 0;
    for (size_t i = 0; i < list.size(); ++i)
    {
        sum += list[i].observantExpenses();
    }
    return sum / list.size();
}

//середня кількість спостерігачів
int Constituency::avgObservantCount(const vector<Constituency> list)
{
    int sum = 0;
    for (size_t i = 0; i < list.size(); ++i)
    {
        sum += list[i].iObservants;
    }
    return sum / list.size();
}

//витрати на члена ДВК менші середніх
void Constituency::memberExpensesLessThanAvg(vector<Constituency>& list)
{
    int avg = Constituency::avgMemberExpenses(list);
    for (size_t i = 0; i < list.size(); ++i)
    {
        if (!(list[i].memberExpenses() < avg))
        {
            list.erase(list.begin() + i);
            i--;
        }
    }
}

//пошук 5 округів за критерієм
void Constituency::fiveByCondition(vector<Constituency>& list)
{
    int avgCount = avgObservantCount(list);
    int avgExpenses = avgObservantExpenses(list);
    for (size_t i = 0; i < list.size(); ++i)
    {
        if (!(list[i].iObservants > avgCount && list[i].observantExpenses() < avgExpenses))
        {
            list.erase(list.begin() + i);
            i--;
        }
    }
}

//поділ вхідної стрічки файлу на частини
vector<string> Constituency::Split(string s, string del)
{
    vector<string> vec;
    int start, end = -1*del.size();
    do
    {
        start = end + del.size();
        end = s.find(del, start);
        vec.push_back(s.substr(start, end - start));
    } while (end != -1);
    return vec;
}

//перевантажений оператор виводу
ostream &operator<< (ostream& out, Constituency& c)
{
    out << c.getName() << " " << c.getEducation() << " " << c.getObservants() << " " << c.getMembers() << endl;
    return out;
}

//перевантажений оператор вводу
istream &operator>> (istream& in, Constituency& c)
{
    string line;
    vector<string> tokens;
    getline(in, line);
    size_t n;
    tokens = Constituency::Split(line, ",");
    c.sName = tokens[0];

    n = tokens[1].length() + 1;
    char strEd[n];
    strcpy(strEd, tokens[1].c_str());
    c.iEducation = atoi(strEd);

    n = tokens[2].length() + 1;
    char strObsv[n];
    strcpy(strObsv, tokens[2].c_str());
    c.iObservants = atoi(strObsv);

    n = tokens[3].length() + 1;
    char strMem[n];
    strcpy(strMem, tokens[3].c_str());
    c.iMembers = atoi(strMem);
    return in;
}

