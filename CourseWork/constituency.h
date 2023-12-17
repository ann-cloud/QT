#ifndef CONSTITUENCY_H
#define CONSTITUENCY_H
#include <string>
#include <vector>

using namespace std;
class Constituency
{
private:
    string sName;
    int iEducation;
    int iObservants;
    int iMembers;
public:
    Constituency();
    Constituency(string sName, int iEducation, int iObservants, int iMembers);
    Constituency(const Constituency& c1);

    string getName() const;
    int getEducation() const;
    int getObservants() const;
    int getMembers() const;

    void setName(string name);
    void setEducation(int education);
    void setObservants(int observants);
    void setMembers(int members);

    int avgExpenses() const;
    int memberExpenses() const;
    int observantExpenses() const;
    Constituency& operator = (const Constituency& C );

    static int avgMemberExpenses(const vector<Constituency> list);
    static int avgObservantExpenses(const vector<Constituency> list);
    static int avgObservantCount(const vector<Constituency> list);

    static void memberExpensesLessThanAvg(vector<Constituency>& list);
    static void fiveByCondition(vector<Constituency>& list);

    static void Swap(Constituency& c1, Constituency& c2);
    static void SortByMembers(vector<Constituency>& list);
    static vector<string> Split(string s, string del);

    friend istream& operator>> (istream& in, Constituency& c);
    friend ostream& operator<< (ostream& out, Constituency& c);
};

#endif // CONSTITUENCY_H
