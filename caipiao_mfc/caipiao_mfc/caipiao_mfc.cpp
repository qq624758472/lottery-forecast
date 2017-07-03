
// caipiao_mfc.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "caipiao_mfc.h"
#include "caipiao_mfcDlg.h"
#include <stdio.h>  
#include <iostream>  
#include <Windows.h>    
#include "curl.h"    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#pragma comment(lib, "libcurl.lib")     
#pragma comment(lib, "wldap32.lib")     
#pragma comment(lib, "ws2_32.lib")     
#pragma comment(lib, "winmm.lib")     

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcaipiaoApp

BEGIN_MESSAGE_MAP(CcaipiaoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CcaipiaoApp 构造

CcaipiaoApp::CcaipiaoApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CcaipiaoApp 对象

CcaipiaoApp theApp;


size_t write_data(char *buffer,size_t size, size_t nitems,void *outstream)  
{  
	int written = fwrite(buffer, size, nitems, (FILE*)outstream);  
	return written;  
}  

// CcaipiaoApp 初始化

BOOL CcaipiaoApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//趴下来网上的数据。
	// 将note.xml写入myxml.xml文件里  
	CURL *pCurl;    
	FILE* pFile = fopen( "..\\Debug\\myxml.xml", "wb" );  
	pCurl = curl_easy_init();    
	curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, (void*)pFile);  
	curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, write_data);  
	curl_easy_setopt(pCurl, CURLOPT_URL, "http://www.pc28yc.com/pre.php/");  
	curl_easy_perform(pCurl);  
	fclose(pFile);  
	curl_easy_cleanup( pCurl );  

	//网页已经被down下来了。
	////开始分析里边的数据
	/*if( system( "xcyk.exe") == -1 )
	{
		perror( "execl error " );
		MessageBox(NULL,_T("xcyk.exe Error"),_T("ERROR"),MB_ERR_INVALID_CHARS);
		exit(1);
	}*/
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = _T("xcyk.exe");
	ShExecInfo.lpParameters = _T("");
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	Ccaipiao_mfcDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

