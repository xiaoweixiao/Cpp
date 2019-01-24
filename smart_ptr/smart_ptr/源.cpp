//#include<iostream>
//#include<vector>
//#include<exception>
//
//using namespace std;
//
//class A
//{
//public:
//	A()
//	{
//		cout << "A()" << endl;
//	}
//
//	~A()
//	{
//		cout << "~A()" << endl;
//	}
//public:
//	void Print()
//	{
//		cout << "I am a func of class A" << endl;
//	}
//};
//
//template<class T>
//class Auto_Ptr
//{
//public:
//	Auto_Ptr(T* ptr = nullptr)
//		:_ptr(ptr)
//	{
//	}
//	~Auto_Ptr()
//	{
//		if (_ptr != nullptr)
//			delete _ptr;
//	}
//
//	T& operator*()
//	{
//		return *_ptr;
//	}
//	T* operator->()
//	{
//		return _ptr;
//	}
//	//拷贝构造，用sp2(sp1),让sp2指向sp1指向的空间，sp1置空，Bug
//	Auto_Ptr(Auto_Ptr<T>& ap)
//		:_ptr(ap._ptr)
//	{
//		ap._ptr = nullptr;
//	}
//
//	Auto_Ptr<T>& operator=(Auto_Ptr<T>& ap)//赋值运算符重载:s2=s1
//	{
//		if (_ptr != ap._ptr)
//		{
//			if (_ptr)
//				delete _ptr;//先释放s2之前的空间
//			_ptr = ap._ptr;
//			ap._ptr = nullptr;
//		}
//		return *this;
//	}
//private:
//	T* _ptr;
//};
//void Func()
//{
//	A* a = new A;
//	Auto_Ptr<A> sp(a);
//	(*sp).Print();
//	sp->Print();
//	Auto_Ptr<A> p2(sp);
//	Auto_Ptr<A> p3;
//	p3 = p2;
//	p2->Print();
//	(*sp).Print();
//}
//int main()
//{
//	Func();
//	system("pause");
//}

//#include<iostream>
//#include<mutex>
//
//using namespace std;
//
//class A
//{
//public:
//	A()
//	{
//		cout << "A()" << endl;
//	}
//
//	~A()
//	{
//		cout << "~A()" << endl;
//	}
//public:
//	void Print()
//	{
//		cout << "I am a func of class A" << endl;
//	}
//};
//
//template<class T>
//class Shared_Ptr
//{
//public:
//	Shared_Ptr(T* ptr = nullptr)
//		:_ptr(ptr)
//		,_pCount(new int(1))
//		,_mt(new mutex)
//	{
//		if (_ptr == nullptr)
//			*_pCount = 0;
//	}
//	~Shared_Ptr()
//	{
//		if (SubCountlock() == 0&&_ptr)//如果引用计数减1之后等于0，释放资源
//		{
//			delete _ptr;
//			delete _pCount;
//			delete _mt;
//		}
//	}
//
//	T& operator*()
//	{
//		return *_ptr;
//	}
//	T* operator->()
//	{
//		return _ptr;
//	}
//
//	int AddCountlock()
//	{
//		_mt->lock();
//		(*_pCount)++;
//		_mt->unlock();
//
//		return *_pCount;
//	}
//
//	int SubCountlock()
//	{
//		_mt->lock();
//		(*_pCount)--;
//		_mt->unlock();
//
//		return *_pCount;
//	}
//	Shared_Ptr(Shared_Ptr<T>& ap)
//		:_ptr(ap._ptr)
//		,_pCount(ap._pCount)
//		,_mt(ap._mt)
//	{
//		//拷贝构造，当_ptr=nullptr不能拷贝
//		if (_ptr)
//			AddCountlock();
//	}
//
//	Shared_Ptr<T>& operator=(Shared_Ptr<T>& ap)//赋值运算符重载:s2=s1
//	{
//		if (_ptr != ap._ptr)
//		{
//			if (_ptr == nullptr&&SubCountlock()==0)
//			{
//				delete _ptr;//先释放s2之前的空间
//				delete _pCount;
//				delete _mt;
//			}
//
//			_ptr = ap._ptr;
//			_pCount = ap._pCount;
//			_mt = ap._mt;
//
//			AddCountlock();
//		}
//		return *this;
//	}
//	int UseCount(){ return *_pCount; }
//	T* Get(){ return _ptr; }
//private:
//	T* _ptr;
//	int* _pCount;
//	mutex* _mt;
//};
//void Func()
//{
//	A* a = new A;
//	Shared_Ptr<A> sp(a);
//	cout << sp.UseCount() << endl;
//	Shared_Ptr<A> p2(sp);
//	cout << sp.UseCount() << endl;
//	Shared_Ptr<A> p3;
//	p3 = p2;
//	cout << sp.UseCount() << endl;
//}
//int main()
//{
//	Func();
//	system("pause");
//}


#include<iostream>
#include<memory>

using namespace std;
//
//struct ListNode
//{
//	int _data;
//	shared_ptr<ListNode> _prev;
//	shared_ptr<ListNode> _next;
//	~ListNode(){ cout << "~ListNode()" << endl; }
//};
//void Func()
//{
//	shared_ptr<ListNode> node1(new ListNode);
//	shared_ptr<ListNode> node2(new ListNode);
//	cout << node1.use_count() << endl;
//	cout << node2.use_count() << endl;
//	node1->_next = node2;
//	node2->_prev = node1;
//	cout << node1.use_count() << endl;
//	cout << node2.use_count() << endl;
//}
//int main()
//{
//	Func();
//	system("pause");
//	return 0;
//}

struct ListNode
{
	int _data;
	weak_ptr<ListNode> _prev;
	weak_ptr<ListNode> _next;
	~ListNode(){ cout << "~ListNode()" << endl; }
};
void Func()
{
	shared_ptr<ListNode> node1(new ListNode);
	shared_ptr<ListNode> node2(new ListNode);
	cout << node1.use_count() << endl;
	cout << node2.use_count() << endl;
	node1->_next = node2;
	node2->_prev = node1;
	cout << node1.use_count() << endl;
	cout << node2.use_count() << endl;
}
int main()
{
	Func();
	system("pause");
	return 0;
}

