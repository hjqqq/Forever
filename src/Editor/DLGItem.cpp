// ..\..\src\Editor\DLGItem.cpp : ��@��
//

#include "stdafx.h"
#include "ForeverEditor.h"
#include "DLGItem.h"

#include "CItemInfoLoader.h"
#include "AttributeSet.h"


// DLGItem ��ܤ��

IMPLEMENT_DYNAMIC(DLGItem, CDialog)

DLGItem::DLGItem(CWnd* pParent /*=NULL*/)
	: CDialog(DLGItem::IDD, pParent)
{

}

DLGItem::~DLGItem()
{
}

void DLGItem::initDlg()
{
	createPage () ;
	upDate();

	CListBox* pLB = (CListBox*)GetDlgItem (IDC_ItemList);
	pLB->SetCurSel(0);
	CItemInfo* pInfo = CItem::getInfo(0);
	CComboBox* pTB = (CComboBox*)GetDlgItem (IDC_addClass);
	pTB->SetCurSel(0);
	replaceSelItem(pInfo);
	
}

void DLGItem::upDate()
{
	char buf[256] ;

	CListBox* pLB = (CListBox*)GetDlgItem (IDC_ItemList) ;
	int oriSel = pLB->GetCurSel () ;
	pLB->ResetContent () ;
	for (int i = 0; i< CItem::getInfoCount (); i++)
	{
		CItemInfo* pInfo = CItem::getInfo (i) ;

		CString str ;
		sprintf_s (buf, sizeof(buf), "[%d] %s", i, (const char*)pInfo->getName().c_str()) ;
		str = buf ;

		pLB->AddString (str) ;
	}

	pLB->SetCurSel (oriSel) ;

}

void DLGItem::createPage()
{
	m_page1.Create(IDD_ItemTypeWeapon, &m_tab);
	m_page2.Create(IDD_ItemTypeArmor, &m_tab);
	m_page3.Create(IDD_ItemTypeConsumable, &m_tab);
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 2;
	rc.bottom -= 10;
	rc.left += 2;
	rc.right -= 10;
	m_page1.MoveWindow(&rc);
	m_page2.MoveWindow(&rc);
	m_page3.MoveWindow(&rc);
	pDialog[WAEPON] = &m_page1;
	pDialog[ARMOR] = &m_page2;
	pDialog[CONSUMABLE] = &m_page3;
	m_CurSelTab = WAEPON;
}

void DLGItem::replaceSelItem(CItemInfo* pInfo)
{
	if(pInfo != NULL)
	{
		SetDlgItemText(IDC_ItemName, pInfo->getName().c_str());		//��ܦW�r

		CComboBox* pTB = (CComboBox*) GetDlgItem (IDC_ItemType);	//�ŧiComboBox�ܼ�
		pTB->SetCurSel(pInfo->getItemType());						//��ܪ��~���A

		CButton* pChB = (CButton*) GetDlgItem (IDC_ItemSoulBind);	//�ŧiCheckBox�ܼ�
		pChB->SetCheck(pInfo->getSoulBind());						//��ܬO�_�j�w

		SetDlgItemInt(IDC_ItemLevel,pInfo->getLevel());				//��ܨϥε���
		
		SetDlgItemInt(IDC_ItemStackLimit,pInfo->getStackLimit());	//��ܰ��|�W��
		
		SetDlgItemInt(IDC_ItemSellPrice,pInfo->getSellPrice());		//��ܽ��
		
		SetDlgItemInt(IDC_ItemBuyPrice,pInfo->getBuyPrice());		//��ܶR��

		SetDlgItemText(IDC_iconName, pInfo->geticonName().c_str());	//��ܹϥܦW��

		pageShow(pInfo);											//������ܭ���

	}

}

void DLGItem::pageShow(CItemInfo* pInfo)
{
	if(pInfo->getClassType() == WEAPON)
		{
			pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
			m_CurSelTab = WAEPON;
			pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);

			CWeaponInfo* pWInfo;
			pWInfo = ((CWeaponInfo*) pInfo);

			m_page1.initPage(pWInfo);

		}
	else if(pInfo->getClassType() == ARMOR)
		{	
			pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
			m_CurSelTab = ARMOR;
			pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);

			CArmorInfo* pAInfo;
			pAInfo = ((CArmorInfo*) pInfo);

			m_page2.initPage(pAInfo);
		}
	else if(pInfo->getClassType() == CONSUMABLE)
		{
			pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
			m_CurSelTab = CONSUMABLE;
			pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);

			CConsumableInfo* pCInfo;
			pCInfo = ((CConsumableInfo*) pInfo);

			m_page3.initPage(pCInfo);
		}
}

void DLGItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_ItemTypeMenu,m_tab);

}

void DLGItem::OnClose () 
{
}

void DLGItem::OnOK () 
{
}

void DLGItem::OnCancel () 
{
}

BEGIN_MESSAGE_MAP(DLGItem, CDialog)
	ON_LBN_SELCHANGE(IDC_ItemList, &DLGItem::OnLbnSelchangeItemlist)
	ON_EN_CHANGE(IDC_ItemName, &DLGItem::OnEnChangeItemname)
	ON_CBN_SELCHANGE(IDC_ItemType, &DLGItem::OnCbnSelchangeItemtype)
	ON_BN_CLICKED(IDC_ItemSoulBind, &DLGItem::OnBnClickedItemsoulbind)
	ON_EN_CHANGE(IDC_ItemLevel, &DLGItem::OnEnChangeItemlevel)
	ON_EN_CHANGE(IDC_ItemStackLimit, &DLGItem::OnEnChangeItemstacklimit)
	ON_EN_CHANGE(IDC_ItemSellPrice, &DLGItem::OnEnChangeItemsellprice)
	ON_EN_CHANGE(IDC_ItemBuyPrice, &DLGItem::OnEnChangeItembuyprice)
	ON_BN_CLICKED(IDC_SaveList, &DLGItem::OnBnClickedSavelist)
	ON_BN_CLICKED(IDC_LoadList, &DLGItem::OnBnClickedLoadlist)
	ON_BN_CLICKED(IDC_AddItem, &DLGItem::OnBnClickedAdditem)
	ON_EN_CHANGE(IDC_iconName, &DLGItem::OnEnChangeiconname)
   ON_BN_CLICKED(IDC_DelItem, &DLGItem::OnBnClickedDelitem)
END_MESSAGE_MAP()


// DLGItem �T���B�z�`��

void DLGItem::OnLbnSelchangeItemlist()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	CListBox* pLB = (CListBox*) GetDlgItem (IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);

	replaceSelItem(pInfo);
	

}

void DLGItem::OnEnChangeItemname()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialog::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);
	if(pInfo != NULL)
	{
		CString str;
		GetDlgItemText(IDC_ItemName, str);		
		pInfo->setName((LPCTSTR) str);


		upDate();
	}
}

void DLGItem::OnCbnSelchangeItemtype()
{
	// TODO: �b���[�J����i���B�z�`���{���X

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);
	if(pInfo != NULL)
	{		
		CComboBox* pTB = (CComboBox*) GetDlgItem(IDC_ItemType);

		int type = pTB->GetCurSel();
		CItemInfoLoader loader;
		if(WEAPON == pInfo->getClassType())
		{
			if(loader.isWeapon(type))
			{
				pInfo->setItemType((ItemType) pTB->GetCurSel());
			}
			else
			{
				pTB->SetCurSel(pInfo->getItemType());
			}
		}
		else if(ARMOR == pInfo->getClassType())
		{
			if(loader.isArmor(type))
			{
				pInfo->setItemType((ItemType) pTB->GetCurSel());
			}
			else
			{
				pTB->SetCurSel(pInfo->getItemType());
			}
		}
		else if(CONSUMABLE == pInfo->getClassType())
		{
			if(loader.isConsumable(type))
			{
				pInfo->setItemType((ItemType) pTB->GetCurSel());
			}
			else
			{
				pInfo->setItemType((ItemType) pTB->GetCurSel());
			}
		}


		pageShow(pInfo);

	}
}

void DLGItem::OnBnClickedItemsoulbind()
{
	// TODO: �b���[�J����i���B�z�`���{���X

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);
	if(pInfo != NULL)
	{		
		CButton* pCHB = (CButton*) GetDlgItem(IDC_ItemSoulBind);

		if(pCHB->GetCheck())
		{
			pInfo->setSoulBind(true);
		}
		else
		{
			pInfo->setSoulBind(false);
		}


	}
}

void DLGItem::OnEnChangeItemlevel()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialog::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);
	if(pInfo != NULL)
	{	
		pInfo->setLevel(GetDlgItemInt(IDC_ItemLevel));


	}
}

void DLGItem::OnEnChangeItemstacklimit()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialog::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);
	if(pInfo != NULL)
	{	
		pInfo->setStackLimit(GetDlgItemInt(IDC_ItemStackLimit));


	}
}

void DLGItem::OnEnChangeItemsellprice()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialog::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);
	if(pInfo != NULL)
	{	
		pInfo->setSellPrice(GetDlgItemInt(IDC_ItemSellPrice));


	}
}

void DLGItem::OnEnChangeItembuyprice()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialog::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);
	if(pInfo != NULL)
	{	
		pInfo->setBuyPrice(GetDlgItemInt(IDC_ItemBuyPrice));


	}
}

void DLGItem::OnBnClickedSavelist()
{
	// TODO: �b���[�J����i���B�z�`���{���X
    CItem::write ("Item.fla") ;
}

void DLGItem::OnBnClickedLoadlist()
{
	// TODO: Add your control notification handler code here
	CItem::read("Item.fla");
	upDate();
	CListBox* pLB = (CListBox*)GetDlgItem (IDC_ItemList);
	pLB->SetCurSel(0);
	CItemInfo* pInfo = CItem::getInfo(0);
	replaceSelItem(pInfo);
}

void DLGItem::OnBnClickedAdditem()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	CComboBox* pTB = (CComboBox*)GetDlgItem (IDC_addClass);
	if(WEAPON == (ItemClassType) pTB->GetCurSel())
	{
		CWeaponInfo* pWp = new CWeaponInfo();
		AdvancedAttribute baseAttr;
		AdvancedAttribute extendAttr;
		AttributeClear(baseAttr);
		AttributeClear(extendAttr);

		pWp->initWeaponInfo("�Z��", "", "", DAGGER, false, 0, 1, 0, 0, COMMON, baseAttr, extendAttr,
			ONE_HAND);

		CItem::addInfo(pWp);
	}
	else if(ARMOR == (ItemClassType) pTB->GetCurSel())
	{
		CArmorInfo* pAm = new CArmorInfo();
		AdvancedAttribute baseAttr;
		AdvancedAttribute extendAttr;
		AttributeClear(baseAttr);
		AttributeClear(extendAttr);

		pAm->initArmorInfo("����", "", "", CLOTH, false, 0, 1, 0, 0, COMMON, baseAttr, extendAttr,
			CLOTHES);

		CItem::addInfo(pAm);
	}
	else if(CONSUMABLE == (ItemClassType) pTB->GetCurSel())
	{
		CConsumableInfo* pCs = new CConsumableInfo();
		
		pCs->initConsumableInfo("���Ӫ��~", "", POTION, false, 0, 1, 0, 0, "��r����", EDIBLE_HP, 0);

		CItem::addInfo(pCs);
	}
	upDate();
}

void DLGItem::OnEnChangeiconname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CListBox* pLB = (CListBox*) GetDlgItem(IDC_ItemList);
	int offset = pLB->GetCurSel();
	CItemInfo* pInfo = CItem::getInfo(offset);

	if(NULL != pInfo)
	{
		CString str;
		GetDlgItemText(IDC_iconName,str);
		pInfo->seticonName((LPCTSTR) str);
	}
}

void DLGItem::OnBnClickedDelitem()
{
   CListBox* pLB = (CListBox*)GetDlgItem (IDC_ItemList);
   if(pLB->GetCurSel() > -1) {
      int offset = pLB->GetCurSel();
      CItem::delInfo(offset);
      upDate();
   }
}
