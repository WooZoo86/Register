// SelectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Register.h"
#include "SelectDlg.h"
#include "afxdialogex.h"
#include "RegisterNumDlg.h"

// CSelectDlg �Ի���

IMPLEMENT_DYNAMIC(CSelectDlg, CDialogEx)

CSelectDlg::CSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SELECT, pParent)
	, m_Radio(0)
{

}

CSelectDlg::~CSelectDlg()
{
}

void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_RADIO1, m_Radio);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio);
}

void CSelectDlg::OnPaint()
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

		/******************************************************/
		/** StretchBlt()                                     **/
		/** ����x��yλͼĿ��������Ͻ�x��y������ֵ ����      **/
		/** nWidth��nHeigthλͼĿ����ε��߼���Ⱥ͸߶�      **/
		/** pSrcDC��ʾԴ�豸CDCָ��                          **/
		/** xSrc��ySrc��ʾλͼԴ���ε����Ͻǵ�x��y�߼�����ֵ **/
		/** dwRop��ʾ��ʾλͼ�Ĺ�դ������ʽ                  **/
		/** SRCCOPY����ֱ�ӽ�λͼ���Ƶ�Ŀ�껷����            **/
		/******************************************************/
	}
}



BEGIN_MESSAGE_MAP(CSelectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CSelectDlg::OnOk)
END_MESSAGE_MAP()


// CSelectDlg ��Ϣ�������


BOOL CSelectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ��ȡע���
	HKEY key;
	char data[4];
	DWORD size = 4;
	DWORD type = REG_SZ;
	string filename = "F://c++//generateRegCode//generateRegCode//sn.txt";
	ifstream in(filename);//���ļ���
	int i;
	string str;
	for (i = 0; i< 3; i++)
		getline(in,str, '\n');//��ȡ���ݡ�

	int count = atoi(str.c_str());
	if (count != 0) {
		CString strTime;
		// �ڽ�������ʾ���ô���
		strTime.Format("�㻹����ʹ��%d��",count);
		GetDlgItem(IDC_STATICTIME)->SetWindowText(strTime);
	}
	else {
		// �����ϵĿؼ�����Ϊ������
		GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		// ��ʾ�������������
		GetDlgItem(IDC_STATICTIME)->SetWindowText("���Ѿ������������ñ�����ˣ�");
	}
	/*
	CString skey = "Software\\mingrisoft";
	LSTATUS iret = RegOpenKeyEx(HKEY_CURRENT_USER, skey,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &key);
	if (iret == 0) {
		CString value;
		// ��ȡ���ô���
		iret = RegQueryValueEx(key, "tryout", 0, &type, (BYTE *)data, &size);
		if (iret == 0) {
			if (data != 0) {
				CString strTime;
				// �ڽ�������ʾ���ô���
				strTime.Format("�㻹����ʹ��%s��", data);
				GetDlgItem(IDC_STATICTIME)->SetWindowText(strTime);
			}
			else {
				// �����ϵĿؼ�����Ϊ������
				GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
				// ��ʾ�������������
				GetDlgItem(IDC_STATICTIME)->SetWindowText("���Ѿ������������ñ�����ˣ�");
			}
		}
		else {
			// �������ô���Ϊ30
			RegSetValueEx(key, "tryout", 0, REG_SZ, (BYTE *)"30", 2);
			OnCancel();
		}
	}
	*/
	// ����"ok"��ť��ͼƬ
	m_OK.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAPOK)));
	// ����"cancel"��ť��ͼƬ
	m_Cancel.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAPOFF)));
	m_Radio = 0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CSelectDlg::OnOk()
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	// ѡ����"ע��"
	if (m_Radio == 0) {
		CDialog::OnOK();
		CRegisterNumDlg dlg;
		dlg.DoModal();
	}
	// ѡ����"����"
	else if (m_Radio == 1) {
		// ��ע����� �������ô����ļ�ֵ,׼��д��
		HKEY key;
		CString skey = "Software\\mingrisoft";
		long iret = RegOpenKeyEx(HKEY_CURRENT_USER,
			skey,
			REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS,
			&key);
		if (iret == 0) {
			// �ӽ����ϻ�����ô����������
			CString str;
			GetDlgItem(IDC_STATICTIME)->GetWindowText(str);
			CString num;
			// �����ô���ת��Ϊ��������
			int run = atoi(str.Mid(12, str.GetLength() - 14));
			num.Format("%d", run - 1);
			// д��ע���
			RegSetValueEx(key, "tryout", 0, REG_SZ, (BYTE *)num.GetBuffer(0)
				, num.GetLength());
			// ����ȫ�ֱ�־λ
			//Flag = TRUE;
			CDialog::OnOK();
		}
	}
}
