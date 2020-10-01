#pragma once

template <class T>
class Singleton
{
public:
	static T* getInstance()
	{
		if (!theInstance) theInstance = new T();
		return theInstance;
	}
protected:
	Singleton() {};
	~Singleton() { theInstance = nullptr; }
	Singleton(const Singleton& root) = delete;
	Singleton& operator=(const Singleton& root) = delete;
	static T* theInstance;
};

template <class T>
T* Singleton<T>::theInstance = nullptr;
