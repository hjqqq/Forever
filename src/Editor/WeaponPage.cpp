// WeaponPage.cpp : ��@��
//

#include "stdafx.h"
#include "ForeverEditor.h"
#include "WeaponPage.h"
#include "Common.h"


// WeaponPage ��ܤ��

IMPLEMENT_DYNAMIC(WeaponPage, CDialog)

WeaponPage::WeaponPage(CWnd* pParent /*=NULL*/)
	: CDialog(WeaponPage::IDD, pParent)
{

}

WeaponPage::~WeaponPage()
{
}

void WeaponPage::initPage(CWeaponInfo* pInfo)
{
	m_pCW = pInfo;
	CComboBox* pTB = (CComboBox*) GetDlgItem (IDC_Quality);	//�ŧiComboBox�ܼ�
	pTB->SetCurSel(pInfo->getQuality());					//��ܫ~��

	pTB = (CComboBox*) GetDlgItem (IDC_Wield);				//�ŧiComboBox�ܼ�
	pTB->SetCurSel(pInfo->getWield());						//��ܭ���˳�

	pTB = (CComboBox*) GetDlgItem (IDC_AttrType);			//�ŧiComboBox�ܼ�
	AttrType = BASE_ATTR;
	pTB->SetCurSel(AttrType);								//�w�]��ܰ��ݩ�

	SetDlgItemText(IDC_MeshName, pInfo->getMeshName().c_str());

	AttrTypeShow();
}

void WeaponPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void WeaponPage::AttrTypeShow()
{
	if(AttrType == BASE_ATTR)
	{
		AdvancedAttribute Attr = m_pCW->getBaseAttr();

		setAttrAll(Attr);
	}
	else if(AttrType == EXTEND_ATTR)
	{
		AdvancedAttribute Attr = m_pCW->getExtendAttr();

		setAttrAll(Attr);
	}
}

void WeaponPage::setAttrAll(AdvancedAttribute Attr)
{
		SetDlgItemInt(IDC_AttrHP, Attr.iHP);

		SetDlgItemInt(IDC_AttrMP, Attr.iMP);

		SetDlgItemInt(IDC_AttrHPMax, Attr.iHPMax);

		SetDlgItemInt(IDC_AttrMPMax, Attr.iMPMax);

		SetDlgItemInt(IDC_AttrATK, Attr.iATK);

		SetDlgItemInt(IDC_AttrDEF, Attr.iDEF);

		SetDlgItemInt(IDC_AttrHIT, Attr.iHIT);

		SetDlgItemInt(IDC_AttrCRI, Attr.iCRI);

		SetDlgItemInt(IDC_AttrMATK, Attr.iMATK);

		SetDlgItemInt(IDC_AttrMDEF, Attr.iMDEF);

		SetDlgItemInt(IDC_AttrMHIT, Attr.iMHIT);

		SetDlgItemInt(IDC_AttrMCRI, Attr.iMCRI);

		SetDlgItemInt(IDC_AttrSDEF, Attr.iSDEF);

		SetDlgItemInt(IDC_AttrWDEF, Attr.iWDEF);

		SetDlgItemInt(IDC_AttrFlee, Attr.iFlee);
//--------------------------------------------------------
		CString str;
		str.Format("%f", Attr.fMove);
		SetDlgItemText(IDC_AttrMove, str);

		str.Format("%f", Attr.fATKSpeed);
		SetDlgItemText(IDC_AttrATKSpeed, str);

		str.Format("%f", Attr.fCasting);
		SetDlgItemText(IDC_AttrCasting, str);

}

AdvancedAttribute WeaponPage::getAttrAll()
{
	AdvancedAttribute Attr;

	Attr.iHP = GetDlgItemInt(IDC_AttrHP);

	Attr.iMP = GetDlgItemInt(IDC_AttrMP);
	
	Attr.iHPMax = GetDlgItemInt(IDC_AttrHPMax);
	
	Attr.iMPMax = GetDlgItemInt(IDC_AttrMPMax);
	
	Attr.iATK = GetDlgItemInt(IDC_AttrATK);
	
	Attr.iDEF = GetDlgItemInt(IDC_AttrDEF);
	
	Attr.iHIT = GetDlgItemInt(IDC_AttrHIT);
	
	Attr.iCRI = GetDlgItemInt(IDC_AttrCRI);
	
	Attr.iMATK = GetDlgItemInt(IDC_AttrMATK);
	
	Attr.iMDEF = GetDlgItemInt(IDC_AttrMDEF);
	
	Attr.iMHIT = GetDlgItemInt(IDC_AttrMHIT);
	
	Attr.iMCRI = GetDlgItemInt(IDC_AttrMCRI);
	
	Attr.iSDEF = GetDlgItemInt(IDC_AttrSDEF);
	
	Attr.iWDEF = GetDlgItemInt(IDC_AttrWDEF);
	
	Attr.iFlee = GetDlgItemInt(IDC_AttrFlee);
//---------------------------------------------------
	CString str;
	
	GetDlgItemText(IDC_AttrMove, str);
	Attr.fMove = (float) atof(str);
	
	GetDlgItemText(IDC_AttrATKSpeed, str);
	Attr.fATKSpeed = (float) atof(str);

	GetDlgItemText(IDC_AttrCasting, str);
	Attr.fCasting = (float) atof(str);
	return Attr;
}

void WeaponPage::AttrSave()
{
	AdvancedAttribute Attr = getAttrAll();
	if(AttrType == BASE_ATTR)
	{
		m_pCW->setBaseAttr(Attr);
	}
	else if(AttrType == EXTEND_ATTR)
	{
		m_pCW->setExtendAttr(Attr);
	}
}

BEGIN_MESSAGE_MAP(WeaponPage, CDialog)
	ON_BN_CLICKED(IDC_AttrSave, &WeaponPage::OnBnClickedAttrsave)
	ON_CBN_SELCHANGE(IDC_AttrType, &WeaponPage::OnCbnSelchangeAttrtype)
	ON_CBN_SELCHANGE(IDC_Quality, &WeaponPage::OnCbnSelchangeQuality)
	ON_CBN_SELCHANGE(IDC_Wield, &WeaponPage::OnCbnSelchangeWield)
	ON_EN_CHANGE(IDC_MeshName, &WeaponPage::OnEnChangeMeshname)
END_MESSAGE_MAP()


// WeaponPage �T���B�z�`��


void WeaponPage::OnBnClickedAttrsave()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	AttrSave();
}

void WeaponPage::OnCbnSelchangeAttrtype()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	AttrSave();
		
	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_AttrType);

	AttrType = pTB->GetCurSel();

	AttrTypeShow();
}

void WeaponPage::OnCbnSelchangeQuality()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_Quality);

	m_pCW->setQuality((EquipQuality) pTB->GetCurSel());
}

void WeaponPage::OnCbnSelchangeWield()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_Wield);

	m_pCW->m_wield = ((WeaponWieldType) pTB->GetCurSel());
}

void WeaponPage::OnEnChangeMeshname()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialog::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	CString str;
	GetDlgItemText(IDC_MeshName, str);
	m_pCW->setMeshName(str.GetBuffer());
}
