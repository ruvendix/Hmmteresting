// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 프로퍼티에 사용되는 저장소의 인터페이스입니다.
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