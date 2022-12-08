#pragma once


#include <atomic>
#include <mutex>
#include <memory>


template<typename T>
class Singleton
{
public:
	Singleton() = default;
	~Singleton() = default;
	static T& Instance()
	{
#ifdef _MSC_VER
		call_once(mcreate_, [=] { s_value_ = std::make_unique<T>(); });
#else
		call_once(mcreate_, [=] { s_value_ = std::unique_ptr<T>(new T()); });
#endif
		return *s_value_;

	}

private:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
private:
	static std::unique_ptr<T> s_value_;
	static std::once_flag mcreate_;
};


template<typename T>
std::unique_ptr<T> Singleton<T>::s_value_ = nullptr;

template<typename T>
std::once_flag Singleton<T>::mcreate_;