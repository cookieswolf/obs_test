
// OBSTestDlg.h : 头文件
//

#pragma once

#include "obs.hpp"
#include "afxwin.h"

// COBSTestDlg 对话框
class COBSTestDlg : public CDialogEx
{
// 构造
public:
	COBSTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_OBSTEST_DIALOG };

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

private:
	bool ResetAudio();
	bool ResetVideo();
	bool ResetOutputs();

	bool CreateWindowSource();
	bool CreateDisplayContext();

	static void DrawMain(void* data, uint32_t cx, uint32_t cy);

private:
	OBSEncoder h264Recording;
	OBSEncoder aacRecording;
	OBSOutput fileOutput;
	OBSSource windowSource;
	OBSDisplay windowsDisplay;
	CStatic m_StaticDisplay;
	CComboBox m_ComboWindow;
};
