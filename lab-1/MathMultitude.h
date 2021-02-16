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

//������������� ��������� 
void initMathMult(void);

//������ �� �������� (����� � �������)
void showHelpList(void);

//�������� ������
void delMathMult(void);


/// ������������ � �����������
//�������� ���������
t_mult* CreatArray(char name);
//�������� ������������� ���������
void DelArray(char name);


/// ������ � �������� ���������
//������� �������� ���������
void CountElem(char name);
//�������� �������
void AddElem(t_mult *pMult, char *elem);
//������� �������
void DelElem(t_mult *pMult, char *elem);
//���������, ����������� �� ������� ���������
int CheckElem(t_mult *pMult, char *elem);


/// �������� ��� �����������
//�����������
t_mult *UnityArray(char nameExit, char nameA, char nameB);
//�����������
t_mult *InterArray(char nameExit, char nameA, char nameB);
//��������
t_mult *DiffArray(char nameExit, char nameA, char nameB);
//�������������� ��������
t_mult *SymmDeffArray(char nameExit, char nameA, char nameB);
//�������� ���������
int isIncludeArray(char nameA, char nameB);


/// ������������� �������� ��� ������������
//�������� ������ ������������ ��������
void ShowMultList(void);
//�������� ��������� ������������� ���������
void ShowElemListMult(t_mult *pMult);

#endif // !MATH_MULTITUDE_INCLUDE__
