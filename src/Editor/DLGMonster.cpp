// DLGMonster.cpp : ��@��
//

#include "stdafx.h"
#include "ForeverEditor.h"
#include "DLGMonster.h"


// DLGMonster ��ܤ��

IMPLEMENT_DYNAMIC(DLGMonster, CDialog)

DLGMonster::DLGMonster(CWnd* pParent /*=NULL*/)
	: CDialog(DLGMonster::IDD, pParent)
{

}

DLGMonster::~DLGMonster()
{
}

void DLGMonster::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DLGMonster, CDialog)
END_MESSAGE_MAP()


// DLGMonster �T���B�z�`��
