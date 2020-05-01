// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 참조자를 사용하는 프로퍼티의 저장소입니다.
// =====================================================================================

#ifndef REF_STORAGE_H__
#define REF_STORAGE_H__

#include <memory>
#include "IStorage.h"

namespace property
{
	namespace storage
	{

		template<class TValue>
		class Ref : IStorage<TValue>
		{
		public:
#pragma region 생성자와 소멸자
			Ref() = default;
			virtual ~Ref() = default;

			explicit Ref(TValue& value)
			{
				m_value(std::addressof(value));
			}
#pragma endregion

			void BindRef(const TValue& value)
			{
				// & 연산자는 오버로딩이 가능하므로 안전하게 std::addressof()를 사용함!
				m_value = std::addressof(value);
			}

#pragma region Getter와 Setter
			virtual const TValue& OnGet() const override
			{
				return *m_value;
			}

			virtual TValue& OnGetRef() override
			{
				return *m_value;
			}

			virtual TValue OnGetValue() const override
			{
				return *m_value;
			}

			virtual void OnSet(const TValue& value) override
			{
				if (m_value == nullptr)
				{
					m_value = std::addressof(*(const_cast<TValue*>(&value)));
				}

				*m_value = value;
			}
#pragma endregion

		private:
			TValue* m_value = nullptr;
		};

	} // namespace stroage end
} // namespace property end

#endif