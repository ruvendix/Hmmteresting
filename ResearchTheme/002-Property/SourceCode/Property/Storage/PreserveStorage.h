// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 원본값을 보존하는 프로퍼티의 저장소입니다.
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
#pragma region 생성자와 소멸자
            Preservation() = default;
            virtual ~Preservation() = default;
            
            Preservation(const TValue& value) : 
				m_value(value)
            {
            
            }
#pragma endregion

#pragma region Getter와 Setter
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