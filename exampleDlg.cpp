
// exampleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "example.h"
#include "exampleDlg.h"
#include "stdlib.h"
#include <io.h>
#include <iostream>
#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
struct SampleInfo sampleInfo;



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CexampleDlg 对话框




CexampleDlg::CexampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CexampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CexampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRAM_LANG_LIST, m_programLangList);
	DDX_Control(pDX, IDC_PIC1, m_jpgshow);
	DDX_Control(pDX, IDC_PIC2, m_jpgshow1);
	DDX_Control(pDX, IDC_PIC3, m_jpgshow2);
	DDX_Control(pDX, IDC_PIC4, m_jpgshow3);
	DDX_Control(pDX, IDC_PIC5, m_jpgshow4);
	DDX_Control(pDX, IDC_SCORE1, m_score1);
}

BEGIN_MESSAGE_MAP(CexampleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_LONG_SEL_EDIT, &CexampleDlg::OnEnChangeLongSelEdit)
	//ON_NOTIFY(NM_CLICK, IDC_PROGRAM_LANG_LIST, &CexampleDlg::OnNMClickProgramLangList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PROGRAM_LANG_LIST, &CexampleDlg::OnLvnItemchangedProgramLangList)
	ON_BN_CLICKED(IDC_BUTTON1, &CexampleDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CexampleDlg 消息处理程序

CString folderPath="E:\\Project\\20150918";
CString strfind = folderPath + "\\";

BOOL CexampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	GetDlgItem(IDC_EDITWJ)->SetWindowText("0");

	// TODO: 在此添加额外的初始化代码
	CRect rect;   

	// 获取编程语言列表视图控件的位置和大小   
	m_programLangList.GetClientRect(&rect); 
	// 为列表视图控件添加全行选中和栅格风格   
	m_programLangList.SetExtendedStyle(m_programLangList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   

	// 为列表视图控件添加2列   
	m_programLangList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, rect.Width()/2, 0);   
	m_programLangList.InsertColumn(1, _T("文件名"), LVCFMT_CENTER, rect.Width()/2, 1);     

	/*m_programLangList.InsertItem(0, _T("Java"));   
	m_programLangList.SetItemText(0, 1, _T("1"));   
	m_programLangList.SetItemText(0, 2, _T("1"));   
	m_programLangList.InsertItem(1, _T("C"));   
	m_programLangList.SetItemText(1, 1, _T("2"));   
	m_programLangList.SetItemText(1, 2, _T("2"));   
	m_programLangList.InsertItem(2, _T("C#"));   
	m_programLangList.SetItemText(2, 1, _T("3"));   
	m_programLangList.SetItemText(2, 2, _T("6"));   */

	HANDLE hSearch = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA data;

	 //CString m_strScanFolder = "E:\\Project\\20150911";
	 //m_strScanFolder += "\\";
	
	std::string strScanName(strfind);
	strScanName += "*.jpg" ;

	hSearch = ::FindFirstFile(strScanName.c_str(),&data);
	if (hSearch == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	do
	{

		if (data.dwFileAttributes!=FILE_ATTRIBUTE_DIRECTORY
			&&strcmp(data.cFileName,".")
			&&strcmp(data.cFileName,".."))
		{
			//std::string strExtName(data.cFileName);
			///strExtName.erase(strExtName.begin(), strExtName.begin() + strExtName.rfind("."));

			//if (strcmp(strExtName.c_str(),m_strFilterExt.c_str()) == 0)
			//{
			std::string strFullFileName(strfind);
			strFullFileName += data.cFileName;
			m_fileInfoVec.push_back(strFullFileName);
			
			//}
		}

	} while (FindNextFile(hSearch,&data));

	FindClose(hSearch);
	int ImageNum=0;
	char id[1024];
	int j=0;
	for (vector<string>::const_iterator itr = m_fileInfoVec.begin();itr != m_fileInfoVec.end();++itr)
	{
		std::string::size_type stPosB = itr->rfind("\\" );
		std::string::size_type stPosE = itr->rfind("." );

		string strFileID(*itr,stPosB+1,stPosE-stPosB-1);
		//int nFileNameID = atoi(strFileID.c_str());
           

		j++;
		CString ID=itoa(j,id,10);
		m_programLangList.InsertItem(ImageNum, _T(ID));   
		m_programLangList.SetItemText(ImageNum, 1, _T(strFileID.c_str()));
        ImageNum++;

	}
    
	FileOption("F:\\xuexi\\example\\HitResult.txt");
	//system("pause");
	//creader.readfile("F:\xuexi\example\HitResult.txt");
	//creader.findvalue(key);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CexampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CexampleDlg::OnPaint()
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
		CDialog::OnPaint();

		//DrawPic();
		//DrawPic1();
		
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CexampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CexampleDlg::OnEnChangeLongSelEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

////图片编辑框的初始化//////
void CexampleDlg::DrawInit(CStatic& JipShow)
{
	CRect rc;
	JipShow.GetClientRect(&rc);

	CDC *pDC =JipShow.GetDC();
	if (pDC != NULL)
	{
		//COLORREF a=pDC->GetBkColor();
		/*DWORD dwData;
		dwData=::GetSysColor(COLOR_BTNFACE);
		pDC->FillSolidRect(rc1, dwData);*/
		pDC->FillSolidRect(rc, RGB(192,192,192));
		JipShow.ReleaseDC(pDC);
	}
}
////画图函数//////
void CexampleDlg::DrawPic(CString PicName,CStatic& JipShow)
{
	CImage img;
	if (PicName.IsEmpty())
	{
		return;
	}
	

		img.Load(PicName);
		if (!img.IsNull())  
		{
			RECT rc;
			JipShow.GetClientRect(&rc);
			CDC *pDC =JipShow.GetDC();
			if (pDC != NULL)
			{
				JipShow.GetClientRect(&rc);
				img.Draw(pDC->m_hDC,rc);
				JipShow.ReleaseDC(pDC);
			}
		}
	
}

////读结果文件函数////
int CexampleDlg:: FileOption(const char* FilePath)
{  
	FILE* fp = fopen(FilePath, "r");
	if (fp == NULL)
		return 0;

	char line[1024] = {0};
	char q[64] = {0};
	char* p = NULL;
	string srv_name;
	while (fgets(line, sizeof(line), fp))
	{
		char delims[] = "-- (,)\n";  
		char *result = NULL;  
		string strCaptureName;
		result = strtok(line, delims ); 
		if(result == NULL)
			return 0;
		strCaptureName = result;
		int n=1;
		while( result != NULL ) 
		{  
			if(result==NULL)
				break;
			result = strtok( NULL, delims ); 
			if (result==NULL)
			{
				break;
			}
			if(n%2==1)
			{
				sampleInfo.SampleName=result;  
			}
			else
			{
				sampleInfo.SampleScore=result;
				m_sampleInfoVec.push_back(sampleInfo);
			}

			n++;
			 
		} 
		m_sampleInfoMap.insert(map<string,vector<SampleInfo>>::value_type(strCaptureName,m_sampleInfoVec));
	
		vector<SampleInfo>().swap(m_sampleInfoVec);
	}
	fclose(fp);
	return 0;  
} 

void CexampleDlg::OnLvnItemchangedProgramLangList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	CString strLangName;    // 选择抓拍图名称字符串1001.
	string  strLangsamName;
 
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;   
	/*strLangName.Format(_T("Item index: %d,SubItem:%d"), pNMListView->iItem,
		pNMListView->iSubItem);*/

	if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
	{   
		// 获取被选择列表项第一个子项的文本   
		strLangName = m_programLangList.GetItemText(pNMListView->iItem, 1);
		if (!strLangName.IsEmpty())
		{
			strLangsamName = strLangName+".jpg";
			string ImgPath = strfind + strLangName;
			ImgPath += ".jpg";
			
			m_strPic = ImgPath.c_str();
			/*RECT rc;
			m_jpgshow.GetClientRect(&rc);
			m_jpgshow.ClientToScreen(&rc);
			ScreenToClient(&rc);*/
			//InvalidateRect(&rc);
			DrawPic(m_strPic,m_jpgshow);
			RECT rc1;
			RECT rc2;

			m_strSamPic.Empty();
			//DrawPic1();
			//SetDlgItemText(IDC_SCORE1,"");
			int count = 1;
			map<string,vector<SampleInfo>>::const_iterator itr = m_sampleInfoMap.find(strLangsamName);
			SetDlgItemText(IDC_SCORE1,"");
			SetDlgItemText(IDC_SCORE2,"");
			SetDlgItemText(IDC_SCORE3,"");
			SetDlgItemText(IDC_SCORE4,"");
			DrawInit(m_jpgshow1);
			DrawInit(m_jpgshow2);
			DrawInit(m_jpgshow3);
			DrawInit(m_jpgshow4);
			if (itr != m_sampleInfoMap.end())
			{   
				//strSamPic=itr->first;
				for(vector<SampleInfo>::const_iterator itrinfo = (itr->second).begin();itrinfo != (itr->second).end();itrinfo++)
				//while( itrinfo != (itr->second).end())
				//{//m_strSamPic=itr->first;
				{	
					m_strSamPic="E:\\Project\\2015.08.27\\";
					m_strSamPic += itrinfo->SampleName.c_str();
					m_strSamPic += ".jpg";
				    
			        switch(count++)
					{
						case 1:
							SetDlgItemText(IDC_SCORE1,itrinfo->SampleScore.c_str());
							DrawPic(m_strSamPic,m_jpgshow1);
							break;
						case 2:
							SetDlgItemText(IDC_SCORE2,itrinfo->SampleScore.c_str());
							DrawPic(m_strSamPic,m_jpgshow2);
							break;
						case 3:
							SetDlgItemText(IDC_SCORE3,itrinfo->SampleScore.c_str());
							DrawPic(m_strSamPic,m_jpgshow3);
							break;
						case 4:
							SetDlgItemText(IDC_SCORE4,itrinfo->SampleScore.c_str());
							DrawPic(m_strSamPic,m_jpgshow4);
							break;
						default:
							break;

					}

				}
				
			}
		

			SetDlgItemText(IDC_LONG_SEL_EDIT, strLangName);

		}
		
	}  
	*pResult = 0;
}

void CexampleDlg::OnBnClickedButton1()
{
	CString pszText;
	GetDlgItem(IDC_EDITWJ)->GetWindowText(pszText);

	pszText.Format("%d", atoi(pszText)+1);

	GetDlgItem(IDC_EDITWJ)->SetWindowText(pszText);



}
