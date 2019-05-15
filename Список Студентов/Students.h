#pragma once
#ifndef Students
#define Students
//���������� ����������� ����������
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
//������
class Information;
class GradesForTheExam;
class Subjects;
template <class T>
//������ ������
class List
{
	friend class List<GradesForTheExam>;
	friend class GradesForTheExam;
	//��������� �� ��������� ������� ������
	List<T> *next;
	//�������������� ����
	T data;
	//�����������
	List(T &v) { data = v; next = NULL; }
public:
	List<T> *get_next() { return next; }
	void set_next(List<T> *next) { this->next = next; }
	T get_data() { return data; }
	void set_data(T data) { this->data = data; }
	//������ ������
	void WriteExamens(std::ofstream &f);
	void WriteExamensOnScreen();
	void LoadOnScreenSubjects();
	int  ReadExamens(int Exames, std::ifstream &f, List<Subjects> *&R);
	int LoadSubjectsFromFile(const char *SubjectsIn);
	void LoadSubjectsInFile(const char *SubjectsOut);
	void AddExam(char *ch, int number, int mark, List<Subjects> *&);
	void ChangeExam();
	float AVG();
	int AddExamens(List<Subjects> *&R, int Examens);
	//�����������
	List()
	{
		next = NULL;
	};
	//����������
	~List()
	{
		if (next != NULL) delete next;
	};
	//������� ���������� ������� � ������
	void AddElements(T &c)
	{
		List *p, *q;
		T S = c;
		p = new List(c);
		q = this;
		p->next = q->next;
		q->next = p;
	};
};

//������ �� �������� ��� ��������
class GradesForTheExam
{
	friend class List<GradesForTheExam>;
	//����� ��������
	int subject;
	//��������� �� ��������������� ������� ������ ���������
	List<Subjects> *Sub;
	//������
	int mark;
public:
	//������ ������
	int  ReadExam(std::ifstream &f, List<Subjects> *&R);
	void WriteExam(std::ofstream &f);
	void WriteExamOnScreen();
	//�����������
    GradesForTheExam()
	{
		Sub = NULL;
		subject = 0;
		mark = 0;
	};
	//����������
	~GradesForTheExam()
	{
	};
};

//���������� � ��������: ������ � ������� ����
class Information
{
	friend class List<Information>;
	//��� ��������
	string StudentName;
	//���������� ������� ���������
	int  CountOfExam;
	//������� ����
	float Avg;
	//��������� �� ������ ��������� ��� ������� ��������
	List<GradesForTheExam> *pass;
public:
	bool operator==(string s_name) { return(StudentName == s_name); }
	int get_count_of_exam() { return CountOfExam; }
	void set_count_of_exam(int c) { CountOfExam = c; }
	List<GradesForTheExam> * get_pass() { return pass; }
	void set_pass(List<GradesForTheExam> * c) { pass = c; }
	float get_avg() { return Avg; }
	void set_avg(float c) { Avg = c; }
	string get_name() { return StudentName; }
	void set_name(string c) { StudentName = c; }
	//������ ������
	void Write(std::ofstream &f);
	void WriteOnScreen();
	int  Read(Information *a, std::ifstream &f, List<Subjects> *&R);
	//�����������
	Information()
	{
		CountOfExam = 0;
		Avg = 0;
		pass = NULL;
		StudentName = "NONAME";
	};
	//����������
	~Information()
	{

	};
};
//���������� � ��������: ����� � ��������
class Subjects 
{
public:
	//����� ��������
	int NumberOfSubject;
	//�������� ��������
	char NameOfSubject[20];
	//�����������
	Subjects()
	{
		NumberOfSubject = 0;
	};
	//����������
	~Subjects()
	{
	};
	//������ ������
	int ReadSubject(std::ifstream &f);
	void  WriteSubjects(std::ofstream &f);
	void WriteSubjectsOnScreen();
};

//������� ��� ����� ���������� �������� �� �����
int Information::Read(Information *a, std::ifstream &f, List<Subjects> *&R)
{
	//���� ��� ���������� �� �����
	int flag = 1; 
	try
	{
		//������ ���
		f >> a->StudentName;
		//��������� �� ������ ������
		if ((a->StudentName.length() == 0)||(a->StudentName == "NONAME")) return 1;
		//������ ���������� ���������
		f >> (a->CountOfExam);
		//������� ���������� ��� ������ ���������� ��������� � ��������
		float n = a->CountOfExam;
		//��������� ���������� - ������ ��������� ��� ��������
		List<GradesForTheExam> *b = new List<GradesForTheExam>();
		//�������� ������� ������ ������ ��������� ��� ��������
		//��������� ������� ���� ��������: ����� ���� ������ ����� �� ���������� ���������
		a->Avg = b->ReadExamens(a->CountOfExam, f, *&R) / n;
		a->pass = b;
		return 0;
	}
	catch (...)
	{
		return 1;
	}
}
template<>
//������� ���������� n ��������� � ���������� �� ������ ������
int List<GradesForTheExam>::ReadExamens(int Exames, std::ifstream &f, List<Subjects> *&R)
{
	//���������� ���������
	int n = 0;
	for (int i = 0; i < Exames; i++)
	{
		//������� �������������� ����������
		GradesForTheExam a;
		//�������� ������� ��� ����� � ���������� (�) ���������� �������� �� ����� (f)
		int flag = a.ReadExam(f, *&R);
		if (flag) 
		{
			//��������� ����� ������� � ������
			AddElements(*&a);
			//����� ������ ��������
			n += flag;
		}
		else break;
	}
	//���������� ����� ������
	return n;
}
//������� ���������� ������ ��������
int  GradesForTheExam::ReadExam(std::ifstream &f, List<Subjects> *&R)
{
	//��������� �� ����� f ����� ��������
	f >> (this->subject);
	//��������� �� ����� f ������
	f >> (this->mark);
	//������ ���������� � ���������� n
	int n = this->mark;
	List<Subjects> *q = R;
	for (q = R->next; q != NULL; q = q->next)
	{
		Subjects W = q->data;
		//���������� ����� �������� �� ������ ��������� � ������� �������� �� ������ ��������� ��� ������� ��������
		if (this->subject == W.NumberOfSubject)
		{
			this->Sub = q;
		}
	}
	//���������� ������
	return n;
}
//������� ������ � ���� ���������� � ��������
void   Information::Write(std::ofstream &f)
{
	//�������� ������� ������ ������ ��������� ��� ��������
	this->pass->WriteExamens(f);
	f << "\n";
}
//������� ������ � ���� ������ ��������� ��� ������ ��������
template<>
void List<GradesForTheExam>::WriteExamens(std::ofstream &f)
{
	//������� ���������� - ������ ���������
	List<GradesForTheExam> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//�������� ������� ������ ���������� �� ����� ��������
		q->data.WriteExam(f);
	}
}
//������� ������ ���������� �� ��������
void GradesForTheExam::WriteExam(std::ofstream &f)
{
	Subjects S;
	S= (this->Sub)->data;
	f << this->subject << " " << S.NameOfSubject << "(" << this->mark << ");";
}
//������� �������� ������ ��������� �� �����
template<>
int List<Subjects>::LoadSubjectsFromFile(const char *SubjectsIn)
{
	std::ifstream fin(SubjectsIn);
	//���������� ��������� � ������
	int number = 0;
	while (fin)
	{
		//������� ���������� - ������� ������ ���������
		Subjects subject;
		//����� ������� ������ ������ �������� �� �����
		int flag = subject.ReadSubject(fin);
		if (!flag)
		{
			//��������� ������� � ������
			AddElements(subject);
			//���������� 1 � �������� ���������
			number++;
		}
		else break;
	}
	return number; 
}
//������� �������� ���������� �� ����� �������� 
int  Subjects::ReadSubject(std::ifstream &f)
{
	try
	{
		//������ ��������
		f >> (NumberOfSubject);
		//������ �����
		f >> (NameOfSubject);
		//��������� �� ������ ������
		if (strlen(NameOfSubject) == 0) return 1;
		return 0;
	}
	catch (...)
	{
		return 1;
	}
}
//������� �������� ������ ��������� � ����
template<>
void List<Subjects>::LoadSubjectsInFile(const char *SubjectsOut)
{
	std::ofstream f_out;
	//��������� ����
	f_out.open(SubjectsOut, std::ios::app);
	f_out << "	������ ���������\n\n������:\n\n";
	//������� ���������� - ������ ���������
	List<Subjects> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//�������� ������� ������ ���������� �� ����� �������� � ����
		q->data.WriteSubjects(f_out);
	}
	f_out << "\n�����\n\n";
}
//������� �������� ���������� �� ����� �������� 
void   Subjects::WriteSubjects(std::ofstream &f)
{
	f << "����� - " << this->NumberOfSubject << "\n";
	f << "�������� - " << this->NameOfSubject << "\n";
	f << "\n";
}
//������� ������ ���������� �� ����� ��������
void   Information::WriteOnScreen()
{
	//�������� ������� ������ ������ ��������� ��� ��������
	this->pass->WriteExamensOnScreen();
	cout << "\n";
}
//������� ������ ������ ��������� ��� ��������
template<>
void List<GradesForTheExam>::WriteExamensOnScreen()
{
	//������� ���������� - ������ ���������
	List<GradesForTheExam> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//�������� ������� ������ ���������� �� ����� ��������
		q->data.WriteExamOnScreen();
	}
}
//������� ������ ���������� �� ����� ��������
void GradesForTheExam::WriteExamOnScreen()
{
	Subjects S;
	S = (this->Sub)->data;
	cout << this->subject << " " << S.NameOfSubject << "(" << this->mark << ");";
}
//������� ������ ������ ��������� �� �����
template<>
void List<Subjects>::LoadOnScreenSubjects()
{
	cout << "	������ ���������\n\n������:\n\n";
	//������ ���������
	List<Subjects> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//����� ������� ������ ���������� �� ����� �������� �� �����
		q->data.WriteSubjectsOnScreen();
	}
	cout << "\n�����\n\n";
}
//������� ������ ���������� �� ����� �������� �� �����
void   Subjects::WriteSubjectsOnScreen()
{
	cout << "�������� - " << this->NameOfSubject << " ";
	cout << "����� - " << this->NumberOfSubject << "\n";
	cout << "\n";
}
template<>
float List<GradesForTheExam>::AVG()
{
	float Sum=0;
	int n = 0;
	List<GradesForTheExam> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		Sum=Sum+q->data.mark;
		n++;
	}
	Sum = Sum / n;
	return Sum;
}
//������� ���������� ���������� � ����� �������� ��� ��������
template<>
void List<GradesForTheExam>::AddExam(char *ch, int number, int mark, List<Subjects> *&R)
{
	//���������� � ��������
	GradesForTheExam a;
	//���������� ����� ��������
	a.subject = number;
	//���������� ������
	a.mark = mark;
	List<Subjects> *q = R;
	for (q = R->next; q != NULL; q = q->next)
	{
		Subjects W = q->data;
		//���������� ����� �������� �� ������ ��������� � ������� �������� �� ������ ��������� ��� ������� ��������
		if (number == W.NumberOfSubject)
		{
			a.Sub = q;
		}
	}
	//��������� ������� � ������
	AddElements(a);
}
template<>
//������� ���������� n ��������� � ���������� �� ������ ������
int List<GradesForTheExam>::AddExamens(List<Subjects> *&R, int Examens)
{
	//���������� ���������
	int n = 0;
	for (int i = 0; i < Examens; i++)
	{
		//������� �������������� ����������
		GradesForTheExam a;
		cout << "������� ����� ��������";
		int number = 0;
		cin >> number;
		cout << "������� ������";
		int mark = 0;
		cin >> mark;
		a.mark = mark;
		a.subject = number;
List<Subjects> *q = R;
for (q = R->next; q != NULL; q = q->next)
{
	Subjects W = q->data;
	//���������� ����� �������� �� ������ ��������� � ������� �������� �� ������ ��������� ��� ������� ��������
	if (number == W.NumberOfSubject)
	{
		a.Sub = q;
	}
}
			//��������� ����� ������� � ������
			AddElements(*&a);
			//����� ������ ��������
			n = n + mark;
	}
	//���������� ����� ������
	return n;
}
template<>
void List<GradesForTheExam>::ChangeExam()
{
	cout << "������� ����� ��������";
	int ch;
	cin >> ch;
	cout << "������� ����� ������";
	int mark = 0;
	cin >> mark;
	List<GradesForTheExam> *flag;
	List<GradesForTheExam> *p = this->next;
	while (p != NULL)
	{
		if (p->data.subject== ch)
			break;
		p = p->next;
	}
	flag = p;
	if (flag == NULL)
	{
		cout << "������� �� ������.\n";
		return;
	}
	p->data.mark = mark;
}
#endif