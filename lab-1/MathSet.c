#include "MathSet.h"
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
#define MNULL (t_set *)NULL

t_set *HeadSetList = (t_set*)NULL;

static t_set *findSet(char name) {
	t_set *pSet;
	for ( pSet = HeadSetList; pSet != MNULL && pSet->name != name; pSet = pSet->next );
	return pSet;
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

	while ( size < arrSize ) {
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

	if ( !(size < arrSize) ) {
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
void initMathSet(void)
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
						AddElem(findSet(*(arg[0])), arg[1]);
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
						DelElem(findSet(*(arg[0])), arg[1]);
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
						switch ( CheckElem(findSet(*(arg[0])), arg[1]) )
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
						t_set *pm = UnityArray(*(arg[0]), *(arg[1]), *(arg[2]));
#ifdef PRINT_MULT_OPER
						if ( pm ) ShowElemListSet(pm);
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
						t_set *pm = InterArray(*(arg[0]), *(arg[1]), *(arg[2]));
#ifdef PRINT_MULT_OPER
						if ( pm ) ShowElemListSet(pm);
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
						t_set *pm = DiffArray(*(arg[0]), *(arg[1]), *(arg[2]));
#ifdef PRINT_MULT_OPER
						if ( pm ) ShowElemListSet(pm);
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
						t_set *pm = SymmDeffArray(*(arg[0]), *(arg[1]), *(arg[2]));
#ifdef PRINT_MULT_OPER
						if ( pm ) ShowElemListSet(pm);
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
				ShowSetList();
			}
			else if ( !strcmp(cmd, "le") ) {
				char *(arg[1]);
				if ( CH == '\n' ) { printf("ERROR: Неверный синтаксис.\n"); continue; }
				if ( getArguments(arg, sizeof(arg) / sizeof(arg[0])) ) {
					if ( strlen(arg[0]) == 1 ) {
						ShowElemListSet(findSet(*(arg[0])));
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

	delMathSet();
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

void delMathSet(void)
{
	t_set *pSet = HeadSetList, *pSetNext;

	while ( pSet )
	{
		DelAllElem(pSet->array);
		pSetNext = pSet->next;
		free(pSet);
		pSet = pSetNext;
	}
}

//----------------------------------------------------------------------------------------------------
t_set *CreatArray(char name)
{
	t_set *pNewSet, *pSet;

	if ( !(name >= 'A' && name <= 'Z' || name >= 'a' && name <= 'z') ) {
		printf("ERROR: Неверное имя.\n");
		return MNULL;
	}

	pSet = findSet(name);

	if ( pSet ) {
		printf("ERROR: Множество с таким именем существует\n");
		return MNULL;
	}

	// Создание множества
	pNewSet = malloc(sizeof(t_set));
	if ( !pNewSet ) {
		printf("ERROR: Недостаточно памяти\n");
		return MNULL;
	}
	
	pNewSet->name = name;
	pNewSet->array = NULL;
	pNewSet->next = NULL;
	
	// Вставка множество сортировкой
	if ( !HeadSetList ) {
		HeadSetList = pNewSet;
	}
	else if ( HeadSetList->name > name ) {
		pNewSet->next = HeadSetList;
		HeadSetList = pNewSet;
	}
	else {
		for ( pSet = HeadSetList; pSet->next != MNULL && pSet->next->name < name; pSet = pSet->next );
		pNewSet->next = pSet->next;
		pSet->next = pNewSet;
	}

	return pNewSet;
}

void DelArray(char name)
{
	t_set *pSet = NULL, *pSetPrev;

	if ( !HeadSetList ) {
		printf("ERROR: Множество с таким именем не существует\n");
	}else if ( HeadSetList->name == name ) {
		pSet = HeadSetList->next;
		DelAllElem(HeadSetList->array);
		HeadSetList = pSet;
	}
	else {
		for ( pSet = HeadSetList; pSet->next != MNULL && pSet->next->name < name; pSet = pSet->next );
		if ( pSet->next != MNULL && pSet->next->name == name ) {
			pSetPrev = pSet;
			pSet = pSet->next;
			pSetPrev->next = pSet->next;
			DelAllElem(pSet->array);
			free(pSet);
		}
		else {
			printf("ERROR: Множество с таким именем не существует\n");
		}
	}
}

void CountElem(char name)
{
	t_set *pSet;
	t_element *pElem;
	int count;

	for ( pSet = HeadSetList; pSet != MNULL && pSet->name != name; pSet = pSet->next );
	if ( pSet ) {
		for ( pElem = pSet->array, count = 0; pElem != ENULL; pElem = pElem->next, count++ );

		printf("Мощность множества |%c| = %i\n", name, count);
	}
	else {
		printf("ERROR: Множество с таким именем не существует\n");
	}
}

// ! Интересно, элемент длиной 80 не добавляет, а длиной 79 - да
void AddElem(t_set *pSet, char *elem)
{
	t_element *pHeadElemList, *pNewElem, *pElem;

	if ( pSet ) {
		pHeadElemList = pSet->array;
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
			pSet->array = pNewElem;
		}
		else if ( strcmp(pHeadElemList->elem, elem) > 0 ) {
			pNewElem->next = pHeadElemList;
			pSet->array = pNewElem;
		}
		else {
			for ( pElem = pHeadElemList; pElem->next != ENULL && strcmp(pElem->next->elem,elem) < 0; pElem = pElem->next );
			
			if ( strcmp(pElem->elem, elem) == 0 ) {
				free(elem);
				free(pNewElem);
				
				printf("ERROR: Данный элемент существует в множестве %c.\n", pSet->name);
				return;
			}

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

void DelElem(t_set *pSet, char *elem)
{
	t_element *pHeadElemList, *pElemPrev, *pElem;

	if ( pSet ) {
		pHeadElemList = pSet->array;

		if ( pHeadElemList )
			if ( strcmp(pHeadElemList->elem, elem) == 0 ) {
				pElem = pHeadElemList->next;
				pSet->array = pElem;
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

// ! Хорошая функция, все находит
int CheckElem(t_set *pSet, char *elem)
{
	t_element *pElem;
	int is = 0;

	if ( pSet ) {
		for ( pElem = pSet->array; pElem != ENULL && strcmp(pElem->elem, elem) != 0; pElem = pElem->next );
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
t_set *UnityArray(char nameExit, char nameA, char nameB)
{
	t_set *mA, *mB, *mC;
	t_element *pa, *pb, *c, *e, *p;
	int is;
	char *d;

	mA = findSet(nameA);
	mB = findSet(nameB);
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

t_set *InterArray(char nameExit, char nameA, char nameB)
{
	t_set *mA, *mB, *mC;
	t_element *pa, *pb, *c, *e;
	int is;

	mA = findSet(nameA);
	mB = findSet(nameB);
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

// ! Куда-то пропала концовка после применения dif
t_set *DiffArray(char nameExit, char nameA, char nameB)
{
	t_set *mA, *mB, *mC;
	t_element *pa, *pb, *c, *e;
	int is;

	mA = findSet(nameA);
	mB = findSet(nameB);
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

	while (pa != ENULL) {
		if ( !Append(&c, &e, pa->elem) ) {
				DelAllElem(c);
				DelArray(nameExit);
				return MNULL;
			}
		pa = pa->next;
	}

	mC->array = c;
	return mC;

	return 0;
}

t_set *SymmDeffArray(char nameExit, char nameA, char nameB)
{
	t_set *mA, *mB, *mC;
	t_element *pa, *pb, *c, *e, *p;
	int is;

	mA = findSet(nameA);
	mB = findSet(nameB);
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
	t_set *mA, *mB;
	t_element *pa, *pb;
	int is;
	mA = findSet(nameA);
	mB = findSet(nameB);
	
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
void ShowSetList(void)
{
	t_set *set = HeadSetList;
	printf("Список множеств:\n");
	if ( set != MNULL ) {
		while ( set )
		{
			printf("%c\n", set->name);
			set = set->next;
		}
	}
	else {
		printf("Пусто.\n");
	}
}

void ShowElemListSet(t_set *pSet)
{
	t_element *pElem;

	if ( pSet == MNULL ) {
		printf("ERROR: Множество с таким именем не существует\n");
		return;
	}
	
	printf("Элементы множества %c:\n %c = {\n", pSet->name, pSet->name);
	pElem = pSet->array;
	if ( pElem != ENULL ) {
		while ( pElem )
		{
			printf("\t\"%s\"", pElem->elem);
			pElem = pElem->next;
			printf(pElem == NULL ? "\n" : ",\n");
		}
		printf("}\n");
	}
	else {
		printf("Пусто.\n");
	}
}

