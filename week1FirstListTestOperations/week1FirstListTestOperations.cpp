#include <iostream>

using namespace std;




template<typename T>
class LinkedList
{
private:
	struct Node
	{
		T element;
		Node* next = nullptr;

		Node(const T& element)
		{
			this->element = element;
		}

		~Node()
		{
			delete next;
		}
	};

	Node* front = nullptr;
	unsigned int nrOfElements = 0;

	Node*& Walk(unsigned int nrOfSteps);

public:
	LinkedList() = default;
	~LinkedList();
	LinkedList(const LinkedList& other) = delete;
	LinkedList& operator=(const LinkedList& other) = delete;
	LinkedList(const LinkedList&& other) = delete;
	LinkedList& operator=(const LinkedList&& other) = delete;

	unsigned int Size() const;
	void InsertAtPosition(unsigned int index, const T& element);
	T& GetAtPosition(unsigned int index);
	void RemoveAtPosition(unsigned int index);
	
	void Push(const T& element);
	void Inject(const T& element);
	void Pop();
	void Eject();
};


template<typename T>
typename LinkedList<T>::Node*& LinkedList<T>::Walk(unsigned int nrOfSteps)
{
	Node** walker = &front;
	for (unsigned int i = 0; i < nrOfSteps; ++i)
		walker = &((*walker)->next);

	return *walker;
}

template<typename T>
unsigned int LinkedList<T>::Size() const
{
	return nrOfElements;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	delete front;
}



template<typename T>
void LinkedList<T>::Push(const T& element)
{
	
	auto& currentNodeAtIndexPtr = Walk(0);
	Node* newNode = new Node(element);
	newNode->next = currentNodeAtIndexPtr;
	currentNodeAtIndexPtr = newNode;
	++nrOfElements;
}



template<typename T>
void LinkedList<T>::Inject(const T& element)
{
	if (this->nrOfElements > 0) 
	{
		auto& currentNodeAtIndexPtr = Walk(this->nrOfElements);
		Node* newNode = new Node(element);
		newNode->next = nullptr;
		currentNodeAtIndexPtr = newNode;
		++nrOfElements;
	}
	
}

template<typename T>
void LinkedList<T>::Pop()
{
	cout << GetAtPosition(0) << endl;

	Node*& ptrToNodeToRemove = Walk(0);
	Node* next = ptrToNodeToRemove->next;
	ptrToNodeToRemove->next = nullptr;
	delete ptrToNodeToRemove;
	ptrToNodeToRemove = next;
	--nrOfElements;
}

template<typename T>
void LinkedList<T>::Eject()
{
	cout << GetAtPosition(this->nrOfElements-1) << endl;

	Node*& ptrToNodeToRemove = Walk(this->nrOfElements-1);
	Node* next = nullptr;
	ptrToNodeToRemove->next = nullptr;
	delete ptrToNodeToRemove;
	ptrToNodeToRemove = next;
	--nrOfElements;
}



template<typename T>
void LinkedList<T>::InsertAtPosition(unsigned int index, const T& element)
{
	if (index > nrOfElements)
		return;

	auto& currentNodeAtIndexPtr = Walk(index);
	Node* newNode = new Node(element);
	newNode->next = currentNodeAtIndexPtr;
	currentNodeAtIndexPtr = newNode;
	++nrOfElements;
}

template<typename T>
T& LinkedList<T>::GetAtPosition(unsigned int index)
{
	if (index >= nrOfElements)
		throw std::out_of_range("Index greater than or equal to size of linked list");

	return Walk(index)->element;
}

template<typename T>
void LinkedList<T>::RemoveAtPosition(unsigned int index)
{
	if (index >= nrOfElements)
		return;

	Node*& ptrToNodeToRemove = Walk(index);
	Node* next = ptrToNodeToRemove->next;
	ptrToNodeToRemove->next = nullptr;
	delete ptrToNodeToRemove;
	ptrToNodeToRemove = next;
	--nrOfElements;
}




int main()
{
	LinkedList<int> list;

	list.Push(1);
	list.Push(2);
	list.Push(3);
	list.Push(4);
	list.Push(5);
	list.Push(6);

	

	list.Inject(7);
	list.Inject(8);

	
	


	for (unsigned int i = 0; i < list.Size(); i++)
	{
		cout << list.GetAtPosition(i) << endl;
	}

	cout << endl;
	list.Pop();
	list.Pop();
	list.Eject();
	cout << endl;


	for (unsigned int i = 0; i < list.Size(); i++)
	{
		cout << list.GetAtPosition(i) << endl;
	}


}