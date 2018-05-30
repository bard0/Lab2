#pragma once
#include <iostream>
#include <stdio.h>

template <class T>
class TStack // Организация данных такова: Первым пришел, последним ушел
{
private:
	T * mas;
	int MaxSize;//Максимально возможный размер
	int pos;//Позиция верхнего элемента 
public:
	TStack(int _MaxSize = 1000) // Конструктор по умолчанию
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
// Деструктор
//
template <class T>
TStack<T>::~TStack()
{
	delete[] mas;
	mas = NULL;
}
//
//	Конструктор копирования
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
// Оператор присваивания
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
// Проверка полноты
//
template <class T>
int TStack<T>::Full()
{
	return (pos == MaxSize - 1);
}
//
// Проверка пустоты
//
template <class T>
int TStack<T>::Empty()
{
	return (pos == -1);
}
//
// Положить элемент в стек
//
template <class T>
void TStack<T>::Push(T el)
{
	mas[pos + 1] = el;
	pos++;
}
//
// Вытащить верхний элемент из стека
//
template <class T>
T TStack<T>::Pop()
{
	return mas[pos--];
}
//
// Посмотреть элемент
//
template <class T>
T TStack<T>::Top()
{
	return mas[pos];
}
//
// Очистить стек
//
template <class T>
void TStack<T>::Clear()
{
	pos = -1;
}