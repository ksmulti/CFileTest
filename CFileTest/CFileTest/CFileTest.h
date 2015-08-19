#pragma once

#include "resource.h"
void MyTest();
void OpenFile();
void OpenFileTryCatch();
void CreateFile();
void ReadAndWrite();
void FindFile();
void EnumerateFolders();
void MySerialize();

class CLine : public CObject
{
	DECLARE_SERIAL(CLine)

protected:
	CPoint m_ptFrom;
	CPoint m_ptTo;
	COLORREF m_clrLine; // Line color (new in version 2)

public:
	CLine() {}
	CLine (CPoint from, CPoint to, COLORREF color) { m_ptFrom = from; m_ptTo = to; m_clrLine = color; }
	void Serialize(CArchive& ar);
};
