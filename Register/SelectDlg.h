#pragma once
#include "afxwin.h"


// CSelectDlg �Ի���

class CSelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectDlg)

public:
	CSelectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelectDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
//	int m_Radio;
	CButton m_OK;
	CButton m_Cancel;
	int m_Radio;
	afx_msg void OnOk();
};
