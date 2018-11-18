#pragma once

/*未使用freelist优化
template<typename E>
class DualNode {
public:
	E value;
	DualNode* prev;
	DualNode* next;
	DualNode(const E& v,DualNode* p = nullptr, DualNode* n = nullptr)
		:value(v),prev(p),next(n){}
	DualNode( DualNode* p = nullptr, DualNode* n = nullptr)
		:prev(p),next(n){}
	~DualNode(){}
};
*/

template<typename E>
class DualNode {
private:
	static DualNode<E>* freelist;
public:
	E value;
	DualNode* prev;
	DualNode* next;

	DualNode(const E& v,DualNode* p = nullptr,DualNode* n = nullptr)
		:value(v),prev(p),next(n){}
	
	DualNode(DualNode* p = nullptr,DualNode* n = nullptr)
		:prev(p),next(n){}

	void* operator new(size_t s)
	{
		if (freelist == nullptr)
			return ::new DualNode;
		DualNode<E>* temp = freelist;
		freelist = freelist->next;
		return temp;
	}

	void operator delete(void* ptr)
	{
		((DualNode<E>*)ptr)->next = freelist;
		freelist = (DualNode<E>*)ptr;
	}
};

template<typename E>
DualNode<E>* DualNode<E>::freelist = nullptr;