// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������Ƽ�� ���Ǵ� ������� �������̽��Դϴ�.
// =====================================================================================

#ifndef I_STORAGE_H__
#define I_STORAGE_H__

namespace property
{
    namespace storage
    {

        template <typename TValue>
        class IStorage abstract
        {
        public:
            IStorage() = default;
            virtual ~IStorage() = default;
            
            virtual const TValue& OnGet() const abstract;
            virtual TValue& OnGetRef() abstract;
            virtual TValue OnGetValue() const abstract;
            virtual void OnSet(const TValue&) abstract;
        };

    } // namespace stroage end
} // namespace property end

#endif