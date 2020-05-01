// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ĸ��ȭ�� ��Ű�� ������Ƽ�Դϴ�.
// ������Ƽ�� �� ����ҿ� ���� �������� ����˴ϴ�.
// �⺻ ����Ҵ� �������Դϴ�.
// 
// ����: https://gist.github.com/cheind/1473513
// =====================================================================================

#ifndef PROPERTY_H__
#define PROPERTY_H__

#include "Storage\RefStorage.h" // ����Ʈ
#include "Storage\PreserveStorage.h"
#include "Storage\ProxyStorage.h"

namespace property
{

	// ����Ʈ ����Ҵ� ������!
	template <typename TValue, typename TStorage = storage::Ref<TValue>>
	class Basic
	{
	public:
#pragma region �����ڿ� �Ҹ���
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

#pragma region ������Ƽ Getter�� Setter
        // 1. const T& => get => �⺻
        // 2. T& => getRef => ������
        // 3. T => getValue => �����ε� ���� ����(Copy Elision)�� �� ���� ����...
        
        const TValue& get() const
        {
            return m_storage.OnGet();
        }
        
        // ĳ������ �̿��� ���
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

        // ��ȯ ��, ���� �����ؾ� �ϹǷ� const ����
        TStorage& getStorage()
        {
            return m_storage;
        }
        
        // ��ȯ ��, ���� ���� �Ұ����ؾ� �ϹǷ� const �߰�
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