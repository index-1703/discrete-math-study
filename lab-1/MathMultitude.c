#include "MathMultitude.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#pragma warning(disable:4996)

// Выводить список элементов множества после Операций над множествами
#define PRINT_MULT_OPER

#define SIZE_ELEMENT 81
#define MAX_ARGUMENTS 5
#define ENULL (t_element *)NULL
#define MNULL (t_mult *)NULL

t_mult *HeadMultList = (t_mult*)NULL;

static t_mult *findMult(char name) {
	t_mult *pMult;
	for ( pMult = HeadMultList; pMult != MNULL && pMult->name != name; pMult = pMult->next );
	return pMult;
}

static char getWords(char *arr, int arrSize) {
	char ch, endch = ' ';
	int size = 0;

	while ( (ch = getchar()) == ' ' );

	if ( ch == '\n' ) {
		arr[0] = '\0';
		return ch;
	}
	else if ( ch == '"' ) {
		endch = '"';
	}
	else if ( ch >= (char) 32 && ch <= (char) 126 && ch != '"' ) {
		arr[size++] = ch;
	}
	else {
		skip();
		return (char) 0;
	}

	while ( size < arrSize - 1 ) {
		ch = getchar();

		if ( ch == endch || ch == '\n' ) {
			break;
		}
		else if(ch >= (char) 32 && ch <= (char) 126 && ch != '"') {
			arr[size++] = ch;
		}
		else {
			skip();
			return (char) 0;
		}
	}

	if ( !(size < arrSize - 1) ) {
		if ( ch != '\n' ) skip();
		return (char) 0;
	}
	if ( endch == '"' ) ch = getchar();
	arr[size++] = 0;

	return ch;
}

static int skip() {
	char ch;
	int is = 0;
	while ( ch = getchar() != '\n' ) {
		if ( !isspace(ch) ) is = 1;
	}
	return is;
}

static int getArguments(char **word, int size) {
	int i = 0;
	char lastCh = ' ', *str = NULL;

	for ( i = 0; i < size; i++ ) word[i] = NULL;

	for ( i = 0, lastCh = ' '; i < size && lastCh == ' '; i++ ) {
		str = malloc(SIZE_ELEMENT);
		if ( !str ) break;
		lastCh = getWords(str, SIZE_ELEMENT);
		word[i] = str;
	}

	if ( !str ) {
		for ( int j = 0; j < i; j++ ) free(word[j]);
		printf("ERROR: Недостаточно памяти.\n");
		return 0;
	}else if ( lastCh == 0 ) {
		for ( int j = 0; j < size; j++ ) free(word[j]);
		printf("ERROR: Неверный синтаксис.\n");
		return 0;
	}
	else if ( i != size ) {
		if( lastCh != '\n' ) skip();
		for ( int j = 0; j <= i; j++ ) free(word[j]);
		printf("ERROR: Неверный синтаксис.\n");
		return 0;
	}
	else if ( lastCh != '\n' ) {
		if ( skip() ) {
			for ( int j = 0; j < size; j++ ) free(word[j]);
			printf("ERROR: Неверный синтаксис.\n");
			return 0;
		}
	}

	return 1;
}

static int Append(t_element **c, t_element **e, char *d) {
	char *str = malloc(sizeof(char) * SIZE_ELEMENT);
	t_element *q = malloc(sizeof(t_element));

	if ( !str || !q ) {
		free(str);
		free(q);
		printf("ERROR: Недостаточно памяти.\n");
		return 0;
	}

	strcpy(str, d);

	q->elem = str;
	q->next = ENULL;

	if ( *c == ENULL ) *c = q;
	else (*e)->next = q;

	*e = q;
	return 1;
}

//----------------------------------------------------------------------------------------------------
void initMathMult(void)
{
	char cmd[10], CH;

	setlocale(LC_ALL, "Russian");

	while ( 1 ) {
		CH = getWords(cmd, sizeof(cmd));
		if ( CH == 0 ) {
			printf("ERROR: Неверная команда.\n");
		}
		else {
			if ( !strcmp(cmd, "") ) {
				continue;
			}
			else if ( !strcmp(cmd, "NEW") ) {
				char *(arg[1]);
				if ( CH == '\n' ) { printf("ERROR: Неверный синтаксис.\n"); continue; }
				if ( getArguments(arg, sizeof(arg) / sizeof(arg[0])) ) {
					if ( strlen(arg[0]) == 1 ) {
						CreatArray(*(arg[0]));
					}
					else {
						printf("ERROR: Неверный синтаксис.\n");
					}
					free(arg[0]);
				}
			}
			else if ( !strcmp(cmd, "DEL") ) {
				char *(arg[1]);
				if ( CH == '\n' ) { printf("ERROR: Неверный синтаксис.\n"); continue; }
				if ( getArguments(arg, sizeof(arg) / sizeof(arg[0])) ) {
					if ( strlen(arg[0]) == 1 ) {
						DelArray(*(arg[0]));
					}
					else
					{
						printf("ERROR: Неверный синтаксис.\n");
					}
					free(arg[0]);
				}
			}
			else if ( !strcmp(cmd, "pow") ) {
				char *(arg[1]);
				if ( CH == '\n' ) { printf("ERROR: Неверный синтаксис.\n"); continue; }
				if ( getArguments(arg, sizeof(arg) / sizeof(arg[0])) ) {
					if ( strlen(arg[0]) == 1 ) {
						CountElem(*(arg[0]));
					}
					else
					{
						printf("ERROR: Неверный синтаксис.\n");
					}
					free(arg[0]);
				}
			}
			else if ( !strcmp(cmd, "add") ) {
				char *(arg[2]);
				if ( CH == '\n' ) { printf("ERROR: Неверный синтаксис.\n"); continue; }
				if ( getArguments(arg, sizeof(arg) / sizeof(arg[0])) ) {
					if ( strlen(arg[0]) == 1 ) {
						AddElem(findMult(*(arg[0])), arg[1]);
					}
					else
					{
						printf("ERROR: Неверный синтаксис.\n");
					}
					free(arg[0]);
				}
			}
			else if ( !strcmp(cmd, "del") ) {
				char *(arg[2]);
				if ( CH == '\n' ) { printf("ERROR: Неверный синтаксис.\n"); continue; }
				if ( getArguments(arg, sizeof(arg) / sizeof(arg[0])) ) {
					if ( strlen(arg[0]) == 1 ) {
						DelElem(findMult(*(arg[0])), arg[1]);
					}
					else
					{
						printf("ERROR: Неверный синтаксис.\n");
					}
					free(arg[0]);
				}
			}
			else if ( !strcmp(cmd, "che") ) {
				char *(arg[2]);
				if ( CH == '\n' ) { printf("ERROR: Неверный синтаксис.\n"); continue; }
				if ( getArguments(arg, sizeof(arg) / sizeof(arg[0])) ) {
					if ( strlen(arg[0]) == 1 ) {
						switch ( CheckElem(findMult(*(arg[0])), arg[1]) )
						{
						case 1:
							printf("Элемент найден\n");
							break;
						case 0:
							printf("Элемент не найден\n");
							break;
						case -1:
							printf("ERROR: Множество с таким именем не существует\n");
							break;
						default:
							break;
						}
					}
					else
					{
						printf("ERROR: Неверный синтаксис.\n");
					}
					free(arg[0]);
				}
			}
			else if ( !strcmp(cmd, "uni") ) {
				char *(arg[3]);
				if ( CH == '\n' ) { printf("ERROR: Неверный синтаксис.\n"); continue; }
				if ( getArguments(arg, sizeof(arg) / sizeof(arg[0])) ) {
					if ( strlen(arg[0]) == 1 && strlen(arg[1]) == 1 && strlen(arg[2]) == 1 ) {
						t_mult *pm = UnityArray(*(arg[0]), *(arg[1]), *(arg[2]));
#ifdef PRINT_MULT_OPER
						if ( pm ) ShowElemListMult(pm);
#endif // PRINT_MULT_OPER
					}
					else
					{
						printf("ERROR: Неверный синтаксис.\n");
					}
					free(arg[0]);
					free(arg[1]);
					free(arg[2]);
				}
			}
			else if ( !strcmp(cmd, "int") ) {
				char *(arg[3]);
				if ( CH == '\n' ) { printf("ERROR: Неверный синтаксис.\n"); continue; }
				if ( getArguments(arg, sizeof(arg) / sizeof(arg[0])) ) {
					if ( strlen(arg[0]) == 1 && strlen(arg[1]) == 1 && strlen(arg[2]) == 1 ) {
						t_mult *pm = InterArray(*(arg[0]), *(arg[1]), *(arg[2]));
#ifdef PRINT_MULT_OPER
						if ( pm ) ShowElemListMult(pm);
#endif // PRINT_MULT_OPER
					}
					else
					{
						printf("ERROR: Неверный синтаксис.\n");
					}
					free(arg[0]);
					free(arg[1]);
					free(arg[2]);
				}
			}
			else if ( !strcmp(cmd, "dif") ) {
				char *(arg[3]);
				if ( CH == '\n' ) { printf("ERROR: Неверный синтаксис.\n"); continue; }
				if ( getArguments(arg, sizeof(arg) / sizeof(arg[0])) ) {
					if ( strlen(arg[0]) == 1 && strlen(arg[1]) == 1 && strlen(arg[2]) == 1 ) {
						t_mult *pm = DiffArray(*(arg[0]), *(arg[1]), *(arg[2]));
#ifdef PRINT_MULT_OPER
						if ( pm ) ShowElemListMult(pm);
#endif // PRINT_MULT_OPER
					}
					else
					{
						printf("ERROR: Неверный синтаксис.\n");
					}
					free(arg[0]);
					free(arg[1]);
					free(arg[2]);
				}
			}
			else if ( !strcmp(cmd, "sym") ) {
				char *(arg[3]);
				if ( CH == '\n' ) { printf("ERROR: Неверный синтаксис.\n"); continue; }
				if ( getArguments(arg, sizeof(arg) / sizeof(arg[0])) ) {
					if ( strlen(arg[0]) == 1 && strlen(arg[1]) == 1 && strlen(arg[2]) == 1 ) {
						t_mult *pm = SymmDeffArray(*(arg[0]), *(arg[1]), *(arg[2]));
#ifdef PRINT_MULT_OPER
						if ( pm ) ShowElemListMult(pm);
#endif // PRINT_MULT_OPER
					}
					else
					{
						printf("ERROR: Неверный синтаксис.\n");
					}
					free(arg[0]);
					free(arg[1]);
					free(arg[2]);
				}
			}
			else if ( !strcmp(cmd, "inc") ) {
				char *(arg[2]);
				if ( CH == '\n' ) { printf("ERROR: Неверный синтаксис.\n"); continue; }
				if ( getArguments(arg, sizeof(arg) / sizeof(arg[0])) ) {
					if ( strlen(arg[0]) == 1 && strlen(arg[1]) == 1 ) {
						switch ( isIncludeArray(*(arg[0]), *(arg[1])) )
						{
						case 0:
							printf("Множество %c НЕ включено в %c\n", *(arg[0]), *(arg[1]));
							break;
						case 1:
							printf("Множество %c включено в %c\n", *(arg[0]), *(arg[1]));
							break;
						default:
							break;
						} 
					}
					else
					{
						printf("ERROR: Неверный синтаксис.\n");
					}
					free(arg[0]);
					free(arg[1]);
				}
			}
			else if ( !strcmp(cmd, "ls") ) {
				if ( CH != '\n' ) {
					if ( skip() ) {
						printf("Неверный синтаксис.\n");
						continue;
					}
				}
				ShowMultList();
			}
			else if ( !strcmp(cmd, "le") ) {
				char *(arg[1]);
				if ( CH == '\n' ) { printf("ERROR: Неверный синтаксис.\n"); continue; }
				if ( getArguments(arg, sizeof(arg) / sizeof(arg[0])) ) {
					if ( strlen(arg[0]) == 1 ) {
						ShowElemListMult(findMult(*(arg[0])));
					}
					else
					{
						printf("ERROR: Неверный синтаксис.\n");
					}
					free(arg[0]);
				}
			}
			else if ( !strcmp(cmd, "help") ) {
				if ( CH != '\n' ) {
					if ( skip() ) {
						printf("Неверный синтаксис.\n");
						continue;
					}
				}
				showHelpList();
			}
			else if ( !strcmp(cmd, "exit") ) {
				if ( CH != '\n' ) {
					if ( skip() ) {
						printf("Неверный синтаксис.\n");
						continue;
					}
				}
				break;
			}
			else {
				if ( CH != '\n' )
					skip();
				printf("ERROR: Неверная команда.\n");
			}
		}
	}

	delMathMult();
}

void showHelpList(void)
{
	printf("Пояснение:\n"
		"<имя_множ>\tНаименование множества одной буквой [A-Z | a-z]\n"
		"<элем>\t\tЭлементами множеств являются строки длиной до 80 символов (включительно),\n"
		"\t\tсоставленные из символов таблицы ASCII, кроме символа двойных кавычек\n"
		"\n"
		"Конструкторы и деструкторы:\n"
		"NEW <имя_множ>\tсоздание множества\n"
		"DEL <имя_множ>\tудаление существующего множества\n"
		"\n"
		"Методы и свойства множества:\n"
		"pow <имя_множ>\t\tвывести мощность множества\n"
		"add <имя_множ> <элем>\tдобавить элемент\n"
		"del <имя_множ> <элем>\tудалить элемент\n"
		"che <имя_множ> <элем>\tпроверить, принадлежит ли элемент множеству\n"
		"\n"
		"Операции над множествами:\n"
		"uni <имя_множ> <имя_множ1> <имя_множ2>\tобъединение\n"
		"int <имя_множ> <имя_множ1> <имя_множ2>\tпересечение\n"
		"dif <имя_множ> <имя_множ1> <имя_множ2>\tразность\n"
		"sym <имя_множ> <имя_множ1> <имя_множ2>\tсимметрическая разность\n"
		"inc <имя_множ1> <имя_множ2>\t\tпроверка включения\n"
		"\n"
		"Представление множеств для пользователя:\n"
		"ls\t\tпросмотр списка существующих множеств\n"
		"le <имя_множ>\tпросмотр элементов существующего множества\n"
		"\n"
		"help\tвывод списка команд\n"
		"exit\tвыход из приложения\n");
}

void DelAllElem(t_element *head)
{
	t_element *p1, *p2 = head;
	while ( p2 ) {
		p1 = p2;
		p2 = p2->next;
		free(p1->elem);
		free(p1);
	}
}

void delMathMult(void)
{
	t_mult *pMult = HeadMultList, *pMultNext;

	while ( pMult )
	{
		DelAllElem(pMult->array);
		pMultNext = pMult->next;
		free(pMult);
		pMult = pMultNext;
	}
}

//----------------------------------------------------------------------------------------------------
t_mult *CreatArray(char name)
{
	t_mult *pNewMult, *pMult = findMult(name);

	if ( pMult ) {
		printf("ERROR: Множество с таким именем существует\n");
		return MNULL;
	}

	// Создание множества
	pNewMult = malloc(sizeof(t_mult));
	if ( !pNewMult ) {
		printf("ERROR: Недостаточно памяти\n");
		return MNULL;
	}
	
	pNewMult->name = name;
	pNewMult->array = NULL;
	pNewMult->next = NULL;
	
	// Вставка множество сортировкой
	if ( !HeadMultList ) {
		HeadMultList = pNewMult;
	}
	else if ( HeadMultList->name > name ) {
		pNewMult->next = HeadMultList;
		HeadMultList = pNewMult;
	}
	else {
		for ( pMult = HeadMultList; pMult->next != MNULL && pMult->next->name < name; pMult = pMult->next );
		pNewMult->next = pMult->next;
		pMult->next = pNewMult;
	}

	return pNewMult;
}

void DelArray(char name)
{
	t_mult *pMult = NULL, *pMultPrev;

	if ( !HeadMultList ) {
		printf("ERROR: Множество с таким именем не существует\n");
	}else if ( HeadMultList->name == name ) {
		pMult = HeadMultList->next;
		DelAllElem(HeadMultList->array);
		HeadMultList = pMult;
	}
	else {
		for ( pMult = HeadMultList; pMult->next != MNULL && pMult->next->name < name; pMult = pMult->next );
		if ( pMult->next != MNULL && pMult->next->name == name ) {
			pMultPrev = pMult;
			pMult = pMult->next;
			pMultPrev->next = pMult->next;
			DelAllElem(pMult->array);
			free(pMult);
		}
		else {
			printf("ERROR: Множество с таким именем не существует\n");
		}
	}
}

void CountElem(char name)
{
	t_mult *pMult;
	t_element *pElem;
	int count;

	for ( pMult = HeadMultList; pMult != MNULL && pMult->name != name; pMult = pMult->next );
	if ( pMult ) {
		for ( pElem = pMult->array, count = 0; pElem != ENULL; pElem = pElem->next, count++ );

		printf("Мощность множества |%c| = %i\n", name, count);
	}
	else {
		printf("ERROR: Множество с таким именем не существует\n");
	}
}

void AddElem(t_mult *pMult, char *elem)
{
	t_element *pHeadElemList, *pNewElem, *pElem;

	if ( pMult ) {
		pHeadElemList = pMult->array;
		pNewElem = malloc(sizeof(t_element));
		if ( !pNewElem ) {
			printf("ERROR: Недостаточно памяти\n");
			free(elem);
			return;
		}

		pNewElem->elem = elem;
		pNewElem->next = ENULL;

		// Вставка элемента сортировкой
		if ( !pHeadElemList ) {
			pMult->array = pNewElem;
		}
		else if ( strcmp(pHeadElemList->elem, elem) > 0 ) {
			pNewElem->next = pHeadElemList;
			pMult->array = pNewElem;
		}
		else {
			for ( pElem = pHeadElemList; pElem->next != ENULL && strcmp(pElem->next->elem,elem) < 0; pElem = pElem->next );
			pNewElem->next = pElem->next;
			pElem->next = pNewElem;
		}
	}
	else {
		printf("ERROR: Множество с таким именем не существует\n");
		free(elem);
		return;
	}
}

void DelElem(t_mult *pMult, char *elem)
{
	t_element *pHeadElemList, *pElemPrev, *pElem;

	if ( pMult ) {
		pHeadElemList = pMult->array;

		if ( pHeadElemList )
			if ( strcmp(pHeadElemList->elem, elem) == 0 ) {
				pElem = pHeadElemList->next;
				pMult->array = pElem;
				free(pHeadElemList);

				free(elem);
				return;
			}
			else {
				for ( pElem = pHeadElemList; pElem->next != ENULL && strcmp(pElem->next->elem, elem) < 0; pElem = pElem->next );
				if ( pElem->next != ENULL ) {
					pElemPrev = pElem;
					pElem = pElem->next;
					pElemPrev->next = pElem->next;
					free(pElem->elem);
					free(pElem);

					free(elem);
					return;
				}
			}

		printf("ERROR: Такой элемента не существует в этом множестве\n");
	}
	else {
		printf("ERROR: Множество с таким именем не существует\n");
	}

	free(elem);
}

int CheckElem(t_mult *pMult, char *elem)
{
	t_element *pElem;
	int is = 0;

	if ( pMult ) {
		for ( pElem = pMult->array; pElem != ENULL && strcmp(pElem->elem, elem) == 0; pElem = pElem->next );
		if ( pElem != ENULL ) {
			is = 1;
		}
		else {
			is = 0;
		}
	}
	else {
		is = -1;
	}

	free(elem);
	return is;
}

//----------------------------------------------------------------------------------------------------
t_mult *UnityArray(char nameExit, char nameA, char nameB)
{
	t_mult *mA, *mB, *mC;
	t_element *pa, *pb, *c, *e, *p;
	int is;
	char *d;

	mA = findMult(nameA);
	mB = findMult(nameB);
	if ( !mA || !mB ) {
		if ( !mA ) printf("ERROR: Множество %c не найдено.\n", nameA);
		if ( !mB ) printf("ERROR: Множество %c не найдено.\n", nameB);
		return MNULL;
	}

	mC = CreatArray(nameExit);
	if ( !mC ) return MNULL;

	pa = mA->array;
	pb = mB->array;
	c = e = ENULL;
	
	while ( pa != ENULL && pb != ENULL )
	{
		is = strcmp(pa->elem, pb->elem);
		if ( is == -1 ) {
			d = pa->elem;
			pa = pa->next;
		}
		else if ( is == 1 ) {
			d = pb->elem;
			pb = pb->next;
		}
		else {
			d = pa->elem;
			pa = pa->next;
			pb = pb->next;
		}
		if ( !Append(&c, &e, d) ) {
			DelAllElem(c);
			DelArray(nameExit);
			return MNULL;
		}
	}

	p = ENULL;
	if ( pa != ENULL ) p = pa;
	if ( pb != ENULL ) p = pb;
	while ( p != ENULL )
	{
		if ( !Append(&c, &e, p->elem) ) {
			DelAllElem(c);
			DelArray(nameExit);
			return MNULL;
		}
		p = p->next;
	}

	mC->array = c;
	return mC;
}

t_mult *InterArray(char nameExit, char nameA, char nameB)
{
	t_mult *mA, *mB, *mC;
	t_element *pa, *pb, *c, *e;
	int is;

	mA = findMult(nameA);
	mB = findMult(nameB);
	if ( !mA || !mB ) {
		if ( !mA ) printf("ERROR: Множество %c не найдено.\n", nameA);
		if ( !mB ) printf("ERROR: Множество %c не найдено.\n", nameB);
		return MNULL;
	}

	mC = CreatArray(nameExit);
	if ( !mC ) return MNULL;

	pa = mA->array;
	pb = mB->array;
	c = e = ENULL;

	while ( pa != ENULL && pb != ENULL )
	{
		is = strcmp(pa->elem, pb->elem);
		if ( is == -1 ) {
			pa = pa->next;
		}
		else if ( is == 1 ) {
			pb = pb->next;
		}
		else {
			if ( !Append(&c, &e, pa->elem) ) {
				DelAllElem(c);
				DelArray(nameExit);
				return MNULL;
			}
			pa = pa->next;
			pb = pb->next;
		}
	}

	mC->array = c;
	return mC;
}

t_mult *DiffArray(char nameExit, char nameA, char nameB)
{
	t_mult *mA, *mB, *mC;
	t_element *pa, *pb, *c, *e;
	int is;

	mA = findMult(nameA);
	mB = findMult(nameB);
	if ( !mA || !mB ) {
		if ( !mA ) printf("ERROR: Множество %c не найдено.\n", nameA);
		if ( !mB ) printf("ERROR: Множество %c не найдено.\n", nameB);
		return MNULL;
	}

	mC = CreatArray(nameExit);
	if ( !mC ) return MNULL;

	pa = mA->array;
	pb = mB->array;
	c = e = ENULL;

	while ( pa != ENULL && pb != ENULL )
	{
		is = strcmp(pa->elem, pb->elem);
		if ( is == -1 ) {
			if ( !Append(&c, &e, pa->elem) ) {
				DelAllElem(c);
				DelArray(nameExit);
				return MNULL;
			}
			pa = pa->next;
		}
		else if ( is == 1 ) {
			pb = pb->next;
		}
		else {
			pa = pa->next;
			pb = pb->next;
		}
	}

	mC->array = c;
	return mC;

	return 0;
}

t_mult *SymmDeffArray(char nameExit, char nameA, char nameB)
{
	t_mult *mA, *mB, *mC;
	t_element *pa, *pb, *c, *e, *p;
	int is;

	mA = findMult(nameA);
	mB = findMult(nameB);
	if ( !mA || !mB ) {
		if ( !mA ) printf("ERROR: Множество %c не найдено.\n", nameA);
		if ( !mB ) printf("ERROR: Множество %c не найдено.\n", nameB);
		return MNULL;
	}

	mC = CreatArray(nameExit);
	if ( !mC ) return MNULL;

	pa = mA->array;
	pb = mB->array;
	c = e = ENULL;

	while ( pa != ENULL && pb != ENULL )
	{
		is = strcmp(pa->elem, pb->elem);
		if ( is == -1 ) {
			if ( !Append(&c, &e, pa->elem) ) {
				DelAllElem(c);
				DelArray(nameExit);
				return MNULL;
			}
			pa = pa->next;
		}
		else if ( is == 1 ) {
			if ( !Append(&c, &e, pb->elem) ) {
				DelAllElem(c);
				DelArray(nameExit);
				return MNULL;
			}
			pb = pb->next;
		}
		else {
			pa = pa->next;
			pb = pb->next;
		}
	}

	p = ENULL;
	if ( pa != ENULL ) p = pa;
	if ( pb != ENULL ) p = pb;
	while ( p != ENULL )
	{
		if ( !Append(&c, &e, p->elem) ) {
			DelAllElem(c);
			DelArray(nameExit);
			return MNULL;
		}
		p = p->next;
	}

	mC->array = c;
	return mC;
}

int isIncludeArray(char nameA, char nameB)
{
	t_mult *mA, *mB;
	t_element *pa, *pb;
	int is;
	mA = findMult(nameA);
	mB = findMult(nameB);

	if ( !mA || !mB ) {
		if ( !mA ) printf("ERROR: Множество %c не найдено.\n", nameA);
		if ( !mB ) printf("ERROR: Множество %c не найдено.\n", nameB);
		return -1;
	}

	pa = mA->array;
	pb = mB->array;

	while ( pa != ENULL && pb != ENULL )
	{
		is = strcmp(pa->elem, pb->elem);
		if ( is == -1 )
			return 0;
		else if ( is == 1 )
			pb = pb->next;
		else {
			pa = pa->next;
			pb = pb->next;
		}
	}

	return pa == ENULL;
}

//----------------------------------------------------------------------------------------------------
void ShowMultList(void)
{
	t_mult *mult = HeadMultList;
	printf("Список множеств:\n");
	if ( mult != MNULL ) {
		while ( mult )
		{
			printf("%c\n", mult->name);
			mult = mult->next;
		}
	}
	else {
		printf("Пусто.\n");
	}
}

void ShowElemListMult(t_mult *pMult)
{
	t_element *pElem;


	if ( pMult == MNULL ) {
		printf("ERROR: Множество с таким именем не существует\n");
		return;
	}
	
	printf("Элементы множества %c:\n", pMult->name);
	pElem = pMult->array;
	if ( pElem != ENULL ) {
		while ( pElem )
		{
			printf("%s\n", pElem->elem);
			pElem = pElem->next;
		}
	}
	else {
		printf("Пусто.\n");
	}
}
