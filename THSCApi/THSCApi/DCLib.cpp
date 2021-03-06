/*************************************************************************
*	BEGIN OF FILE
*		FileName	:	DCLib.cpp
*		Author		:	Wu Di
*		Modify Date	:	2012.09.09
*************************************************************************/

#include "stdafx.h"
#include "DCLib.h"

/*
 * These lib may be located in the directory:
 * "C:\Program Files\Microsoft SDKs\Windows\v6.0A\Lib"
 * referenced header file may be located in the directory:
 * "C:\Program Files\Microsoft SDKs\Windows\v6.0A\Include"
**/

#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"winspool.lib")
#pragma comment(lib,"comdlg32.lib")
#pragma comment(lib,"advapi32.lib")
#pragma comment(lib,"shell32.lib")
#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"oleaut32.lib")
#pragma comment(lib,"uuid.lib")
#pragma comment(lib,"odbc32.lib")
#pragma comment(lib,"odbccp32.lib")

/* DStr class implement */

const char DStr::FileChangeLineStr[3] = {0x0D,0x0A,0x00}; /* 0x0D=Enter'\r' 0x0A=Space'\n' */
int DStr::InstrW(wchar_t * PSourceStr,wchar_t * PFindStr)
{
	if (NULL==PSourceStr || NULL == PFindStr)
	{
		return (-1);
	}
	return Instr_FromHeadToTailW(PSourceStr,PFindStr);
}
int DStr::InstrA(char * PSourceStr,char * PFindStr)
{
	if (NULL==PSourceStr || NULL == PFindStr)
	{
		return (-1);
	}
	DStr BaseStrOP;
	int CntByteS=DStr::GetStrLenthA(PSourceStr)+1;
	wchar_t * wcsPS=new wchar_t[CntByteS];
	DStr::CMbsToWcs(wcsPS,PSourceStr,CntByteS);
	int CntByteF=DStr::GetStrLenthA(PFindStr)+1;
	wchar_t * wcsPF=new wchar_t[CntByteF];
	DStr::CMbsToWcs(wcsPF,PFindStr,CntByteF);
	int ret=InstrW(wcsPS,wcsPF);
	delete [] wcsPS;
	delete [] wcsPF;
	return ret;
}
int DStr::Instr_FromHeadToTailW(wchar_t * PSourceStr,wchar_t * PFindStr)
{
	if (NULL==PSourceStr || NULL == PFindStr)
	{
		return (-1);
	}
	wchar_t * GPIndex=PSourceStr;
	wchar_t * IPIndex=GPIndex;
	wchar_t * FIPIndex=PFindStr;
	int RetFindPos=0;
	while (*GPIndex!=L'\0')
	{
		while(*IPIndex==*FIPIndex && *PFindStr!=L'\0' && *IPIndex!=L'\0')
		{
			IPIndex++;
			FIPIndex++;
			if (*FIPIndex==L'\0')
			{
				return RetFindPos;
			}
		}
		GPIndex++;
		IPIndex=GPIndex;
		FIPIndex=PFindStr;
		RetFindPos++;
	}
	return (-1);
}
int DStr::Instr_FromHeadToTailA(char * PSourceStr,char * PFindStr)
{
	if (NULL==PSourceStr || NULL == PFindStr)
	{
		return (-1);
	}
	DStr BaseStrOP;
	int CntByteS=DStr::GetStrLenthA(PSourceStr)+1;
	wchar_t * wcsPS=new wchar_t[CntByteS];
	DStr::CMbsToWcs(wcsPS,PSourceStr,CntByteS);
	int CntByteF=DStr::GetStrLenthA(PFindStr)+1;
	wchar_t * wcsPF=new wchar_t[CntByteF];
	DStr::CMbsToWcs(wcsPF,PFindStr,CntByteF);
	int ret=Instr_FromHeadToTailW(wcsPS,wcsPF);
	delete [] wcsPS;
	delete [] wcsPF;
	return ret;
}
int DStr::Instr_FromTailToHeadW(wchar_t * PSourceStr,wchar_t * PFindStr)
{
	if (NULL==PSourceStr || NULL == PFindStr)
	{
		return (-1);
	}
	int LenS=DStr::GetStrLenthW(PSourceStr);
	int LenF=DStr::GetStrLenthW(PFindStr);
	wchar_t * GPIndex=&PSourceStr[LenS];
	wchar_t * IPIndex=GPIndex;
	wchar_t * FIPIndex=&PFindStr[LenF-1];
	int RetFindPos=LenS;
	while (RetFindPos>=0)
	{
		int svFP=RetFindPos;
		int CntSur=0;
		while(*IPIndex==*FIPIndex && CntSur<LenF && svFP>=0 )
		{
			CntSur++;
			svFP--;
			IPIndex--;
			FIPIndex--;
			if (CntSur>=LenF)
			{
				return RetFindPos-LenF+1;
			}
		}
		GPIndex--;
		IPIndex=GPIndex;
		FIPIndex=&PFindStr[LenF-1];
		RetFindPos--;
	}
	return (-1);
}
int DStr::Instr_FromTailToHeadA(char * PSourceStr,char * PFindStr)
{
	if (NULL==PSourceStr || NULL == PFindStr)
	{
		return (-1);
	}
	DStr BaseStrOP;
	int CntByteS=DStr::GetStrLenthA(PSourceStr)+1;
	wchar_t * wcsPS=new wchar_t[CntByteS];
	DStr::CMbsToWcs(wcsPS,PSourceStr,CntByteS);
	int CntByteF=DStr::GetStrLenthA(PFindStr)+1;
	wchar_t * wcsPF=new wchar_t[CntByteF];
	DStr::CMbsToWcs(wcsPF,PFindStr,CntByteF);
	int ret=Instr_FromTailToHeadW(wcsPS,wcsPF);
	delete [] wcsPS;
	delete [] wcsPF;
	return ret;
}
int DStr::InstrTrimIgnoreULW(wchar_t * PSourceStr,wchar_t * PFindStr)
{
	if (NULL==PSourceStr || NULL == PFindStr)
	{
		return (-1);
	}

	int LenS=DStr::GetStrLenthW(PSourceStr);
	wchar_t * Psr=new wchar_t[LenS+1];
	lstrcpyW(Psr,PSourceStr);
	TrimW(Psr);
	UCaseW(Psr);

	int LenF=DStr::GetStrLenthW(PFindStr);
	wchar_t * PFs=new wchar_t[LenF+1];
	lstrcpyW(PFs,PFindStr);
	TrimW(PFs);
	UCaseW(PFs);

	int RetPos=InstrW(Psr,PFs);

	delete [] Psr;
	delete [] PFs;

	return RetPos;
}

int DStr::InstrTrimIgnoreULA(char * PSourceStr,char * PFindStr)
{
	if (NULL==PSourceStr || NULL == PFindStr)
	{
		return (-1);
	}
	DStr BaseStrOP;
	int CntBytelens=DStr::GetStrLenthA(PSourceStr)+1;
	int CntBytelenf=DStr::GetStrLenthA(PFindStr)+1;
	wchar_t * PS=new wchar_t[CntBytelens];
	wchar_t * PF=new wchar_t[CntBytelenf];
	DStr::CMbsToWcs(PS,PSourceStr,CntBytelens);
	DStr::CMbsToWcs(PF,PFindStr,CntBytelenf);
	int ret=InstrTrimIgnoreULW(PS,PF);
	delete [] PS;
	delete [] PF;
	return ret;
}
int DStr::CmpStrIgnoreULW(wchar_t * in_CmpStr1,wchar_t * in_CmpStr2)
{
	int lenOfbytesStr1=DStr::GetStrLenthW(in_CmpStr1)+1;
	wchar_t * PCmp1=new wchar_t[lenOfbytesStr1];
	lstrcpyW(PCmp1,in_CmpStr1);
	UCaseW(PCmp1);
	int lenOfbytesStr2=DStr::GetStrLenthW(in_CmpStr2)+1;
	wchar_t * PCmp2=new wchar_t[lenOfbytesStr2];
	lstrcpyW(PCmp2,in_CmpStr2);
	UCaseW(PCmp2);
	int ret=lstrcmpW(PCmp1,PCmp2);
	delete [] PCmp1;
	delete [] PCmp2;
	return ret;
}
int DStr::CmpStrIgnoreULA(char * in_CmpStr1,char * in_CmpStr2)
{
	DStr BaseStrOP;
	int SizeOfStr1=DStr::GetStrLenthA(in_CmpStr1)+1;
	wchar_t * PCmp1=new wchar_t[SizeOfStr1];
	DStr::CMbsToWcs(PCmp1,in_CmpStr1,SizeOfStr1);
	int SizeOfStr2=DStr::GetStrLenthA(in_CmpStr2)+1;
	wchar_t * PCmp2=new wchar_t[SizeOfStr2];
	DStr::CMbsToWcs(PCmp2,in_CmpStr2,SizeOfStr2);
	int ret=CmpStrIgnoreULW(PCmp1,PCmp2);
	delete [] PCmp1;
	delete [] PCmp2;
	return ret;
}
int DStr::UCaseW(wchar_t * PConvertStr)
{
	if (NULL == PConvertStr)
	{
		return (-1);
	}
	wchar_t * PSave = PConvertStr;
	while (*PConvertStr!=L'\0')
	{
		if (*PConvertStr>=L'a' && *PConvertStr<=L'z')
		{

			*PConvertStr=*PConvertStr-32;
		}
		PConvertStr++;
	}
	return DStr::GetStrLenthW(PSave);
}

int DStr::LCaseW(wchar_t * PConvertStr)
{
	wchar_t * PSave = PConvertStr;
	if (NULL == PConvertStr)
	{
		return (-1);
	}
	while (*PConvertStr!=L'\0')
	{
		if (*PConvertStr>=L'A' && *PConvertStr<=L'Z')
		{

			*PConvertStr=*PConvertStr+32;
		}
		PConvertStr++;
	}
	return DStr::GetStrLenthW(PSave);
}
int DStr::LTrimW(wchar_t * PConvertStr)
{
	if (NULL == PConvertStr)
	{
		return (-1);
	}
	int CutCount=0;
	int Len=DStr::GetStrLenthW(PConvertStr);
	wchar_t * PCurrent=PConvertStr;
	wchar_t * PSave=PConvertStr;
	while (L' '==*PCurrent || L'\r'==*PCurrent || L'\n'==*PCurrent)
	{
		CutCount++;
		PCurrent++;
	}
	int NowLen=Len-CutCount;
	for (int k=0;k<NowLen;k++)
	{
		*PSave=*PCurrent;
		PSave++;
		PCurrent++;
	}
	*PSave=L'\0';
	return DStr::GetStrLenthW(PConvertStr);
}

int DStr::RTrimW(wchar_t * PConvertStr)
{
	if (NULL == PConvertStr)
	{
		return (-1);
	}
	int CutCount=0;
	int Len=DStr::GetStrLenthW(PConvertStr);
	int Index=Len-1;
	wchar_t C=PConvertStr[Index];
	while(L' '==C || L'\r'==C || L'\n'==C)
	{
		CutCount++;
		Index--;
		C=PConvertStr[Index];
	}
	PConvertStr[Index+1]=L'\0';
	return DStr::GetStrLenthW(PConvertStr);
}

int DStr::TrimW(wchar_t * PConvertStr)
{
	if (NULL == PConvertStr)
	{
		return (-1);
	}
	int RetValue=(-1);
	RetValue=LTrimW(PConvertStr);
	RetValue=RTrimW(PConvertStr);
	return RetValue;
}
int DStr::TrimA(char * PConvertStr)
{
	if (NULL == PConvertStr)
	{
		return (-1);
	}
	int RetValue=(-1);
	DWORD lenPConvertStr = DStr::GetStrLenthA(PConvertStr);
	wchar_t * wcsPConvertStr = new wchar_t[lenPConvertStr+1];
	if (DStr::WinMbsToWcs(PConvertStr,wcsPConvertStr,lenPConvertStr+1)>0)
	{
		DWORD iTrimW = TrimW(wcsPConvertStr);
		if (iTrimW>0)
		{
			if (DStr::WinWcsToMbs(wcsPConvertStr,PConvertStr,lenPConvertStr+1)>0)
			{
				RetValue = iTrimW;
			}
		} 
		else
		{
			RetValue = (-1);
		}
	}
	else
	{
		RetValue = (-1);
	}
	delete[] wcsPConvertStr;
	return RetValue;
}
int DStr::GetSubStr_FormHeadToTail_AfterSpecialStrW(wchar_t * PSourceStr,wchar_t * SpecialStr,wchar_t * SubStr,DWORD & NeedSize)
{
	NeedSize = (-1);
	if (NULL == PSourceStr || NULL == SpecialStr)
	{
		return (-1);
	}
	int iLefOfSpecialstr=DStr::GetStrLenthW(SpecialStr);
	int pos=InstrW(PSourceStr,SpecialStr);
	wchar_t * PNow=&PSourceStr[pos+iLefOfSpecialstr];
	NeedSize = (DStr::GetStrLenthW(PNow)+1)*2;
	if (pos>=0)
	{
		if (NULL != SubStr)
		{
			*SubStr=L'\0';
			lstrcpyW(SubStr,PNow);
			return NeedSize;
		}
		else
		{
			return NeedSize;
		}
	}
	else
	{
		return (-1);
	}
}
int DStr::GetSubStr_FormHeadToTail_AfterSpecialStrA(char * PSourceStr,char * SpecialStr,char * SubStr,DWORD & NeedSize)
{
	NeedSize = -1;
	if (NULL == PSourceStr || NULL == SpecialStr)
	{
		return (-1);
	}
	DWORD dwLenPSource = DStr::GetStrLenthA(PSourceStr);
	DWORD dwLenSpecialStr = DStr::GetStrLenthA(SpecialStr);
	wchar_t * wcsPSourceStr = new wchar_t[dwLenPSource + 1];
	wchar_t * wcsSpecialStr = new wchar_t[dwLenSpecialStr + 1];
	if (DStr::WinMbsToWcs(PSourceStr,wcsPSourceStr,dwLenPSource + 1)<=0 ||
		DStr::WinMbsToWcs(SpecialStr,wcsSpecialStr,dwLenSpecialStr + 1)<=0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		return (-1);
	}
	DWORD RetNeedSize =(-1);
	GetSubStr_FormHeadToTail_AfterSpecialStrW(wcsPSourceStr,wcsSpecialStr,NULL,RetNeedSize);
	if (RetNeedSize < 0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		return (-1);
	}
	NeedSize = RetNeedSize/2;
	if (NULL == SubStr)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		return NeedSize;
	}
	wchar_t * wcsBuffer = (wchar_t *)new byte[RetNeedSize];
	if (GetSubStr_FormHeadToTail_AfterSpecialStrW(wcsPSourceStr,wcsSpecialStr,wcsBuffer,RetNeedSize)<0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		delete[] wcsBuffer;
		return (-1);
	}
	if (DStr::WinWcsToMbs(wcsBuffer,SubStr,NeedSize)<=0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		delete[] wcsBuffer;
		return (-1);
	}
	delete[] wcsPSourceStr;
	delete[] wcsSpecialStr;
	delete[] wcsBuffer;
	return NeedSize;
}
int DStr::GetSubStr_FormHeadToTail_BeforeSpecialStrW(wchar_t * PSourceStr,wchar_t * SpecialStr,wchar_t * SubStr,DWORD & NeedSize)
{
	NeedSize = -1;
	if (NULL == PSourceStr || NULL == SpecialStr)
	{
		return (-1);
	}
	int pos=InstrW(PSourceStr,SpecialStr);
	if (pos>=0)
	{
		NeedSize = (pos + 1)*2;
		if (NULL != SubStr)
		{
			memcpy(SubStr,PSourceStr,pos*2);
			SubStr[pos] = L'\0';
			return NeedSize;
		} 
		else
		{
			return NeedSize;
		}
	}
	else
	{
		return (-1);
	}
}
int DStr::GetSubStr_FormHeadToTail_BeforeSpecialStrA(char * PSourceStr,char * SpecialStr,char * SubStr,DWORD & NeedSize)
{
	NeedSize = -1;
	if (NULL == PSourceStr || NULL == SpecialStr)
	{
		return (-1);
	}
	DWORD dwLenPSource = DStr::GetStrLenthA(PSourceStr);
	DWORD dwLenSpecialStr = DStr::GetStrLenthA(SpecialStr);
	wchar_t * wcsPSourceStr = new wchar_t[dwLenPSource + 1];
	wchar_t * wcsSpecialStr = new wchar_t[dwLenSpecialStr + 1];
	if (DStr::WinMbsToWcs(PSourceStr,wcsPSourceStr,dwLenPSource + 1)<=0 ||
		DStr::WinMbsToWcs(SpecialStr,wcsSpecialStr,dwLenSpecialStr + 1)<=0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		return (-1);
	}
	DWORD RetNeedSize =(-1);
	GetSubStr_FormHeadToTail_BeforeSpecialStrW(wcsPSourceStr,wcsSpecialStr,NULL,RetNeedSize);
	if (RetNeedSize < 0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		return (-1);
	}
	NeedSize = RetNeedSize/2;
	if (NULL == SubStr)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		return NeedSize;
	}
	wchar_t * wcsBuffer = (wchar_t *)new byte[RetNeedSize];
	if (GetSubStr_FormHeadToTail_BeforeSpecialStrW(wcsPSourceStr,wcsSpecialStr,wcsBuffer,RetNeedSize)<0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		delete[] wcsBuffer;
		return (-1);
	}
	if (DStr::WinWcsToMbs(wcsBuffer,SubStr,NeedSize)<=0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		delete[] wcsBuffer;
		return (-1);
	}
	delete[] wcsPSourceStr;
	delete[] wcsSpecialStr;
	delete[] wcsBuffer;
	return NeedSize;
}
int DStr::GetSubStr_FormTailToHead_AfterSpecialStrW(wchar_t * PSourceStr,wchar_t * SpecialStr,wchar_t * SubStr,DWORD & NeedSize)
{
	NeedSize = -1;
	if (NULL == PSourceStr || NULL == SpecialStr)
	{
		return (-1);
	}
	int iLenOfSpecialStr=DStr::GetStrLenthW(SpecialStr);
	int pos=Instr_FromTailToHeadW(PSourceStr,SpecialStr);
	wchar_t * PNow=&PSourceStr[pos+iLenOfSpecialStr];
	NeedSize = (DStr::GetStrLenthW(PNow)+1)*2;
	if (pos>=0)
	{
		if (NULL != SubStr)
		{
			*SubStr=L'\0';
			lstrcpyW(SubStr,PNow);
			return NeedSize;
		} 
		else
		{
			return NeedSize;
		}
	}
	else
	{
		return (-1);
	}
}
int DStr::GetSubStr_FormTailToHead_AfterSpecialStrA(char * PSourceStr,char * SpecialStr,char * SubStr,DWORD & NeedSize)
{
	NeedSize = -1;
	if (NULL == PSourceStr || NULL == SpecialStr)
	{
		return (-1);
	}
	DWORD dwLenPSource = DStr::GetStrLenthA(PSourceStr);
	DWORD dwLenSpecialStr = DStr::GetStrLenthA(SpecialStr);
	wchar_t * wcsPSourceStr = new wchar_t[dwLenPSource + 1];
	wchar_t * wcsSpecialStr = new wchar_t[dwLenSpecialStr + 1];
	if (DStr::WinMbsToWcs(PSourceStr,wcsPSourceStr,dwLenPSource + 1)<=0 ||
		DStr::WinMbsToWcs(SpecialStr,wcsSpecialStr,dwLenSpecialStr + 1)<=0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		return (-1);
	}
	DWORD RetNeedSize =(-1);
	GetSubStr_FormTailToHead_AfterSpecialStrW(wcsPSourceStr,wcsSpecialStr,NULL,RetNeedSize);
	if (RetNeedSize < 0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		return (-1);
	}
	NeedSize = RetNeedSize/2;
	if (NULL == SubStr)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		return NeedSize;
	}
	wchar_t * wcsBuffer = (wchar_t *)new byte[RetNeedSize];
	if (GetSubStr_FormTailToHead_AfterSpecialStrW(wcsPSourceStr,wcsSpecialStr,wcsBuffer,RetNeedSize)<0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		delete[] wcsBuffer;
		return (-1);
	}
	if (DStr::WinWcsToMbs(wcsBuffer,SubStr,NeedSize)<=0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		delete[] wcsBuffer;
		return (-1);
	}
	delete[] wcsPSourceStr;
	delete[] wcsSpecialStr;
	delete[] wcsBuffer;
	return NeedSize;
}
int DStr::GetSubStr_FormTailToHead_BeforeSpecialStrW(wchar_t * PSourceStr,wchar_t * SpecialStr,wchar_t * SubStr,DWORD & NeedSize)
{
	NeedSize = -1;
	if (NULL == PSourceStr || NULL == SpecialStr)
	{
		return (-1);
	}
	int pos=Instr_FromTailToHeadW(PSourceStr,SpecialStr);
	if (pos>=0)
	{
		NeedSize = (pos + 1)*2;
		if (NULL != SubStr)
		{
			memcpy(SubStr,PSourceStr,pos*2);
			SubStr[pos] = L'\0';
			return NeedSize;
		} 
		else
		{
			return NeedSize;
		}
	}
	else
	{
		return (-1);
	}
}
int DStr::GetSubStr_FormTailToHead_BeforeSpecialStrA(char * PSourceStr,char * SpecialStr,char * SubStr,DWORD & NeedSize)
{
	NeedSize = -1;
	if (NULL == PSourceStr || NULL == SpecialStr)
	{
		return (-1);
	}
	DWORD dwLenPSource = DStr::GetStrLenthA(PSourceStr);
	DWORD dwLenSpecialStr = DStr::GetStrLenthA(SpecialStr);
	wchar_t * wcsPSourceStr = new wchar_t[dwLenPSource + 1];
	wchar_t * wcsSpecialStr = new wchar_t[dwLenSpecialStr + 1];
	if (DStr::WinMbsToWcs(PSourceStr,wcsPSourceStr,dwLenPSource + 1)<=0 ||
		DStr::WinMbsToWcs(SpecialStr,wcsSpecialStr,dwLenSpecialStr + 1)<=0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		return (-1);
	}
	int RetNeedSize =(-1);
	DWORD dwNeedSize;
	RetNeedSize = GetSubStr_FormTailToHead_BeforeSpecialStrW(wcsPSourceStr,wcsSpecialStr,NULL,dwNeedSize);
	if (RetNeedSize < 0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		return (-1);
	}
	NeedSize = RetNeedSize/2;
	if (NULL == SubStr)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		return NeedSize;
	}
	wchar_t * wcsBuffer = (wchar_t *)new byte[RetNeedSize];
	if (GetSubStr_FormTailToHead_BeforeSpecialStrW(wcsPSourceStr,wcsSpecialStr,wcsBuffer,dwNeedSize)<0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		delete[] wcsBuffer;
		return (-1);
	}
	if (DStr::WinWcsToMbs(wcsBuffer,SubStr,NeedSize)<=0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsSpecialStr;
		delete[] wcsBuffer;
		return (-1);
	}
	delete[] wcsPSourceStr;
	delete[] wcsSpecialStr;
	delete[] wcsBuffer;
	return NeedSize;
}
int DStr::GetSubStr_BetweenSpecialStrW(wchar_t * PSourceStr,wchar_t * PLeft,wchar_t * PRight,wchar_t * SubStr,DWORD & NeedSize)
{
	NeedSize = (-1);
	if (NULL == PSourceStr || NULL == PLeft || NULL == PRight)
	{
		return (-1);
	}
	int RetCount=0;
	int dwPosLeft = InstrW(PSourceStr,PLeft);
	int dwPosRight = InstrW(PSourceStr,PRight);
	int dwLenLeft = DStr::GetStrLenthW(PLeft);
	if (dwPosLeft>=0 && dwPosRight>=0)
	{
		DWORD TestNeedCnt = dwPosRight - dwPosLeft - dwLenLeft + 1;
		if (TestNeedCnt>=0)
		{
			NeedSize = TestNeedCnt * 2;
			if (NULL != SubStr)
			{
				wchar_t * PCopyStart = PSourceStr + dwPosLeft + dwLenLeft;
				memcpy(SubStr,PCopyStart,(TestNeedCnt-1)*2);
				SubStr[TestNeedCnt-1] = L'\0';
				RetCount = DStr::GetStrLenthW(SubStr);
				return NeedSize;
			} 
			else
			{
				return NeedSize;
			}
		} 
		else
		{
			return (-1);
		}
	} 
	else
	{
		return (-1);
	}
}
int DStr::GetSubStr_BetweenSpecialStrA(char * PSourceStr,char * PLeft,char * PRight,char * SubStr,DWORD & NeedSize)
{
	NeedSize = -1;
	if (NULL == PSourceStr || NULL == PLeft || NULL == PRight)
	{
		return (-1);
	}
	DWORD dwLenPSource = DStr::GetStrLenthA(PSourceStr);
	DWORD dwLenPLeft = DStr::GetStrLenthA(PLeft);
	DWORD dwLenPRight = DStr::GetStrLenthA(PRight);
	wchar_t * wcsPSourceStr = new wchar_t[dwLenPSource + 1];
	wchar_t * wcsPLeft = new wchar_t[dwLenPLeft + 1];
	wchar_t * wcsPRight = new wchar_t[dwLenPRight + 1];
	if (DStr::WinMbsToWcs(PSourceStr,wcsPSourceStr,dwLenPSource + 1)<=0 ||
		DStr::WinMbsToWcs(PLeft,wcsPLeft,dwLenPLeft + 1)<=0 ||
		DStr::WinMbsToWcs(PRight,wcsPRight,dwLenPRight + 1)<=0 )
	{
		delete[] wcsPSourceStr;
		delete[] wcsPLeft;
		delete[] wcsPRight;
		return (-1);
	}
	DWORD RetNeedSize =(-1);
	GetSubStr_BetweenSpecialStrW(wcsPSourceStr,wcsPLeft,wcsPRight,NULL,RetNeedSize);
	if (RetNeedSize < 0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsPLeft;
		delete[] wcsPRight;
		return (-1);
	}
	NeedSize = RetNeedSize/2;
	if (NULL == SubStr)
	{
		delete[] wcsPSourceStr;
		delete[] wcsPLeft;
		delete[] wcsPRight;
		return NeedSize;
	}
	wchar_t * wcsBuffer = (wchar_t *)new byte[RetNeedSize];
	if (GetSubStr_BetweenSpecialStrW(wcsPSourceStr,wcsPLeft,wcsPRight,wcsBuffer,RetNeedSize)<0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsPLeft;
		delete[] wcsPRight;
		delete[] wcsBuffer;
		return (-1);
	}
	if (DStr::WinWcsToMbs(wcsBuffer,SubStr,NeedSize)<=0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsPLeft;
		delete[] wcsPRight;
		delete[] wcsBuffer;
		return (-1);
	}
	delete[] wcsPSourceStr;
	delete[] wcsPLeft;
	delete[] wcsPRight;
	delete[] wcsBuffer;
	return NeedSize;
}
int DStr::ReplaceOneStr_FormHeadToTailW(wchar_t * PSourceStr,DWORD dwSize, wchar_t * StrWantReplace, wchar_t * StrReplace)
{
	DWORD lenPSourceStr = DStr::GetStrLenthW(PSourceStr);
	DWORD lenStrWantReplace = DStr::GetStrLenthW(StrWantReplace);
	DWORD lenStrReplace = DStr::GetStrLenthW(StrReplace);
	DWORD needNewSize = (lenPSourceStr-lenStrWantReplace+lenStrReplace+1)*2;
	if (needNewSize > dwSize)
	{
		return (-1);
	}
	wchar_t * pTempPSourceStr = new wchar_t[dwSize];
	memcpy(pTempPSourceStr,PSourceStr,dwSize);
	int posRepBegin = InstrW(PSourceStr,StrWantReplace);
	if (posRepBegin<0)
	{
		delete[] pTempPSourceStr;
		return (-1);
	}
	wchar_t * pCopyOldLastStr = PSourceStr + posRepBegin + lenStrWantReplace;
	wchar_t * pCopyNewLastStr = pTempPSourceStr + posRepBegin + lenStrReplace;
	DWORD CntCopy = lenPSourceStr - posRepBegin - lenStrWantReplace + 1;
	memcpy(pCopyNewLastStr,pCopyOldLastStr,2*CntCopy);
	/* set replace string */
	memcpy(pCopyNewLastStr-lenStrReplace,StrReplace,lenStrReplace*2);
	memcpy(PSourceStr,pTempPSourceStr,needNewSize);
	delete[] pTempPSourceStr;
	return needNewSize;

}
int DStr::ReplaceOneStr_FormHeadToTailA(char * PSourceStr,DWORD dwSize, char * StrWantReplace, char * StrReplace)
{
	DWORD dwLenStrWantReplace = DStr::GetStrLenthA(StrWantReplace);
	DWORD dwLenStrReplace = DStr::GetStrLenthA(StrReplace);
	wchar_t * wcsPSourceStr = new wchar_t[dwSize];
	wchar_t * wcsStrWantReplace = new wchar_t[dwLenStrWantReplace+1];
	wchar_t * wcsStrReplace = new wchar_t[dwLenStrReplace+1];
	memset(wcsPSourceStr,0,dwSize*2);
	memset(wcsStrWantReplace,0,(dwLenStrWantReplace+1)*2);
	memset(wcsStrReplace,0,(dwLenStrReplace+1)*2);
	if (DStr::WinMbsToWcs(PSourceStr,wcsPSourceStr,dwSize)<0 ||
		DStr::WinMbsToWcs(StrWantReplace,wcsStrWantReplace,dwLenStrWantReplace+1)<0 ||
		DStr::WinMbsToWcs(StrReplace,wcsStrReplace,dwLenStrReplace+1)<0)
	{
		delete[] wcsPSourceStr;
		delete[] wcsStrWantReplace;
		delete[] wcsStrReplace;
		return (-1);
	}
	int RetValue = (-1);
	RetValue = ReplaceOneStr_FormHeadToTailW(wcsPSourceStr,dwSize*2,wcsStrWantReplace,wcsStrReplace);
	if (RetValue<0)
	{
		RetValue = (-1);
	}
	else
	{
		if (DStr::WinWcsToMbs(wcsPSourceStr,PSourceStr,dwSize)<=0)
		{
			RetValue = (-1);
		}
	}
	delete[] wcsPSourceStr;
	delete[] wcsStrWantReplace;
	delete[] wcsStrReplace;
	return ((-1) == RetValue)?RetValue:RetValue/2 ;
}
int DStr::WinWcsToMbs(LPCWSTR lpWideCharStr,int cchWideChar,LPSTR lpMultiByteStr,int cbMultiByte)
{
	return WideCharToMultiByte(CP_ACP,0,lpWideCharStr,cchWideChar,lpMultiByteStr,cbMultiByte,NULL,NULL);
}
int DStr::WinMbsToWcs(LPCSTR lpMultiByteStr,int cbMultiByte, LPWSTR lpWideCharStr,int cchWideChar)
{
	return MultiByteToWideChar(CP_ACP,0,lpMultiByteStr,cbMultiByte,lpWideCharStr,cchWideChar);
}
int DStr::WinWcsToMbs(LPCWSTR lpWideCharStr,LPSTR lpMultiByteStr,int cbMultiByte)
{
	return WinWcsToMbs(lpWideCharStr,-1,lpMultiByteStr,cbMultiByte);
}
int DStr::WinMbsToWcs(LPCSTR lpMultiByteStr,LPWSTR lpWideCharStr,int cchWideChar)
{
	return WinMbsToWcs(lpMultiByteStr,-1,lpWideCharStr,cchWideChar);
}
int DStr::CWcsToMbs(LPSTR lpMultiByteStr,LPCWSTR lpWideCharStr,int cbMultiByte)
{
	size_t iConvertedCnt = 0;
	int iRetErrNo = wcstombs_s(&iConvertedCnt,
		lpMultiByteStr,cbMultiByte,lpWideCharStr,cbMultiByte);
	if (0==iRetErrNo)
	{
		return iConvertedCnt;
	} 
	else
	{
		return (-1);
	}
}
int DStr::CMbsToWcs(LPWSTR lpWideCharStr,LPCSTR lpMultiByteStr,int cchWideChar)
{
	size_t iConvertedCnt = 0;
	int iRetErrNo = mbstowcs_s(&iConvertedCnt,
		lpWideCharStr,cchWideChar,lpMultiByteStr,cchWideChar);
	if (0==iRetErrNo)
	{
		return iConvertedCnt;
	} 
	else
	{
		return (-1);
	}
}

bool DStr::IsNumberW(wchar_t * PStr)
{
	if (* PStr == L'\0')
	{
		return false;
	}
	bool BRet=true;
	int LenOfStr=DStr::GetStrLenthW(PStr);
	for(int i=0;i<LenOfStr;i++)
	{
		if ( PStr[i]>L'9' ||  PStr[i]<L'0')
		{
			BRet=false;
		}
	}
	return BRet;
}
bool DStr::IsNumberA(char * PStr)
{
	if (*PStr == '\0')
	{
		return false;
	}
	bool BRet=true;
	int LenOfStr=DStr::GetStrLenthA(PStr);
	for(int i=0;i<LenOfStr;i++)
	{
		if ( PStr[i]>'9' ||  PStr[i]<'0')
		{
			BRet=false;
		}
	}
	return BRet;
}
bool DStr::IsBeginWithW(wchar_t * PStr, wchar_t * CheckBegin)
{
	if (0 == Instr_FromHeadToTailW(PStr,CheckBegin))
	{
		return true;
	} 
	else
	{
		return false;
	}
}
bool DStr::IsBeginWithA(char * PStr, char * CheckBegin)
{
	int LenPStr = DStr::GetStrLenthA(PStr);
	int LenCheckBegin = DStr::GetStrLenthA(CheckBegin);
	wchar_t * wcsPStr = new wchar_t[LenPStr+1];
	wchar_t * wcsCheckBegin = new wchar_t[LenCheckBegin+1];
	WinMbsToWcs(PStr,LenPStr+1,wcsPStr,LenPStr+1);
	WinMbsToWcs(CheckBegin,LenCheckBegin+1,wcsCheckBegin,LenCheckBegin+1);
	bool bRet = IsBeginWithW(wcsPStr,wcsCheckBegin);
	delete[] wcsPStr;
	delete[] wcsCheckBegin;
	return bRet;
}
bool DStr::IsEndWithW(wchar_t * PStr, wchar_t * CheckEnd)
{
	int FindPos = Instr_FromTailToHeadW(PStr,CheckEnd);
	int LenOfPstr = DStr::GetStrLenthW(PStr);
	int LenCheckEnd = DStr::GetStrLenthW(CheckEnd);
	if (FindPos + LenCheckEnd == LenOfPstr)
	{
		return true;
	} 
	else
	{
		return false;
	}
}
bool DStr::IsEndWithA(char * PStr, char * CheckEnd)
{
	int LenPStr = DStr::GetStrLenthA(PStr);
	int LenCheckEnd = DStr::GetStrLenthA(CheckEnd);
	wchar_t * wcsPStr = new wchar_t[LenPStr+1];
	wchar_t * wcsCheckEnd = new wchar_t[LenCheckEnd+1];
	WinMbsToWcs(PStr,LenPStr+1,wcsPStr,LenPStr+1);
	WinMbsToWcs(CheckEnd,LenCheckEnd+1,wcsCheckEnd,LenCheckEnd+1);
	bool bRet = IsEndWithW(wcsPStr,wcsCheckEnd);
	delete[] wcsPStr;
	delete[] wcsCheckEnd;
	return bRet;
}
int DStr::GetStrLenthW(const wchar_t * PStr)
{
	return lstrlenW(PStr);
}
int DStr::GetStrLenthA(const char * PStr)
{
	return lstrlenA(PStr);
}
int DStr::GetStrSizeW(const wchar_t * PStr)
{
	return (GetStrLenthW(PStr)+1)*2;
}
int DStr::GetStrSizeA(const char * PStr)
{
	int iSize=0;
	while (true)
	{
		if ('\0' != PStr[iSize])
		{
			iSize++;
		}
		else
		{
			break;
		}
	}
	return iSize+1;
}
const char * DStr::GetCstFileShortNameFormFileName(const char * PStr)
{
	if (DStr::InstrA((char*)PStr,"\\")>0)
	{
		for (int i= lstrlenA(PStr);i>0;i--)
		{
			if ('\\' == PStr[i])
			{
				return (const char *)(&PStr[i]+1);
			}
		}
	} 
	return PStr;
}

using namespace std;

std::list<std::string> DString::split(std::string s, std::string delim, bool ignoreNull)
{
	std::list<std::string> ret;

	if (s.empty())
	{
		return ret;
	}

	string tmp;
	string::size_type pos_begin = s.find_first_not_of(delim);
	string::size_type comma_pos = 0;

	if (!ignoreNull)
	{
		if (pos_begin != string::npos && s.find(delim) == 0)
		{
			ret.push_back("");
		}
	}

	while (pos_begin != string::npos)
	{
		comma_pos = s.find(delim, pos_begin);
		if (comma_pos != string::npos)
		{
			tmp = s.substr(pos_begin, comma_pos - pos_begin);
			pos_begin = comma_pos + delim.length();
		}
		else
		{
			tmp = s.substr(pos_begin);
			pos_begin = comma_pos;
		}

		if (!tmp.empty())
		{
			ret.push_back(tmp);
			tmp.clear();
		}
		else
		{
			if (!ignoreNull)
			{
				ret.push_back("");
				tmp.clear();
			}
		}
	}

	return ret;
}

std::string DString::replace(std::string s, std::string strSrc, std::string strDes)
{
	std::string ret;
	ret.assign(s);

	std::string::size_type pos = 0;
	std::string::size_type srcLen = strSrc.size();
	std::string::size_type desLen = strDes.size();
	pos = ret.find(strSrc, pos);
	while ((pos != std::string::npos))
	{
		ret.replace(pos, srcLen, strDes);
		pos = ret.find(strSrc, (pos + desLen));
	}
	return ret;
}

/* DFile class implement */

DFile::DFile()
{
	memset(m_FileName,0,MaxFileFullNameLen);
	m_bIsBinaryFile = false;
	m_FileSize = 0;
	m_pFile = NULL;
}
DFile::~DFile()
{
	if (NULL != m_pFile)
	{
		if (Close())
		{
			memset(m_FileName,0,MaxFileFullNameLen);
			m_FileSize = 0;
			m_pFile = NULL;
		}
	}
}
bool DFile::Open(char * mbsFileName, OPENMODE eOpenMode)
{
	if (NULL == mbsFileName)
	{
		return false;
	}
	if (NULL != m_pFile)
	{
		return false;
	}
	char OpenModeStr[4];
	memset(OpenModeStr,0,4);
	switch(eOpenMode)
	{
	case OPEN_R:
		lstrcpyA(OpenModeStr,"r");
		break;
	case OPEN_W:
		lstrcpyA(OpenModeStr,"w");
		break;
	case OPEN_A:
		lstrcpyA(OpenModeStr,"a");
		break;
	case OPEN_RP:
		lstrcpyA(OpenModeStr,"r+");
		break;
	case OPEN_WP:
		lstrcpyA(OpenModeStr,"w+");
		break;
	case OPEN_AP:
		lstrcpyA(OpenModeStr,"a+");
		break;
	case OPEN_RTP:
		lstrcpyA(OpenModeStr,"rt+");
		break;
	case OPEN_WTP:
		lstrcpyA(OpenModeStr,"wt+");
		break;
	case OPEN_ATP:
		lstrcpyA(OpenModeStr,"at+");
		break;
	case OPEN_RBP:
		lstrcpyA(OpenModeStr,"rb+");
		break;
	case OPEN_WBP:
		lstrcpyA(OpenModeStr,"wb+");
		break;
	case OPEN_ABP:
		lstrcpyA(OpenModeStr,"ab+");
		break;
	default:
		return false;
	}
	m_pFile = NULL;
	int iRetErrNo = -1;
	/* GetSize begin */
	iRetErrNo = fopen_s(&m_pFile,mbsFileName,"rb+");
	if (NULL != m_pFile && 0 == iRetErrNo)
	{
		if (!Seek(0,SEEK_FROM_END))
		{
			fclose(m_pFile);
			return false;
		}
		m_FileSize = ftell(m_pFile);
		if (0!=fclose(m_pFile))
		{
			return false;
		}
	}
	/* GetSize end */
	m_pFile = NULL;
	iRetErrNo = -1;
	iRetErrNo = fopen_s(&m_pFile,mbsFileName,OpenModeStr);
	if (NULL != m_pFile && 0 == iRetErrNo)
	{
		lstrcpyA(m_FileName,mbsFileName);
		if (DStr::InstrA(OpenModeStr,"b")>0)
		{
			m_bIsBinaryFile = true;
		}
		return true;
	} 
	return false;
}
bool DFile::Close()
{
	if (NULL == m_pFile)
	{
		return false;
	}
	DWORD dwFlag = fclose(m_pFile);
	if (0 == dwFlag)
	{
		m_pFile = NULL;
		return true;
	} 
	else
	{
		return false;
	}
}
bool DFile::IsOpen()
{
	if (NULL != m_pFile)
	{
		return true;
	} 
	else
	{
		return false;
	}
}
bool DFile::Seek(DWORD dwOffset, SEEK_FROMWHERE eFromWhere)
{
	if (NULL == m_pFile)
	{
		return false;
	}
	DWORD dwSeekFlag = -1;
	switch(eFromWhere)
	{
	case SEEK_FROM_BEGIN:
		dwSeekFlag = SEEK_SET;
		break;
	case SEEK_FROM_CUR:
		dwSeekFlag = SEEK_CUR;
		break;
	case SEEK_FROM_END:
		dwSeekFlag = SEEK_END;
		break;
	default:
		return false;
	}
	int FlagSeek = fseek(m_pFile,dwOffset,dwSeekFlag);
	if (0 == FlagSeek)
	{
		return true;
	}
	else
	{
		return false;
	}
}
DWORD DFile::Read(void * pvBuff, DWORD dwSize)
{
	if (NULL == m_pFile)
	{
		return (-1);
	}
	return fread(pvBuff,1,dwSize,m_pFile);
}
DWORD DFile::Write(void * pvBuff, DWORD dwSize)
{
	if (NULL == m_pFile)
	{
		return (-1);
	}
	DWORD iCntOfSpaceCharacter = 0;
	if (!m_bIsBinaryFile)
	{
		/* when write text file 0x0D=space, it will write 2 character 0x0D 0x0A (enter space) */
		for (DWORD i=0;i<dwSize;i++)
		{
			if ( 0x0A == ((byte*)pvBuff)[i])
			{
				iCntOfSpaceCharacter ++;
			}
		}
	}
	return fwrite(pvBuff,1,dwSize,m_pFile) + iCntOfSpaceCharacter;
}
DWORD DFile::GetFileSize()
{
	if (NULL == m_pFile)
	{
		return (-1);
	}
	return m_FileSize;
}
DWORD DFile::GetCurrentOffsetFromBegin()
{
	if (NULL == m_pFile)
	{
		return (-1);
	}
	return ftell(m_pFile);
}
bool DFile::IsCurrentOffsetEOF()
{
	if (NULL == m_pFile)
	{
		return false;
	}
	int iEOFFlag = feof(m_pFile);
	if (iEOFFlag > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
const char * DFile::GetFileName()
{
	if (NULL != m_pFile && 0 != lstrcmpA(m_FileName,""))
	{
		return (const char *)&m_FileName;
	}
	else
	{
		return NULL;
	}
}
bool DFile::CreateEmplyFile(char * mbsFileName)
{
	DFile cFile;
	if (!cFile.Open(mbsFileName,DFile::OPEN_WBP))
	{
		return false;
	}
	if (!cFile.Close())
	{
		return false;
	}
	return true;
}
bool DFile::IsExist(char * mbsFileName)
{
	return DFile::CheckAccess(mbsFileName,DFile::FILEACCESS_EXIST);
}
DWORD DFile::GetFileSize(char * mbsFileName)
{
	DWORD dwRetFileSize=-1;
	DFile cDFile;
	if (!cDFile.Open(mbsFileName,DFile::OPEN_RBP))
	{
		return (-1);
	}
	dwRetFileSize = cDFile.GetFileSize();
	if (!cDFile.Close())
	{
		return (-1);
	}
	return dwRetFileSize;
}
bool DFile::Copy(char * mbsDestFileName,char* mbsSourceFileName,bool bOverwrite)
{
	if (!bOverwrite)
	{
		if (DFile::CheckAccess(mbsDestFileName,FILEACCESS_EXIST))
		{
			return false;
		}
	}
	if (!DFile::CheckAccess(mbsSourceFileName,FILEACCESS_EXIST))
	{
		return false;
	}
	DFile cSFile;
	DFile cDFile;
	if (!cSFile.Open(mbsSourceFileName,DFile::OPEN_RBP))
	{
		return false;
	}
	if (!cDFile.Open(mbsDestFileName,DFile::OPEN_WBP))
	{
		cSFile.Close();
		return false;
	}
	/* copy process */
	byte TempBurrer[256];
	int itempRead=-1;
	int itempWrite=-1;
	while (true)
	{
		itempRead = cSFile.Read(TempBurrer,256);
		if ((-1) == itempRead)
		{
			cSFile.Close();
			cDFile.Close();
			Delete(mbsDestFileName);
			return false;
		}
		if (itempRead == 256)
		{
			itempWrite = cDFile.Write(TempBurrer,itempRead);
			if (itempRead == itempWrite)
			{
				continue;
			}
			else
			{
				cSFile.Close();
				cDFile.Close();
				Delete(mbsDestFileName);
				return false;
			}
		} 
		else
		{
			itempWrite = cDFile.Write(TempBurrer,itempRead);
			if (itempRead == itempWrite)
			{
				break;
			}
			else
			{
				cSFile.Close();
				cDFile.Close();
				Delete(mbsDestFileName);
				return false;
			}
		}
	}

	if (!cSFile.Close())
	{
		return false;
	}
	if (!cDFile.Close())
	{
		return false;
	}
	return true;
}
bool DFile::Move(char * mbsDestFileName,char* mbsSourceFileName,bool bOverwrite)
{
	if (Copy(mbsDestFileName,mbsSourceFileName,bOverwrite))
	{
		if (Delete(mbsSourceFileName))
		{
			return true;
		} 
		else
		{
			Delete(mbsDestFileName);
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool DFile::Delete(char * mbsFileName)
{
	int iRetRmove = remove(mbsFileName);
	if (0 == iRetRmove)
	{
		return true;
	} 
	else
	{
		return false;
	}
}
bool DFile::CheckAccess(char * mbsFileName,FILEACCESS eAccess)
{
	if (NULL == mbsFileName)
	{
		return false;
	}
	DWORD dwAccessModeCode = -1;
	switch(eAccess)
	{
	case FILEACCESS_EXIST:
		dwAccessModeCode = 0;
		break;
	case FILEACCESS_EXCUTE:
		dwAccessModeCode = 1;
		break;
	case FILEACCESS_WRITE:
		dwAccessModeCode = 2;
		break;
	case FILEACCESS_READ:
		dwAccessModeCode = 4;
		break;
	case FILEACCESS_READWRITE:
		dwAccessModeCode = 6;
		break;
	default:
		break;
	}
	DWORD dwAccessRet = _access(mbsFileName,dwAccessModeCode);
	if (0 == dwAccessRet)
	{
		return true;
	} 
	else
	{
		return false;
	}
}

/* DDir class implement */

bool DDir::IsExist(char * mbsDirName)
{
	bool bRetValue = false;
	long Handle = -1;
	char StrFindName[DFile::MaxFileFullNameLen];
	memset(StrFindName,0,DFile::MaxFileFullNameLen);
	lstrcatA(StrFindName,mbsDirName);
	_finddata_t fdinfo;
	/* root disk check */
	if (':' == mbsDirName[1] && 2 == DStr::GetStrLenthA(mbsDirName))
	{
		lstrcatA(StrFindName,"\\*");
		Handle = _findfirst(StrFindName,&fdinfo);
		if((-1) == Handle)
		{
			_findclose(Handle);
			return false;
		}
		else
		{
			_findclose(Handle);
			return true;
		}
	}
	Handle = _findfirst(StrFindName,&fdinfo);
	if((-1) == Handle)
	{
		_findclose(Handle);
		return false;
	}
	if ( (fdinfo.attrib & _A_SUBDIR) == _A_SUBDIR)
	{
		bRetValue = true;
	}
	_findclose(Handle);
	return bRetValue;
}
bool DDir::IsEmpty(char * mbsDirName)
{
	if (!IsExist(mbsDirName))
	{
		return true;
	}
	char FindFirstName[DFile::MaxFileFullNameLen];
	memset(FindFirstName,0,DFile::MaxFileFullNameLen);
	lstrcatA(FindFirstName,mbsDirName);
	lstrcatA(FindFirstName,"\\*");
	long Handle = -1;
	_finddata_t FdInfo;
	memset(&FdInfo,0,sizeof(_finddata_t));
	Handle = _findfirst(FindFirstName,&FdInfo);
	do 
	{
		char TempDirName[DFile::MaxFileFullNameLen];
		memset(TempDirName,0,DFile::MaxFileFullNameLen);
		lstrcatA(TempDirName,mbsDirName);
		lstrcatA(TempDirName,"\\");
		lstrcatA(TempDirName,FdInfo.name);
		if (0 == lstrcmpA(FdInfo.name,".") || 0 == lstrcmpA(FdInfo.name,"..") )
		{
			continue;
		}
		_findclose(Handle);
		return false;
	} while ( (-1) != _findnext(Handle,&FdInfo));
	_findclose(Handle);
	return true;
}
bool DDir::CreateDir(char * mbsDirName, bool bOverwrite)
{
	if (!bOverwrite)
	{
		if (IsExist(mbsDirName))
		{
			return false;
		}
	}
	if (IsExist(mbsDirName))
	{
		if (!RemoveDir(mbsDirName))
		{
			return false;
		}
	}
	if (0 == _mkdir(mbsDirName))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool DDir::CreateDirWithParent(char * mbsDirName, bool bOverwrite)
{
	if (!bOverwrite)
	{
		if (IsExist(mbsDirName))
		{
			return false;
		}
	}
	if (IsExist(mbsDirName))
	{
		if (!RemoveDir(mbsDirName))
		{
			return false;
		}
	}
	return CreateDirWithParent_Help(mbsDirName);
}
bool DDir::CreateDirWithParent_Help(char * mbsDirName)
{
	char mbsAbsDirName[DFile::MaxFileFullNameLen];
	memset(mbsAbsDirName,0,DFile::MaxFileFullNameLen);
	lstrcpyA(mbsAbsDirName,mbsDirName);
	if ((-1)==GetAbsoluteDir(mbsDirName,mbsAbsDirName,DFile::MaxFileFullNameLen))
	{
		return false;
	}
	char ParentDir[DFile::MaxFileFullNameLen];
	memset(ParentDir,0,DFile::MaxFileFullNameLen);
	lstrcpyA(ParentDir,mbsDirName);
	for (int i= DStr::GetStrLenthA(ParentDir)-1; i>=0;i--)
	{
		if ('\\'==ParentDir[i])
		{
			ParentDir[i] = '\0';
			break;
		}
		if (0 == i)
		{
			if (IsExist(mbsDirName))
			{
				return true;
			} 
			else
			{
				CreateDir(mbsDirName,false);
				if (IsExist(mbsDirName))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	/* first level dir */
	if (DStr::Instr_FromHeadToTailA(ParentDir,"\\") == DStr::Instr_FromTailToHeadA(ParentDir,"\\") &&
		DStr::Instr_FromHeadToTailA(ParentDir,"\\") > 0) 
	{
		CreateDir(ParentDir,false);
	}
	
	bool bCreateParent = false;
	if (!IsExist(ParentDir))
	{
		bCreateParent = CreateDirWithParent(ParentDir);
	}
	else
	{
		bCreateParent = true;
	}
	return bCreateParent & CreateDir(mbsDirName,false);
}
bool DDir::RemoveDir(char * mbsDirName)
{
	if (!IsExist(mbsDirName))
	{
		return true;
	}
	char FindFirstName[DFile::MaxFileFullNameLen];
	memset(FindFirstName,0,DFile::MaxFileFullNameLen);
	lstrcatA(FindFirstName,mbsDirName);
	lstrcatA(FindFirstName,"\\*");
	long Handle = -1;
	_finddata_t FdInfo;
	memset(&FdInfo,0,sizeof(_finddata_t));
	Handle = _findfirst(FindFirstName,&FdInfo);
	do 
	{
		char TempDirName[DFile::MaxFileFullNameLen];
		memset(TempDirName,0,DFile::MaxFileFullNameLen);
		lstrcatA(TempDirName,mbsDirName);
		lstrcatA(TempDirName,"\\");
		lstrcatA(TempDirName,FdInfo.name);
		if (0 == lstrcmpA(FdInfo.name,".") || 0 == lstrcmpA(FdInfo.name,"..") )
		{
			continue;
		}
		if((FdInfo.attrib & _A_SUBDIR) == _A_SUBDIR)
		{
			RemoveDir(TempDirName);
		}
		else
		{
			DFile::Delete(TempDirName);
		}
	} while ( (-1) != _findnext(Handle,&FdInfo));
	_findclose(Handle);
	_rmdir(mbsDirName);
	if (!IsExist(mbsDirName))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool DDir::ClearDir(char * mbsDirName)
{
	if (!IsExist(mbsDirName))
	{
		return true;
	}
	char FindFirstName[DFile::MaxFileFullNameLen];
	memset(FindFirstName,0,DFile::MaxFileFullNameLen);
	lstrcatA(FindFirstName,mbsDirName);
	lstrcatA(FindFirstName,"\\*");
	long Handle = -1;
	_finddata_t FdInfo;
	memset(&FdInfo,0,sizeof(_finddata_t));
	Handle = _findfirst(FindFirstName,&FdInfo);
	do 
	{
		char TempDirName[DFile::MaxFileFullNameLen];
		memset(TempDirName,0,DFile::MaxFileFullNameLen);
		lstrcatA(TempDirName,mbsDirName);
		lstrcatA(TempDirName,"\\");
		lstrcatA(TempDirName,FdInfo.name);
		if (0 == lstrcmpA(FdInfo.name,".") || 0 == lstrcmpA(FdInfo.name,"..") )
		{
			continue;
		}
		if((FdInfo.attrib & _A_SUBDIR) == _A_SUBDIR)
		{
			RemoveDir(TempDirName);
		}
		else
		{
			DFile::Delete(TempDirName);
		}
	} while ( (-1) != _findnext(Handle,&FdInfo));
	_findclose(Handle);
	if (IsEmpty(mbsDirName))
	{
		return true;
	} 
	else
	{
		return false;
	}
}
DWORD DDir::GetAbsoluteDir(char * CurrentDir,char * RelativeDir,char * OutAbsoluteDir,DWORD dwSize)
{
	if (NULL == RelativeDir || NULL == OutAbsoluteDir)
	{
		return (-1);
	}
	/* RelativeDir is absolute */
	if (':' == RelativeDir[1])
	{
		memcpy(OutAbsoluteDir,RelativeDir,DStr::GetStrLenthA(RelativeDir)+1);
		return DStr::GetStrLenthA(RelativeDir)+1;
	}
	char TempCurrentDir[DFile::MaxFileFullNameLen];
	lstrcpyA(TempCurrentDir,CurrentDir);
	char TempRelativeDir[DFile::MaxFileFullNameLen];
	lstrcpyA(TempRelativeDir,RelativeDir);
	char * PTempRelativeDir = TempRelativeDir;
	while(true)
	{
		if (DStr::IsBeginWithA(PTempRelativeDir,".."))
		{
			char CurParentDir[DFile::MaxFileFullNameLen];
			if ((-1)==DDir::GetParentDir(TempCurrentDir,CurParentDir,DFile::MaxFileFullNameLen))
			{
				return (-1);
			}
			lstrcpyA(TempCurrentDir,CurParentDir);
			PTempRelativeDir=PTempRelativeDir+3;
		} 
		else
		{
			if ('.' == (*PTempRelativeDir))
			{
				PTempRelativeDir++;
			}
			if ('\\' == (*PTempRelativeDir))
			{
				PTempRelativeDir++;
			}
			break;
		}
	}
	char TempAbsDir[DFile::MaxFileFullNameLen];
	lstrcpyA(TempAbsDir,TempCurrentDir);
	lstrcatA(TempAbsDir,"\\");
	lstrcatA(TempAbsDir,PTempRelativeDir);
	DWORD dwNS = DStr::GetStrLenthA(TempAbsDir)+1;
	if (dwSize >= dwNS)
	{
		lstrcpyA(OutAbsoluteDir,TempAbsDir);
	}
	return dwNS;
}
DWORD DDir::GetAbsoluteDir(char * RelativeDir,char * OutAbsoluteDir,DWORD dwSize)
{
	char mbsCurrentDir[DFile::MaxFileFullNameLen];
	memset(mbsCurrentDir,0,DFile::MaxFileFullNameLen);
	if ((-1) == DEnv::GetExecuteDirFullNameA(mbsCurrentDir,DFile::MaxFileFullNameLen))
	{
		return (-1);
	}
	return GetAbsoluteDir(mbsCurrentDir,RelativeDir,OutAbsoluteDir,dwSize);
}
DWORD DDir::GetParentDir(char * StrDir, char * OutParentDir, DWORD dwSize)
{
	char TempDir[DFile::MaxFileFullNameLen];
	memset(TempDir,0,DFile::MaxFileFullNameLen);
	DWORD needSize=-1;
	int dwGetSub = DStr::GetSubStr_FormTailToHead_BeforeSpecialStrA(StrDir,"\\",TempDir,needSize);
	if (dwGetSub<=0)
	{
		return (-1);
	}
	if (NULL!=OutParentDir && dwSize >= needSize)
	{
		memcpy(OutParentDir,TempDir,needSize);
	}
	return needSize;
}

/* DEnv class implement */

DWORD DEnv::GetSystemPartitionA(char * Buff, DWORD dwSize)
{
	char mbsSysPartitionDirName[DFile::MaxFileFullNameLen];
	memset(mbsSysPartitionDirName,0,DFile::MaxFileFullNameLen);
	GetWindowsDirectoryA(mbsSysPartitionDirName,DFile::MaxFileFullNameLen);
	if (':' == mbsSysPartitionDirName[1])
	{
		if (dwSize>=3 && NULL != Buff)
		{
			memcpy(Buff,mbsSysPartitionDirName,2);
			Buff[2]='\0';
		}
		return 3;
	}
	else
	{
		return (-1);
	}
	
}
DWORD DEnv::GetWindowsDirA(char * Buff, DWORD dwSize)
{
	char mbsWinDirName[DFile::MaxFileFullNameLen];
	memset(mbsWinDirName,0,DFile::MaxFileFullNameLen);
	GetWindowsDirectoryA(mbsWinDirName,DFile::MaxFileFullNameLen);
	DWORD dwNeedSize = DStr::GetStrSizeA(mbsWinDirName);
	if (dwSize>= dwNeedSize && NULL != Buff)
	{
		lstrcpyA(Buff,mbsWinDirName);
	} 
	return dwNeedSize;
}
DWORD DEnv::GetWindowsTempDirA(char * Buff, DWORD dwSize)
{
	char WinTempFoler[DFile::MaxFileFullNameLen];
	int iGetEnv = GetEnvVarA("TEMP",WinTempFoler,DFile::MaxFileFullNameLen);
	if ((-1) != iGetEnv)
	{
		DWORD dwNeedSize = DStr::GetStrSizeA(WinTempFoler);
		if (dwSize>= dwNeedSize && NULL != Buff)
		{
			lstrcpyA(Buff,WinTempFoler);
		}
		return dwNeedSize;
	}
	else
	{
		return (-1);
	}
}
DWORD DEnv::GetExecuteFileFullNameA(char * Buff, DWORD dwSize)
{
	char mbsFileName[DFile::MaxFileFullNameLen];
	memset(mbsFileName,0,DFile::MaxFileFullNameLen);
	GetModuleFileNameA(NULL,mbsFileName,DFile::MaxFileFullNameLen);
	if (DFile::IsExist(mbsFileName))
	{
		DWORD dwLenOfName = DStr::GetStrLenthA(mbsFileName);
		if (dwLenOfName+1<=dwSize)
		{
			memcpy(Buff,mbsFileName,dwLenOfName+1);
			return dwLenOfName+1;
		} 
		else
		{
			return (-1);
		}
	}
	else
	{
		return (-1);
	}
}
DWORD DEnv::GetExecuteDirFullNameA(char * Buff, DWORD dwSize)
{
	char mbsDirName[DFile::MaxFileFullNameLen];
	memset(mbsDirName,0,DFile::MaxFileFullNameLen);
	if ((-1) == GetExecuteFileFullNameA(mbsDirName,DFile::MaxFileFullNameLen))
	{
		return (-1);
	}
	if ((-1) == DDir::GetParentDir(mbsDirName,mbsDirName,DFile::MaxFileFullNameLen))
	{
		return (-1);
	}
	DWORD dwNeedSize=DStr::GetStrLenthA(mbsDirName)+1;
	if (dwSize < dwNeedSize)
	{
		return (-1);
	}
	lstrcpyA(Buff,mbsDirName);
	return dwNeedSize;
}
DWORD DEnv::GetEnvVarA(char * EnvName, char * Buff, DWORD dwSize)
{
	char * EnvValue=NULL;
	size_t EnvValueSize=0;
	int iErrNo = _dupenv_s(&EnvValue,&EnvValueSize,EnvName);
	if (0== iErrNo && NULL!=EnvValue)
	{
		DWORD dwNeedSize = DStr::GetStrSizeA(EnvValue);
		if (dwSize>= dwNeedSize && NULL != Buff)
		{
			lstrcpyA(Buff,EnvValue);
		}
		delete[] EnvValue;
		EnvValue =NULL;
		return dwNeedSize;
	}
	else
	{
		return (-1);
	}
}

/* DRegManager class implement */

bool DRegManager::WriteRegistryValueW(HKEY HRootKey, LPWSTR RegPath, LPCWSTR ValueName,LPBYTE ValueData,DWORD ValueType)
{
	HKEY hKEY;
	DWORD dwDisposition=REG_CREATED_NEW_KEY;
	long ret0=(::RegCreateKeyExW(HRootKey,RegPath,0,RegPath,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKEY,&dwDisposition));
	if(ret0!=ERROR_SUCCESS)
	{
		return false;
	}
	if(RegSetValueExW(hKEY,ValueName,0,ValueType,ValueData,256)!= ERROR_SUCCESS)
	{
		::RegCloseKey(hKEY);
		return false;
	}
	::RegCloseKey(hKEY);
	return true;
}
bool DRegManager::WriteRegistryValueA(HKEY HRootKey, LPSTR RegPath, LPSTR ValueName,LPBYTE ValueData,DWORD ValueType)
{

	int CntByteRegPath=DStr::GetStrLenthA(RegPath)+1;
	int CntByteValueName=DStr::GetStrLenthA(ValueName)+1;
	int CntByteValueData=DStr::GetStrLenthA((char*)ValueData)+1;
	wchar_t * wcsRegPath=new wchar_t[CntByteRegPath];
	DStr::CMbsToWcs(wcsRegPath,RegPath,CntByteRegPath);
	wchar_t * wcsValueName=new wchar_t[CntByteValueName];
	DStr::CMbsToWcs(wcsValueName,ValueName,CntByteValueName);
	wchar_t * wcsValueData=new wchar_t[CntByteValueData];
	DStr::CMbsToWcs(wcsValueData,(char*)ValueData,CntByteValueData);
	bool ret=WriteRegistryValueW(HRootKey,wcsRegPath,wcsValueName,(LPBYTE)wcsValueData,ValueType);
	delete [] wcsRegPath;
	delete [] wcsValueName;
	delete [] wcsValueData;
	return ret;
}
bool DRegManager::ReadRegistryValueW(HKEY HRootKey, LPCWSTR RegPath, LPCWSTR ValueName,LPBYTE ValueData,DWORD ValueType)
{
	HKEY hKEY;
	long ret0=(::RegOpenKeyExW(HRootKey,RegPath,0,KEY_READ,&hKEY));
	if(ret0!=ERROR_SUCCESS)
	{
		return false;
	}
	DWORD CountByte=256;
	long ret1=::RegQueryValueExW(hKEY,ValueName,NULL,&ValueType,ValueData,&CountByte);
	if(ret1!=ERROR_SUCCESS)
	{
		::RegCloseKey(hKEY);
		return false;
	}
	::RegCloseKey(hKEY);
	return true;
}
bool DRegManager::ReadRegistryValueA(HKEY HRootKey, LPCSTR RegPath, LPCSTR ValueName,LPBYTE ValueData,DWORD ValueType)
{
	int CntByteRegPath=DStr::GetStrLenthA(RegPath)+1;
	int CntByteValueName=DStr::GetStrLenthA(ValueName)+1;
	wchar_t * wcsRegPath=new wchar_t[CntByteRegPath];
	DStr::CMbsToWcs(wcsRegPath,RegPath,CntByteRegPath);
	wchar_t * wcsValueName=new wchar_t[CntByteValueName];
	DStr::CMbsToWcs(wcsValueName,ValueName,CntByteValueName);
	wchar_t wcsValueData[MaxKeyValueLen];
	bool ret=ReadRegistryValueW(HRootKey,wcsRegPath,wcsValueName,(LPBYTE)wcsValueData,ValueType);
	if (ret)
	{
		int CntByteValueData=DStr::GetStrLenthW(wcsValueData)+1;
		DStr::CWcsToMbs((char*)ValueData,wcsValueData,CntByteValueData);
	}
	delete [] wcsRegPath;
	delete [] wcsValueName;
	return ret;
}
bool DRegManager::DeleteRegistryKeyW(HKEY HRootKey, LPCWSTR RegPath)
{
	long ret1=RegDeleteKeyW(HRootKey,RegPath); 
	if(ret1!=ERROR_SUCCESS)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool DRegManager::DeleteRegistryKeyA(HKEY HRootKey, LPCSTR RegPath)
{
	int CntByteRegPath=DStr::GetStrLenthA(RegPath)+1;
	wchar_t * wcsRegPath=new wchar_t[CntByteRegPath];
	DStr::CMbsToWcs(wcsRegPath,RegPath,CntByteRegPath);
	bool ret=DeleteRegistryKeyW(HRootKey,wcsRegPath);
	delete [] wcsRegPath;
	return ret;
}

/* DTextFile class implement */

bool DTextFile::Open(char * mbsFileName,TEXTOPENMODE eOpenMode)
{
	OPENMODE eDfileOpenMode = DFile::OPEN_R;
	switch(eOpenMode)
	{
	case TOPEN_RP:
		eDfileOpenMode = DFile::OPEN_RBP;
		break;
	case TOPEN_WP:
		eDfileOpenMode = DFile::OPEN_WBP;
		break;
	case TOPEN_AP:
		eDfileOpenMode = DFile::OPEN_ABP;
		break;
	default:
		return false;
		break;
	}
	/* check the last change line character */
	m_IsFirstOpenWithAPModeNeedAddChangeLine = false;
	if (TOPEN_AP == eOpenMode)
	{
		char mbsLast2[2];
		memset(mbsLast2,0,2);
		if(DFile::Open(mbsFileName,OPEN_RBP))
		{
			if(DFile::Seek(-2,SEEK_FROM_END))
			{
				if(!DFile::Read(mbsLast2,2))
				{
					return false;
				}
				if(!DFile::Close())
				{
					return false;
				}
				if (0 != memcmp(mbsLast2,DStr::FileChangeLineStr,2))
				{
					m_IsFirstOpenWithAPModeNeedAddChangeLine = true;
				}
			}
			else
			{
				if (!DFile::Close())
				{
					return false;
				}
			}
		}
	}
	m_OpenMode = eOpenMode;
	return DFile::Open(mbsFileName,eDfileOpenMode);
}
bool DTextFile::Close()
{
	return DFile::Close();
}
DWORD DTextFile::Read(char * pcBuff, DWORD dwSize)
{
	return DFile::Read(pcBuff,dwSize);
}
DWORD DTextFile::ReadLine(char * pcBuff, DWORD dwSize)
{
	if (!IsOpen())
	{
		return (-1);
	}
	char * s = fgets(pcBuff,dwSize,m_pFile);
	if (NULL == s)
	{
		return (-1);
	}
	DWORD dwReadLen = DStr::GetStrLenthA(s);
	DWORD iMinLen = DMath::Min(dwSize,dwReadLen);
	if (0 == memcmp(pcBuff+iMinLen-2,DStr::FileChangeLineStr,2))
	{
		pcBuff[iMinLen-2] = '\0';
	}
	dwReadLen = DStr::GetStrLenthA(s);
	return dwReadLen;
}
DWORD DTextFile::Write(const char * pvBuff, DWORD dwSize)
{
	return DFile::Write((void*)pvBuff,dwSize);
}
DWORD DTextFile::WriteLine(const char * pvBuff, DWORD dwSize)
{
	if (NULL == m_pFile)
	{
		return (-1);
	}
	/* check previous 
	   must open file with read write */
	int iW1 = 0;
	if (Seek(-2,DFile::SEEK_FROM_CUR))
	{
		char Pre2[2]={0};
		int iR = Read(Pre2,2);
		if (2==iR)
		{
			if (0 != memcmp(Pre2,DStr::FileChangeLineStr,DStr::GetStrLenthA(DStr::FileChangeLineStr)))
			{
				if (!Seek(0,SEEK_FROM_END))
				{
					return -1;
				}
				iW1 = Write(DStr::FileChangeLineStr,2); 
			}
		}

	}
	if (TOPEN_AP == m_OpenMode)
	{	
		if (m_IsFirstOpenWithAPModeNeedAddChangeLine)
		{
			iW1 = Write(DStr::FileChangeLineStr,2);
			m_IsFirstOpenWithAPModeNeedAddChangeLine = false;
		}
	} 
	if (!Seek(0,SEEK_FROM_END))
	{
		return -1;
	}
	int iW2 = Write(pvBuff,DMath::Min(dwSize,DStr::GetStrLenthA(pvBuff)));
	return iW1 + iW2;
}
bool DTextFile::IsToEOF()
{
	return DFile::IsCurrentOffsetEOF();
}
DTextFile::DTextFile()
{
	DFile::DFile();
	m_OpenMode = TOPEN_RP;
}
DTextFile::~DTextFile()
{
	DFile::~DFile();
}

/* DPerformanceChecker class implement */

bool DPerformanceChecker::m_bEnableFileOutput = true;
bool DPerformanceChecker::m_bEnableConsoleOutput = true;
bool DPerformanceChecker::m_IsBegining = false;
PerformanceCheckerItem DPerformanceChecker::curPFCI={0};
char DPerformanceChecker::m_OutPutFileName[DFile::MaxFileFullNameLen]={0};
void DPerformanceChecker::SetOutPutFileName(char * FileName)
{
	lstrcpyA(m_OutPutFileName,FileName);
}
void DPerformanceChecker::SetEnableConsoleOutput(bool bEnable)
{
	m_bEnableConsoleOutput = bEnable;
}
void DPerformanceChecker::SetEnableFileOutput(bool bEnable)
{
	m_bEnableFileOutput = bEnable;
}
DWORD DPerformanceChecker::GetTickCount()
{
	return ::GetTickCount();
}
DWORD DPerformanceChecker::GetThreadTime()
{
	FILETIME m_ftDummy;
	FILETIME m_ftKernelTime;
	FILETIME m_ftUserTime;
	HANDLE hT = ::GetCurrentThread();
	::GetThreadTimes(hT, &m_ftDummy,&m_ftDummy, 
		&m_ftKernelTime, &m_ftUserTime);
	DWORD thread_us_time=0;
	thread_us_time = m_ftUserTime.dwLowDateTime / 10000;
	thread_us_time += m_ftUserTime.dwHighDateTime * 429497;
	return thread_us_time;
}
bool DPerformanceChecker::CreateOneTestFile(char* FileName, char* RepeatBuff, DWORD dwBuffSize, DWORD dwFileSize)
{
	DFile cFile;
	if (!cFile.Open(FileName,DFile::OPEN_WBP))
	{
		return false;
	}
	int iRepeatTime = dwFileSize/dwBuffSize;
	int iLastWriteSize = dwFileSize%dwBuffSize;
	for(int i=0;i<iRepeatTime;i++)
	{
		if (!cFile.Write(RepeatBuff,dwBuffSize))
		{
			cFile.Close();
			return false;
		}
	}
	if (!cFile.Write(RepeatBuff,iLastWriteSize))
	{
		cFile.Close();
		return false;
	}
	if (!cFile.Close())
	{
		return false;
	}
	return true;
}
void DPerformanceChecker::PerformanceCheckBegin(char * ProcName, char * TestCaseName)
{
	if (true == m_IsBegining)
	{
		PerformanceCheckEnd();
		return;
	}
	m_IsBegining = true;
	/* proc name */
	if (NULL == ProcName || 
		0 == lstrcmpA(ProcName,"") || 
		DStr::GetStrSizeA(ProcName)>DStr::SimpleStringBufferSize)
	{
		lstrcpyA(curPFCI.ProcName,"NULL");
	}
	else
	{
		lstrcpyA(curPFCI.ProcName,ProcName);
	}
	/* testcase name */
	if (NULL == TestCaseName || 
		0 == lstrcmpA(TestCaseName,"") || 
		DStr::GetStrSizeA(TestCaseName)>DStr::SimpleStringBufferSize)
	{
		lstrcpyA(curPFCI.TestCaseName,"NULL");
	}
	else
	{
		lstrcpyA(curPFCI.TestCaseName,TestCaseName);
	}
	curPFCI.TickCountBegin = DPerformanceChecker::GetTickCount();
	curPFCI.ThreadTimeBegin = DPerformanceChecker::GetThreadTime();
}
void DPerformanceChecker::PerformanceCheckEnd()
{
	if (false == m_IsBegining)
	{
		return;
	}
	m_IsBegining = false;
	curPFCI.TickCountEnd= DPerformanceChecker::GetTickCount();
	curPFCI.ThreadTimeEnd = DPerformanceChecker::GetThreadTime();
	OutPutResult();
}
bool DPerformanceChecker::OutPutResult()
{
	if (true == m_IsBegining)
	{
		PerformanceCheckEnd();
	}
	/* format: [VOICE]AL_AplCommonData: thr_d[2] tick_s[7421] tick_e[7424] tick_d[3] */
	char BufferOut[DStr::SimpleStringBufferSize];
	sprintf_s(BufferOut,"[%s]%s:  thr_d[%d] tick_s[%d] tick_e[%d] tick_d[%d]",
	curPFCI.ProcName,
	curPFCI.TestCaseName,
	curPFCI.ThreadTimeEnd-curPFCI.ThreadTimeBegin,
	curPFCI.ThreadTimeBegin,
	curPFCI.ThreadTimeEnd,
	curPFCI.TickCountEnd-curPFCI.TickCountBegin);
	char * PerformanmceCheckerBeginStr = "DPerformanceChecker Begin";
	char * PerformanmceCheckerEndStr = "DPerformanceChecker End";
	if (m_bEnableFileOutput)
	{
		char TestHelperOutFile[DFile::MaxFileFullNameLen];
		memset(TestHelperOutFile,0,DFile::MaxFileFullNameLen);
		DEnv::GetExecuteDirFullNameA(TestHelperOutFile,DFile::MaxFileFullNameLen);
		lstrcatA(TestHelperOutFile,"\\PerformanceCheckerOutPut.txt");
		DTextFile cDTFile;
		cDTFile.Open(TestHelperOutFile,DTextFile::TOPEN_AP);
		cDTFile.WriteLine(PerformanmceCheckerBeginStr,lstrlenA(PerformanmceCheckerBeginStr));
		cDTFile.WriteLine(BufferOut,lstrlenA(BufferOut));
		cDTFile.WriteLine(PerformanmceCheckerEndStr,lstrlenA(PerformanmceCheckerEndStr));
		cDTFile.Close();
	}
#if defined(_CONSOLE)
	if (m_bEnableConsoleOutput)
	{
		printf(PerformanmceCheckerBeginStr);printf("\n");
		printf(BufferOut);printf("\n");
		printf(PerformanmceCheckerEndStr);printf("\n");
	}
#endif
	return true;
}

/* DFileLog class implement */

DFileLog * DFileLog::m_Instance = NULL;
DFileLog * DFileLog::GetInstance()
{
	if (NULL == m_Instance)
	{
		m_Instance = new DFileLog(GLOBAL_LOG_FILENAME,GLOBAL_LOG_SYNCOBJNAME);
	}
	return m_Instance;
}
void DFileLog::Destory()
{
	if (NULL != m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}
DFileLog::DFileLog(char * FileName, char * SyncObjName)
{
	m_bEnableSaveLog = true;
	m_pDTFile = new DTextFile();
	lstrcpyA(m_FileLogName,FileName);
	if (NULL == SyncObjName)
	{
		DGUID ResGUID;
		m_DSyncRes = new DSyncResource(1,1,ResGUID.GuidStr);
	}
	else
	{
		m_DSyncRes = new DSyncResource(1,1,SyncObjName);
	}
}
DFileLog::~DFileLog()
{
	m_bEnableSaveLog = false;
	if (NULL != m_pDTFile)
	{
		m_pDTFile->Close();
		delete m_pDTFile;
	}
	memset(m_FileLogName,0,DFile::MaxFileFullNameLen);
	if (NULL!=m_DSyncRes)
	{
		delete m_DSyncRes;
		m_DSyncRes = NULL;
	}
}
bool DFileLog::Clear()
{
	if (NULL == m_pDTFile || NULL == m_DSyncRes)
	{
		return false;
	}
	m_DSyncRes->ApplyResource();
	if (m_pDTFile->Open(m_FileLogName,DTextFile::TOPEN_WP))
	{
		if (m_pDTFile->Close())
		{
			m_DSyncRes->ReleaseResource();
			return true;
		}
	}
	m_DSyncRes->ReleaseResource();
	return false;
}
void DFileLog::EnableSaveLog(bool Enable)
{
	m_bEnableSaveLog=Enable;
}
bool __cdecl DFileLog::OutoutW(const wchar_t * lpwcsFormat,...)
{
	if (NULL == lpwcsFormat)
	{
		return false;
	}
	/* wide char buffer */
	DWORD dwCntOfText = DStr::GetStrLenthW(lpwcsFormat)+512;
	wchar_t * pwcsBuffer = new wchar_t[dwCntOfText];
	memset(pwcsBuffer,0,dwCntOfText*2);
	/* create text in wide char buffer */
	va_list args; 
	va_start(args, lpwcsFormat); 
	_vsnwprintf_s(pwcsBuffer,dwCntOfText,dwCntOfText,lpwcsFormat,args); 
	va_end(args); 
	/* multi char buffer */
	char * pmbsBuffer = new char[dwCntOfText];
	memset(pmbsBuffer,0,dwCntOfText);
	/* convert */
	DStr::CWcsToMbs(pmbsBuffer,pwcsBuffer,dwCntOfText);
	/* call multi char function */
	bool bRet = OutoutA(pmbsBuffer);
	delete[] pwcsBuffer;
	delete[] pmbsBuffer;
	return bRet;
}
bool __cdecl DFileLog::OutoutA(const char * lpmbsFormat,...)
{
	if (NULL == m_pDTFile || NULL == m_DSyncRes)
	{
		return false;
	}
	if (m_bEnableSaveLog)
	{
		int SizeOfFmt = DStr::GetStrLenthA(lpmbsFormat)+512;
		char * PInfoBuffer=new char[SizeOfFmt];
		memset(PInfoBuffer,0,SizeOfFmt);
		/* Get time information */
		SYSTEMTIME SysTime;
		GetLocalTime( &SysTime ); 
		char mbsSysTimeInfoLine[256];
		wsprintfA(mbsSysTimeInfoLine,"[%02d/%02d/%04d %02d:%02d:%02d] ",SysTime.wMonth,SysTime.wDay,SysTime.wYear,
			SysTime.wHour,SysTime.wMinute,SysTime.wSecond);
		lstrcpyA(PInfoBuffer,mbsSysTimeInfoLine);
		DWORD dwLenOfTimeStr = DStr::GetStrLenthA(PInfoBuffer);
		/* Get log text string */
		va_list args; 
		va_start(args, lpmbsFormat); 
		_vsnprintf_s(PInfoBuffer+dwLenOfTimeStr,SizeOfFmt-dwLenOfTimeStr,SizeOfFmt-dwLenOfTimeStr,lpmbsFormat,args); 
		va_end(args); 
		/* Write to log file */
		m_DSyncRes->ApplyResource();
		if (m_pDTFile->Open(m_FileLogName,DTextFile::TOPEN_AP))
		{
			if ( (-1) != m_pDTFile->WriteLine(PInfoBuffer,DStr::GetStrLenthA(PInfoBuffer)))
			{
				//printf("%s", PInfoBuffer);
				if (m_pDTFile->Close())
				{
					delete [] PInfoBuffer;
					m_DSyncRes->ReleaseResource();
					return true;
				}
			}
		}
		delete [] PInfoBuffer;
		m_pDTFile->Close();
		m_DSyncRes->ReleaseResource();
		return false;
	}
	else
	{
		return true;
	}
}

/* DMath class implement */

long DMath::Min(long N1,long N2)
{
	return min(N1,N2);
}
long DMath::Max(long N1,long N2)
{
	return max(N1,N2);
}

/* DConfigFile class implement */

DConfigFile::DConfigFile(char * ConfigFileName)
{
	memset(m_fileName,0,DFile::MaxFileFullNameLen);
	m_pDTFile = new DTextFile();
}
DConfigFile::DConfigFile(wchar_t * ConfigFileName)
{
	DStr::CWcsToMbs(m_fileName,ConfigFileName,DFile::MaxFileFullNameLen);
	m_pDTFile = new DTextFile();
}
DConfigFile::~DConfigFile()
{
	if (NULL != m_pDTFile)
	{
		m_pDTFile->Close();
		delete m_pDTFile;
		m_pDTFile = NULL;
	}
}
bool DConfigFile::GetValueDataA(char * ValueName,char * ValueData,DWORD dwSize)
{
	if (NULL == m_pDTFile)
	{
		return false;
	}
	if (NULL == ValueName || NULL == ValueData )
	{
		return false;
	}
	memset(ValueData,0,dwSize);
	char * pCurLineBuffer = new char[MaxSizeOfOneLineInConfigDataFile];
	if (!m_pDTFile->Open(m_fileName,DTextFile::TOPEN_RP))
	{
		delete[] pCurLineBuffer;
		return false;
	}
	while (true)
	{
		DWORD dwReadSize = m_pDTFile->ReadLine(pCurLineBuffer,MaxSizeOfOneLineInConfigDataFile);
		if ( (-1) == dwReadSize) /* read */
		{
			if (m_pDTFile->IsToEOF()) /* reach end */
			{
				m_pDTFile->Close();
				delete[] pCurLineBuffer;
				return true;
			} 
			else
			{
				m_pDTFile->Close();
				delete[] pCurLineBuffer;
				return false;
			}
		}
		if ( dwReadSize >= MaxSizeOfOneLineInConfigDataFile)  /* buffer not enough */
		{
			m_pDTFile->Close();
			delete[] pCurLineBuffer;
			return false;
		}
		if(DStr::InstrTrimIgnoreULA(pCurLineBuffer,ValueName)>=0) /* find the line that have ValueName */
		{
			DWORD dwNeedSize=-1;
			DStr::GetSubStr_FormHeadToTail_AfterSpecialStrA(pCurLineBuffer,"=",NULL,dwNeedSize);
			if (dwNeedSize<0 || dwNeedSize>dwSize )
			{
				m_pDTFile->Close();
				delete[] pCurLineBuffer;
				return false;
			} 
			if (DStr::GetSubStr_FormHeadToTail_AfterSpecialStrA(pCurLineBuffer,"=",ValueData,dwNeedSize)<0)
			{
				delete[] pCurLineBuffer;
				return false;
			}
			m_pDTFile->Close();
			delete[] pCurLineBuffer;
			return true;
		}
	}
	m_pDTFile->Close();
	delete[] pCurLineBuffer;
	return false;
}
bool DConfigFile::SetValueDataA(char * ValueName,char * ValueData)
{
	/* get count of config data */
	DWORD MaxCountOfCurrentConfigData = 0;
	char LineBuffer[MaxSizeOfOneLineInConfigDataFile];
	char** ppDataBuffers=NULL;
	if (DFile::IsExist(m_fileName))
	{
		if (!m_pDTFile->Open(m_fileName,DTextFile::TOPEN_RP))
		{
			return false;
		}
		while (true)
		{
			int dwReadSize = m_pDTFile->ReadLine(LineBuffer,MaxSizeOfOneLineInConfigDataFile);
			if (dwReadSize>=0)
			{
				if (DStr::Instr_FromHeadToTailA(LineBuffer,"=")>=0)
				{
					MaxCountOfCurrentConfigData ++ ;
				}
			} 
			else
			{
				break;
			}
		}
		if (!m_pDTFile->Close())
		{
			return false;
		}
	}
	ppDataBuffers = new char*[MaxCountOfCurrentConfigData+1];
	for (DWORD i = 0; i<MaxCountOfCurrentConfigData+1; i++)
	{
		ppDataBuffers[i] = new char[MaxSizeOfOneLineInConfigDataFile];
		memset(ppDataBuffers[i],0,MaxSizeOfOneLineInConfigDataFile);
	}

	if (DFile::IsExist(m_fileName))
	{
		/* read all data to buffers */
		if (!m_pDTFile->Open(m_fileName,DTextFile::TOPEN_RP))
		{
			/* relese block */
			for (DWORD i = 0; i<MaxCountOfCurrentConfigData+1; i++)
			{
				delete[] ppDataBuffers[i];
			}
			delete[] ppDataBuffers;
			return false;
		}
		DWORD iCurrentReadLineIndex = 0;
		while (true)
		{
			int dwReadSize = m_pDTFile->ReadLine(ppDataBuffers[iCurrentReadLineIndex],MaxSizeOfOneLineInConfigDataFile);
			if (dwReadSize<0)
			{
				break;
			}
			if (DStr::Instr_FromHeadToTailA(ppDataBuffers[iCurrentReadLineIndex],"=")>=0)
			{
				iCurrentReadLineIndex ++ ;
			}
		}
		if (!m_pDTFile->Close())
		{
			/* relese block */
			for (DWORD i = 0; i<MaxCountOfCurrentConfigData+1; i++)
			{
				delete[] ppDataBuffers[i];
			}
			delete[] ppDataBuffers;
			return false;
		}
	}

	/* update data */
	bool bUpdate = false;
	for (DWORD i=0;i<MaxCountOfCurrentConfigData;i++)
	{
		DWORD needSize =0;
		char CurValueName[MaxSizeOfOneLineInConfigDataFile] = {0};
		char CurValueData[MaxSizeOfOneLineInConfigDataFile] = {0};
		DStr::GetSubStr_FormHeadToTail_BeforeSpecialStrA(ppDataBuffers[i],"=",CurValueName,needSize);
		DStr::TrimA(CurValueName);
		if (0 == DStr::CmpStrIgnoreULA(CurValueName,ValueName))
		{
			if (DStr::GetSubStr_FormHeadToTail_AfterSpecialStrA(ppDataBuffers[i],"=",CurValueData,needSize)>0)
			{
				if (DStr::ReplaceOneStr_FormHeadToTailA(ppDataBuffers[i],MaxSizeOfOneLineInConfigDataFile,CurValueData,ValueData)>0)
				{
					lstrcatA(ppDataBuffers[i],DStr::FileChangeLineStr);
					bUpdate = true;
				}
			}
		}
	}

	/* write new data */
	if (!m_pDTFile->Open(m_fileName,DTextFile::TOPEN_WP))
	{
		/* relese block */
		for (DWORD i = 0; i<MaxCountOfCurrentConfigData+1; i++)
		{
			delete[] ppDataBuffers[i];
		}
		delete[] ppDataBuffers;
		return false;
	}
	for(DWORD i=0;i<MaxCountOfCurrentConfigData;i++)
	{
		int dwReadSize = m_pDTFile->WriteLine(ppDataBuffers[i],DStr::GetStrLenthA(ppDataBuffers[i]));
		if (dwReadSize<0)
		{
			/* relese block */
			for (DWORD i = 0; i<MaxCountOfCurrentConfigData+1; i++)
			{
				delete[] ppDataBuffers[i];
			}
			delete[] ppDataBuffers;
			return false;
		}
	}
	if (!bUpdate)
	{
		lstrcatA(ppDataBuffers[MaxCountOfCurrentConfigData],ValueName);
		lstrcatA(ppDataBuffers[MaxCountOfCurrentConfigData],"=");
		lstrcatA(ppDataBuffers[MaxCountOfCurrentConfigData],ValueData);
		int dwReadSize = m_pDTFile->WriteLine(ppDataBuffers[MaxCountOfCurrentConfigData],
			DStr::GetStrLenthA(ppDataBuffers[MaxCountOfCurrentConfigData]));
	}
	if (!m_pDTFile->Close())
	{
		/* relese block */
		for (DWORD i = 0; i<MaxCountOfCurrentConfigData+1; i++)
		{
			delete[] ppDataBuffers[i];
		}
		delete[] ppDataBuffers;
		return false;
	}

	/* relese block */
	for (DWORD i = 0; i<MaxCountOfCurrentConfigData+1; i++)
	{
		delete[] ppDataBuffers[i];
	}
	delete[] ppDataBuffers;
	return true;
}

/* DEncode class implement */

bool DEncode::SecurityEncode(BYTE * PSourceByte,DWORD dwSize)
{
	for (DWORD i=0;i<dwSize;i++)
	{
		BYTE sc;
		BYTE bymid1=0x00; 
		BYTE bymid2=0x00; 
		BYTE des;
		sc=PSourceByte[i];
		/* process 12345678 -> 78123456 */
		bymid1 = ( sc << 6 ) & 0xC0;
		bymid2 = ( sc >> 2 ) & 0x3F;
		des = bymid1 | bymid2;
		PSourceByte[i]=des;
	}
	return true;
}
bool DEncode::SecurityDecode(BYTE * PSourceByte,DWORD dwSize)
{
	for (DWORD i=0;i<dwSize;i++)
	{
		BYTE sc;
		BYTE bymid1=0x00; 
		BYTE bymid2=0x00; 
		BYTE des;
		sc=PSourceByte[i];
		/*process 78123456 -> 12345678 */
		bymid1 = ( sc << 2 ) & 0xFC;
		bymid2 = ( sc >> 6 ) & 0x03;
		des = bymid1 | bymid2;
		PSourceByte[i]=des;
	}
	return true;
}

/* DList class implement */

bool DList::AddToTail(void * pvData)
{
	DListNode * PNode;
	PNode=new DListNode();
	PNode->PData=pvData;
	if (NULL==PTail || 0==Count)
	{
		PHead=PNode;
		PTail=PNode;
	}
	else
	{
		PTail->NextPoint=PNode;
		if (NULL==PTail->PrePoint)
		{
			PNode->PrePoint=PHead;
		}
		else
		{
			PNode->PrePoint=PTail;
		}
		PTail=PNode;
	}
	Count++;
	return true;
}
bool DList::AddToHead(void * pvData)
{
	DListNode * PNode;
	PNode=new DListNode();
	PNode->PData=pvData;
	if (NULL==PHead || 0==Count)
	{
		PHead=PNode;
		PTail=PNode;
	}
	else
	{
		PHead->PrePoint=PNode;
		if (NULL==PHead->NextPoint)
		{
			PNode->NextPoint=PTail;
		}
		else
		{
			PNode->NextPoint=PHead;
		}
		PHead=PNode;
	}
	Count++;
	return true;
}
bool DList::GerFromTail(void * &pvData)
{
	DListNode * PGetNode=NULL;
	if (Count<=0)
	{
		return false;
	}
	else if(1==Count)
	{
		PGetNode = PHead;
		PHead=NULL;
		PTail=NULL;
		pvData = PGetNode->PData;
		delete PGetNode;
	}
	else
	{
		PGetNode = PTail;
		PTail=PTail->PrePoint;
		PTail->NextPoint=NULL;
		pvData = PGetNode->PData;
		delete PGetNode;
	}
	Count--;
	return true;
}
bool DList::GerFromHead(void * &pvData)
{
	DListNode * PGetNode=NULL;
	if (Count<=0)
	{
		return false;
	}
	else if(1==Count)
	{
		PGetNode = PHead;
		PHead=NULL;
		PTail=NULL;
		pvData = PGetNode->PData;
		delete PGetNode;
	}
	else
	{
		PGetNode=PHead;
		PHead=PHead->NextPoint;
		PHead->PrePoint=NULL;
		pvData = PGetNode->PData;
		delete PGetNode;
	}
	Count--;
	return true;
}
bool DList::PeekTail(void * &pvData)
{
	if (0==Count)
	{
		return false;
	}
	pvData = PTail->PData;
	return true;
}
bool DList::PeekHead(void * &pvData)
{
	if (0==Count)
	{
		return false;
	}
	pvData = PHead->PData;
	return true;
}

/* DThread class implement */

/* used for C/C++ security thread about some C function and globle variable
   you must not call the function: _endthreadex */
typedef unsigned (__stdcall *PTHREAD_START)(void*);
#define CTS_BeginThreadEx(psa, cbStack, pfnStartAddr,	\
	pvParam, fdwCreate, pdwThreadID)					\
	((HANDLE) _beginthreadex(							\
	(void*)(psa),										\
	(unsigned)(cbStack),								\
	(PTHREAD_START)(pfnStartAddr),						\
	(void*)(pvParam),									\
	(unsigned)(fdwCreate),								\
	(unsigned*)(pdwThreadID)))

static DWORD WINAPI DThreadProc(LPVOID lpParam)
{
	if(NULL!=lpParam)
	{
		DThread * pDT = (DThread*)lpParam;
		return pDT->ThreadProc(pDT->m_pvThreadParam);
	}
	else
	{
		return (-1);
	}
}
DThread::DThread(){
	m_dwThreadID = 0;
	m_hThread = NULL;
	m_pvThreadParam = NULL;
}
DThread::~DThread()
{ 
	if (NULL != m_hThread)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}
HANDLE DThread::Begin(void * lpParam)
{
	if (NULL != m_hThread)
	{
		return false;
	}
	m_pvThreadParam = lpParam;
	m_hThread = CTS_BeginThreadEx(NULL,
		0,
		(LPTHREAD_START_ROUTINE)DThreadProc,
		this,
		0,
		&m_dwThreadID);
	return m_hThread;
}
DWORD DThread::Suspend()
{
	if (NULL == m_hThread)
	{
		return (-1);
	}
	return SuspendThread(m_hThread);
}
DWORD DThread::Resume()
{
	if (NULL == m_hThread)
	{
		return (-1);
	}
	return ResumeThread(m_hThread);
}
bool DThread::GetExitCode(DWORD * pdwRetVal)
{
	if (NULL == m_hThread || 0 == GetExitCodeThread(m_hThread,pdwRetVal))
	{
		return false;
	}
	return true;
}

/* DTimer class implement */

class DTimerThread: public DThread
{
public:
	friend class DTimer;
	virtual DWORD ThreadProc(void * lpParam);
};
DWORD DTimerThread::ThreadProc(void * lpParam)
{
	if (NULL != lpParam)
	{
		while(true)
		{
			DTimer * pDT = (DTimer*)lpParam;
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
			WaitForSingleObject(pDT->m_hWaitableTimer,INFINITE);
#else
			Sleep(pDT->m_dwTimerIntervalMillisecond);
#endif
			pDT->Run();
			if (!pDT->m_bIsCycle)
			{
				return 1;
			}
		}
	}
	else
	{
		return (-1);
	}
}
DTimer::DTimer(DWORD dwTimerIntervalMillisecond, bool bIsCycle)
{
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
	m_hWaitableTimer = CreateWaitableTimerW(NULL,FALSE,NULL);
#endif
	m_pDTimerThread = new DTimerThread();
	m_dwTimerIntervalMillisecond = dwTimerIntervalMillisecond;
	m_bIsCycle = bIsCycle;
}
DTimer::~DTimer()
{
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
	CancelWaitableTimer(m_hWaitableTimer);
#endif
	if (NULL!=m_pDTimerThread)
	{
		delete m_pDTimerThread;
	}
}
bool DTimer::Start()
{
	if (NULL == m_pDTimerThread)
	{
		return false;
	}
	m_pDTimerThread->Begin(this);
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
	long lPeriod = 0;
	if (false == m_bIsCycle)
	{
		lPeriod = 0;
	}
	else
	{
		lPeriod = m_dwTimerIntervalMillisecond;
	}
	LARGE_INTEGER li;
	li.QuadPart = -(10*1000*((LONGLONG)(m_dwTimerIntervalMillisecond)));
	if (!SetWaitableTimer(m_hWaitableTimer,&li,lPeriod,NULL,NULL,FALSE))
	{
		return false;
	}
#endif
	return true;
}

/* DSyncResource class implement */

DSyncResource::DSyncResource(long lInitResCnt, long lMaxResCnt,const char * mbsSyncResObjName)
{
	m_lInitResCnt = lInitResCnt;
	m_lMaxResCnt = lMaxResCnt;
	m_hSemaphore = CreateSemaphoreA(NULL,lInitResCnt,lMaxResCnt,mbsSyncResObjName);
}
DSyncResource::~DSyncResource()
{
	if (NULL != m_hSemaphore)
	{
		CloseHandle(m_hSemaphore);
		m_hSemaphore = NULL;
	}
}
bool DSyncResource::ApplyResource(long lResCnt)
{
	DWORD ret = 0;
	for (int i=0; i<lResCnt; i++)
	{
		ret = WaitForSingleObject(m_hSemaphore,INFINITE);
		DWORD dwLastErr = GetLastError();
		switch (ret) 
		{ 
		case WAIT_OBJECT_0: 
			break; 
		case WAIT_TIMEOUT: 
			return false;
			break;
		}
	}
	return true;
}
bool DSyncResource::ReleaseResource(long lResCnt, long * plPreCnt)
{
	if (0 == ReleaseSemaphore(m_hSemaphore,lResCnt,plPreCnt))
	{
		return false;
	}
	return true;
}

/* DSync implement */

DSyncObj::DSyncObj()
{
	::InitializeCriticalSection(&cs);
}
DSyncObj::~DSyncObj()
{
	::DeleteCriticalSection(&cs);
}
VOID DSyncObj::SyncStart()
{
	::EnterCriticalSection(&cs);
}
bool DSyncObj::TrySyncStart()
{
	bool blRet = ::TryEnterCriticalSection(&cs);
	return blRet;
}
VOID DSyncObj::SyncEnd()
{
	::LeaveCriticalSection(&cs);
}
DAutoSync::DAutoSync(DSyncObj& cSync)
: m_cSync(cSync)
{
	m_cSync.SyncStart();
	return;
}
DAutoSync::~DAutoSync()
{
	m_cSync.SyncEnd();
	return;
}

/* DGUID class implement */

DGUID::DGUID()
{
	memset(&Guid,0,sizeof(Guid));
	memset(GuidStr,0,sizeof(GuidStr));
	if (CreateNewGUID(&Guid))
	{
		_snprintf_s(GuidStr, sizeof(GuidStr),sizeof(GuidStr),
			"{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}",
			Guid.Data1,
			Guid.Data2,
			Guid.Data3,
			Guid.Data4[0],
			Guid.Data4[1],
			Guid.Data4[2], 
			Guid.Data4[3], 
			Guid.Data4[4], 
			Guid.Data4[5],
			Guid.Data4[6], 
			Guid.Data4[7]);
	}
}
DWORD DGUID::CreateNewGUIDStr(char * buf, DWORD dwBufSize)
{
	GUID guid;
	if (NULL == buf || dwBufSize < 37 || !CreateNewGUID(&guid))
	{
		return (-1);
	}
	_snprintf_s(buf, dwBufSize,dwBufSize,
		"{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}",
		guid.Data1,
		guid.Data2,
		guid.Data3,
		guid.Data4[0],
		guid.Data4[1],
		guid.Data4[2], 
		guid.Data4[3], 
		guid.Data4[4], 
		guid.Data4[5],
		guid.Data4[6], 
		guid.Data4[7]);
	return 1;
}
DWORD DGUID::CreateNewGUID(GUID * pGuid)
{
	if (NULL == pGuid || S_OK != ::CoCreateGuid(pGuid))
	{
		return (-1);
	}
	return 1;
}

/* DTestHelper class implement */

bool DTestHelper::m_bEnableConsoleOutput = true;
bool DTestHelper::m_bEnableFileOutput = true;
void DTestHelper::TestHelperOutPutA(const char * lpmbsFormat,...)
{
	int SizeOfFmt = lstrlenA(lpmbsFormat)+512;
	char * PInfoBuffer=new char[SizeOfFmt];
	memset(PInfoBuffer,0,SizeOfFmt);
	/* Get log text string */
	va_list args; 
	va_start(args, lpmbsFormat); 
	_vsnprintf_s(PInfoBuffer,SizeOfFmt,SizeOfFmt,lpmbsFormat,args); 
	va_end(args); 
	if (m_bEnableFileOutput)
	{
		char TestHelperOutFile[DFile::MaxFileFullNameLen];
		memset(TestHelperOutFile,0,DFile::MaxFileFullNameLen);
		DEnv::GetExecuteDirFullNameA(TestHelperOutFile,DFile::MaxFileFullNameLen);
		lstrcatA(TestHelperOutFile,"\\TestHelperOutPut.txt");
		DTextFile cDTFile;
		cDTFile.Open(TestHelperOutFile,DTextFile::TOPEN_AP);
		cDTFile.WriteLine(PInfoBuffer,lstrlenA(PInfoBuffer));
		cDTFile.Close();
	}
#if defined(_CONSOLE)
	if (m_bEnableConsoleOutput)
	{
		lstrcatA(PInfoBuffer,"\n");
		printf(PInfoBuffer);
	}
#endif
	delete [] PInfoBuffer;
}
void DTestHelper::SetEnableConsoleOutput(bool bEnable)
{
	m_bEnableConsoleOutput=bEnable;
}
void DTestHelper::SetEnableFileOutput(bool bEnable)
{
	m_bEnableFileOutput=bEnable;
}
#define DTestHelper_CONDITION_OUTPUT(bCondition)										\
{																						\
	if (true == (bCondition))															\
	{																					\
		DTestHelper::TestHelperOutPutA("[OK] File(%s)Line(%d) TestCase=%s",				\
			DStr::GetCstFileShortNameFormFileName(mbsFileName),dwLineNo,mbsCaseName);	\
		return true;																	\
	}																					\
	else																				\
	{																					\
		DTestHelper::TestHelperOutPutA("[Fail] File(%s)Line(%d) TestCase=%s",			\
			DStr::GetCstFileShortNameFormFileName(mbsFileName),dwLineNo,mbsCaseName);	\
		return false;																	\
	}																					\
}
bool DTestHelper::TestValueEQ(char * mbsFileName, DWORD dwLineNo, 
							  bool cValue, bool cExpect, char * mbsCaseName)
{
	DTestHelper_CONDITION_OUTPUT(cValue == cExpect)
}
bool DTestHelper::TestValueEQ(char * mbsFileName, DWORD dwLineNo, 
							  int cValue, int cExpect, char * mbsCaseName)
{
	DTestHelper_CONDITION_OUTPUT(cValue == cExpect)
}
bool DTestHelper::TestStrAEQ(char * mbsFileName, DWORD dwLineNo, 
							  char * cValue, char  * cExpect, char * mbsCaseName)
{
	DTestHelper_CONDITION_OUTPUT (0 == lstrcmpA(cValue,cExpect))
}
bool DTestHelper::TestStrWEQ(char * mbsFileName, DWORD dwLineNo, 
							  wchar_t * cValue, wchar_t  * cExpect, char * mbsCaseName)
{
	DTestHelper_CONDITION_OUTPUT (0 == lstrcmpW(cValue,cExpect))
}
bool DTestHelper::TestPointEQ(char * mbsFileName, DWORD dwLineNo, 
							  void * cValue, void  * cExpect, char * mbsCaseName)
{
	DTestHelper_CONDITION_OUTPUT (cValue == cExpect)
}

/************************************************************************
*	END OF FILE
*************************************************************************/