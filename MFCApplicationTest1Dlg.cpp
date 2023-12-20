
// MFCApplicationTest1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplicationTest1.h"
#include "MFCApplicationTest1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HHOOK g_hHook = NULL;  // 전역 키 후킹 핸들

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN))
	{
		KBDLLHOOKSTRUCT* pKbStruct = (KBDLLHOOKSTRUCT*)lParam;
		if (pKbStruct->vkCode == VK_F7)
		{
			AfxGetMainWnd()->PostMessage(WM_USER + 1, 0, 0);  // F7 키 감지
		}
		else if (pKbStruct->vkCode == VK_F8)
		{
			AfxGetMainWnd()->PostMessage(WM_USER + 2, 0, 0);  // F8 키 감지
		}
	}

	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplicationTest1Dlg 대화 상자



CMFCApplicationTest1Dlg::CMFCApplicationTest1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATIONTEST1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationTest1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_POWER, m_power_chk);
}

BEGIN_MESSAGE_MAP(CMFCApplicationTest1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(WM_USER + 1, OnUserF7)
	ON_MESSAGE(WM_USER + 2, OnUserF8)
	ON_EN_UPDATE(IDC_EDIT_COUNT, &CMFCApplicationTest1Dlg::OnEnUpdateEditCount)
ON_WM_TIMER()
ON_WM_DESTROY()
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCApplicationTest1Dlg 메시지 처리기

BOOL CMFCApplicationTest1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	/********************************
	***** 프로그램 실행 시 발생 *****
	*********************************/
	g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, AfxGetInstanceHandle(), 0);
	CheckRadioButton(IDC_RADIO_LC, IDC_RADIO_RC, IDC_RADIO_LC);





	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplicationTest1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplicationTest1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplicationTest1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


afx_msg LRESULT CMFCApplicationTest1Dlg::OnUserF7(WPARAM wParam, LPARAM lParam)
{
	SetupClickTimer();
	return 0;
}

afx_msg LRESULT CMFCApplicationTest1Dlg::OnUserF8(WPARAM wParam, LPARAM lParam)
{
	CleanupClickTimer();
	return 0;
}


/****************************************
 ***** 마우스 클릭 횟수 타이머 설정 *****
 ****************************************/
void CMFCApplicationTest1Dlg::SetupClickTimer()
{
	CString strCount;
	GetDlgItemText(IDC_EDIT_COUNT, strCount);

	int timerInterval = _ttoi(strCount);

	if (timerInterval >= 1)
	{
		// 타이머 이벤트 주기 설정
		m_timer_click = SetTimer(1, timerInterval, NULL);
		GetDlgItem(IDC_STATIC_POWER)->SetWindowText(_T("ON"));
	}
	else
		MessageBox(_T("1이상의 정수를 입력해야 실행됩니다"), _T("MFC오토마우스"));
}


/****************************************
 ***** 마우스 클릭 횟수 타이머 해제 *****
 ****************************************/
void CMFCApplicationTest1Dlg::CleanupClickTimer()
{
	KillTimer(m_timer_click);

	clickcount = 0;
	CString clickcountStr;
	clickcountStr.Format(_T("%d"), clickcount);
	GetDlgItem(IDC_STATIC_CHECK)->SetWindowText(clickcountStr);
	GetDlgItem(IDC_STATIC_POWER)->SetWindowText(_T("OFF"));
	m_timer_click = 0;
	m_power_chk.Invalidate();
}


/****************************************
 ***** 마우스 왼쪽 오른쪽 선택 클릭 *****
 ****************************************/
void CMFCApplicationTest1Dlg::LMouseClicked()
{
	clickcount++;

	CString clickcountStr;
	clickcountStr.Format(_T("%d"), clickcount);
	GetDlgItem(IDC_STATIC_CHECK)->SetWindowText(clickcountStr);

	if (IsDlgButtonChecked(IDC_RADIO_LC))
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}

	else if (IsDlgButtonChecked(IDC_RADIO_RC))
	{
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	}
}


/******************************************************************************
 ***** 다이얼로그 내에서 마우스 클릭 이벤트(전역으로 써야해서 사용 안 함) *****
 ******************************************************************************/
BOOL CMFCApplicationTest1Dlg::PreTranslateMessage(MSG* pMsg)
{
	//// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//if (pMsg->message == WM_KEYDOWN)
	//{
	//	if (pMsg->wParam == VK_F7)
	//		SetupClickTimer();
	//	else if (pMsg->wParam == VK_F8)
	//		CleanupClickTimer();
	//}
	return CDialogEx::PreTranslateMessage(pMsg);
}


/****************************
 ***** 타이머 발동 함수 *****
 ****************************/
void CMFCApplicationTest1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == m_timer_click)
	{
		LMouseClicked();
	}

	CDialogEx::OnTimer(nIDEvent);
}


/**********************
 *****  해제 함수 *****
 **********************/
void CMFCApplicationTest1Dlg::OnDestroy()
{
	UnhookWindowsHookEx(g_hHook);


	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


/****************************************
 ***** 속도 입력 정수 아니면 삭제됨 *****
 ****************************************/
void CMFCApplicationTest1Dlg::OnEnUpdateEditCount()
{
	// IDC_EDIT_COUNT의 값을 읽어옴
	CString strCount;
	GetDlgItemText(IDC_EDIT_COUNT, strCount);

	// 입력된 문자열이 숫자가 아니면 삭제
	for (int i = 0; i < strCount.GetLength(); ++i)
	{
		if (!isdigit(strCount[i]))
		{
			strCount.Delete(i);
			SetDlgItemText(IDC_EDIT_COUNT, strCount);
			break;
		}
	}
}


HBRUSH CMFCApplicationTest1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	if (nCtlColor == CTLCOLOR_STATIC && pWnd->GetDlgCtrlID() == IDC_STATIC_POWER)
	{
		if (m_timer_click != 0)
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		else
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
	}

	return hbr;
}
