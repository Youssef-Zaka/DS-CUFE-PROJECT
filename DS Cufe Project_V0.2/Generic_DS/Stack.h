#ifndef STACK_
#define STACK_
#pragma once
#include"Node.h"
using namespace std;
template <typename T>
class Stack
{
private:

	T data;
	Node<T>* Head;

public:

	Stack()
	{
		Head = nullptr;
	}

	bool isEmpty() //Check if the Stack is empty or not
	{
		if (Head == nullptr) { return true; }
		else
		{
			return false;
		}
	}

	void push(T newentry)
	{
		Node<T>* temp;
		temp = new Node<T>();
		temp->setItem(newentry);
		temp->setNext(Head);
		Head = temp;
	}

	bool pop()
	{
		if (isEmpty()) { return false; }
		Node<T>* temp;
		temp = Head;
		Head = Head->getNext();
		temp->setNext(nullptr);
		delete temp;
		return true;
	}

	T peek()
	{
		if (!isEmpty())
		{
			return Head->getItem();
		};
		return nullptr;
	}

	void display()
	{
		if (isEmpty())
		{
			return;
		}
		Node<T>* temp;
		temp = Head;
		while (temp)
		{
			cout << temp->getItem() << " ";
			temp = temp->getNext();
		}
	}

	~Stack()
	{
		Head = nullptr;
	}

};
#endif
