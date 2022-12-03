#pragma once

#include "SGTypes.h"
#include "HAL/UnrealMemory.h"

struct SGCORE_API IoBuffer
{
	uint8* m_data;
	uint32 m_capacity;
	uint32 m_head;
	uint32 m_tail;

	// 构造
	IoBuffer()
		: m_data(nullptr), m_capacity(0), m_head(0), m_tail(0)
	{

	}

	// 构造
	// @param: nLen 数据长度
	IoBuffer(uint32 nLen)
	{
		m_data = (uint8*)FMemory::Malloc(nLen);
		m_capacity = nLen;
		m_head = 0;
		m_tail = 0;
	}

	// 析构
	~IoBuffer()
	{
		if (m_data)
		{
			FMemory::Free(m_data);
			m_data = nullptr;
		}
	}

	// 清空数据
	void Clear()
	{
		if (m_data)
		{
			FMemory::Free(m_data);
			m_data = nullptr;
		}
		m_data = nullptr;
		m_capacity = 0;
		m_head = 0;
		m_tail = 0;
	}

	// 拷贝构造
	IoBuffer(const IoBuffer& rhs)
	{
		m_data = (uint8*)FMemory::Malloc(rhs.m_capacity);
		m_head = rhs.m_head;
		m_tail = rhs.m_tail;
		m_capacity = rhs.m_capacity;
		FMemory::Memcpy(m_data + m_head, rhs.m_data + m_head, m_tail - m_head);
	}

	//// 通过string构造
	//IoBuffer(const std::string& str)
	//{
	//	m_capacity = (uint32)str.size();
	//	m_data = (char*)malloc(sizeof(char) * m_capacity);
	//	memcpy(m_data, str.c_str(), m_capacity);
	//	m_head = 0;
	//	m_tail = m_capacity;
	//}

	// c string 构造
	IoBuffer(const uint8* data, uint32 len, bool rvalue = false)
	{
		m_capacity = len;
		m_head = 0;
		m_tail = m_capacity;
		m_data = nullptr;

		if (len == 0)
		{
			return;
		}

		if (rvalue == false)
		{
			m_data = (uint8*)FMemory::Malloc(sizeof(char) * m_capacity);
			FMemory::Memcpy(m_data, data, m_capacity);
		}
		else
		{
			m_data = const_cast<uint8*>(data);
		}
	}

	// 赋值操作符
	IoBuffer& operator = (const IoBuffer& rhs)
	{
		m_data = (uint8*)FMemory::Malloc(rhs.m_capacity);
		m_head = rhs.m_head;
		m_tail = rhs.m_tail;
		m_capacity = rhs.m_capacity;
		FMemory::Memcpy(m_data + m_head, rhs.m_data + m_head, m_tail - m_head);
		return *this;
	}

	// 初始化
	void Init(uint32 size)
	{
		if (m_data)
		{
			FMemory::Free(m_data);
			m_data = nullptr;
		}
		m_capacity = size;
		m_data = (uint8*)FMemory::MallocZeroed(size, sizeof(char));
		m_head = 0;
		m_tail = 0;
	}

	// 外部添加数据
	void Append(const uint8* pData, uint32 nLen)
	{
		if (GetFreeSize() < nLen)
		{
			MoveToHead();
			if (GetFreeSize() < nLen)
			{
				Reserve(FGenericPlatformMath::Max<uint32>(m_capacity + nLen, m_capacity * 2));
			}
		}
		FMemory::Memcpy(m_data + m_tail, pData, nLen);
		m_tail += nLen;
	}

	// 获取头指针
	inline uint8* GetHead()
	{
		return m_data + m_head;
	}

	// 获取尾指针
	inline uint8* GetTail()
	{
		return m_data + m_tail;
	}

	// 当前数据长度
	inline uint32 GetSize() const
	{
		return m_tail - m_head;
	}

	// 获取尾部空闲大小
	inline uint32 GetFreeSize() const
	{
		return m_capacity - m_tail;
	}

	// 获取所有的空闲大小
	inline uint32 GetAllFreeSize() const
	{
		return m_capacity - GetSize();
	}

	// 获取容量
	inline uint32 GetCapacity() const
	{
		return m_capacity;
	}

	// 重置
	void Reset()
	{
		m_head = 0;
		m_tail = 0;
	}

	// 移动头
	void MoveHead(uint32 len)
	{
		check(len <= GetSize());
		m_head += len;
		if (m_head == m_tail)
		{
			m_head = m_tail = 0;
		}
	}

	// 移动尾
	void MoveTail(uint32 len)
	{
		check(len <= GetFreeSize());
		uint32_t size = GetSize() + len;
		m_tail += len;
		if (m_tail == m_capacity && m_head != 0)
		{
			FMemory::Memmove(m_data, m_data + m_head, size);
			m_head = 0;
			m_tail = size;
		}
	}

	// 移动到头： 数据头部对齐， m_head = 0
	void MoveToHead()
	{
		if (m_head == 0)
		{
			return;
		}
		uint32 size = GetSize();
		FMemory::Memmove(m_data, m_data + m_head, size);
		m_head = 0;
		m_tail = size;
	}

	// 预分配空间
	void Reserve(uint32 size)
	{
		if (m_capacity >= size)
		{
			return;
		}
		if (m_data == nullptr)
		{
			m_data = (uint8*)FMemory::MallocZeroed(size, sizeof(char));
		}
		else
		{
			m_data = (uint8*)FMemory::Realloc(m_data, size);
		}
		m_capacity = size;
	}
};
