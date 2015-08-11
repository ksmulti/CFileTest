// CFileTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CFileTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			MyTest();
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

void MyTest()
{
	//OpenFile();
	//OpenFileTryCatch();
	//CreateFile();
	//ReadAndWrite();
	//FindFile();
	EnumerateFolders();
	getchar();
}

void OpenFile()
{
	CFile file;
	CFileException e;
	if (file.Open(_T("File.txt"), CFile::modeReadWrite, &e))
	{
		//It worked
	}
	else
	{
		e.ReportError();
	}
}

void OpenFileTryCatch()
{
	try
	{
		CFile file(_T("File.txt"), CFile::modeReadWrite);
	}
	catch (CFileException* e)
	{
		cout << e->m_cause;
		e->ReportError();
		e->Delete();
	}
}

void CreateFile()
{
	CFile file;
	file.Open(_T("File.txt"), CFile::modeReadWrite|CFile::modeCreate|CFile::modeNoTruncate|CFile::shareDenyNone);
}

void ReadAndWrite()
{
	BYTE buffer[0x1000];
	try
	{
		CFile file(_T("File.txt"), CFile::modeReadWrite);
		ULONGLONG dwBytesRemaining = file.GetLength();
		while (dwBytesRemaining) 
		{
			ULONGLONG dwPosition = file.GetPosition();
			UINT nBytesRead = file.Read(buffer, sizeof(buffer));
			DWORD a = ::CharLowerBuff((LPTSTR)buffer, nBytesRead);
			file.Seek(dwPosition, CFile::begin);
			file.Write(buffer, nBytesRead);
			dwBytesRemaining -= nBytesRead;
		}
	}
	catch (CFileException* e)
	{
		e->ReportError();
		e->Delete();
	}
}

void FindFile()
{
	WIN32_FIND_DATA fd;
	HANDLE hFind = :: FindFirstFile(_T("*.*"), &fd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				TRACE(_T("%s\n"), fd.cFileName);
		} while(::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
}

void EnumerateFolders()
{
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(_T("*.*"), &fd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				CString name = fd.cFileName;
				if (name != _T(".") && name != _T(".."))
				{
					TRACE(_T("%s\n"), fd.cFileName);
					::SetCurrentDirectory(fd.cFileName);
					EnumerateFolders();
					::SetCurrentDirectory(_T(".."));
				}
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
}
