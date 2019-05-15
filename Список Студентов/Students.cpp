
#include "Students.h"
#include <fstream>
#include <vector>
using namespace std;

void LoadFromFile(vector<Information> &Q, const char *StudentsIn, List<Subjects> *&R)
{
	std::ifstream f_in(StudentsIn);
	//Обнуляем счетчик студентов
	int n = 0;
	//Пока файл существует
	while (f_in)
	{
		//Создаем информационную переменную
		Information a;
		//Вызываем функцию для чтения информации об очередном студенте из файла
		int flag = a.Read(&a, f_in, *&R);
		//Проверяем флаг на успешный ввод, при flag == 0
		if (!flag)
		{
			//Добавляем элемент в список
			Q.push_back(a);
			n++;
		}
		else break;
	}
	//Закрываем файл
	f_in.close();
}
void LoadInFile(vector<Information>& Q, const char *StudentsOut)
{
	std::ofstream f_out;
	//Открывам файл
	f_out.open(StudentsOut, std::ios::app);
	f_out << "	Список студентов\n\nНачало:\n\n";
	for (int q = 0; q < Q.size(); q++)
	{
		f_out << "Фамилия: " << Q[q].get_name() << endl;
		f_out << "Количество сданных экзаменов: " << Q[q].get_count_of_exam() << endl;
		f_out << "Средний балл: " << Q[q].get_avg() << endl;
		Q[q].Write(f_out);
	}
	f_out << "\nКонец\n\n";
}

void LoadOnScreen(vector<Information> &Q)
{
	cout << "	Список студентов\n\nНачало:\n\n";
	for (int q = 0; q < Q.size(); q++)
	{
		cout << "Фамилия: " << Q[q].get_name() << endl;
		cout << "Количество сданных экзаменов: " << Q[q].get_count_of_exam() << endl;
		cout << "Средний балл: " << Q[q].get_avg() << endl;
		Q[q].WriteOnScreen();
	}
	cout << "\nКонец\n\n";
}

void AddEXAM(vector<Information> &Q, char *ch, int number, int mark, List<Subjects> *&R)
{
	for (int i = 0; i < (Q.end() - Q.begin()); i++)
	{
		if (Q[i] == ch)
		{
			//Списк экзаменов для студента
			List<GradesForTheExam> *b = new List<GradesForTheExam>();
			b = Q[i].get_pass();
			//Вызываем функцию добавления информации о новом экзамене для студента
			b->AddExam(ch, number, mark, *&R);
			Q[i].set_pass(b);
			Q[i].set_avg(b->AVG());
		}
	}
}
void Delete(vector<Information> &Q)
{
	string ch;
	cout << "Введите имя студента: ";
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
	cout << "Введите фамилию студента";
	string ch;
	cin >> ch;
	cout << "Введите количество экзаменов";
	int count = 0;
	cin >> count;
	Information a;
	a.set_name(ch);
	a.set_count_of_exam(count);
	List<GradesForTheExam> *b = new List<GradesForTheExam>();
	a.set_avg(b->AddExamens(*&R, count) / count);
	a.set_pass(b);
	//Добавляем элемент в конец списка
	Q.push_back(a);
}
void Change(vector<Information> &Q)
{
	cout << "Введите фамилию студента";
	string s_name;
	cin >> s_name;
	for (int i = 0; i < (Q.end() - Q.begin()); i++)
	{
		if (Q[i] == s_name)
		{
			//Списк экзаменов для студента
			List<GradesForTheExam> *b = new List<GradesForTheExam>();
			b = Q[i].get_pass();
			//Вызываем функцию добавления информации о новом экзамене для студента
			b->ChangeExam();
			Q[i].set_pass(b);
			Q[i].set_avg(b->AVG());
		}
	}
}
int main()
{
	//Используем русскую раскладку
	setlocale(LC_ALL, "Russian");
	//Команда пользователя
	int comand = -1;
	cout << "1. Загрузить список студентов из файла" << endl;
	cout << "2. Загрузить список студентов в файл" << endl;
	cout << "3. Вывести список студентов на экран" << endl;
	cout << "4. Загрузить список предметов из файла" << endl;
	cout << "5. Загрузить список предметов в файл" << endl;
	cout << "6. Вывести список предметов на экран" << endl;
	cout << "7. Добавить экзамен" << endl;
	cout << "8. Удалить студента" << endl;
	cout << "9. Добавить студента" << endl;
	cout << "10. Изменить оценку" << endl;
	cout << "0. Выйти" << endl;
	//Пользоватедль вводит команду
	cin >> comand;
	List<Subjects> *K = new List<Subjects>();
	K->LoadSubjectsFromFile("SubjectsIn.txt");
	vector<Information> I;
	while (comand != 0)
	{
		//Загрузка списка студентов из файла
		if (comand == 1)
		{
			LoadFromFile(I,"StudentsIn.txt", *&K);
			cout << "Cписок студентов загружен из файла" << endl;
		}
		//Загрузка списка студентов в файл
		if (comand == 2)
		{
			LoadInFile(I,"StudentsOut.txt");
			cout << "Cписок студентов загружен в файл" << endl;
		}
		//Вывод списка студентов на экран
		if (comand == 3)
		{
			LoadOnScreen(I);
		}
		//Загрузка списка предметов из файла
		if (comand == 4)
		{
			cout << "Cписок предметов загружен из файла" << endl;
		}
		//Загрузка списка предметов в файл
		if (comand == 5)
		{
			K->LoadSubjectsInFile("SubjectsOut.txt");
			cout << "Cписок предметов загружен в файл" << endl;
		}
		//Вывод списка предметов на экран
		if (comand == 6)
		{
			K->LoadOnScreenSubjects();
		}
		//Добавление информации об экзамене для студента
		if (comand == 7)
		{
			cout << "Введите фамилию студента";
			char ch[20];
			cin >> ch;
			cout << "Введите номер предмета";
			int number = 0;
			cin >> number;
			cout << "Введите оценку";
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
		cout << "1. Загрузить список студентов из файла" << endl;
		cout << "2. Загрузить список студентов в файл" << endl;
		cout << "3. Вывести список студентов на экран" << endl;
		cout << "4. Загрузить список предметов из файла" << endl;
		cout << "5. Загрузить список предметов в файл" << endl;
		cout << "6. Вывести список предметов на экран" << endl;
		cout << "7. Добавить экзамен" << endl;
		cout << "8. Удалить студента" << endl;
		cout << "9. Добавить студента" << endl;
		cout << "10. Изменить оценку" << endl;
		cout << "0. Выйти" << endl;
		cin >> comand;
	}
	system("pause");
}









