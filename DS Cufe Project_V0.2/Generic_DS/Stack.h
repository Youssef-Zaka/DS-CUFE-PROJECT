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
		Head = nullptr;		//initialize head to null
	}

	bool isEmpty() //Check if the Stack is empty or not
	{
		if (Head == nullptr) { return true; }
		else
		{
			return false;
		}
	}

	void push(T newentry)		//Make the head point to the new item, set new item next to previous head
	{
		Node<T>* temp;
		temp = new Node<T>();
		temp->setItem(newentry);
		temp->setNext(Head);
		Head = temp;
	}

	bool pop()					//Pop the head, ad relplace it with its next, if it exists
	{
		if (isEmpty()) { return false; }		//if is alrady empty, return
		Node<T>* temp;
		temp = Head;
		Head = Head->getNext();
		temp->setNext(nullptr);
		delete temp;
		return true;
	}

	T peek()							//return the item of the head node 
	{
		if (!isEmpty())
		{
			return Head->getItem();
		};
		return nullptr;
	}

	void display()					//cout the stack, head to toe
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
