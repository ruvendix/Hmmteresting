// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �������� �����ϴ� ������Ƽ�� ������Դϴ�.
// =====================================================================================

#ifndef PRESERVER_STORAGE_H__
#define PRESERVER_STORAGE_H__

#include "IStorage.h"

namespace property
{
	namespace storage
	{

		template<class TValue>
		class Preservation : IStorage<TValue>
		{
		public:
#pragma region �����ڿ� �Ҹ���
            Preservation() = default;
            virtual ~Preservation() = default;
            
            Preservation(const TValue& value) : 
				m_value(value)
            {
            
            }
#pragma endregion

#pragma region Getter�� Setter
            virtual const TValue& OnGet() const override
            {
                return m_value;
            }
            
            virtual TValue& OnGetRef() override
            {
                return m_value;
            }
            
            virtual TValue OnGetValue() const override
            {
                return m_value;
            }
            
            virtual void OnSet(const TValue& value) override
            {
                m_value = value;
            }
#pragma endregion
        
        private:
            TValue m_value;
		};

	} // namespace stroage end
} // namespace property end

#endif