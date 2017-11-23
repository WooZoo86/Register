
// RegisterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Register.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include "SelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRegisterDlg �Ի���



CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REGISTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CRegisterDlg ��Ϣ�������

BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// ��ȡע���
	/*
	HKEY key;
	char data[2];
	DWORD size = 2;
	DWORD type = REG_SZ;
	CString skey = "Software\\mingrisoft";
	
	long iret = RegOpenKeyEx(HKEY_CURRENT_USER, skey,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &key);*/
	// �򿪳ɹ�
	/*
	if (iret == 0) {
		CString value;
		// ��ȡ��ֵ
		iret = RegQueryValueEx(key, "isreg", 0, &type, (BYTE *)data, &size);
		if (iret == 0) {
			if (data[0] == '0') {
				// ��ʾѡ��Ի��� 
				CSelectDlg dlg;
				if (dlg.DoModal() != IDOK) {
					// �˳�
					OnCancel();
				}
				// ����־λ
				if (!Flag) {
					// �˳�
					OnCancel();
				}
			}
			else {
				return TRUE;
			}
		}
		else {
			RegSetValueEx(key, "isreg", 0, REG_SZ, (BYTE *)"0", 1);
			OnCancel();
		}
	}*/
	fstream file;
	string filename = "//reg.txt";
	file.open(filename,ios::in);
	if (!file)
	{
		CSelectDlg dlg;
		if (dlg.DoModal() != IDOK) {
			// �˳�
			OnCancel();
		}
	}
	else
	{
		file.close();
		return TRUE;
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRegisterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRegisterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

