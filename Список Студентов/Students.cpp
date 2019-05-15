
#include "Students.h"
#include <fstream>
#include <vector>
using namespace std;

void LoadFromFile(vector<Information> &Q, const char *StudentsIn, List<Subjects> *&R)
{
	std::ifstream f_in(StudentsIn);
	//�������� ������� ���������
	int n = 0;
	//���� ���� ����������
	while (f_in)
	{
		//������� �������������� ����������
		Information a;
		//�������� ������� ��� ������ ���������� �� ��������� �������� �� �����
		int flag = a.Read(&a, f_in, *&R);
		//��������� ���� �� �������� ����, ��� flag == 0
		if (!flag)
		{
			//��������� ������� � ������
			Q.push_back(a);
			n++;
		}
		else break;
	}
	//��������� ����
	f_in.close();
}
void LoadInFile(vector<Information>& Q, const char *StudentsOut)
{
	std::ofstream f_out;
	//�������� ����
	f_out.open(StudentsOut, std::ios::app);
	f_out << "	������ ���������\n\n������:\n\n";
	for (int q = 0; q < Q.size(); q++)
	{
		f_out << "�������: " << Q[q].get_name() << endl;
		f_out << "���������� ������� ���������: " << Q[q].get_count_of_exam() << endl;
		f_out << "������� ����: " << Q[q].get_avg() << endl;
		Q[q].Write(f_out);
	}
	f_out << "\n�����\n\n";
}

void LoadOnScreen(vector<Information> &Q)
{
	cout << "	������ ���������\n\n������:\n\n";
	for (int q = 0; q < Q.size(); q++)
	{
		cout << "�������: " << Q[q].get_name() << endl;
		cout << "���������� ������� ���������: " << Q[q].get_count_of_exam() << endl;
		cout << "������� ����: " << Q[q].get_avg() << endl;
		Q[q].WriteOnScreen();
	}
	cout << "\n�����\n\n";
}

void AddEXAM(vector<Information> &Q, char *ch, int number, int mark, List<Subjects> *&R)
{
	for (int i = 0; i < (Q.end() - Q.begin()); i++)
	{
		if (Q[i] == ch)
		{
			//����� ��������� ��� ��������
			List<GradesForTheExam> *b = new List<GradesForTheExam>();
			b = Q[i].get_pass();
			//�������� ������� ���������� ���������� � ����� �������� ��� ��������
			b->AddExam(ch, number, mark, *&R);
			Q[i].set_pass(b);
			Q[i].set_avg(b->AVG());
		}
	}
}
void Delete(vector<Information> &Q)
{
	string ch;
	cout << "������� ��� ��������: ";
	cin >> ch;
	for (int i = 0; i < (Q.end() - Q.begin()); i++)
	{
		if (Q[i] == ch)
		{
			Q.erase(Q.begin() + i);
		}
	}
}
void AddStudent(vector<Information> &Q,List<Subjects> *&R)
{
	cout << "������� ������� ��������";
	string ch;
	cin >> ch;
	cout << "������� ���������� ���������";
	int count = 0;
	cin >> count;
	Information a;
	a.set_name(ch);
	a.set_count_of_exam(count);
	List<GradesForTheExam> *b = new List<GradesForTheExam>();
	a.set_avg(b->AddExamens(*&R, count) / count);
	a.set_pass(b);
	//��������� ������� � ����� ������
	Q.push_back(a);
}
void Change(vector<Information> &Q)
{
	cout << "������� ������� ��������";
	string s_name;
	cin >> s_name;
	for (int i = 0; i < (Q.end() - Q.begin()); i++)
	{
		if (Q[i] == s_name)
		{
			//����� ��������� ��� ��������
			List<GradesForTheExam> *b = new List<GradesForTheExam>();
			b = Q[i].get_pass();
			//�������� ������� ���������� ���������� � ����� �������� ��� ��������
			b->ChangeExam();
			Q[i].set_pass(b);
			Q[i].set_avg(b->AVG());
		}
	}
}
int main()
{
	//���������� ������� ���������
	setlocale(LC_ALL, "Russian");
	//������� ������������
	int comand = -1;
	cout << "1. ��������� ������ ��������� �� �����" << endl;
	cout << "2. ��������� ������ ��������� � ����" << endl;
	cout << "3. ������� ������ ��������� �� �����" << endl;
	cout << "4. ��������� ������ ��������� �� �����" << endl;
	cout << "5. ��������� ������ ��������� � ����" << endl;
	cout << "6. ������� ������ ��������� �� �����" << endl;
	cout << "7. �������� �������" << endl;
	cout << "8. ������� ��������" << endl;
	cout << "9. �������� ��������" << endl;
	cout << "10. �������� ������" << endl;
	cout << "0. �����" << endl;
	//������������� ������ �������
	cin >> comand;
	List<Subjects> *K = new List<Subjects>();
	K->LoadSubjectsFromFile("SubjectsIn.txt");
	vector<Information> I;
	while (comand != 0)
	{
		//�������� ������ ��������� �� �����
		if (comand == 1)
		{
			LoadFromFile(I,"StudentsIn.txt", *&K);
			cout << "C����� ��������� �������� �� �����" << endl;
		}
		//�������� ������ ��������� � ����
		if (comand == 2)
		{
			LoadInFile(I,"StudentsOut.txt");
			cout << "C����� ��������� �������� � ����" << endl;
		}
		//����� ������ ��������� �� �����
		if (comand == 3)
		{
			LoadOnScreen(I);
		}
		//�������� ������ ��������� �� �����
		if (comand == 4)
		{
			cout << "C����� ��������� �������� �� �����" << endl;
		}
		//�������� ������ ��������� � ����
		if (comand == 5)
		{
			K->LoadSubjectsInFile("SubjectsOut.txt");
			cout << "C����� ��������� �������� � ����" << endl;
		}
		//����� ������ ��������� �� �����
		if (comand == 6)
		{
			K->LoadOnScreenSubjects();
		}
		//���������� ���������� �� �������� ��� ��������
		if (comand == 7)
		{
			cout << "������� ������� ��������";
			char ch[20];
			cin >> ch;
			cout << "������� ����� ��������";
			int number = 0;
			cin >> number;
			cout << "������� ������";
			int mark = 0;
			cin >> mark;
			AddEXAM(I,ch, number, mark, *&K);
		}
		if (comand == 8)
		{
		Delete(I);
		}
		if (comand == 9)
		{
			AddStudent(I,*&K);
		}
		if (comand == 10)
		{
			Change(I);
		}
		cout << "1. ��������� ������ ��������� �� �����" << endl;
		cout << "2. ��������� ������ ��������� � ����" << endl;
		cout << "3. ������� ������ ��������� �� �����" << endl;
		cout << "4. ��������� ������ ��������� �� �����" << endl;
		cout << "5. ��������� ������ ��������� � ����" << endl;
		cout << "6. ������� ������ ��������� �� �����" << endl;
		cout << "7. �������� �������" << endl;
		cout << "8. ������� ��������" << endl;
		cout << "9. �������� ��������" << endl;
		cout << "10. �������� ������" << endl;
		cout << "0. �����" << endl;
		cin >> comand;
	}
	system("pause");
}









