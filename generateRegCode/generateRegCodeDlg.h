
// generateRegCodeDlg.h : ͷ�ļ�
//

#pragma once
#include "nb30.h"
#pragma comment(lib,"netapi32.lib")

// CgenerateRegCodeDlg �Ի���
class CgenerateRegCodeDlg : public CDialogEx
{
// ����
public:
	CgenerateRegCodeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GENERATEREGCODE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	CString GetCPUNum();//��ȡCPU���кŴӵ�����ַ����3���ַ�
	CString GetDiskNum();//��ȡC�����к��дӵ������ַ��������ַ�
	//������Ϣ�ṹ��
	struct ADAPTER_INFO
	{
		ADAPTER_STATUS nStatus;
		NAME_BUFFER nBuffer;
	};
	CString GetMacAddress();//��ȡ������ַ�ӵ�4���ַ����4���ַ�
public:
	afx_msg void OnOk();
};
