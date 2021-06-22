#define debug 0
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <cstdlib>
using namespace std;

class FIO {
public:
	char* fam;
	char* name;
	char* fath;
	FIO();
	~FIO();
};
FIO::FIO() {
	if (debug == 1)
		cout << "Debug: " << "Конструктор FIO" << endl;
	fam = new char[50];
	strcpy(fam, " ");
	name = new char[50];
	strcpy(name, " ");
	fath = new char[50];
	strcpy(fath, " ");
}
FIO::~FIO() {
	if (debug == 1)
		cout << "Debug: " << "Деструктор FIO" << endl;
	delete[] fam;
	delete[] name;
	delete[] fath;
}

class Common {
private:
	FIO fio;
public:
	~Common();
	Common();
	char* get_fam() { return fio.fam; };
	void set_fam(char* new_fam);
	char* get_name() { return fio.name; };
	void set_name(char* new_name);
	char* get_fath() { return fio.fath; };
	void set_fath(char* new_fath);
	void delete_fio();
	FIO get_fio() { return fio; }
};
Common::Common() {
	if (debug == 1)
		cout << "Debug: " << "Конструктор Common" << endl;
}
Common::~Common() {
	if (debug == 1)
		cout << "Debug: " << "Денструктор Common" << endl;
}
void Common::set_fam(char* new_fam) {
	fio.fam = new char[strlen(new_fam) + 1];
	strcpy(fio.fam, new_fam);
}
void Common::set_name(char* new_name) {
	fio.name = new char[strlen(new_name) + 1];
	strcpy(fio.name, new_name);
}
void Common::set_fath(char* new_fath) {
	fio.fath = new char[strlen(new_fath) + 1];
	strcpy(fio.fath, new_fath);
}

class Leaner : public Common {
private:
	char* faculty;
	int group;
public:
	friend boolean operator==(Leaner& leaner, FIO fio);
	static int count;
	Leaner();
	Leaner(char* fam, char* name, char* fath, char* fac, int group);
	~Leaner();
	char* get_faculty() { return faculty; };
	void set_faculty(char* new_faculty);
	int get_group() { return group; };
	void set_group(int new_group);
	void operator=(Leaner& COPY);
	friend std::ostream& operator<<(std::ostream& output, Leaner& ob) {
		output << left << setw(11) << ob.get_fam() << left << setw(11) << ob.get_name() << left << setw(11) << ob.get_fath() << left << setw(11) << ob.get_faculty() << left << setw(11) << ob.get_group() << endl;
		return output;
	}
	boolean by_fam(char* fam);
	boolean by_group(int group);
	boolean by_faculty(char* faculty);
};
int Leaner::count = 0;
Leaner::Leaner() {
	if (debug == 1)
	cout << "Debug: " << "Конструктор Leaner" << endl;
	faculty = new char[50];
	strcpy(faculty, " ");
	group = 0;
	count++;
}
Leaner::Leaner(char* fam, char* name, char* fath, char* fac, int group) {
	if (debug == 1)
		cout << "Debug: " << "Конструктор Leaner (с параметрами)" << endl;
	this->set_fam(fam);
	this->set_name(name);
	this->set_fath(fath);
	faculty = new char[strlen(fac) + 1];
	strcpy(faculty, fac);
	this->group = group;
	count++;
}
Leaner::~Leaner() {
	if (debug == 1)
	cout << "Debug: " << "Деструктор Leaner" << endl;
	delete[] faculty;
	group = 0;
	count--;
}
void Leaner::set_faculty(char* new_faculty) {
	this->faculty = new char[strlen(new_faculty) + 1];
	strcpy(this->faculty, new_faculty);
}
void Leaner::set_group(int new_group) {
	this->group = new_group;
}

Leaner* add_leaner(Leaner*& leaners) {
	int start = Leaner::count;
	Leaner* pointer = leaners;
	leaners = new Leaner[start + 1];
	if (Leaner::count != 1) {
		for (int i = 0; i < start; i++) {
			leaners[i].set_fam(pointer[i].get_fam());
			leaners[i].set_name(pointer[i].get_name());
			leaners[i].set_fath(pointer[i].get_fath());
			leaners[i].set_faculty(pointer[i].get_faculty());
			leaners[i].set_group(pointer[i].get_group());
		}
	}
	delete[] pointer;
	char buff[50];
	printf("%s", "Фамилия: ");
	while (getc(stdin) != '\n');
	scanf("%50[^\n]%*c", buff);
	leaners[Leaner::count - 1].set_fam(buff);

	printf("%s", "Имя: ");
	scanf("%50[^\n]%*c", buff);
	leaners[Leaner::count - 1].set_name(buff);

	printf("%s", "Отчество: ");
	scanf("%50[^\n]%*c", buff);
	leaners[Leaner::count - 1].set_fath(buff);

	printf("%s", "Факультет: ");
	scanf("%50[^\n]%*c", buff);
	leaners[Leaner::count - 1].set_faculty(buff);

	int buffg;
	printf("%s", "Группа: ");
	scanf("%i", &buffg);
	leaners[Leaner::count - 1].set_group(buffg);
	return leaners;
}
boolean Leaner::by_fam(char* fam) {
	if (strcmp(this->get_fam(), fam) == 0) {
		return true;
	}
	else {
		return false;
	}
}
boolean Leaner::by_group(int group) {
	if (this->get_group() == group) {
		return true;
	}
	else {
		return false;
	}
}
boolean Leaner::by_faculty(char* faculty) {
	if (strcmp(this->faculty, faculty) == 0) {
		return true;
	}
	else {
		return false;
	}
}
void Leaner::operator=(Leaner& copy) {
	this->set_fam(copy.get_fam());
	this->set_name(copy.get_name());
	this->set_fath(copy.get_fath());
	this->set_faculty(copy.get_faculty());
	this->set_group(copy.get_group());

}

enum course { none, spintex, ipovs };
class Teacher : public Common {
private:
	char* cafedra;
	course course;
public:
	friend boolean operator==(Teacher& teacher, FIO fio);
	static int count;
	Teacher();
	Teacher(char* fam, char* name, char* fath, char* cafedra, char* course);
	~Teacher();
	char* get_cafedra() { return cafedra; };
	void set_cafedra(char* new_cafedra);
	char* get_course() {
		char* ret = new char[20];
		switch (course) {
			case (spintex):
				strcpy(ret, "spintex");
				break;
			case (ipovs):
				strcpy(ret, "ipovs");
				break;
			case (none):
				strcpy(ret, "none");
				break;
		}
		return ret;
		delete[] ret;
	};
	void set_course(char* new_course);
	void operator=(Teacher& copy);
	friend std::ostream& operator<<(std::ostream& output, Teacher& ob) {
		output << left << setw(11) << ob.get_fam() << left << setw(11) << ob.get_name() << left << setw(11) << ob.get_fath() << left << setw(11) << ob.get_cafedra() << left << setw(11) << ob.get_course() << endl;
		return output;
	}
	boolean by_fam(char* fam);
};
Teacher::Teacher() {
	if (debug == 1)
		cout << "Debug: " << "Конструктор Teacher" << endl;
	cafedra = new char[50];
	strcpy(cafedra, " ");
	course = none;
	count++;
}
Teacher::Teacher(char* fam, char* name, char* fath, char* cafedra, char* course) {
	if (debug == 1)
		cout << "Debug: " << "Конструктор Teacher (с параметрами)" << endl;
	this->set_fam(fam);
	this->set_name(name);
	this->set_fath(fath);
	this->set_cafedra(cafedra);
	this->set_course(course);
	count++;
}
Teacher::~Teacher() {
	if (debug == 1)
		cout << "Debug: " << "Деструктор Teacher" << endl;
	delete[] cafedra;
	course = none;
	count--;
}
void Teacher::set_cafedra(char* new_cafedra) {
	cafedra = new char[strlen(new_cafedra) + 1];
	strcpy(cafedra, new_cafedra);
}
void Teacher::set_course(char* course) {
	if (strcmp(course, "spintex") == 0)
		this->course = spintex;
	else if (strcmp(course, "ipovs") == 0)
		this->course = ipovs;
	else this->course = none;
}
int Teacher::count = 0;
Teacher* add_teacher(Teacher*& teachers) {
	int start = Teacher::count;
	Teacher* pointer = teachers;
	teachers = new Teacher[start + 1];
	if (Teacher::count != 1) {
		for (int i = 0; i < start; i++) {
			teachers[i].set_fam(pointer[i].get_fam());
			teachers[i].set_name(pointer[i].get_name());
			teachers[i].set_fath(pointer[i].get_fath());
			teachers[i].set_cafedra(pointer[i].get_cafedra());
			teachers[i].set_course(pointer[i].get_course());
		}
	}
	delete[] pointer;
	char buff[50];
	printf("%s", "Фамилия: ");
	while (getc(stdin) != '\n');
	scanf("%50[^\n]%*c", buff);
	teachers[Teacher::count - 1].set_fam(buff);

	printf("%s", "Имя: ");
	scanf("%50[^\n]%*c", buff);
	teachers[Teacher::count - 1].set_name(buff);

	printf("%s", "Отчество: ");
	scanf("%50[^\n]%*c", buff);
	teachers[Teacher::count - 1].set_fath(buff);

	printf("%s", "Кафедра: ");
	scanf("%50[^\n]%*c", buff);
	teachers[Teacher::count - 1].set_cafedra(buff);

	printf("%s", "Курс: ");
	scanf("%50[^\n]%*c", buff);
	teachers[Teacher::count - 1].set_course(buff);
	if (debug==1)
	cout << "Debug: teachers[Leaner::count - 1] = " << teachers[Teacher::count - 1] << endl;
	return teachers;
}
boolean Teacher::by_fam(char* fam) {
	if (strcmp(this->get_fam(), fam) == 0) {
		return true;
	}
	else {
		return false;
	}
}
void Teacher::operator=(Teacher& copy) {
	this->set_fam(copy.get_fam());
	this->set_name(copy.get_name());
	this->set_fath(copy.get_fath());
	this->set_cafedra(copy.get_cafedra());
	this->set_course(copy.get_course());

}

Leaner* load_leaners(char* file_name)
{
	Leaner* leaners = new Leaner[0];
	FILE* file_pointer;
	char buffs[50];
	// Проверка на прошлые записи + загрузка
	if ((file_pointer = fopen(file_name, "rb+")) == NULL) {
		printf("Файла нет!\n");
		return leaners;
	}
	else {
		printf("Файл найден!\n");
		if ((file_pointer = fopen(file_name, "r")) == NULL)
		{
			perror("Ошибка открытия файла");
		}
		// Перебор всего файла
		int intBuff;
		char buff[50];
		fscanf(file_pointer, "%s\n", buff);
		intBuff = 0;
		sscanf(buff, "%d", &intBuff);

		int start = intBuff;
		Leaner* result = new Leaner[start];
		for (int i = 0; !feof(file_pointer); i++)
		{
			fscanf(file_pointer, "%s\n", buff);
			result[i].set_name(buff);

			fscanf(file_pointer, "%s\n", buff);
			result[i].set_fam(buff);

			fscanf(file_pointer, "%s\n", buff);
			result[i].set_fath(buff);

			fscanf(file_pointer, "%s\n", buff);
			result[i].set_faculty(buff);

			fscanf(file_pointer, "%s\n", buff);
			int intBuff = 0;
			sscanf(buff, "%d", &intBuff);
			result[i].set_group(intBuff);
		}
		fclose(file_pointer); // закрыть файл
		printf("Данные успешно загружены!\n");
		if (debug == 1)
			cout << "Debug: " <<"Leaner::count = " << Leaner::count << endl;
		delete[] leaners;
		return result;
	}
};
boolean save_leaners(Leaner* massive, char* file_name)
{
	Leaner* tw;
	FILE* file_pointer;
	tw = massive;
	if ((file_pointer = fopen(file_name, "w")) == NULL)
	{
		perror("Ошибка открытия файла: режим save_txt");
		return false;
	}
	// запись строк в текстовый файл
	fprintf(file_pointer, "%i\n", Leaner::count);
	for (tw = massive; tw < massive + Leaner::count; tw++)
	{
		fprintf(file_pointer, "%s\n", tw->get_name());
		fprintf(file_pointer, "%s\n", tw->get_fam());
		fprintf(file_pointer, "%s\n", tw->get_fath());
		fprintf(file_pointer, "%s\n", tw->get_faculty());
		fprintf(file_pointer, "%i\n", tw->get_group());
	}
	fclose(file_pointer);
	return true;
};
Teacher* load_teachers(char* file_name)
{
	Teacher* teachers = new Teacher[0];
	FILE* file_pointer;
	char buffs[50];
	// Проверка на прошлые записи + загрузка
	if ((file_pointer = fopen(file_name, "rb+")) == NULL) {
		printf("Файла нет!\n");
		return teachers;
	}
	else {
		printf("Файл найден!\n");
		if ((file_pointer = fopen(file_name, "r")) == NULL)
		{
			perror("Ошибка открытия файла");
		}
		// Перебор всего файла
		int intBuff;
		char buff[50];
		fscanf(file_pointer, "%s\n", buff);
		intBuff = 0;
		sscanf(buff, "%d", &intBuff);

		int start = intBuff;
		Teacher* result = new Teacher[start];
		for (int i = 0; !feof(file_pointer); i++)
		{
			fscanf(file_pointer, "%s\n", buff);
			result[i].set_name(buff);

			fscanf(file_pointer, "%s\n", buff);
			result[i].set_fam(buff);

			fscanf(file_pointer, "%s\n", buff);
			result[i].set_fath(buff);

			fscanf(file_pointer, "%s\n", buff);
			result[i].set_cafedra(buff);

			fscanf(file_pointer, "%s\n", buff);
			result[i].set_course(buff);
		}
		fclose(file_pointer); // закрыть файл
		printf("Данные успешно загружены!\n");
		if (debug == 1)
			cout << "Debug: " << "Teacher::count = " << Teacher::count << endl;
		delete[] teachers;
		return result;
	}
};
boolean save_teachers(Teacher* massive, char* file_name)
{
	Teacher* tw;
	FILE* file_pointer;
	tw = massive;
	if ((file_pointer = fopen(file_name, "w")) == NULL)
	{
		perror("Ошибка открытия файла: режим save_txt");
		return false;
	}
	// запись строк в текстовый файл
	fprintf(file_pointer, "%i\n", Teacher::count);
	for (tw = massive; tw < massive + Teacher::count; tw++)
	{
		fprintf(file_pointer, "%s\n", tw->get_name());
		fprintf(file_pointer, "%s\n", tw->get_fam());
		fprintf(file_pointer, "%s\n", tw->get_fath());
		fprintf(file_pointer, "%s\n", tw->get_cafedra());
		fprintf(file_pointer, "%s\n", tw->get_course());
	}
	fclose(file_pointer);
	return true;
};

void alph_order_leaners(Leaner* leaners) {
	int start = Leaner::count;
	Leaner new_leaners;
	for (int i = 0; i < start; i++) {
		for (int j = i + 1; j < start; j++) {
			if (strcmp(leaners[i].get_fam(), leaners[j].get_fam()) > 0) {
				new_leaners = leaners[i];
				leaners[i] = leaners[j];
				leaners[j] = new_leaners;
			}
		}
	}
}

void alph_order_teachers(Teacher* teachers) {
	int start = Teacher::count;
	Teacher new_teachers;
	for (int i = 0; i < start; i++) {
		for (int j = i + 1; j < start; j++) {
			if (strcmp(teachers[i].get_fam(), teachers[j].get_fam()) > 0) {
				new_teachers = teachers[i];
				teachers[i] = teachers[j];
				teachers[j] = new_teachers;
			}
		}
	}
}

void group_order_leaners(Leaner* leaners) {
	int start = Leaner::count;
	Leaner new_leaners;
	for (int i = 0; i < start; i++) {
		for (int j = i + 1; j < start; j++) {
			if (leaners[i].get_group() > leaners[j].get_group()) {
				new_leaners = leaners[i];
				leaners[i] = leaners[j];
				leaners[j] = new_leaners;
			}
		}
	}
}

boolean operator==(Leaner& first, FIO* fio) {
	if (strcmp(first.get_fam(), fio->fam) == 0 & strcmp(first.get_name(), fio->name) == 0 & strcmp(first.get_fath(), fio->fath) == 0)
		return true;
	else
		return false;
}
boolean operator==(Teacher& first, FIO* fio) {
	if (strcmp(first.get_fam(), fio->fam) == 0 & strcmp(first.get_name(), fio->name) == 0 & strcmp(first.get_fath(), fio->fath) == 0)
		return true;
	else
		return false;
}
void main() {
	Leaner* leaners = new Leaner[0];
	Teacher* teachers = new Teacher[0];
	FILE* file_pointer;
	setlocale(LC_ALL, "Rus");

	char* filename = new char[50];
	strcpy(filename, "leaners.txt");
	leaners = load_leaners(filename);
	strcpy(filename, "teachers.txt");
	teachers = load_teachers(filename);


	while (TRUE) {
		cout << "1 - New leaner" << endl
			<< "2 - New teacher" << endl
			<< "3 - Table leaner" << endl
			<< "4 - Table teachers" << endl
			<< "5 - Find by fam leaner" << endl
			<< "6 - Find by fam teacher" << endl
			<< "7 - Find by group leaner" << endl
			<< "8 - Find by faculty leaner" << endl
			<< "9 - Alph order leaners" << endl
			<< "10 - Alph order teachers" << endl
			<< "11 - Group order leaners" << endl
			<< "12 - Name + fam + fath filter leaners" << endl
			<< "13 - Name + fam + fath teachers" << endl
			<< "9 - Эталонный обьект" << endl
			<< "14 - Закрыть" << endl;
		int buff;
		scanf("%i", &buff);
		switch (buff) {
		case 1: {
			leaners = add_leaner(leaners);
			break;
		}
		case 2: {
			teachers = add_teacher(teachers);
			break;
		}
		case 3: {
			printf("\n\n%-10s %-10s %-10s %-10s %-10s %s\n", "Номер", "Фамилия", "Имя", "Отчество", "Факультет", "Номер группы");
			printf("%s\n", "-----------------------------------------------------------------");
			for (int i = 0; i < Leaner::count; i++) {
				printf("%-11d", i + 1);
				cout << leaners[i];
			}
			printf("%s\n", "-----------------------------------------------------------------");
			printf("Количество записей в базе: %i\n\n\n", Leaner::count);
			break;
		}
		case 4: {
			printf("\n\n%-10s %-10s %-10s %-10s %-10s %s\n", "Номер", "Фамилия", "Имя", "Отчество", "Кафедра", "Курс");
			printf("%s\n", "-----------------------------------------------------------------");
			for (int i = 0; i < Teacher::count; i++) {
				printf("%-11d", i + 1);
				cout << teachers[i];
			}
			printf("%s\n", "-----------------------------------------------------------------");
			printf("Количество записей в базе: %i\n\n\n", Teacher::count);
			break;
		}
		case 5: {
			char buff[50];
			printf("Введите фамилию: ");
			while (getc(stdin) != '\n');
			scanf("%50[^\n]%*c", buff);
			printf("\n\n%-10s %-10s %-10s %-10s %-10s %s\n", "Номер", "Фамилия", "Имя", "Отчество", "Факультет", "Номер группы");
			printf("%s\n", "-----------------------------------------------------------------");
			for (int i = 0; i < Leaner::count; i++) {
				if (leaners[i].by_fam(buff)) {
					printf("%-10d", i + 1);
					cout << leaners[i];
				}
			}
			printf("%s\n", "-----------------------------------------------------------------");
			break;
		}
		case 6: {
			char buff[50];
			printf("Введите фамилию: ");
			while (getc(stdin) != '\n');
			scanf("%50[^\n]%*c", buff);
			printf("\n\n%-10s %-10s %-10s %-10s %-10s %s\n", "Номер", "Фамилия", "Имя", "Отчество", "Кафедра", "Курс");
			printf("%s\n", "-----------------------------------------------------------------");
			for (int i = 0; i < Teacher::count; i++) {
				if (teachers[i].by_fam(buff)) {
					printf("%-10d", i + 1);
					cout << teachers[i];
				}
			}
			printf("%s\n", "-----------------------------------------------------------------");
			break;
		}
		case 7: {
			int buff;
			printf("Введите группу: ");
			cin >> buff;
			printf("\n\n%-10s %-10s %-10s %-10s %-10s %s\n", "Номер", "Фамилия", "Имя", "Отчество", "Факультет", "Номер группы");
			printf("%s\n", "-----------------------------------------------------------------");
			for (int i = 0; i < Leaner::count; i++) {
				if (leaners[i].by_group(buff)) {
					printf("%-10d", i + 1);
					cout << leaners[i];
				}
			}
			printf("%s\n", "-----------------------------------------------------------------");
			break;
		}
		case 8: {
			char buff[50];
			printf("Введите факультет: ");
			while (getc(stdin) != '\n');
			scanf("%50[^\n]%*c", buff);
			printf("\n\n%-10s %-10s %-10s %-10s %-10s %s\n", "Номер", "Фамилия", "Имя", "Отчество", "Факультет", "Номер группы");
			printf("%s\n", "-----------------------------------------------------------------");
			for (int i = 0; i < Leaner::count; i++) {
				if (leaners[i].by_faculty(buff)) {
					printf("%-10d", i + 1);
					cout << leaners[i];
				}
			}
			printf("%s\n", "-----------------------------------------------------------------");
			break;
		}
		case 9: {
			alph_order_leaners(leaners);
			break;
		}
		case 10: {
			alph_order_teachers(teachers);
			break;
		}
		case 11: {
			group_order_leaners(leaners);
			break;
		}
		case 12: {
			char buff[50];
			FIO* fio = new FIO[1];
			cout << "fam: ";
			cin >> buff;
			strcpy(fio->fam, buff);
			cout << "name: ";
			cin >> buff;
			strcpy(fio->name, buff);
			cout << "fath: ";
			cin >> buff;
			strcpy(fio->fath, buff);
			printf("\n\n%-10s %-10s %-10s %-10s %-10s %s\n", "Номер", "Фамилия", "Имя", "Отчество", "Факультет", "Номер группы");
			printf("%s\n", "-----------------------------------------------------------------");
			for (int i = 0; i < Leaner::count; i++) {
				if (leaners[i] == fio) {
					printf("%-10d", i + 1);
					cout << leaners[i];
				}
			}
			printf("%s\n", "-----------------------------------------------------------------");
			delete[] fio;
			break;
		}
		case 13: {
			char buff[50];
			FIO* fio = new FIO[1];
			cout << "fam: ";
			cin >> buff;
			strcpy(fio->fam, buff);
			cout << "name: ";
			cin >> buff;
			strcpy(fio->name, buff);
			cout << "fath: ";
			cin >> buff;
			strcpy(fio->fath, buff);
			printf("\n\n%-10s %-10s %-10s %-10s %-10s %s\n", "Номер", "Фамилия", "Имя", "Отчество", "Кафедра", "Курс");
			printf("%s\n", "-----------------------------------------------------------------");
			for (int i = 0; i < Teacher::count; i++) {
				if (teachers[i] == fio) {
					printf("%-10d", i + 1);
					cout << teachers[i];
				}
			}
			printf("%s\n", "-----------------------------------------------------------------");
			delete[] fio;
			break;
		}
		case 14: {
			if (Leaner::count != 0) {
				char* filename = new char[50];
				strcpy(filename, "leaners.txt");
				save_leaners(leaners, filename);
			}
			if (Teacher::count != 0) {
				char* filename = new char[50];
				strcpy(filename, "teachers.txt");
				save_teachers(teachers, filename);
			}
			delete[] leaners;
			delete[] teachers;
			return;
		}
		}
		buff = 0;
	}
}
