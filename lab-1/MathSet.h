#pragma once

#ifndef MATH_MULTITUDE_INCLUDE__
#define MATH_MULTITUDE_INCLUDE__

typedef struct t_element {
	char *elem;
	struct t_element *next;
}t_element;

typedef struct t_set {
	char name;
	t_element *array;
	struct t_set *next;
}t_set;

//инициализация программы 
void initMathSet(void);

//помощь по командам (Вывод в консоль)
void showHelpList(void);

//очищение памяти
void delMathSet(void);


/// Конструкторы и деструкторы
//создание множества
t_set* CreatArray(char name);
//удаление существующего множества
void DelArray(char name);


/// Методы и свойства множества
//вывести мощность множества
void CountElem(char name);
//добавить элемент
void AddElem(t_set *pSet, char *elem);
//удалить элемент
void DelElem(t_set *pSet, char *elem);
//проверить, принадлежит ли элемент множеству
int CheckElem(t_set *pSet, char *elem);


/// Операции над множествами
//объединение
t_set *UnityArray(char nameExit, char nameA, char nameB);
//пересечение
t_set *InterArray(char nameExit, char nameA, char nameB);
//разность
t_set *DiffArray(char nameExit, char nameA, char nameB);
//симметрическая разность
t_set *SymmDeffArray(char nameExit, char nameA, char nameB);
//проверка включения
int isIncludeArray(char nameA, char nameB);


/// Представление множеств для пользователя
//просмотр списка существующих множеств
void ShowSetList(void);
//просмотр элементов существующего множества
void ShowElemListSet(t_set *pSet);

#endif // !MATH_MULTITUDE_INCLUDE__
