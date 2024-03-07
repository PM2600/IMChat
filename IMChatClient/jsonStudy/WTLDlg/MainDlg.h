// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
//#include "atlwin.h"
#define ATL_MSG_MAP(msgMapID) \
		break; \
		case msgMapID:

template <LPCTSTR res>
class CEdyButton : public CWindowImpl<CEdyButton<res>, CButton> {
public:
	BEGIN_MSG_MAP_EX(CEdyButton)
		MSG_WM_SETCURSOR(OnSetCursor)
	END_MSG_MAP()

	LRESULT OnSetCursor(HWND hWnd, UINT uHitTest, UINT uMsg) {
		static HCURSOR hcur = LoadCursor(NULL, res);
		if (hcur != NULL) {
			SetCursor(hcur);
			return TRUE;
		}
		else {
			SetMsgHandled(FALSE);
			return FALSE;
		}
	}
};

class CEdyEdit :public CWindowImpl<CEdyEdit, CEdit> {
public:
	BEGIN_MSG_MAP_EX(CEdyEdit)
		MSG_WM_CONTEXTMENU(OnContextMenu)
	END_MSG_MAP()

	void OnContextMenu(HWND, CPoint pt) {
		MessageBox(_T("Menu done"));
	}
};

class CMainDlg : public CDialogImpl<CMainDlg>,
	public CWinDataExchange<CMainDlg>
{
public:
	enum { IDD = IDD_MAINDLG };
	CMainDlg():m_btnOk(this, 1), m_btnCancel(this, 2) {}

	BEGIN_DDX_MAP(CMainDlg)
		DDX_CONTROL(IDC_EDIT2, m_edit2)
	END_DDX_MAP()

	BEGIN_MSG_MAP_EX(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	ATL_MSG_MAP(1)
		MSG_WM_SETCURSOR(OnSetCursorOk)
	ATL_MSG_MAP(2)
		MSG_WM_SETCURSOR(OnSetCursorCancel)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// center the dialog on the screen
		CenterWindow();

		// set icons
		HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
		SetIcon(hIconSmall, FALSE);
		HWND hWnd = GetDlgItem(IDC_LIST1);
		m_list.Attach(hWnd);

		hWnd = GetDlgItem(IDC_EDIT1);
		m_edit.Attach(hWnd);

		m_edit.SetWindowText(_T("edy !!"));
		m_btnOk.SubclassWindow(GetDlgItem(IDOK));
		m_btnCancel.SubclassWindow(GetDlgItem(IDCANCEL));
		m_btnAbout.SubclassWindow(GetDlgItem(ID_APP_ABOUT));
		DoDataExchange(FALSE);
		return TRUE;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add validation code 
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnSetCursorOk(HWND hWnd, UINT uHitTest, UINT uMsg) {
		static HCURSOR hcur = LoadCursor(NULL, IDC_HAND);
		if (hcur != NULL) {
			SetCursor(hcur);
			return TRUE;
		}
		else {
			SetMsgHandled(FALSE);
			return FALSE;
		}
	}

	LRESULT OnSetCursorCancel(HWND hWnd, UINT uHitTest, UINT uMsg) {
		static HCURSOR hcur = LoadCursor(NULL, IDC_NO);
		if (hcur != NULL) {
			SetCursor(hcur);
			return TRUE;
		}
		else {
			SetMsgHandled(FALSE);
			return FALSE;
		}
	}
protected:
	CListViewCtrl m_list;
	CEdit m_edit;
	CContainedWindow m_btnOk;
	CContainedWindow m_btnCancel;
	CEdyButton<IDC_HELP> m_btnAbout;
	CEdyEdit m_edit2;
};
