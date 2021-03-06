// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 공용으로 사용되는 구조체 모음입니다.
// POD(Plain Old Data, C언어 스타일의 구조체)만 정의합니다.
// =====================================================================================

#ifndef COMMON_STRUCT__H__
#define COMMON_STRUCT__H__

#include "CommonType.h"

struct SizeInfo
{
	TSize width = 0;
	TSize height = 0;
};

struct UI_PosInfo
{
	COORD startPos = { 0, 0 };
	COORD menuStartPos = { 0, 0 };
	SizeInfo diffSize;
};

#endif