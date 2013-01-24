// ActionEditorDlg.cpp : ��@��
//

#include "stdafx.h"
#include "ActionEditor.h"
#include "ActionEditorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ܤ�����
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CActionEditorDlg ��ܤ��




CActionEditorDlg::CActionEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CActionEditorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

   m_pActionSystem = new CActionSystem(0);
   m_iActionListIdx = -1;
   m_iEventListIdx = -1;
}

void CActionEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CActionEditorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
   ON_BN_CLICKED(BTN_NEWACTION, &CActionEditorDlg::OnBnClickedNewaction)
   ON_LBN_SELCHANGE(LST_ACTIONLIST, &CActionEditorDlg::OnLbnSelchangeActionlist)
   ON_BN_CLICKED(BTN_CANCELSELACTIONLIST, &CActionEditorDlg::OnBnClickedCancelselactionlist)
   ON_BN_CLICKED(BTN_DELACTION, &CActionEditorDlg::OnBnClickedDelaction)
   ON_BN_CLICKED(BTN_NEWEVENT, &CActionEditorDlg::OnBnClickedNewevent)
   ON_LBN_SELCHANGE(LST_EVENTLIST, &CActionEditorDlg::OnLbnSelchangeEventlist)
   ON_BN_CLICKED(BTN_CANCELSELEVENTLIST, &CActionEditorDlg::OnBnClickedCancelseleventlist)
   ON_BN_CLICKED(BTN_DELEVENT, &CActionEditorDlg::OnBnClickedDelevent)
   ON_BN_CLICKED(BTN_SAVE, &CActionEditorDlg::OnBnClickedSave)
   ON_BN_CLICKED(BTN_LOAD, &CActionEditorDlg::OnBnClickedLoad)
END_MESSAGE_MAP()


// CActionEditorDlg �T���B�z�`��

BOOL CActionEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

   CComboBox *pcmbMove = (CComboBox*)GetDlgItem(CMB_MOVE);
   pcmbMove->SetCurSel(1);

	CComboBox *pcmbEvent = (CComboBox*)GetDlgItem(CMB_EVENT);
   pcmbEvent->SetCurSel(0);

   CButton *pbtnDelAction = (CButton*)GetDlgItem(BTN_DELACTION);
   pbtnDelAction->EnableWindow(FALSE);

   CButton *pbtnNewEvent = (CButton*)GetDlgItem(BTN_NEWEVENT);
   pbtnNewEvent->EnableWindow(FALSE);

   CButton *pbtnDelEvent = (CButton*)GetDlgItem(BTN_DELEVENT);
   pbtnDelEvent->EnableWindow(FALSE);

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

void CActionEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CActionEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CActionEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CActionEditorDlg::updateActionList()
{
   CListBox *pActionList = (CListBox*)GetDlgItem(LST_ACTIONLIST);
   pActionList->ResetContent();

   std::vector<CAction *>::iterator it = m_pActionSystem->m_pvtActionSet->begin();
   while(it != m_pActionSystem->m_pvtActionSet->end()) {
      CString str;
      char buf[256];
      memset(buf, 0, sizeof(buf));
      sprintf_s(buf, "[%d] %s", (*it)->getID(), (*it)->getName().c_str());
		str = buf;
		pActionList->AddString(str);

      it++;
   }

   pActionList->SetCurSel(m_iActionListIdx);
}

void CActionEditorDlg::clearActionData()
{
   SetDlgItemText(EDT_ACTIONID, "");
   SetDlgItemText(EDT_ACTIONNAME, "");
   SetDlgItemText(EDT_ANINAME, "");
   SetDlgItemText(EDT_ANITIME, "");
   CComboBox *pcmbMove = (CComboBox*)GetDlgItem(CMB_MOVE);
   pcmbMove->SetCurSel(1);
   SetDlgItemText(EDT_NEXTACTIONID, "");
}

void CActionEditorDlg::updateEventList()
{
   CListBox *pEventList = (CListBox*)GetDlgItem(LST_EVENTLIST);
   pEventList->ResetContent();

   CString str;
   char buf[256];

   CAction *pAction = m_pActionSystem->m_pvtActionSet->at(m_iActionListIdx);
   std::vector<CActionEventHandler *>::iterator it = pAction->m_pvtEventHandlerSet->begin();
   while(it != pAction->m_pvtEventHandlerSet->end()) {
      switch((*it)->m_triggerEvent.m_event) {
         case AET_NULL: {     
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_NULL => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }

         case AET_REACH: {
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_REACH => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }

         case AET_NOT_REACH: {
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_NOT_REACH => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }

         case AET_KEY: {
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_KEY => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }

         case AET_KEY_WASD: {
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_KEY_WASD => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }

         case AET_CAST_SKILL: {
            str.Empty();
            memset(buf, 0, sizeof(buf));
            sprintf_s(buf, "AET_CAST_SKILL => [%d]", (*it)->m_iNextActionID);
		      str = buf;
		      pEventList->AddString(str);
            break;
         }
      }

      it++;
   }

   pEventList->SetCurSel(m_iEventListIdx);
}

void CActionEditorDlg::clearEventData()
{
   CComboBox *pcmbEvent = (CComboBox*)GetDlgItem(CMB_EVENT);
   pcmbEvent->SetCurSel(0);
   SetDlgItemText(EDT_EVENTNEXTACTIONID, "");
   SetDlgItemText(EDT_KEY, "");
   SetDlgItemText(EDT_KEYDOWN, "");
   SetDlgItemText(EDT_KEYUP, "");
}

void CActionEditorDlg::OnBnClickedNewaction()
{
   CString str;
   ACTION_DATA actData;

   actData.iID           = GetDlgItemInt(EDT_ACTIONID);
   
   str.Empty();
   GetDlgItemText(EDT_ACTIONNAME, str);
   actData.name          = str.GetBuffer(0);
   
   str.Empty();
   GetDlgItemText(EDT_ANINAME, str);
   actData.animationName = str.GetBuffer(0);

   str.Empty();
   GetDlgItemText(EDT_ANITIME, str);
   std::string strFTime = str.GetBuffer(0);
   actData.fTime = fromString<float>(strFTime);

   CComboBox *pcmbMove = (CComboBox*)GetDlgItem(CMB_MOVE);
   int iMoveIdx = pcmbMove->GetCurSel();
   if(iMoveIdx == 0)
      actData.bMove      = true;
   else if(iMoveIdx == 1)
      actData.bMove      = false;

   actData.iNextActID    = GetDlgItemInt(EDT_NEXTACTIONID);

   if(m_iActionListIdx == -1) {
      CAction *pAction = new CAction();
      pAction->init(actData);
      m_pActionSystem->addAction(pAction);
   }
   else {
      CAction *pAction = m_pActionSystem->m_pvtActionSet->at(m_iActionListIdx);
      pAction->m_iID = actData.iID;
      pAction->m_name = actData.name;
      pAction->m_animationName = actData.animationName;
      pAction->m_fTime = actData.fTime;
      pAction->m_bMove = actData.bMove;
      pAction->m_iNextActID = actData.iNextActID;
   }

   //---���������ܩ�List
   updateActionList();

   clearActionData();

   if(m_iActionListIdx == -1) {
      CButton *pbtnDelAction = (CButton*)GetDlgItem(BTN_DELACTION);
      pbtnDelAction->EnableWindow(FALSE);

      CButton *pbtnNewEvent = (CButton*)GetDlgItem(BTN_NEWEVENT);
      pbtnNewEvent->EnableWindow(FALSE);

      CButton *pbtnDelEvent = (CButton*)GetDlgItem(BTN_DELEVENT);
      pbtnDelEvent->EnableWindow(FALSE);
   }
   else {
      CButton *pbtnDelAction = (CButton*)GetDlgItem(BTN_DELACTION);
      pbtnDelAction->EnableWindow(TRUE);

      CButton *pbtnNewEvent = (CButton*)GetDlgItem(BTN_NEWEVENT);
      pbtnNewEvent->EnableWindow(TRUE);
   }
}

void CActionEditorDlg::OnLbnSelchangeActionlist()
{
   CListBox *pActionList = (CListBox*)GetDlgItem(LST_ACTIONLIST);
   m_iActionListIdx = pActionList->GetCurSel();

   if(m_iActionListIdx > -1) {
      CAction *pAction = m_pActionSystem->m_pvtActionSet->at(m_iActionListIdx);

      SetDlgItemText(EDT_ACTIONID, toString<int>(pAction->m_iID).c_str());
      SetDlgItemText(EDT_ACTIONNAME, pAction->m_name.c_str());
      SetDlgItemText(EDT_ANINAME, pAction->m_animationName.c_str());
      SetDlgItemText(EDT_ANITIME, toString<float>(pAction->m_fTime).c_str());

      CComboBox *pcmbMove = (CComboBox*)GetDlgItem(CMB_MOVE);
      if(pAction->m_bMove == true)
         pcmbMove->SetCurSel(0);
      else if(pAction->m_bMove == false)
         pcmbMove->SetCurSel(1);

      SetDlgItemText(EDT_NEXTACTIONID, toString<int>(pAction->m_iNextActID).c_str());

      // ���Action�����Ҧ�Event
      updateEventList();

      CButton *pbtnDelAction = (CButton*)GetDlgItem(BTN_DELACTION);
      pbtnDelAction->EnableWindow(TRUE);

      CButton *pbtnNewEvent = (CButton*)GetDlgItem(BTN_NEWEVENT);
      pbtnNewEvent->EnableWindow(TRUE);
   }
   else {
      clearActionData();

      CButton *pbtnDelAction = (CButton*)GetDlgItem(BTN_DELACTION);
      pbtnDelAction->EnableWindow(FALSE);

      CButton *pbtnNewEvent = (CButton*)GetDlgItem(BTN_NEWEVENT);
      pbtnNewEvent->EnableWindow(FALSE);

      CButton *pbtnDelEvent = (CButton*)GetDlgItem(BTN_DELEVENT);
      pbtnDelEvent->EnableWindow(FALSE);
   }
}

void CActionEditorDlg::OnBnClickedCancelselactionlist()
{
   CListBox *pActionList = (CListBox*)GetDlgItem(LST_ACTIONLIST);
   m_iActionListIdx = -1;
   pActionList->SetCurSel(m_iActionListIdx);

   //---�M��
   clearActionData();

   // ����EventList�����
   OnBnClickedCancelseleventlist();

   // �M��EventList
   CListBox *pEventList = (CListBox*)GetDlgItem(LST_EVENTLIST);
   pEventList->ResetContent();

   CButton *pbtnDelAction = (CButton*)GetDlgItem(BTN_DELACTION);
   pbtnDelAction->EnableWindow(FALSE);

   CButton *pbtnNewEvent = (CButton*)GetDlgItem(BTN_NEWEVENT);
   pbtnNewEvent->EnableWindow(FALSE);

   CButton *pbtnDelEvent = (CButton*)GetDlgItem(BTN_DELEVENT);
   pbtnDelEvent->EnableWindow(FALSE);
}

void CActionEditorDlg::OnBnClickedDelaction()
{
   if(m_iActionListIdx > -1) {
      CAction *pAction = m_pActionSystem->m_pvtActionSet->at(m_iActionListIdx);
      std::vector<CAction *>::iterator it = m_pActionSystem->m_pvtActionSet->begin();
      while(it != m_pActionSystem->m_pvtActionSet->end()) {
         if((*it) == pAction) {
            m_pActionSystem->m_pvtActionSet->erase(it);
            break;
         }

         it++;
      }

      if(m_iActionListIdx >= (int)m_pActionSystem->m_pvtActionSet->size())
         m_iActionListIdx--;

      updateActionList();
      OnLbnSelchangeActionlist();
   }
}

void CActionEditorDlg::OnBnClickedNewevent()
{
   if(m_iActionListIdx > -1) {
      CActionEvent actEvent;
      CComboBox *pcmbEvent = (CComboBox*)GetDlgItem(CMB_EVENT);
      if(pcmbEvent->GetCurSel() == 0)
         actEvent.m_event = AET_NULL;
      else if(pcmbEvent->GetCurSel() == 1)
         actEvent.m_event = AET_REACH;
      else if(pcmbEvent->GetCurSel() == 2)
         actEvent.m_event = AET_NOT_REACH;
      else if(pcmbEvent->GetCurSel() == 3) {
         actEvent.m_event = AET_KEY;

         CString str;
         str.Empty();
         GetDlgItemText(EDT_KEY, str);
         std::string strKey = str.GetBuffer(0);
         actEvent.m_iKeyID = int(*(strKey.c_str()));
      }
      else if(pcmbEvent->GetCurSel() == 4) {
         actEvent.m_event = AET_KEY_WASD;

         CString str;
         str.Empty();
         GetDlgItemText(EDT_KEYDOWN, str);
         std::string strKeyDown = str.GetBuffer(0);
         actEvent.m_iKeyDownID = int(*(strKeyDown.c_str()));

         str.Empty();
         GetDlgItemText(EDT_KEYUP, str);
         std::string strKeyUp = str.GetBuffer(0);
         actEvent.m_iKeyUpID = int(*(strKeyUp.c_str()));
      }
      else if(pcmbEvent->GetCurSel() == 5) {
         actEvent.m_event = AET_CAST_SKILL;
      }

      if(m_iEventListIdx == -1) {
         CActionEventHandler *pActionEventHandler = new CActionEventHandler();
         pActionEventHandler->init(actEvent, GetDlgItemInt(EDT_EVENTNEXTACTIONID));

         CAction *pAction = m_pActionSystem->m_pvtActionSet->at(m_iActionListIdx);
         pAction->addEventHandler(pActionEventHandler);
      }
      else {
         CAction *pAction = m_pActionSystem->m_pvtActionSet->at(m_iActionListIdx);
         CActionEventHandler *pActionEventHandler = pAction->m_pvtEventHandlerSet->at(m_iEventListIdx);

         pActionEventHandler->m_triggerEvent = actEvent;
         pActionEventHandler->m_iNextActionID = GetDlgItemInt(EDT_EVENTNEXTACTIONID);
      }

      updateEventList();

      clearEventData();
   }
}

void CActionEditorDlg::OnLbnSelchangeEventlist()
{
   if(m_iActionListIdx > -1) {
      CListBox *pEventList = (CListBox*)GetDlgItem(LST_EVENTLIST);
      m_iEventListIdx = pEventList->GetCurSel();

      if(m_iEventListIdx > -1) {
         CAction *pAction = m_pActionSystem->m_pvtActionSet->at(m_iActionListIdx);
         CActionEventHandler *pActionEventHandler = pAction->m_pvtEventHandlerSet->at(m_iEventListIdx);

         CComboBox *pcmbEvent = (CComboBox*)GetDlgItem(CMB_EVENT);
         switch(pActionEventHandler->m_triggerEvent.m_event) {
            case AET_NULL:
               pcmbEvent->SetCurSel(0);
               break;

            case AET_REACH:
               pcmbEvent->SetCurSel(1);
               break;

            case AET_NOT_REACH:
               pcmbEvent->SetCurSel(2);
               break;

            case AET_KEY:
               pcmbEvent->SetCurSel(3);
               break;

            case AET_KEY_WASD:
               pcmbEvent->SetCurSel(4);
               break;

            case AET_CAST_SKILL:
               pcmbEvent->SetCurSel(5);
               break;
         }

         SetDlgItemText(EDT_EVENTNEXTACTIONID, toString<int>(pActionEventHandler->getNextActionID()).c_str());

         std::string strKey;
         strKey.clear();
         strKey = (char)pActionEventHandler->m_triggerEvent.m_iKeyID;
         SetDlgItemText(EDT_KEY, strKey.c_str());

         strKey.clear();
         strKey = (char)pActionEventHandler->m_triggerEvent.m_iKeyDownID;
         SetDlgItemText(EDT_KEYDOWN, strKey.c_str());

         strKey.clear();
         strKey = (char)pActionEventHandler->m_triggerEvent.m_iKeyUpID;
         SetDlgItemText(EDT_KEYUP, strKey.c_str());

         CButton *pbtnDelEvent = (CButton*)GetDlgItem(BTN_DELEVENT);
         pbtnDelEvent->EnableWindow(TRUE);
      }
      else {
         clearEventData();

         CButton *pbtnDelEvent = (CButton*)GetDlgItem(BTN_DELEVENT);
         pbtnDelEvent->EnableWindow(FALSE);
      }
   }
}

void CActionEditorDlg::OnBnClickedCancelseleventlist()
{
   CListBox *pEventList = (CListBox*)GetDlgItem(LST_EVENTLIST);
   m_iEventListIdx = -1;
   pEventList->SetCurSel(m_iEventListIdx);

   //---�M��
   clearEventData();

   CButton *pbtnDelEvent = (CButton*)GetDlgItem(BTN_DELEVENT);
   pbtnDelEvent->EnableWindow(FALSE);
}

void CActionEditorDlg::OnBnClickedDelevent()
{
   if(m_iActionListIdx > -1) {
      if(m_iEventListIdx > -1) {
         CAction *pAction = m_pActionSystem->m_pvtActionSet->at(m_iActionListIdx);
         CActionEventHandler *pActionEventHandler = pAction->m_pvtEventHandlerSet->at(m_iEventListIdx);

         std::vector<CActionEventHandler *>::iterator it = pAction->m_pvtEventHandlerSet->begin();
         while(it != pAction->m_pvtEventHandlerSet->end()) {
            if((*it) == pActionEventHandler) {
               pAction->m_pvtEventHandlerSet->erase(it);
               break;
            }

            it++;
         }

         if(m_iEventListIdx >= (int)pAction->m_pvtEventHandlerSet->size())
            m_iEventListIdx--;

         updateEventList();
         OnLbnSelchangeEventlist();
      }
   }
}

void CActionEditorDlg::OnBnClickedSave()
{
   TCHAR szFilters[]= "ActionSystem Files (*.acs)|*.acs||";
   CFileDialog fileDlg(FALSE, "acs", "*.acs", OFN_HIDEREADONLY, szFilters);
   if(fileDlg.DoModal() == IDOK) {
      CString fullPathFileName = fileDlg.GetPathName();
      m_pActionSystem->write(fullPathFileName.GetBuffer(0));

      fullPathFileName = CString("�ɦW�G") + fullPathFileName;
      SetDlgItemText(TXT_FILENAME, fullPathFileName);
   }
}

void CActionEditorDlg::OnBnClickedLoad()
{
   TCHAR szFilters[]= "ActionSystem Files (*.acs)|*.acs||";
   CFileDialog fileDlg(TRUE, "acs", "*.acs", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
   if(fileDlg.DoModal() == IDOK) {
      CString fullPathFileName = fileDlg.GetPathName();
      m_pActionSystem->read(fullPathFileName.GetBuffer(0));

      fullPathFileName = CString("�ɦW�G") + fullPathFileName;
      SetDlgItemText(TXT_FILENAME, fullPathFileName);

      updateActionList();
   }
}
