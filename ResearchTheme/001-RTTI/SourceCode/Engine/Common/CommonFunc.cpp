// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 공용으로 사용되는 함수 정의 모음입니다.
// =====================================================================================

#include "PCH.h"
#include "CommonFunc.h"

/*
로그를 출력합니다.
*/
void CommonFunc::ShowLog(const std::string_view& szLogCategory, const std::string_view& szLog)
{
	std::string strLog;

	if (szLogCategory.empty() == false)
	{
		strLog += "[";
		strLog += szLogCategory;
		strLog += "]: ";
	}

	strLog += szLog;
	strLog += "\n"; // 자동 개행!

	::OutputDebugString(strLog.c_str());
}

/*
Create은 생성 데이터를 이용해서 처음부터 만들 때 사용하고
Make는 전달된 데이터들을 조합해서 만들 때 사용합니다. (사실 별로 차이는 없음...)
printf()처럼 서식 문자열을 사용하면 std::string 자료형으로 문자열을 만듭니다.
*/
std::string CommonFunc::MakeFormatString(const char* szFormat, ...)
{
	va_list va = nullptr;
	va_start(va, szFormat);

	// 서식 문자열의 길이를 구합니다.
	// 동적할당을 위해 종료 문자를 포함해야 합니다.
	Int32 length = _vscprintf(szFormat, va) + 1;

	// 가변 인자로 문자열을 조합하려면 메모리 버퍼가 필요합니다.
	// std::string은 메모리 버퍼가 가변적이라 사용할 수 없습니다.
	// 참고로 단순하게 바이트 단위로 동적할당할 때는 std::malloc()을 사용합니다.
	char* pMemoryBuffer = nullptr;
	pMemoryBuffer = reinterpret_cast<char*>(std::malloc(length * sizeof(char)));
	if (pMemoryBuffer == nullptr)
	{
		return std::string();
	}

	::ZeroMemory(pMemoryBuffer, (length * sizeof(char)));

	vsprintf_s(pMemoryBuffer, length, szFormat, va);
	va_end(va);

	std::string strFormat = pMemoryBuffer;
	free(pMemoryBuffer);

	return strFormat;
}