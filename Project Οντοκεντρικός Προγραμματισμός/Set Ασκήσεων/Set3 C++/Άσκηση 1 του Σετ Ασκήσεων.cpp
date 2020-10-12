#include <iostream>
#include <cstdlib>

using namespace std;

class student
{
private:
	string name;
	string surname;
	int Am;
public:
	virtual void message()
	{
		cout << "Hello, I am message() defined in superclass Student." << endl;
	}
};

class undergrad :public student
{
private:
	int entrance_order;
	int passed_courses;
public:
	virtual void message()
	{
		cout << "Hello, I am message() defined in class Undergrad." << endl;
	}
};
class MSc :public student
{
private:
	string dipl_dept;
	int dipl_grade;
	string thesis;
public:
	int get_dipl_grade()
	{
	}
};

class PhD :public student
{
private:
	string PhD_title;
	string professor;
	int start_month;
	int start_year;
public:
	virtual void message()
	{
		cout << "Hello, I am message() defined in class PhD." << endl;
	}
};

int main()
{
	int counter;
	student *array[4];
	student S1;
	undergrad U1;
	MSc M1;
	PhD Ph1;
	array[0]= &S1;
	array[1] = &U1;
	array[2] = &M1;
	array[3] = &Ph1;
	for (counter = 0; counter < 4; counter++)
	{
		array[counter]->message();
	}
	system("pause");
	return 0;
}