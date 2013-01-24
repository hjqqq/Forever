#pragma once

#include "CConsumableInfo.h"

// ConsumablePage ��ܤ��

class ConsumablePage : public CDialog
{
	DECLARE_DYNAMIC(ConsumablePage)

public:
	ConsumablePage(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~ConsumablePage();

// ��ܤ�����
	enum { IDD = IDD_ItemTypeConsumable };

	void initPage(CConsumableInfo* pInfo);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()

private:
	CConsumableInfo* m_pCC;
public:
	afx_msg void OnEnChangeDesc();
	afx_msg void OnCbnSelchangeEffect();
	afx_msg void OnEnChangeMuch();
};
