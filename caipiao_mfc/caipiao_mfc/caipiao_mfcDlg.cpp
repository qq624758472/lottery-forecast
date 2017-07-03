
// caipiao_mfcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "caipiao_mfc.h"
#include "caipiao_mfcDlg.h"
#include "windows.h"
#include "afxdialogex.h"
#include <iostream>
#include "locale.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ccaipiao_mfcDlg 对话框




Ccaipiao_mfcDlg::Ccaipiao_mfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ccaipiao_mfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ccaipiao_mfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_programLangList);
}

BEGIN_MESSAGE_MAP(Ccaipiao_mfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// Ccaipiao_mfcDlg 消息处理程序

BOOL Ccaipiao_mfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Sleep(1000);
	CString str;
	//FILE* pFile = fopen("xc.txt", "r");
	CStdioFile myFile, File;

	//char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));//unicode 乱码问题
	//setlocale(LC_CTYPE, "chs");// 设定

	if (myFile.Open(_T("xc.txt"), CFile::modeRead))
	{
		//读取
		myFile.ReadString(str);
		myFile.Close();
	}
	else
	{
		MessageBox(_T("Open txt Error"), _T("ERROR"), MB_OK);
	}
	//setlocale(LC_CTYPE, old_locale);
	//free(old_locale);// 还原

	//列表框代码
	CRect rect;
	// 获取编程语言列表视图控件的位置和大小   
	m_programLangList.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格   
	m_programLangList.SetExtendedStyle(m_programLangList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加三列   
	m_programLangList.InsertColumn(0, _T("期号"), LVCFMT_CENTER, rect.Width() / 3, 0);//Column：列
	m_programLangList.InsertColumn(1, _T("开奖"), LVCFMT_CENTER, rect.Width() / 3, 1);
	m_programLangList.InsertColumn(2, _T("预测"), LVCFMT_CENTER, rect.Width() / 3, 2);
	m_programLangList.InsertColumn(3, _T("结果"), LVCFMT_CENTER, rect.Width() / 3, 3);

	TCHAR *p = str.GetBuffer();
	str.ReleaseBuffer();
	//----------新结构------
	typedef struct data
	{
		int one;
		int tow;
		int three;
		int add;
	}data_3;
	typedef struct lottery_profile
	{
		CString			number;
		data_3			result;
		int				forecast[2]; //预测结果。 表示单双和大小。
		bool			iftrue;      //预测是否正确。
		lottery_profile * next;
	}profile_versin;
	//----------------------

	profile_versin *view_list = new profile_versin;//头结点。 
	int i = 0; //控制显示
	int numberNum = 0; //数字的个数。 
	char numberBuffer[6] = {0};  //用来储存指针走过的数字。
	memset(numberBuffer, -1, 6);
	int j = 0;  //numberBuffer的索引。
	int plus_num = 0;

	while (p != NULL)
	{
		if ((*p < 48) || (*p > 57) || (*p != ' ') || (*p != '+') || (*p != '='))  //判断所指向的数据不是数字的话，初始化缓冲区数组
		{
			memset(numberBuffer, -1, 6);
			p++;
			numberNum = 0;
			j = 0;
			continue;
		}

		if (numberNum >= 6)
		{
			view_list->number = numberBuffer;
			numberNum = 0;
			p++;
			j = 0;
			continue;
		}

		if (*p == '+')
		{
			plus_num++;
			if (plus_num == 2)
			{

			}
		}
		if ((*p >= 48) && (*p <= 57))
		{
			numberNum++;
			numberBuffer[j] = *p;
			j++;
			p++;
			if (j > 6)
			{
				j = 0;
			}
			continue;
		}

		// 在列表视图控件中插入列表项，并设置列表子项文本   
		m_programLangList.InsertItem(0, _T("Java"));
		m_programLangList.SetItemText(0, 1, _T("1"));
		m_programLangList.SetItemText(0, 2, _T("99"));

		m_programLangList.InsertItem(1, _T("C"));
		m_programLangList.SetItemText(1, 1, _T("2"));
		m_programLangList.SetItemText(1, 2, _T("98"));

		m_programLangList.InsertItem(2, _T("C#"));
		m_programLangList.SetItemText(2, 1, _T("3"));
		m_programLangList.SetItemText(2, 2, _T("97"));

		m_programLangList.InsertItem(3, _T("C++"));
		m_programLangList.SetItemText(3, 1, _T("4"));
		m_programLangList.SetItemText(3, 2, _T("96"));

		i++;
		p++;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Ccaipiao_mfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ccaipiao_mfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Ccaipiao_mfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

