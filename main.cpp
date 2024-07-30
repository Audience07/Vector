#include<iostream>
#include<Windows.h>

template <class T_ELE>
class Vector {
public:
	//���캯����������
	Vector();
	Vector(DWORD dwSize);
	~Vector();
public:
	DWORD at(DWORD dwIndex, OUT T_ELE* pEle);	//����ָ������ֵ�õ�Ԫ��
	DWORD push_back(T_ELE Element);				//��Ԫ�ش洢�����һ��λ��
	VOID pop_back();							//ɾ�����һ��Ԫ��
	DWORD insert(DWORD dwIndex, T_ELE Element);	//��ָ��λ������һ��Ԫ��
	DWORD capacity();							//���ز����ݵ�����»��ܴ洢����Ԫ��
	VOID clear();								//�������Ԫ��
	BOOL empty();								//�ж�Vector�Ƿ�Ϊ�գ����Ϊ�գ�����true
	VOID erase(DWORD dwIndex);					//ɾ��ָ��Ԫ��
	DWORD size();								//�жϵ�ǰVector�Ĵ�С

	
private:
	BOOL expend();


private:
	DWORD m_dwIndex;				//��һ����������
	DWORD m_dwIncrement;			//ÿ�����ݴ�С
	DWORD m_dwLen;					//��ǰ��������
	DWORD m_dwInitSize;				//��ʼ��������
	T_ELE* m_pVector;				//��ǰ����ָ��
};
//�޲ι��캯��
template <class T_ELE>
Vector<T_ELE>::Vector():
	m_dwInitSize(100),m_dwIncrement(5) 
{
	//���ó�ʼVector��С��ռ䲻��ʱÿ�����ӵĴ�С
	this->m_pVector = new T_ELE[m_dwInitSize]{};
	//��ʼ���ڴ�
	//memset(m_pVector, 0, m_dwInitSize * sizeof(T_ELE));

	this->m_dwLen = m_dwInitSize;
	this->m_dwIndex = 0;
}


//�вι��캯��
template <class T_ELE>
Vector<T_ELE>::Vector(DWORD dwSize):
	m_dwInitSize(dwSize),m_dwIncrement(5)
{
	this->m_pVector = new T_ELE[m_dwInitSize]{};
	//��ʼ���ڴ�
	//memset(m_pVector, 0, m_dwInitSize * sizeof(T_ELE));
	this->m_dwLen = m_dwInitSize;
	this->m_dwIndex = 0;
}

//��������
template <class T_ELE>
Vector<T_ELE>::~Vector() 
{
	delete[] m_pVector;
	m_pVector = nullptr;
	std::cout << "�ѱ��ͷ�" << std::endl;
}
//����
template <class T_ELE>
BOOL Vector<T_ELE>::expend() {
	//�����µ��ڴ�
	T_ELE* temp = new T_ELE[m_dwLen + m_dwIncrement];
	if (!temp) {
		return FALSE;
	}
	//��ʼ���ڴ棬����ԭ�������ݵ��µ��ڴ���
	memset(temp, 0, (m_dwLen + m_dwIncrement) * sizeof(T_ELE));
	memcpy(temp, m_pVector, m_dwLen * sizeof(T_ELE));
	//�ͷžɵ��ڴ�
	delete[] m_pVector;

	//����Ϊ��Ա��ֵ
	m_pVector = temp;
	m_dwLen += m_dwIncrement;

	return TRUE;
}



//��ѯ
template <class T_ELE>
DWORD Vector<T_ELE>::at(DWORD dwIndex, OUT T_ELE* pEle) 
{
	//�ж�Խ��
	if (dwIndex > m_dwIndex) {
		return -1;
	}
	*pEle = m_pVector[dwIndex];
	if (pEle) {
		return 0;
	}
	return -1;
}
//��Ԫ�ش������
template <class T_ELE>
DWORD Vector<T_ELE>::push_back(T_ELE Element) {
	//�жϿռ��Ƿ��㹻
	if (m_dwIndex >= m_dwLen) {
		this->expend();
	}
	//��������������,������һ��Ԫ�ص�λ�ü�һ
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
	//�жϿռ��Ƿ��㹻����
	if (m_dwIndex + 1 > m_dwLen) {
		this->expend();
	}
	//�������Խ���ˣ���ô����ʧ��
	if (dwIndex > m_dwIndex) {
		return -1;
	}
	//��������λ�øպ�����һ�����ݵ�λ�ã���ôpush��ȥ
	if (dwIndex == m_dwIndex) {
		this->push_back(Element);
		return 0;
	}
	//�����ݺ�Ų���ճ�һλ
	memcpy(&m_pVector[dwIndex + 1], &m_pVector[dwIndex], (m_dwIndex - dwIndex) * sizeof(T_ELE));

	//��ָ��λ�ò�������
	memcpy(m_pVector + dwIndex, &Element, sizeof(T_ELE));


	//�ں�Ų����һ����������λ�ü�һ
	m_dwIndex++;
}

template<class T_ELE>
DWORD Vector<T_ELE>::capacity() {
	//����ʣ������
	//return m_dwLen - (m_dwIndex - 1);
	return m_dwLen - m_dwIndex;
}


template<class T_ELE>
VOID Vector<T_ELE>::clear() {
	//���ڴ��ʼ��Ϊ0
	memset(m_pVector, 0, m_dwLen * sizeof(T_ELE));
	m_dwIndex = 0;
}

template<class T_ELE>
BOOL Vector<T_ELE>::empty() {
	//�ж�ָ���ڴ�ĵ�һ��Ԫ���Ƿ���0������ǣ����ж�Ϊ��
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

	//�������ֵ�պ������һ�������������ֱ��pop��ȥ
	if (dwIndex == m_dwIndex - 1) {
		this->pop_back();
	}


	//���Ҫȥ��������ֵ���Դ�����֮�У���ô��Ҫȥ������һ����������Ų
	if (dwIndex < m_dwIndex) {
		memcpy(&m_pVector[dwIndex], &m_pVector[dwIndex + 1], (m_dwIndex - dwIndex) * sizeof(T_ELE));
		m_dwIndex--;
	}
	//�ж�Խ��
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