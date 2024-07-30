#include<iostream>
#include<Windows.h>

template <class T_ELE>
class Vector {
public:
	//构造函数析构函数
	Vector();
	Vector(DWORD dwSize);
	~Vector();
public:
	DWORD at(DWORD dwIndex, OUT T_ELE* pEle);	//根据指定索引值得到元素
	DWORD push_back(T_ELE Element);				//将元素存储到最后一个位置
	VOID pop_back();							//删除最后一个元素
	DWORD insert(DWORD dwIndex, T_ELE Element);	//向指定位置新增一个元素
	DWORD capacity();							//返回不增容的情况下还能存储多少元素
	VOID clear();								//清空所有元素
	BOOL empty();								//判断Vector是否为空，如果为空，返回true
	VOID erase(DWORD dwIndex);					//删除指定元素
	DWORD size();								//判断当前Vector的大小

	
private:
	BOOL expend();


private:
	DWORD m_dwIndex;				//下一个可用索引
	DWORD m_dwIncrement;			//每次增容大小
	DWORD m_dwLen;					//当前容器长度
	DWORD m_dwInitSize;				//初始容器长度
	T_ELE* m_pVector;				//当前容器指针
};
//无参构造函数
template <class T_ELE>
Vector<T_ELE>::Vector():
	m_dwInitSize(100),m_dwIncrement(5) 
{
	//设置初始Vector大小与空间不足时每次增加的大小
	this->m_pVector = new T_ELE[m_dwInitSize]{};
	//初始化内存
	//memset(m_pVector, 0, m_dwInitSize * sizeof(T_ELE));

	this->m_dwLen = m_dwInitSize;
	this->m_dwIndex = 0;
}


//有参构造函数
template <class T_ELE>
Vector<T_ELE>::Vector(DWORD dwSize):
	m_dwInitSize(dwSize),m_dwIncrement(5)
{
	this->m_pVector = new T_ELE[m_dwInitSize]{};
	//初始化内存
	//memset(m_pVector, 0, m_dwInitSize * sizeof(T_ELE));
	this->m_dwLen = m_dwInitSize;
	this->m_dwIndex = 0;
}

//析构函数
template <class T_ELE>
Vector<T_ELE>::~Vector() 
{
	delete[] m_pVector;
	m_pVector = nullptr;
	std::cout << "已被释放" << std::endl;
}
//增容
template <class T_ELE>
BOOL Vector<T_ELE>::expend() {
	//分配新的内存
	T_ELE* temp = new T_ELE[m_dwLen + m_dwIncrement];
	if (!temp) {
		return FALSE;
	}
	//初始化内存，复制原来的数据到新的内存中
	memset(temp, 0, (m_dwLen + m_dwIncrement) * sizeof(T_ELE));
	memcpy(temp, m_pVector, m_dwLen * sizeof(T_ELE));
	//释放旧的内存
	delete[] m_pVector;

	//重新为成员赋值
	m_pVector = temp;
	m_dwLen += m_dwIncrement;

	return TRUE;
}



//查询
template <class T_ELE>
DWORD Vector<T_ELE>::at(DWORD dwIndex, OUT T_ELE* pEle) 
{
	//判断越界
	if (dwIndex > m_dwIndex) {
		return -1;
	}
	*pEle = m_pVector[dwIndex];
	if (pEle) {
		return 0;
	}
	return -1;
}
//将元素存至最后
template <class T_ELE>
DWORD Vector<T_ELE>::push_back(T_ELE Element) {
	//判断空间是否足够
	if (m_dwIndex >= m_dwLen) {
		this->expend();
	}
	//将数据填入向量,并把下一个元素的位置加一
	memcpy(&m_pVector[m_dwIndex], &Element, sizeof(T_ELE));
	this->m_dwIndex++;
	return 0;
}

template<class T_ELE>
VOID Vector<T_ELE>::pop_back() {
	if (this->empty()) {
		return;
	}
	memset(&m_pVector[m_dwIndex - 1], 0, sizeof(T_ELE));
	this->m_dwIndex--;
}

template <class T_ELE>
DWORD Vector<T_ELE>::insert(DWORD dwIndex, T_ELE Element) {
	//判断空间是否足够插入
	if (m_dwIndex + 1 > m_dwLen) {
		this->expend();
	}
	//如果插入越界了，那么插入失败
	if (dwIndex > m_dwIndex) {
		return -1;
	}
	//如果插入的位置刚好是下一个数据的位置，那么push进去
	if (dwIndex == m_dwIndex) {
		this->push_back(Element);
		return 0;
	}
	//将数据后挪，空出一位
	memcpy(&m_pVector[dwIndex + 1], &m_pVector[dwIndex], (m_dwIndex - dwIndex) * sizeof(T_ELE));

	//在指定位置插入数据
	memcpy(m_pVector + dwIndex, &Element, sizeof(T_ELE));


	//在后挪后，下一个可用索引位置加一
	m_dwIndex++;
}

template<class T_ELE>
DWORD Vector<T_ELE>::capacity() {
	//计算剩余容量
	//return m_dwLen - (m_dwIndex - 1);
	return m_dwLen - m_dwIndex;
}


template<class T_ELE>
VOID Vector<T_ELE>::clear() {
	//将内存初始化为0
	memset(m_pVector, 0, m_dwLen * sizeof(T_ELE));
	m_dwIndex = 0;
}

template<class T_ELE>
BOOL Vector<T_ELE>::empty() {
	//判断指针内存的第一个元素是否是0，如果是，则判断为空
	if (*m_pVector) {
		return 0;
	}
	return 1;
	/*int i = 0;
	while (m_dwLen-i) {
		if (*(m_pVector+i)) {
			return false;
		}
		i++;
	}
	return true;*/
}

template <class T_ELE>
VOID Vector<T_ELE>::erase(DWORD dwIndex) {

	//如果索引值刚好是最后一个存入的数，则直接pop出去
	if (dwIndex == m_dwIndex - 1) {
		this->pop_back();
	}


	//如果要去除的索引值在以存数据之中，那么将要去除的下一个索引往左挪
	if (dwIndex < m_dwIndex) {
		memcpy(&m_pVector[dwIndex], &m_pVector[dwIndex + 1], (m_dwIndex - dwIndex) * sizeof(T_ELE));
		m_dwIndex--;
	}
	//判断越界
	/*if (dwIndex > m_dwIndex) {
		return;
	}*/
	

}



template<class T_ELE>
DWORD Vector<T_ELE>::size() {
	return m_dwLen;
}


int main() 
{
	//Vector<int>* V1 = new Vector<int>(13);
	Vector<int>* V1 = new Vector<int>;
	for (int i{ 0x10 }; i < 0x20; i++) {
		V1->push_back(i);
	}
	V1->insert(5, 0x70);
	//V1->clear();
	V1->erase(16);
	std::cout << V1->capacity() << std::endl;
	
}