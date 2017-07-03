
// exampleDlg.h : ͷ�ļ�
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
// CexampleDlg �Ի���
class CexampleDlg : public CDialog
{
// ����
public:
	CexampleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXAMPLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
