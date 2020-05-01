// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 캡슐화를 지키는 프로퍼티입니다.
// 프로퍼티는 각 저장소에 따라 다형성이 적용됩니다.
// 기본 저장소는 참조자입니다.
// 
// 참고: https://gist.github.com/cheind/1473513
// =====================================================================================

#ifndef PROPERTY_H__
#define PROPERTY_H__

#include "Storage\RefStorage.h" // 디폴트
#include "Storage\PreserveStorage.h"
#include "Storage\ProxyStorage.h"

namespace property
{

	// 디폴트 저장소는 참조자!
	template <typename TValue, typename TStorage = storage::Ref<TValue>>
	class Basic
	{
	public:
#pragma region 생성자와 소멸자
        Basic() = default;
        ~Basic() = default;
        
        explicit Basic(const TValue& value)
        {
			set(value);
        }
        
        Basic(const TStorage& storage) : 
			m_storage(storage)
        {
        
        }
#pragma endregion

#pragma region 프로퍼티 Getter와 Setter
        // 1. const T& => get => 기본
        // 2. T& => getRef => 참조자
        // 3. T => getValue => 복사인데 복사 생략(Copy Elision)이 될 수도 있음...
        
        const TValue& get() const
        {
            return m_storage.OnGet();
        }
        
        // 캐스팅을 이용한 방법
        operator const TValue& () const
        {
            return m_storage.OnGet();
        }
        
        const TValue& operator()() const
        {
            return m_storage.OnGet();
        }
        
        TValue& getRef()
        {
            return m_storage.OnGetRef();
        }
        
        TValue getValue() const
        {
            return m_storage.OnGetValue();
        }
        
        void set(const TValue& value)
        {
            m_storage.OnSet(value);
        }
        
        void operator()(const TValue& value)
        {
            set(value);
        }
        
        void operator=(const TValue& value)
        {
            set(value);
        }
#pragma endregion

        // 반환 후, 수정 가능해야 하므로 const 생략
        TStorage& getStorage()
        {
            return m_storage;
        }
        
        // 반환 후, 수정 가능 불가능해야 하므로 const 추가
        const TStorage& getStorage() const
        {
            return m_storage;
        }
    
    private:
        TStorage m_storage;
	};

}

template <typename TValue>
using Property = property::Basic<TValue>;

template <typename TValue>
using PreserveProperty = property::Basic<TValue, property::storage::Preservation<TValue>>;

template <typename TValue>
using ProxyProperty = property::Basic<TValue, property::storage::Proxy<TValue>>;

#endif