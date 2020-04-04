// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C의 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include <d3dx9math.h>

#include <list>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <io.h>
//#include <vld.h>


//#include <Vfw.h>
//#pragma comment(lib, "vfw32.lib")

// fmod 활용위한 헤더와 라이브러리 추가.
#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

#include <algorithm>
#include <string>
#include <iostream>		//PathRelativePathTo()를 사용하기 위해서는 헤더필요.
////##[17.07.18_01]

#include "SoundMgr.h"

//##[17.07.24_01] : C++입출력 객체를 사용하기 위해서는 헤더를 추가해야한다.
#include <fstream>

#include <process.h>


