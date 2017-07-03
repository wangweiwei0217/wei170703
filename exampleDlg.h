
// exampleDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include <vector>
#include <map>
#include <string>
#include <WinSock2.h>
#include <Windows.h>
#include "afxwin.h"
#include "IniAnalyzer.h"
using namespace std;

//typedef vector<string> TSFileInfoVec;
struct SampleInfo
{
	string SampleName;
	string SampleScore;
};
// CexampleDlg 对话框
class CexampleDlg : public CDialog
{
// 构造
public:
	CexampleDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXAMPLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_programLangList;
	afx_msg void OnEnChangeLongSelEdit();
	afx_msg void OnLvnItemchangedProgramLangList(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnNMClickProgramLangList(NMHDR *pNMHDR, LRESULT *pResult);
private:
	vector<string> m_fileInfoVec;
	vector<SampleInfo> m_sampleInfoVec;
	map<string,vector<SampleInfo>> m_sampleInfoMap;
private:
	CString m_strPic;
	CString m_strSamPic;
	int FileOption(const char* FilePath);
	//void DrawPic();
	void DrawPic(CString PicName,CStatic& JipShow);
	void DrawInit(CStatic& JipShow);
	void DrawPic1();
public:
	CStatic m_jpgshow;
	CStatic m_jpgshow1;
	CStatic m_jpgshow2;
	CStatic m_jpgshow3;
	CStatic m_jpgshow4;
	CEdit m_score1;
	
	afx_msg void OnBnClickedButton1();
};
