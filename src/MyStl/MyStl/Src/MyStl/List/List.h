#pragma once
#include<iostream>

using namespace std;
template<typename T>
class List
{
private:
	Stock * m_Head;
	Stock * m_Tail;
	unsigned int m_Length;

	void init()
	{
		m_Head = new Stock();
		m_Tail = new Stock();
		m_Head->next = m_Tail;
		m_Tail->prev = m_Head;
		m_Length = 0;
	}
public:
	List();
	virtual ~List();

	bool Insert(T &t);
	bool Insert(T &&t);
	bool Insert(unsigned int index, T &&t);
	bool Insert(unsigned int index, T &t);

	T* GetValue(unsigned int index);
	int GetIndex(T t);

	bool Remove_Front();
	bool Remove_End();
	bool Remove(unsigned int index);

	unsigned int GetLength() { return m_Length; }
	bool IsEmpty() { return m_Length == 0; }

	void Clear();

	void ShowList()
	{
		cout << "Length of List : " << m_Length << endl;
	}

	Iterator begin() { return Iterator(m_Head); }
	Iterator end() { return Iterator(m_Tail); }

private:
	void insert(unsigned int index, T &t, Stock * curNode);
};

template<typename T>
List<T>::List()
{
	this->init();
}
template<typename T>
List<T>::~List()
{
	Clear();
	delete m_Head;
	delete m_Tail;
}

template<typename T>
bool List<T>::Insert(T &t)
{
	Insert(std::move(t));
	return true;
}
template<typename T>
bool List<T>::Insert(T &&t)
{
	this->insert(m_Length, t, m_Tail);
	return true;
}
template<typename T>
bool List<T>::Insert(unsigned int index, T &t)
{
	Insert(index, std::move(t));
	return true;
}
template<typename T>
bool List<T>::Insert(unsigned int index, T &&t)
{
	if (index + 1 > m_Length)
	{
		Insert(t);
	}
	else
	{
		Stock * curNode = m_Head;
		for (int i = index; i >= 0; --i)
			curNode = curNode->next;

		this->insert(index, t, curNode);
	}
	return true;
}
template<typename T>
void List<T>::insert(unsigned int index, T &t, Stock * curNode)
{
	Stock * newNode = new Stock(t);
	newNode->prev = curNode->prev;
	newNode->next = curNode;
	curNode->prev->next = newNode;
	curNode->prev = newNode;
	++m_Length;
	cout << "Insert Value at " << "[" << index << "]" << endl;
}
template<typename T>
T* List<T>::GetValue(unsigned int index)
{
	if (index + 1 >m_Length)
		returnnullptr;

	Stock * curNode = m_Head->next;
	for (int i = 0; i <index; ++i)
		curNode = curNode->next;
	return &(curNode->value);
}
template<typename T>
int List<T>::GetIndex(T t)
{
	int idx = 0;
	for (Stock * curNode = m_Head->next; m_Tail != curNode; curNode = curNode->next)
	{
		if (t == curNode->value) return idx;
		++idx;
	}
	return -1;
}
template<typename T>
bool List<T>::Remove_Front()
{
	if (IsEmpty())
		return false;

	Stock * curNode = m_Head->next;
	curNode->prev->next = curNode->next;
	curNode->next->prev = curNode->prev;
	delete curNode;

	--m_Length;
	return true;
}
template<typename T>
bool List<T>::Remove_End()
{
	if (IsEmpty())
		return false;

	Stock * curNode = m_Tail->prev;
	curNode->prev->next = curNode->next;
	curNode->next->prev = curNode->prev;
	delete curNode;

	--m_Length;
	return true;
}
template<typename T>
bool List<T>::Remove(unsigned int index)
{
	if (index + 1 >m_Length)
		return false;

	Stock * curNode = m_Head->next;
	for (int i = 0; i <index; ++i)
		curNode = curNode->next;
	curNode->prev->next = curNode->next;
	curNode->next->prev = curNode->prev;
	delete curNode;

	--m_Length;
	return true;
}
template<typename T>
void List<T>::Clear()
{
	for (Stock * curNode = m_Head->next; curNode != m_Tail;)
	{
		Stock * delNode = curNode;
		curNode->prev->next = curNode->next;
		curNode->next->prev = curNode->prev;
		curNode = curNode->next;
		delete delNode;

		--m_Length;
	}
}