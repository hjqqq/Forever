// ActionEditorDlg.h : ���Y��
//

#pragma once
#include "CActionSystem.h"

// CActionEditorDlg ��ܤ��
class CActionEditorDlg : public CDialog
{
// �غc
public:
	CActionEditorDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_ACTIONEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩

private:
   void updateActionList();
   void clearActionData();
   void updateEventList();
   void clearEventData();

   CActionSystem *m_pActionSystem;
   int m_iActionListIdx;
   int m_iEventListIdx;

// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedNewaction();
   afx_msg void OnLbnSelchangeActionlist();
   afx_msg void OnBnClickedCancelselactionlist();
   afx_msg void OnBnClickedDelaction();
   afx_msg void OnBnClickedNewevent();
   afx_msg void OnLbnSelchangeEventlist();
   afx_msg void OnBnClickedCancelseleventlist();
   afx_msg void OnBnClickedDelevent();
   afx_msg void OnBnClickedSave();
   afx_msg void OnBnClickedLoad();
};
