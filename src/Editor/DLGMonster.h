#pragma once


// DLGMonster ��ܤ��

class DLGMonster : public CDialog
{
	DECLARE_DYNAMIC(DLGMonster)

public:
	DLGMonster(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~DLGMonster();

// ��ܤ�����
	enum { IDD = IDD_MonsterEdit };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
};
