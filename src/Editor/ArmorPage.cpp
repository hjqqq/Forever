// ArmorPage.cpp : ��@��
//

#include "stdafx.h"
#include "ForeverEditor.h"
#include "ArmorPage.h"
#include "Common.h"


// ArmorPage ��ܤ��

IMPLEMENT_DYNAMIC(ArmorPage, CDialog)

ArmorPage::ArmorPage(CWnd* pParent /*=NULL*/)
	: CDialog(ArmorPage::IDD, pParent)
{

}

ArmorPage::~ArmorPage()
{
}

void ArmorPage::initPage(CArmorInfo* pInfo)
{
	m_pCA = pInfo;
	CComboBox* pTB = (CComboBox*) GetDlgItem (IDC_Quality);	//�ŧiComboBox�ܼ�
	pTB->SetCurSel(pInfo->getQuality());					//��ܫ~��

	pTB = (CComboBox*) GetDlgItem (IDC_Wear);				//�ŧiComboBox�ܼ�
	pTB->SetCurSel(pInfo->getWear());						//��ܬ�b���ӳ���

	pTB = (CComboBox*) GetDlgItem (IDC_AttrType);			//�ŧiComboBox�ܼ�
	AttrType = BASE_ATTR;
	pTB->SetCurSel(AttrType);								//�w�]��ܰ��ݩ�

	SetDlgItemText(IDC_MeshName, pInfo->getMeshName().c_str());

	AttrTypeShow();
}

void ArmorPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void ArmorPage::AttrTypeShow()
{
	if(AttrType == BASE_ATTR)
	{
		AdvancedAttribute Attr = m_pCA->getBaseAttr();

		setAttrAll(Attr);
	}
	else if(AttrType == EXTEND_ATTR)
	{
		AdvancedAttribute Attr = m_pCA->getExtendAttr();

		setAttrAll(Attr);
	}
}

void ArmorPage::setAttrAll(AdvancedAttribute Attr)
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

AdvancedAttribute ArmorPage::getAttrAll()
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

void ArmorPage::AttrSave()
{
	AdvancedAttribute Attr = getAttrAll();
	if(AttrType == BASE_ATTR)
	{
		m_pCA->setBaseAttr(Attr);
	}
	else if(AttrType == EXTEND_ATTR)
	{
		m_pCA->setExtendAttr(Attr);
	}
}

BEGIN_MESSAGE_MAP(ArmorPage, CDialog)
	ON_BN_CLICKED(IDC_AttrSave, &ArmorPage::OnBnClickedAttrsave)
	ON_CBN_SELCHANGE(IDC_AttrType, &ArmorPage::OnCbnSelchangeAttrtype)
	ON_CBN_SELCHANGE(IDC_Quality, &ArmorPage::OnCbnSelchangeQuality)
	ON_CBN_SELCHANGE(IDC_Wear, &ArmorPage::OnCbnSelchangeWear)
	ON_EN_CHANGE(IDC_MeshName, &ArmorPage::OnEnChangeMeshname)
END_MESSAGE_MAP()


// ArmorPage �T���B�z�`��

void ArmorPage::OnBnClickedAttrsave()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	AttrSave();
}

void ArmorPage::OnCbnSelchangeAttrtype()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	AttrSave();

	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_AttrType);

	AttrType = pTB->GetCurSel();

	AttrTypeShow();
}

void ArmorPage::OnCbnSelchangeQuality()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_Quality);

	m_pCA->setQuality((EquipQuality) pTB->GetCurSel());
}

void ArmorPage::OnCbnSelchangeWear()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_Wear);

	m_pCA->m_wear = ((ArmorWearType) pTB->GetCurSel());
}

void ArmorPage::OnEnChangeMeshname()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialog::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	CString str;
	GetDlgItemText(IDC_MeshName, str);
	m_pCA->setMeshName(str.GetBuffer());
}
