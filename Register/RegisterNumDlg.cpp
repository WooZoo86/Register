// RegisterNumDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Register.h"
#include "RegisterNumDlg.h"
#include "afxdialogex.h"
#include "SelectDlg.h"

// CRegisterNumDlg �Ի���

IMPLEMENT_DYNAMIC(CRegisterNumDlg, CDialogEx)

CRegisterNumDlg::CRegisterNumDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REGNUM, pParent)
	, m_strRegisterCode(_T(""))
{

}

CRegisterNumDlg::~CRegisterNumDlg()
{
}

void CRegisterNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDX_Text(pDX, IDC_EDIT3, m_strRegisterCode);
	DDX_Control(pDX, IDC_ADVANCE, m_Advance);
	DDX_Control(pDX, IDC_BACKOFF, m_Backoff);
}

void CRegisterNumDlg::OnPaint()
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
	}
	else
	{
		//��Ӵ���Ի��򱳾���ͼ  
		CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);                                 //��ȡ�Ի��򳤿�         
		CDC   dcBmp;                                           //���岢����һ���ڴ��豸����  
		dcBmp.CreateCompatibleDC(&dc);                         //����������DC  
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);                 //������Դ�е�IDB_BITMAP1ͼƬ  
		BITMAP   m_bitmap;                                     //ͼƬ����                  
		bmpBackground.GetBitmap(&m_bitmap);                    //��ͼƬ����λͼ��  
		CBitmap   *pbmpOld = dcBmp.SelectObject(&bmpBackground); //��λͼѡ����ʱ�ڴ��豸����    
																 //���ú�����ʾͼƬ StretchBlt��ʾ��״�ɱ�  
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0,
			m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
	}
}


BEGIN_MESSAGE_MAP(CRegisterNumDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ADVANCE, &CRegisterNumDlg::OnAdvance)
	ON_BN_CLICKED(IDC_BACKOFF, &CRegisterNumDlg::OnBackoff)
END_MESSAGE_MAP()


// CRegisterNumDlg ��Ϣ�������


BOOL CRegisterNumDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ע�ᰴť��ʾͼƬ
	m_Advance.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_ADVANCE)));
	// ���˰�ť��ʾͼƬ
	m_Backoff.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAPOFF)));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CRegisterNumDlg::OnAdvance()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	// �ж��û�����ע�����Ƿ�������
	if (m_Name.IsEmpty() || m_strRegisterCode.IsEmpty()) {
		MessageBox("�û�����ע�������");
		return;
	}
}


void CRegisterNumDlg::OnBackoff()
{
	// ���ø����OnOk()����
	CDialog::OnOK();
	// ��ʾģ̬�Ի���:ѡ������? or ע��
	CSelectDlg dlg;
	dlg.DoModal();
}
