
// generateRegCodeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "generateRegCode.h"
#include "generateRegCodeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CgenerateRegCodeDlg �Ի���



CgenerateRegCodeDlg::CgenerateRegCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GENERATEREGCODE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgenerateRegCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgenerateRegCodeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CgenerateRegCodeDlg::OnOk)
END_MESSAGE_MAP()


// CgenerateRegCodeDlg ��Ϣ�������

BOOL CgenerateRegCodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CgenerateRegCodeDlg::OnPaint()
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
HCURSOR CgenerateRegCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CgenerateRegCodeDlg::GetCPUNum()
{
	//��ȡCPU���к�
	unsigned long s1, s2;

	CString CPUID1, CPUID2;
	__asm {
		mov eax, 01h // ���빦�ܺ�
		xor edx, edx // ��ս��,ִ��cpuidָ��֮��.��������edx,eax��
		cpuid        // ִ��ָ��,��ȡ���
		mov s1, edx  // ��ȡ���
		mov s2, eax  // ��ȡ���
	}

	CPUID1.Format("%08X%08X", s1, s2);
	__asm {
		mov eax, 03h // ���빦�ܺ�
		xor ecx, ecx // ��ս��,ִ��cpuidָ��֮��.��������edx,eax��
		xor edx, edx // ͬ��
		cpuid        // ִ��ָ��
		mov s1, edx  // ��ȡ���
		mov s2, ecx  // ��ȡ���
	}
	CPUID2.Format("%08X%08X", s1, s2);

	// ƴ�ӽ��
	CString CpuID = CPUID1 + CPUID2;
	return CpuID.Mid(5, 3); // ��ƴ�ӵĽ����ȡ��һ��,��Ϊ���ؽ��

}

CString CgenerateRegCodeDlg::GetDiskNum()
{
	DWORD ser;
	char namebuf[128];
	char filebuf[128];
	//��ȡC�̵����к�
	::GetVolumeInformation("c:\\",   // ����ȡ��Ϣ�Ĵ��̵ĸ�·��
		namebuf,  // ����װ�ش������Ļ�����
		128,      // ���滺�����Ĵ�С
		&ser,     // ����װ�ش������кŵı���
		0,        // ����װ���ļ���ÿһ���ֵĳ���
		0,        // ��־λ
		filebuf,  // ����װ���ļ�ϵͳ������
		128       // ���滺�����Ĵ�С
	);
	CString DiskID;
	DiskID.Format("%08X", ser); 		// ��ʽ�����ַ���
	return DiskID.Mid(3, 3); 			// ���ص�3����ʼ��3���ַ�
}

CString CgenerateRegCodeDlg::GetMacAddress()
{
	NCB nInfo;
	memset(&nInfo, 0, sizeof(NCB)); 					// ��������
	nInfo.ncb_command = NCBRESET; 					// ��������
	nInfo.ncb_lana_num = 0;
	Netbios(&nInfo); 									// ִ��

	ADAPTER_INFO AdaINfo; //�洢������Ϣ
	memset(&nInfo, 0, sizeof(NCB)); 					//��ʼ��NetBIOS
	nInfo.ncb_command = NCBASTAT;
	nInfo.ncb_lana_num = 0;
	nInfo.ncb_buffer = (unsigned char *)&AdaINfo;
	nInfo.ncb_length = sizeof(ADAPTER_INFO);
	strncpy((char *)nInfo.ncb_callname, "*", NCBNAMSZ);
	Netbios(&nInfo);

	CString MacAddr; 									// ��ʽ�����ַ���
	MacAddr.Format("%02X%02X%02X%02X%02X%02X",
		AdaINfo.nStatus.adapter_address[0],
		AdaINfo.nStatus.adapter_address[1],
		AdaINfo.nStatus.adapter_address[2],
		AdaINfo.nStatus.adapter_address[3],
		AdaINfo.nStatus.adapter_address[4],
		AdaINfo.nStatus.adapter_address[5]
	);
	return MacAddr.Mid(4, 4); 						// ����һ���ַ���
}



void CgenerateRegCodeDlg::OnOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString name;
	GetDlgItem(IDC_EDIT1)->GetWindowText(name);
	if (name.IsEmpty()) {
		MessageBox("�û�������Ϊ�գ�");
		return;
	}
	//����һ����Կ����
	CString code[16] = {
		"ah", "tm", "ib", "nw", "rt", "vx", "zc", "gf",
		"pn", "xq", "fc", "oj", "wm", "eq", "np", "qw"
	};
	CString reg, stred;
	int num;
	stred = GetCPUNum() + GetDiskNum() + GetMacAddress();//ƴ��CPU,C�̺�����
	stred.MakeLower();
	//����ʮ���������ִ���Կ������ѡ���ַ���
	for (int i = 0; i < 10; i++) {
		char p = stred.GetAt(i);				// �൱�� ȡ��i���ַ�
		if (p >= 'a' && p <= 'f') {			// ����ַ�Ϊ abcdef
			num = p - 'a' + 10;				// - ��a�� + 10 ת��������ֵ
		}
		else {
			num = p - '0';		// ��������֣��� �C ��0�� ת��Ϊ������
		}
		CString tmp = code[num];			// ȡ��Կ�����е�һ��Ԫ��	
		reg += tmp;					// ׷�ӵ��ַ������棬����γ�ע����
	}

	// ���ת���ɴ�д
	reg.MakeUpper();
	// ���ý����ϱ༭�������
	GetDlgItem(IDC_EDIT2)->SetWindowText(reg.Mid(0, 5));
	GetDlgItem(IDC_EDIT3)->SetWindowText(reg.Mid(5, 5));
	GetDlgItem(IDC_EDIT4)->SetWindowText(reg.Mid(10, 5));
	GetDlgItem(IDC_EDIT5)->SetWindowText(reg.Mid(15, 5));
	// �ѽ��д��ע���
	/*
	HKEY key;
	CString skey = "Software\\mingrisoft"; //���û��������½�
	RegOpenKey(HKEY_CURRENT_USER, skey, &key);
	CString value = name + "-" + reg;
	int iret = RegSetValueEx(key, "regnum", 0, REG_SZ, (BYTE *)value.GetBuffer(0),
		value.GetLength());

	//ֻ��д��REG_SZ������
	if (iret == ERROR_SUCCESS) {
		MessageBox("�����ɹ�", "��ʾ", MB_OK);
	}
	else {
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf,
			0,
			NULL
		);

		// Process any inserts in lpMsgBuf. 
		// ... 

		// Display the string. 
		MessageBox((LPCTSTR)lpMsgBuf);

		// Free the buffer. 
		LocalFree(lpMsgBuf);
	}
	RegSetValueEx(key, "isreg", 0, REG_SZ, (BYTE *)"0", 1);
	*/
	// ��ע���,д��"sn.txt"�ļ�
	CFile file;
	char path[256];
	::GetCurrentDirectory(256, path);
	CString filename = path;
	filename += "\\sn.txt";
	file.Open(filename, CFile::modeCreate | CFile::modeWrite); // ʹ�ö�дģʽ���ļ�
	CString text = name + "\r\n" + reg.Mid(0, 5) + "-" + reg.Mid(5, 5) +
		"-" + reg.Mid(10, 5) + "-" + reg.Mid(15, 5)+"\r\n"+"30";
	// д��
	file.Write(text, text.GetLength());
	// �ر��ļ�
	file.Close();
}
