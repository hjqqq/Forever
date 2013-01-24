#pragma once

#include "CItem.h"
#include "CArmorInfo.h"

// ArmorPage ��ܤ��

class ArmorPage : public CDialog
{
	DECLARE_DYNAMIC(ArmorPage)

public:
	ArmorPage(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~ArmorPage();

// ��ܤ�����
	enum { IDD = IDD_ItemTypeArmor };

	void initPage(CArmorInfo* pInfo);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	void AttrTypeShow();
	void setAttrAll(AdvancedAttribute Attr);
	AdvancedAttribute getAttrAll();
	void AttrSave();

	DECLARE_MESSAGE_MAP()

private:
	enum{BASE_ATTR, EXTEND_ATTR};
	int AttrType;
	CArmorInfo* m_pCA;
public:
	afx_msg void OnBnClickedAttrsave();
	afx_msg void OnCbnSelchangeAttrtype();
	afx_msg void OnCbnSelchangeQuality();
	afx_msg void OnCbnSelchangeWear();
	afx_msg void OnEnChangeMeshname();
};
