//List逻辑操作接口
#pragma once
template<typename E>
class List {
public:
	List(){}
	virtual ~List(){}
	virtual void clear() = 0;//清空
	virtual E remove() = 0;//删除当前位置的元素并返回其值
	virtual void insert(const E & item) = 0;//在当前位置插入元素
	virtual void append(const E & item) = 0;//在表尾插入元素
	virtual void next() = 0;//将当前位置向后挪一位
	virtual void prev() = 0;//将当前位置向前挪一位
	virtual int currPos() = 0;//返回当前位置
	virtual void moveToStart() = 0;//将当前位置移动到表首
	virtual void moveToEnd() = 0;//将当前位置移动到表尾
	virtual void moveToPos(int pos) = 0;//将当前位置移动到指定的位置
	virtual const E& getValue() = 0;//返回当前位置的值
	virtual int length() = 0;//返回表的长度
};