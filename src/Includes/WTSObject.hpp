/*!
 * \file WTSObject.hpp
 * \project	WonderTrader
 *
 * \author Wesley
 * \date 2020/03/30
 * 
 * \brief Wt����Object����
 */
#pragma once
#include <stdint.h>
#include <atomic>
#include <boost/pool/object_pool.hpp>
#include <boost/smart_ptr/detail/spinlock.hpp>

#include "WTSMarcos.h"

NS_WTP_BEGIN
class WTSObject
{
public:
	WTSObject() :m_uRefs(1){}
	virtual ~WTSObject(){}

public:
	inline uint32_t		retain(){ return m_uRefs.fetch_add(1) + 1; }

	virtual void	release()
	{
		if (m_uRefs == 0)
			return;

		try
		{
			uint32_t cnt = m_uRefs.fetch_sub(1);
			if (cnt == 1)
			{
				delete this;
			}
		}
		catch(...)
		{

		}
	}

	inline bool			isSingleRefs() { return m_uRefs == 1; }

	inline uint32_t		retainCount() { return m_uRefs; }

protected:
	volatile std::atomic<uint32_t>	m_uRefs;
};

typedef boost::detail::spinlock BoostSpinLock;

template<typename T>
class WTSPoolObject : public WTSObject
{
private:
	typedef boost::object_pool<T> MyPool;
	MyPool*			_pool;
	BoostSpinLock*	_mutex;

public:
	WTSPoolObject():_pool(NULL){}
	virtual ~WTSPoolObject() {}

public:
	static T*	allocate()
	{
		thread_local static MyPool			pool;
		thread_local static BoostSpinLock	mtx;

		mtx.lock();
		T* ret = pool.construct();
		mtx.unlock();
		ret->_pool = &pool;
		ret->_mutex = &mtx;
		return ret;
	}

public:
	virtual void release() override
	{
		if (m_uRefs == 0)
			return;

		try
		{
			uint32_t cnt = m_uRefs.fetch_sub(1);
			if (cnt == 1)
			{
				_mutex->lock();
				_pool->destroy((T*)this);
				_mutex->unlock();
			}
		}
		catch (...)
		{

		}
	}
};
NS_WTP_END
