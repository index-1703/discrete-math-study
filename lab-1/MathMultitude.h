#pragma once

#ifndef MATH_MULTITUDE_INCLUDE__
#define MATH_MULTITUDE_INCLUDE__

typedef struct t_element {
	char *elem;
	struct t_element *next;
}t_element;

typedef struct t_mult {
	char name;
	t_element *array;
	struct t_mult *next;
}t_mult;

//инициализация программы 
void initMathMult(void);

//помощь по командам (Вывод в консоль)
void showHelpList(void);

//очищение памяти
void delMathMult(void);


/// Конструкторы и деструкторы
//создание множества
t_mult* CreatArray(char name);
//удаление существующего множества
void DelArray(char name);


/// Методы и свойства множества
//вывести мощность множества
void CountElem(char name);
//добавить элемент
void AddElem(t_mult *pMult, char *elem);
//удалить элемент
void DelElem(t_mult *pMult, char *elem);
//проверить, принадлежит ли элемент множеству
int CheckElem(t_mult *pMult, char *elem);


/// Операции над множествами
//объединение
t_mult *UnityArray(char nameExit, char nameA, char nameB);
//пересечение
t_mult *InterArray(char nameExit, char nameA, char nameB);
//разность
t_mult *DiffArray(char nameExit, char nameA, char nameB);
//симметрическая разность
t_mult *SymmDeffArray(char nameExit, char nameA, char nameB);
//проверка включения
int isIncludeArray(char nameA, char nameB);


/// Представление множеств для пользователя
//просмотр списка существующих множеств
void ShowMultList(void);
//просмотр элементов существующего множества
void ShowElemListMult(t_mult *pMult);

#endif // !MATH_MULTITUDE_INCLUDE__
