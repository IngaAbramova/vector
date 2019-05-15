#pragma once
#ifndef Students
#define Students
//Подключаем необходимые библиотеки
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
//Классы
class Information;
class GradesForTheExam;
class Subjects;
template <class T>
//Шаблон списка
class List
{
	friend class List<GradesForTheExam>;
	friend class GradesForTheExam;
	//Указатель на следующий элемент списка
	List<T> *next;
	//Информационное поле
	T data;
	//Конструктор
	List(T &v) { data = v; next = NULL; }
public:
	List<T> *get_next() { return next; }
	void set_next(List<T> *next) { this->next = next; }
	T get_data() { return data; }
	void set_data(T data) { this->data = data; }
	//Методы класса
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
	//Конструктор
	List()
	{
		next = NULL;
	};
	//Деструктор
	~List()
	{
		if (next != NULL) delete next;
	};
	//Функция добавления элемнта в список
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

//Оценки за экзамены для студента
class GradesForTheExam
{
	friend class List<GradesForTheExam>;
	//Номер предмета
	int subject;
	//Указатель на соответствующий элемент списка предметов
	List<Subjects> *Sub;
	//Оценка
	int mark;
public:
	//Методы класса
	int  ReadExam(std::ifstream &f, List<Subjects> *&R);
	void WriteExam(std::ofstream &f);
	void WriteExamOnScreen();
	//Конструктор
    GradesForTheExam()
	{
		Sub = NULL;
		subject = 0;
		mark = 0;
	};
	//Деструктор
	~GradesForTheExam()
	{
	};
};

//Информация о студенте: оценки и средний балл
class Information
{
	friend class List<Information>;
	//Имя студента
	string StudentName;
	//Количество сданных экзаменов
	int  CountOfExam;
	//Средний балл
	float Avg;
	//Указатель на список экзаменов для данного студента
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
	//Методы класса
	void Write(std::ofstream &f);
	void WriteOnScreen();
	int  Read(Information *a, std::ifstream &f, List<Subjects> *&R);
	//Конструктор
	Information()
	{
		CountOfExam = 0;
		Avg = 0;
		pass = NULL;
		StudentName = "NONAME";
	};
	//Деструктор
	~Information()
	{

	};
};
//Информация о предмете: номер и название
class Subjects 
{
public:
	//Номер предмета
	int NumberOfSubject;
	//Название предмета
	char NameOfSubject[20];
	//Конструктор
	Subjects()
	{
		NumberOfSubject = 0;
	};
	//Деструктор
	~Subjects()
	{
	};
	//Методы класса
	int ReadSubject(std::ifstream &f);
	void  WriteSubjects(std::ofstream &f);
	void WriteSubjectsOnScreen();
};

//Функция для ввода очередного студента из файла
int Information::Read(Information *a, std::ifstream &f, List<Subjects> *&R)
{
	//Если нет считывания из файла
	int flag = 1; 
	try
	{
		//Читаем имя
		f >> a->StudentName;
		//Проверяем на пустую строку
		if ((a->StudentName.length() == 0)||(a->StudentName == "NONAME")) return 1;
		//Читаем количество экзаменов
		f >> (a->CountOfExam);
		//Создаем переменную для записи количества экзаменов у студента
		float n = a->CountOfExam;
		//Обьявляем переменную - список предметов для студента
		List<GradesForTheExam> *b = new List<GradesForTheExam>();
		//Вызываем функцию чтения списка экзаменов для студента
		//Вычисляем средний балл студента: сумму всех оценок делим на количество экзаменов
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
//Функция считывания n экзаменов и добавление их список оценок
int List<GradesForTheExam>::ReadExamens(int Exames, std::ifstream &f, List<Subjects> *&R)
{
	//Количество экзаменов
	int n = 0;
	for (int i = 0; i < Exames; i++)
	{
		//Создаем информационную переменную
		GradesForTheExam a;
		//Вызываем функцию для ввода в переменную (а) очередного экзамена из файла (f)
		int flag = a.ReadExam(f, *&R);
		if (flag) 
		{
			//Дабавляем новый элемент в список
			AddElements(*&a);
			//Сумма оценок студента
			n += flag;
		}
		else break;
	}
	//Возвращаем сумму оценок
	return n;
}
//Функция считывания одного экзамена
int  GradesForTheExam::ReadExam(std::ifstream &f, List<Subjects> *&R)
{
	//Прочитаем из файла f номер предмета
	f >> (this->subject);
	//Прочитаем из файла f оценку
	f >> (this->mark);
	//Оценку записываем в переменную n
	int n = this->mark;
	List<Subjects> *q = R;
	for (q = R->next; q != NULL; q = q->next)
	{
		Subjects W = q->data;
		//Сравниваем номер предмета из списка предметов с номером предмета из списка экзаменов для данного студента
		if (this->subject == W.NumberOfSubject)
		{
			this->Sub = q;
		}
	}
	//Возвращаем оценку
	return n;
}
//Функция записи в файл информации о студенте
void   Information::Write(std::ofstream &f)
{
	//Вызываем функцию записи списка экзаменов для студента
	this->pass->WriteExamens(f);
	f << "\n";
}
//Функция записи в файл спсика экзаменов для одного студента
template<>
void List<GradesForTheExam>::WriteExamens(std::ofstream &f)
{
	//Создаем переменную - список экзаменов
	List<GradesForTheExam> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//Вызываем функцию записи информации об одном экзамене
		q->data.WriteExam(f);
	}
}
//Функция записи информации об экзамене
void GradesForTheExam::WriteExam(std::ofstream &f)
{
	Subjects S;
	S= (this->Sub)->data;
	f << this->subject << " " << S.NameOfSubject << "(" << this->mark << ");";
}
//Функция загрузки списка предметов из файла
template<>
int List<Subjects>::LoadSubjectsFromFile(const char *SubjectsIn)
{
	std::ifstream fin(SubjectsIn);
	//Количество предметов в списке
	int number = 0;
	while (fin)
	{
		//Срздаем переменную - элемент списка предметов
		Subjects subject;
		//Вызов функции чтения одного предмета из файла
		int flag = subject.ReadSubject(fin);
		if (!flag)
		{
			//Добавляем элемент в список
			AddElements(subject);
			//Прибавляем 1 к счетчику предметов
			number++;
		}
		else break;
	}
	return number; 
}
//Функция загрузки информации об одном предмете 
int  Subjects::ReadSubject(std::ifstream &f)
{
	try
	{
		//Читаем название
		f >> (NumberOfSubject);
		//Читаем номер
		f >> (NameOfSubject);
		//Проверяем на пустую строку
		if (strlen(NameOfSubject) == 0) return 1;
		return 0;
	}
	catch (...)
	{
		return 1;
	}
}
//Функция загрузки списка предметов в файл
template<>
void List<Subjects>::LoadSubjectsInFile(const char *SubjectsOut)
{
	std::ofstream f_out;
	//Открываем файл
	f_out.open(SubjectsOut, std::ios::app);
	f_out << "	Список предметов\n\nНачало:\n\n";
	//Создаем переменную - список предметов
	List<Subjects> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//Вызываем функцию записи информации об одном предмете в файл
		q->data.WriteSubjects(f_out);
	}
	f_out << "\nКонец\n\n";
}
//Функция загрузки информации об одном предмете 
void   Subjects::WriteSubjects(std::ofstream &f)
{
	f << "Номер - " << this->NumberOfSubject << "\n";
	f << "Название - " << this->NameOfSubject << "\n";
	f << "\n";
}
//Функция вывода информации об одном студенте
void   Information::WriteOnScreen()
{
	//Вызываем функцию вывода спсика экзаменов для студента
	this->pass->WriteExamensOnScreen();
	cout << "\n";
}
//Функция вывода спсика экзаменов для студента
template<>
void List<GradesForTheExam>::WriteExamensOnScreen()
{
	//Создаем прерменную - список экзаменов
	List<GradesForTheExam> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//Вызываем функцию вывода информации об одном экзамене
		q->data.WriteExamOnScreen();
	}
}
//Функция вывода информации об одном экзамене
void GradesForTheExam::WriteExamOnScreen()
{
	Subjects S;
	S = (this->Sub)->data;
	cout << this->subject << " " << S.NameOfSubject << "(" << this->mark << ");";
}
//Функция вывода списка предметов на экран
template<>
void List<Subjects>::LoadOnScreenSubjects()
{
	cout << "	Список предметов\n\nНачало:\n\n";
	//Список предметов
	List<Subjects> *q;
	for (q = this->next; q != NULL; q = q->next)
	{
		//Вызов функции вывода информации об одном предмете на экран
		q->data.WriteSubjectsOnScreen();
	}
	cout << "\nКонец\n\n";
}
//Функция вывода информации об одном предмете на экран
void   Subjects::WriteSubjectsOnScreen()
{
	cout << "Название - " << this->NameOfSubject << " ";
	cout << "Номер - " << this->NumberOfSubject << "\n";
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
//Функция добавления информации о новом экзамене для студента
template<>
void List<GradesForTheExam>::AddExam(char *ch, int number, int mark, List<Subjects> *&R)
{
	//Информация о экзамене
	GradesForTheExam a;
	//Записываем номер предмета
	a.subject = number;
	//Записываем оценку
	a.mark = mark;
	List<Subjects> *q = R;
	for (q = R->next; q != NULL; q = q->next)
	{
		Subjects W = q->data;
		//Сравниваем номер предмета из списка предметов с номером предмета из списка экзаменов для данного студента
		if (number == W.NumberOfSubject)
		{
			a.Sub = q;
		}
	}
	//Добавляем элемент в список
	AddElements(a);
}
template<>
//Функция считывания n экзаменов и добавление их список оценок
int List<GradesForTheExam>::AddExamens(List<Subjects> *&R, int Examens)
{
	//Количество экзаменов
	int n = 0;
	for (int i = 0; i < Examens; i++)
	{
		//Создаем информационную переменную
		GradesForTheExam a;
		cout << "Введите номер предмета";
		int number = 0;
		cin >> number;
		cout << "Введите оценку";
		int mark = 0;
		cin >> mark;
		a.mark = mark;
		a.subject = number;
List<Subjects> *q = R;
for (q = R->next; q != NULL; q = q->next)
{
	Subjects W = q->data;
	//Сравниваем номер предмета из списка предметов с номером предмета из списка экзаменов для данного студента
	if (number == W.NumberOfSubject)
	{
		a.Sub = q;
	}
}
			//Дабавляем новый элемент в список
			AddElements(*&a);
			//Сумма оценок студента
			n = n + mark;
	}
	//Возвращаем сумму оценок
	return n;
}
template<>
void List<GradesForTheExam>::ChangeExam()
{
	cout << "Введите номер предмета";
	int ch;
	cin >> ch;
	cout << "Введите новую оценку";
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
		cout << "Предмет не найден.\n";
		return;
	}
	p->data.mark = mark;
}
#endif