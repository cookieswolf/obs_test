
// OBSTestDlg.h : ͷ�ļ�
//

#pragma once

#include "obs.hpp"
#include "afxwin.h"

// COBSTestDlg �Ի���
class COBSTestDlg : public CDialogEx
{
// ����
public:
	COBSTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OBSTEST_DIALOG };

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
