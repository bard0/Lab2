#pragma once
#include <iostream>
#include <stdio.h>

template <class T>
class TStack // ����������� ������ ������: ������ ������, ��������� ����
{
private:
	T * mas;
	int MaxSize;//����������� ��������� ������
	int pos;//������� �������� �������� 
public:
	TStack(int _MaxSize = 1000) // ����������� �� ���������
	{
		MaxSize = _MaxSize;
		mas = new T[MaxSize];
		pos = -1;
	};
	void SetPos(int _pos) { pos = _pos; };
	~TStack();
	TStack(const TStack<T>& S);
	TStack<T>& operator=(const TStack<T>& S);
	int Full();
	int Empty();
	void Push(T el);
	T Pop();
	T Top();
	void Clear();
};
//
// ����������
//
template <class T>
TStack<T>::~TStack()
{
	delete[] mas;
	mas = NULL;
}
//
//	����������� �����������
//
template <class T>
TStack<T>::TStack(const TStack<T>& S)
{
	MaxSize = S.MaxSize;
	mas = new T[MaxSize];
	pos = S.pos;
	mas = S.mas;
}
//
// �������� ������������
//
template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T>& S)
{
	delete[] mas;
	MaxSize = S.MaxSize;
	mas = new T[MaxSize];
	pos = S.pos;
	mas = S.mas;
	return *(this);
}
//
// �������� �������
//
template <class T>
int TStack<T>::Full()
{
	return (pos == MaxSize - 1);
}
//
// �������� �������
//
template <class T>
int TStack<T>::Empty()
{
	return (pos == -1);
}
//
// �������� ������� � ����
//
template <class T>
void TStack<T>::Push(T el)
{
	mas[pos + 1] = el;
	pos++;
}
//
// �������� ������� ������� �� �����
//
template <class T>
T TStack<T>::Pop()
{
	return mas[pos--];
}
//
// ���������� �������
//
template <class T>
T TStack<T>::Top()
{
	return mas[pos];
}
//
// �������� ����
//
template <class T>
void TStack<T>::Clear()
{
	pos = -1;
}