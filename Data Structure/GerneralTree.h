#pragma once
//广义树节点定义
template<typename E>
class GTNode {
private:
	E v;
	GTNode* lc;//LeftmostChild
	GTNode* rs;//RightSibling
	GTNode* pa;//ParentPointer
public:
	GTNode()
	{
		lc = rs = pa = nullptr;
	}

	GTNode(const E& it,GTNode* l = nullptr,GTNode* r = nullptr,GTNode* p = nullptr)
		:v(it),lc(l),rs(r),pa(p)
	{}

	~GTNode()
	{}

	E value()//返回节点存储的值
	{
		return v;
	}

	bool isLeaf()//判断节点是不是叶节点
	{
		return (lc == nullptr) && (rs == nullptr);
	}

	GTNode* parent()//返回父节点的地址
	{
		return pa;
	}

	GTNode* leftmostChild()//返回左孩子的地址
	{
		return lc;
	}

	GTNode* rightSibling()//返回右兄弟的地址
	{
		return rs;
	}

	void setValue(E& it)//设置节点存储的值
	{
		value = it;
	}

	void insertFirst(GTNode<E>* c)//插入左孩子
	{
		//当左孩子不为空节点的时候，将原来的左孩子变为当前左孩子的右兄弟
		if (lc != nullptr)
		{
			GTNode* temp = lc;
			lc = c;
			c->pa = this;
			c->insertNext(temp);
		}
		else
		{
			lc = c;
			c->pa = this;
		}
	}

	void insertNext(GTNode<E>* s)//插入右兄弟
	{
		//当右兄弟不为空节点时，将原来的右兄弟变为当前节点的右兄弟
		if (rs != nullptr)
		{
			GTNode* temp = rs;
			rs = s;
			s->pa = pa;
			s->insertNext(temp);
		}
		else
		{
			rs = s;
			s->pa = pa;
		}
	}

	//void removeFirst();
	//void removeNext();
};

