#pragma once
/*未使用freelist优化
template<typename E>
class Node {
public:
	E value;
	Node* next;
	Node(const E& v,Node* n = nullptr):value(v),next(n){}
	Node(Node* n = nullptr):next(n){}
	~Node(){}
};
*/

template<typename E>
class Node {
private:
	static Node<E>* freelist;//static表明该成员为所有该类的对象所共享
public:
	E value;
	Node* next;

	Node(const E& v,Node* n = nullptr)
		:value(v),next(n){}

	Node(Node* n = nullptr)
		:next(n){}

	void* operator new(size_t s)
	{
		if (freelist == nullptr)
			return ::new Node;
		Node<E>* temp = freelist;
		freelist = freelist->next;
		return temp;
	}

	void operator delete(void* ptr)
	{
		((Node<E>*)ptr)->next = freelist;
		freelist = (Node<E>*)ptr;
	}
};

//对象创建时一定要初始化freelist
template<typename E>
Node<E>* Node<E>::freelist = nullptr;
//类似于int a = 5;