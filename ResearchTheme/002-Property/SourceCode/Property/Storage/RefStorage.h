// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �����ڸ� ����ϴ� ������Ƽ�� ������Դϴ�.
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
#pragma region �����ڿ� �Ҹ���
			Ref() = default;
			virtual ~Ref() = default;

			explicit Ref(TValue& value)
			{
				m_value(std::addressof(value));
			}
#pragma endregion

			void BindRef(const TValue& value)
			{
				// & �����ڴ� �����ε��� �����ϹǷ� �����ϰ� std::addressof()�� �����!
				m_value = std::addressof(value);
			}

#pragma region Getter�� Setter
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