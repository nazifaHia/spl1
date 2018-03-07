#ifdef _UNICODE
#define _tcslen wcslen
#else
#define _tcslem strlen
#endif // _UNICODE

//#include<WinNT.h>
#include<windows.h>
#include<stdarg.h>
#define DIRNAME_LEN (MAX_PATH+2)


BOOL PrintStrings(HANDLE hOut,LPCTSTR pMsg,DWORD n )
{
	DWORD msgLen,count;
	va_list pMsgList;
	va_start(pMsgList,hOut);

	while((pMsg=va_arg(pMsgList,LPCTSTR))!=NULL){
        msgLen=_tcslen(pMsg);
        if(!writeConsole(hOut,pMsg,msgLen,&count,NULL)&& !writeFile(hOut,pMsg,msgLen*sizeof(TCHAR),&count,NULL))
            va_end(pMsgList);
            return FALSE;
	}
	va_end (pMsgList);
	return TRUE;
}

BOOL PrintMsg(HANDLE hOut,LPCTSTR pMsg ){
	return PrintSrings(hOut,pMsg,NULL);
}

BOOL ConsolePrompt(LPCTSTR pPromtMsg,LPTSTR pResponse,DWORD maxChar,BOOL echo){

	HANDLE hIn,hOut;
	DWORD charIn,echoFlag;
	BOOL success;

	hIn=CreateFile(_T("CONIN$"),GENERIC_READ| GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	hOut=CreateFile(_T("CONOUT$"),GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	echoFlag=echo? ENABLE_ECHO_INPUT :0;
	success=

		SetConsoleMode(hIn,ENABLE_LINE_INPUT|echoFlag|ENABLE_PROCESSED_INPUT)
		&&SetConsoleMode(hOut,ENABLE_WRAP_AT_EOL_OUTPUT|ENABLE_PROCESSED_OUTPUT)
		&& PrintStrings(hOut,pPromtMsg,NULL)
		&& ReadConsole(hIn,pResponse,maxChar-2,&charIn,NULL);

		if(success){
			pResponse[charIn-2]='\0';
		}
		else
		ReportError(_T("console prompt failure"),0,TRUE);

		CloseHandle(hIn);
		CloseHandle(hOut);
		return success;
}



int _tmain(int argc,LPTSTR argv[])
{
	TCHAR pwdBuffer[DIRNAME_LEN];
	DWORD lenCurDir;

	lenCurDir=GetCurrentDirectoty(DIRNAME_LEN,pwdBuffer);

	if(lenCurDir==0)
	{
		ReportError(_T("Failure getting pathname"),1,TRUE);
	}
	if(lenCurDir>DIRNAME_LEN){
		ReportError(_T("Directory name is too long"),2,FALSE);
	}

	PrintMsg(GetStdHandle(STD_OUTPUT_HANDLE),pwdBuffer);

	return 0;
}
