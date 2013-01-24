// onsumablePage.cpp : ��@��
//

#include "stdafx.h"
#include "ForeverEditor.h"
#include "ConsumablePage.h"


// ConsumablePage ��ܤ��

IMPLEMENT_DYNAMIC(ConsumablePage, CDialog)

ConsumablePage::ConsumablePage(CWnd* pParent /*=NULL*/)
	: CDialog(ConsumablePage::IDD, pParent)
{

}

ConsumablePage::~ConsumablePage()
{
}

void ConsumablePage::initPage(CConsumableInfo* pInfo)
{
	m_pCC = pInfo;
	SetDlgItemText(IDC_Desc, m_pCC->getDesc().c_str());

	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_Effect);
	pTB->SetCurSel(m_pCC->getEffect());

	SetDlgItemInt(IDC_Much, m_pCC->getMuch());
}

void ConsumablePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ConsumablePage, CDialog)
	ON_EN_CHANGE(IDC_Desc, &ConsumablePage::OnEnChangeDesc)
	ON_CBN_SELCHANGE(IDC_Effect, &ConsumablePage::OnCbnSelchangeEffect)
	ON_EN_CHANGE(IDC_Much, &ConsumablePage::OnEnChangeMuch)
END_MESSAGE_MAP()


// ConsumablePage �T���B�z�`��

void ConsumablePage::OnEnChangeDesc()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialog::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X

	CString str;
	GetDlgItemText(IDC_Desc, str);
	m_pCC->m_strDesc = ((LPCTSTR) str);
}

void ConsumablePage::OnCbnSelchangeEffect()
{
	// TODO: �b���[�J����i���B�z�`���{���X

	CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_Effect);
	m_pCC->m_effect = ((EdibleEffectType) pTB->GetCurSel());
}

void ConsumablePage::OnEnChangeMuch()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialog::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X

	m_pCC->m_iMuch = GetDlgItemInt(IDC_Much);
}
