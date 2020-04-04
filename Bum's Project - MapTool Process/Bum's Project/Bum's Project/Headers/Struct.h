#pragma once

typedef struct tagInfo
{
	float fCX;
	float fCY;

	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vSize;	

	D3DXMATRIX matWorld;
	
	tagInfo(void){}

	tagInfo(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vSize)
		:vPos(_vPos)
		,vSize(_vSize)
	{}
}INFO, *PINFO, *pINFO;

/*
INFO tInfo;

INFO* pInfo;		//둘다 동일하다.
PINFO pInfo;
pINFO pInfo;
*/

//Texture를 보관하는 구조체를 만들어 보자.
typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9	pTexture;			//이미지 한장을 보관하기 위한 변수.
	D3DXIMAGE_INFO		ImageInfo;		//이미지의 정보를 보관하기 위한 변수.
}TEX_INFO;


typedef struct tagStringCompare
{
	const TCHAR* m_pString;

	template<typename T>
	bool operator () (T rData)
	{
		return !lstrcmp(rData.first, m_pString);
	}

	tagStringCompare(const TCHAR* pKey)
		:m_pString(pKey){}
}STRING_COMPARE;


struct DeleteMap 
{
	template<typename T>
	void operator () (T& Temp)
	{
		if(Temp.second)
		{
			delete [] Temp.first;

			delete Temp.second;
			Temp.second = NULL;
		}
	}
};

struct DeleteObj
{
	template<typename T>
	void operator() (T& rData)
	{
		if (rData)
		{
			safe_delete(rData);
		}
	}
};


//타일 정보를 보관할 구조체.
typedef struct tagTile
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;

	BYTE byOption;		//충돌 여부(갈수있다, 없다, 포탈:마을,상점.., 이벤트)
	BYTE byDrawID;		//타일 이미지

}TILE, *PTILE, *pTILE;

//맵 정보를 보관할 구조체
typedef struct tagBackInfo
{
	int iBackType;
}BACKINFO, *PBACKINFO, *pBACKINFO;

//오브젝트 정보를 보관할 구조체
typedef struct tagObjInfo
{
	float fCX;
	float fCY;

	RECT  rc;

	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;

	BYTE byDrawID;

	bool bAlpa;
}OBJINFO, *POBJINFO, *pOBJINFO;

//몬스터의 정보를 보관할 구조체
typedef struct tagMonInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vSize;

	BYTE byDrawID;
}MONINFO, *PMONINFO, *pMONINFO;

typedef struct tagXYCount
{
	int iXCount;
	int iYCount;
}XYCOUNT, *PXYCOUNT, *pXYCOUNT;

typedef struct tagMINISize
{
	float fXSize;
	float fYSize;
	float fZSize;
}MINISIZE, *PMINISIZE, *pMINISIZE;

typedef struct tagBack
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
		
	eStageType StageType;		
}BACK, *PBACK, *pBACK;


typedef struct tagUnitData 
{
	wstring wstrName;
	int		iAtt;
	int		iHp;
	int		iMp;
	BYTE	byJobIndex;
	BYTE	byItem;

	tagUnitData(void) {};
	tagUnitData(int _iHp, int _iMp)
		:iHp(_iHp), iMp(_iMp) {}
}UNIT_DATA;

//[17.07.21_06] : 파일이름을 찾기 위한 구조체
typedef struct tagImagePath 
{
	wstring		wstrObjKey;		//이미지의 종류(ex.Player, Monster...)
	wstring		wstrStateKey;	//이미지의 상태(Att, Idle, Run...)
	wstring		wstrPath;		//이미지의 경로
	int			iCount;			//이미지 장수

	tagImagePath(void)
		:wstrObjKey(L"")
		,wstrStateKey(L"")
		,wstrPath(L"")
		,iCount(0)
	{}

}IMAGE_PATH;

typedef struct tagFrame
{
	float fIndex;
	float fCount;
	float fMax;

	tagFrame(float _fIndex = 0.f, float _fCount = 0.f, float _fMax = 0.f)
		:fIndex(_fIndex)
		, fCount(_fCount)
		, fMax(_fMax)
	{}
}FRAME, *PFRAME, *pFRAME;

#ifdef _PROJECT_MFC_

//상대경로를 추출하는 함수.
inline wstring RelativePath(wstring szFullPath)
{
	TCHAR szRelativePath[MAX_PATH]  = L"";
	TCHAR szDirectoryPath[MAX_PATH] = L"";


	//프로젝트가 있는 위치까지의 경로를 얻어올수 있는 함수.
	GetCurrentDirectory(sizeof(szDirectoryPath), szDirectoryPath);


	//상대경로를 추출해주는 함수.
	PathRelativePathTo( szRelativePath,
		szDirectoryPath,
		FILE_ATTRIBUTE_DIRECTORY,
		szFullPath.c_str(),
		FILE_ATTRIBUTE_NORMAL );

	return szRelativePath;
}


//[17.07.21_07]

//const int*;
//int*;

//폴더안에 있는 파일(이미지파일_png)의 개수를 계산해주는 함수.
static int DirectoryFileCount(const wstring& wstrPath)
{
	//Png파일만 찾고 싶다.
	//\Texture\Stage\Effect\BossMultiAttack
	
	//\Texture\Stage\Effect\BossMultiAttack\*.png
	wstring wstrTemp = wstrPath + L"\\*.png";

	CFileFind Find;
	Find.FindFile(wstrTemp.c_str());

	int iContinue = 1;
	int iFileCount = 0;

	while(iContinue)
	{
		iContinue = Find.FindNextFile();
		//다음파일이 있는지를 검사.

		//디렉토리 유무룰 검사하자.
		if(!Find.IsDirectory())
			++iFileCount;
	}

	return iFileCount;
}




//폴더의 정보를 추출하는 기능의 함수.
static void DirectoryInfoExtraction(const wstring& wstrPath,
									list<IMAGE_PATH*>& rPathInfoList)
{
	//MFC에서 지원해주는 클래스.
	CFileFind	Find;

	Find.FindFile(wstrPath.c_str());

	int iContinue = 1;
	
	while(iContinue)
	{
		iContinue = Find.FindNextFile();
		//FindNextFile() : 파일 유무를 검사하는 함수.

		if(Find.IsDots())		//내 경로중에 .과 ..을 걸러내기 위한 함수.
			continue;

		//검색되는 파일이 폴더인지? 파일인지를 구분하자.
		if(Find.IsDirectory())		//현재 파일이 폴더이다.
		{
			//재귀함수를 통해서 파일을 찾을때까지 호출하도록 하자.
			
			DirectoryInfoExtraction( wstring(Find.GetFilePath() + L"\\*.*"), rPathInfoList );
		}
		else		//파일
		{
			//파일을 찾았지만 찾은 파일이 시스템 파일인 경우에 예외처리를 하자.
			if(Find.IsSystem())
				continue;

			IMAGE_PATH*		pImagePath = new IMAGE_PATH;
			
			TCHAR	szPathBuffer[MAX_PATH] = L"";


			//추출한 경로를 문자열로 복사를 하자.
			lstrcpy(szPathBuffer, Find.GetFilePath().operator LPCWSTR());
			//\Texture\Stage\Effect\BossMultiAttack\BossMultiAttack0.png


			//제일 위에 있는 경로를 잘라내는 함수.
			PathRemoveFileSpec(szPathBuffer);
			//\Texture\Stage\Effect\BossMultiAttack

			//PathRemoveFileSpec(szPathBuffer);
			////\Texture\Stage\Effect
			
			pImagePath->iCount = DirectoryFileCount(szPathBuffer);


			//현재 Find
			//\Texture\Stage\Effect\BossMultiAttack\BossMultiAttack0.png
			
			//파일이름을 얻어오자.
			wstring wstrImageName = Find.GetFileTitle().operator LPCWSTR();
			//wstrIamgeName -> BossMultiAttack0


			//BossMultiAttack000 -> BossMultiAttack%d
			wstrImageName = wstrImageName.substr(0, wstrImageName.size() - 1) + L"%d.png";
			//substr() : 문자열을 잘라주는 함수.
			
			//경로를 얻어오자.(%d로 바꾼 경로를 얻어오자)
			TCHAR szPath[MAX_PATH] = L"";

			lstrcpy(szPath, Find.GetFilePath().operator LPCWSTR());
			//\Texture\Stage\Effect\BossMultiAttack\BossMultiAttack0.png

			PathRemoveFileSpec(szPath);
			//\Texture\Stage\Effect\BossMultiAttack\
			//현재는 절대경로를 받아오고있다.

			PathCombine(szPath, szPath, wstrImageName.c_str());
			//두 문자열을 결합해주는 함수.


			//상대경로로 변경을 해보도록 하자.
			pImagePath->wstrPath = RelativePath(szPath);
			//\Texture\Stage\Effect\BossMultiAttack\BossMultiAttack%d.png
			

			PathRemoveFileSpec(szPath);
			//\Texture\Stage\Effect\BossMultiAttack

			
			pImagePath->wstrStateKey = PathFindFileName(szPath);
			//\Texture\Stage\Effect\ ->BossMultiAttack

			
			PathRemoveFileSpec(szPath);
			//\Texture\Stage\Effect

			pImagePath->wstrObjKey = PathFindFileName(szPath);

			rPathInfoList.push_back(pImagePath);

			
			//현재 파일에서 하나 위단계를 찾아가자.
			Find.FindFile(Find.GetFilePath());

			
			//다음폴더로 넘어가자
			Find.FindNextFile();
		}
	}
}




#endif

typedef struct tagAStarNode
{
	float		  fCost;
	int			  iIndex;
	tagAStarNode* pParent;
}NODE;






