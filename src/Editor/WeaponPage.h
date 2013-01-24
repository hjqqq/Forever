#pragma once

#include "CItem.h"
#include "CWeaponInfo.h"

// WeaponPage ��ܤ��

class WeaponPage : public CDialog
{
	DECLARE_DYNAMIC(WeaponPage)

public:
	WeaponPage(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~WeaponPage();

// ��ܤ�����
	enum { IDD = IDD_ItemTypeWeapon };

	void initPage(CWeaponInfo* pInfo);

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
	CWeaponInfo* m_pCW;
public:
	afx_msg void OnBnClickedAttrsave();
	afx_msg void OnCbnSelchangeAttrtype();
	afx_msg void OnCbnSelchangeQuality();
	afx_msg void OnCbnSelchangeWield();
	afx_msg void OnEnChangeMeshname();
};
