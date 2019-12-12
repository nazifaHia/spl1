/* Chapter 2. cat. */
/* cat [options] [files]
	Only the -s option is used. Others are ignored.
	-s suppresses error report when a file does not exist */

#include "Everything.h"

#define BUF_SIZE 0x200
VOID ReportError (LPCTSTR userMessage, DWORD exitCode, BOOL printErrorMessage);
DWORD Options (int argc, LPCTSTR argv [], LPCTSTR OptStr, ...);

static VOID CatFile (HANDLE, HANDLE);

int _tmain (int argc, LPTSTR argv [])
{
	HANDLE hInFile, hStdIn = GetStdHandle (STD_INPUT_HANDLE);
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	BOOL dashS;
	int iArg, iFirstFile;

	/*	dashS will be set only if "-s" is on the command line. */
	/*	iFirstFile is the argv [] index of the first input file. */
	iFirstFile = Options (argc, argv, _T("s"), &dashS, NULL);

	if (iFirstFile == argc) { /* No files in arg list. */
		CatFile (hStdIn, hStdOut);
		return 0;
	}

	/* Process the input files. */
	for (iArg = iFirstFile; iArg < argc; iArg++) {
		hInFile = CreateFile (argv [iArg], GENERIC_READ,
				0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hInFile == INVALID_HANDLE_VALUE) {
			if (!dashS) ReportError (_T ("Cat Error: File does not exist."), 0, TRUE);
		} else {
			CatFile (hInFile, hStdOut);
			if (GetLastError() != 0 && !dashS) {
				ReportError (_T ("Cat Error: Could not process file completely."), 0, TRUE);
			}
			CloseHandle (hInFile);
		}
	}
	return 0;
}

static VOID CatFile (HANDLE hInFile, HANDLE hOutFile)
{
	DWORD nIn, nOut;
	BYTE buffer [BUF_SIZE];

	while (ReadFile (hInFile, buffer, BUF_SIZE, &nIn, NULL) && (nIn != 0)
			&& WriteFile (hOutFile, buffer, nIn, &nOut, NULL));

	return;
}


VOID ReportError (LPCTSTR userMessage, DWORD exitCode, BOOL printErrorMessage)

/* General-purpose function for reporting system errors.
	Obtain the error number and convert it to the system error message.
	Display this information and the user-specified message to the standard error device.
	userMessage:		Message to be displayed to standard error device.
	exitCode:		0 - Return.
					> 0 - ExitProcess with this code.
	printErrorMessage:	Display the last system error message if this flag is set. */
{
	DWORD eMsgLen, errNum = GetLastError ();
	LPTSTR lpvSysMsg;
	_ftprintf (stderr, _T("%s\n"), userMessage);
	if (printErrorMessage) {
		eMsgLen = FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				NULL, errNum, MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR) &lpvSysMsg, 0, NULL);
		if (eMsgLen > 0)
		{
			_ftprintf (stderr, _T("%s\n"), lpvSysMsg);
		}
		else
		{
			_ftprintf (stderr, _T("Last Error Number; %d.\n"), errNum);
		}

		if (lpvSysMsg != NULL) LocalFree (lpvSysMsg); /* Explained in Chapter 5. */
	}

	if (exitCode > 0)
		ExitProcess (exitCode);

	return;
}

/* Extension of ReportError to generate a user exception
	code rather than terminating the process. */

VOID ReportException (LPCTSTR userMessage, DWORD exceptionCode)

/* Report as a non-fatal error.
	Print the system error message only if the message is non-null. */
{
	if (lstrlen (userMessage) > 0)
		ReportError (userMessage, 0, TRUE);
			/* If fatal, raise an exception. */

	if (exceptionCode != 0)
		RaiseException (
			(0x0FFFFFFF & exceptionCode) | 0xE0000000, 0, 0, NULL);

	return;
}


/* Utility function to extract option flags from the command line.  */

DWORD Options (int argc, LPCTSTR argv [], LPCTSTR OptStr, ...)

/* argv is the command line.
	The options, if any, start with a '-' in argv[1], argv[2], ...
	OptStr is a text string containing all possible options,
	in one-to-one correspondence with the addresses of Boolean variables
	in the variable argument list (...).
	These flags are set if and only if the corresponding option
	character occurs in argv [1], argv [2], ...
	The return value is the argv index of the first argument beyond the options. */

{
	va_list pFlagList;
	LPBOOL pFlag;
	int iFlag = 0, iArg;

	va_start (pFlagList, OptStr);

	while ((pFlag = va_arg (pFlagList, LPBOOL)) != NULL
				&& iFlag < (int)_tcslen (OptStr)) {
		*pFlag = FALSE;
		for (iArg = 1; !(*pFlag) && iArg < argc && argv [iArg] [0] == _T('-'); iArg++)
			*pFlag = _memtchr (argv [iArg], OptStr [iFlag],
					_tcslen (argv [iArg])) != NULL;
		iFlag++;
	}

	va_end (pFlagList);

	for (iArg = 1; iArg < argc && argv [iArg] [0] == _T('-'); iArg++);

	return iArg;
}

