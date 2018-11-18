#pragma once
//�������ڵ㶨��
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

	E value()//���ؽڵ�洢��ֵ
	{
		return v;
	}

	bool isLeaf()//�жϽڵ��ǲ���Ҷ�ڵ�
	{
		return (lc == nullptr) && (rs == nullptr);
	}

	GTNode* parent()//���ظ��ڵ�ĵ�ַ
	{
		return pa;
	}

	GTNode* leftmostChild()//�������ӵĵ�ַ
	{
		return lc;
	}

	GTNode* rightSibling()//�������ֵܵĵ�ַ
	{
		return rs;
	}

	void setValue(E& it)//���ýڵ�洢��ֵ
	{
		value = it;
	}

	void insertFirst(GTNode<E>* c)//��������
	{
		//�����Ӳ�Ϊ�սڵ��ʱ�򣬽�ԭ�������ӱ�Ϊ��ǰ���ӵ����ֵ�
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

	void insertNext(GTNode<E>* s)//�������ֵ�
	{
		//�����ֵܲ�Ϊ�սڵ�ʱ����ԭ�������ֵܱ�Ϊ��ǰ�ڵ�����ֵ�
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

