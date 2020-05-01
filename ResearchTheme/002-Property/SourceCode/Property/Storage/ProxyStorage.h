// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// Getter와 Setter를 설정할 수 있는 프로퍼티의 저장소입니다.
// =====================================================================================

#ifndef PROXY_STORAGE_H__
#define PROXY_STORAGE_H__

#include <functional>
#include "IStorage.h"

namespace property
{
	namespace storage
	{

		template<class TValue>
		class Proxy : IStorage<TValue>
		{
		public:
            using GetFuncType = std::function<const TValue& ()>;
            using GetRefFuncType = std::function<TValue& ()>;
            using GetValueFuncType = std::function<TValue()>;
            using SetFuncType = std::function<void(const TValue&)>;

#pragma region 생성자와 소멸자
            Proxy() = default;
            virtual ~Proxy() = default;
            
            Proxy(const GetFuncType& getFunc, const SetFuncType& setFunc)
            {
				m_getFunc = getFunc;
				m_setFunc = setFunc;
            }
#pragma endregion

            void BindGetFunc(const GetFuncType& getFunc)
            {
				m_getFunc = getFunc;
            }
            
            void BindGetRefFunc(const GetRefFuncType& getRefFunc)
            {
				m_getRefFunc = getRefFunc;
            }
            
            void BindGetValueFunc(const GetValueFuncType& getValueFunc)
            {
				m_getValueFunc = getValueFunc;
            }
            
            void BindSetFunc(const SetFuncType& setFunc)
            {
				m_setFunc = setFunc;
            }

#pragma region Getter와 Setter
            virtual const TValue& OnGet() const override
            {
                _ASSERT_EXPR(m_getFunc != nullptr, L"Proxy getter isn't bound!");
                return m_getFunc();
            }
            
            virtual TValue& OnGetRef() override
            {
                _ASSERT_EXPR(m_getRefFunc != nullptr, L"Proxy getter ref isn't bound!");
                return m_getRefFunc();
            }
            
            virtual TValue OnGetValue() const override
            {
                _ASSERT_EXPR(m_getValueFunc != nullptr, L"Proxy getter value isn't bound!");
                return m_getValueFunc();
            }
            
            /** Setter */
            virtual void OnSet(const TValue& value) override
            {
                _ASSERT_EXPR(m_setFunc != nullptr, L"Proxy setter isn't bound!");
                m_setFunc(value);
            }
#pragma endregion
        
        private:
            GetFuncType m_getFunc = nullptr;
            GetRefFuncType m_getRefFunc = nullptr;
            GetValueFuncType m_getValueFunc = nullptr;
            
            SetFuncType m_setFunc = nullptr;
		};

	} // namespace stroage end
} // namespace property end

#endif