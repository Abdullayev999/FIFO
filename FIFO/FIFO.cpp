#include <iostream>
#include <string>
/*
	   ДОМАШНЕЕ ЗАДАНИЕ:
	   Задание 1: Реализуйте шаблонный класс queue (FIFO)
	   Методы очереди:
	   + front() возвращает ссылку на первый элемент в очереди
	   + back() возвращает ссылку на последний элемент в очереди
	   + pop() извлекает первый элемент из очереди
	   + push(element) добавляет элемент в очередь
	   + size() возвращает количество элементов в очереди
	   + swap(other_queue) обменивает содержимым две очереди
	   + empty() возвращает true если очередь пустая и false в противном случае
	   + конструкторы/операторы копирования/перемещения
	   + распечатайте содержимое очереди за пределами класса queue
   */

struct Down {
	template<typename T>
	bool operator() (const T left, const T right) {
		return left < right;
	}
};

struct Up {
	template<typename T>
	bool operator() (const T left, const T right) {
		return left > right;
	}
};


template<typename T>
class Queue
{
public:
	Queue(){}

	~Queue(){
    delete[] m_arr;
	}

	T& front()
	{
		return m_arr[0];
	}

     void pop()
     {
     T* tmp = new T[m_size];
     for (size_t i = 1, b = 0; i < m_index; b++, i++) {
     	tmp[b] = m_arr[i];
     }
     delete[] m_arr;
     m_arr = tmp;
     m_index--;
     }

	T& back()
	{
		return m_arr[m_index-1];
	}

	void push(const T& element)
	{
		if (m_size == m_index)capacityUp();
		
		m_arr[m_index++] = element;
	}

	int size()const
	{
		return m_index;
	}
	
	bool empty()const
	{
		return m_index == 0;
	}

	Queue(const Queue& other)
	{
		m_capacity = other.m_capacity;
		m_index = other.m_index;
		m_size = other.m_size;
		m_arr = new T[m_size];

		for (size_t i = 0; i < m_index; i++)
			m_arr[i] = other.m_arr[i];
	}

	void swap(Queue& other)noexcept
	{
		Queue tmp=std::move(other);
		other= std::move(*this);
		*this = std::move(tmp);
	}
	
	Queue(Queue&& other) noexcept
	{
		m_capacity = other.m_capacity;
		m_index = other.m_index;
		m_size = other.m_size;
		m_arr = other.m_arr;
		other.m_arr = nullptr;
	}

	Queue& operator=(const Queue& other)noexcept
	{
		m_capacity = other.m_capacity;
		m_index = other.m_index;
		m_size = other.m_size;
		m_arr = new T[m_size];

		for (size_t i = 0; i < m_index; i++)
			m_arr[i] = other.m_arr[i];

		return *this;
	}

	Queue& operator=(Queue&& other)noexcept
	{
		m_capacity = other.m_capacity;
		m_index = other.m_index;
		m_size = other.m_size;
		m_arr = other.m_arr;
		other.m_arr = nullptr;

		return *this;
	}
	
private:

	friend std::ostream& operator<<(std::ostream& os, Queue<T>& n)
	{
		for (size_t i = 0; i < n.m_index; i++)
		{
			os << n.m_arr[i] << ' ';
		}
		return os;
	}
	void capacityUp()
	{
		m_size += m_capacity;
		
		T* tmp = new T[m_size];

		for (size_t i = 0 ; i < m_index ; i++)
		{
			tmp[i] = m_arr[i];
		}
		delete[] m_arr;
		m_arr = tmp;
	}
	
	size_t m_size = 10;
	size_t m_index = 0;
	size_t m_capacity = 10;
	T* m_arr = new T[m_size];
};



int main()
{
	Queue<int> a;
	Queue<int> b;
	a.push(1);
	a.push(2);
	a.push(3);
	a.push(4);

	b.push(10);
	b.push(20);
	b.push(30);
	b.push(40);
	std::cout << a;
	std::cout << "\n\n====\n\n";
	std::cout << b;
	a.swap(b);
	std::cout << a;
	std::cout << "\n\n====\n\n";
	std::cout << b;
}