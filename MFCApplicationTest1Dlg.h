
// MFCApplicationTest1Dlg.h: 헤더 파일
//
#include <iostream>
#include <windows.h>
#include <wingdi.h>
#pragma once


// CMFCApplicationTest1Dlg 대화 상자
class CMFCApplicationTest1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplicationTest1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATIONTEST1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEnUpdateEditCount();
	DECLARE_MESSAGE_MAP()

public:
	void LMouseClicked();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetupClickTimer();
	void CleanupClickTimer();
	afx_msg LRESULT OnUserF7(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserF8(WPARAM wParam, LPARAM lParam);

private:
	int clickcount = 0;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	UINT_PTR m_timer_click;
	afx_msg void OnDestroy();
	CStatic m_power_chk;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
