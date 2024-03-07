// WTLStudy.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <atlbase.h>

#include <atlapp.h>

#include <atlwin.h>

#include <atlframe.h>
#include <atlmisc.h>
#include <atlcrack.h>
#include "resource.h"


CComModule gModule;

typedef CWinTraits<WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CAPTION, WS_EX_APPWINDOW> EdyTraits;

class CAboutDlg :public CDialogImpl<CAboutDlg, CWindow> {
public:
    enum {
        IDD = IDD_ABOUT
    };
    
    BEGIN_MSG_MAP(CAboutDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)
        COMMAND_ID_HANDLER(IDOK, OnOk)
        COMMAND_ID_HANDLER(IDCANCEL, OnOk)
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        CenterWindow();
        return TRUE;
    }
    LRESULT OnClose(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        EndDialog(IDOK);
        return 0;
    }
    LRESULT OnOk(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled) {
        EndDialog(wID);
        return 0;
    }
};


template<class T, COLORREF clr>
class CPaintBackground :public CMessageMap {
public:
    CPaintBackground() {
        m_br = CreateSolidBrush(clr);
    }
    ~CPaintBackground() {
        if (m_br != NULL) {
            DeleteObject(m_br);
            m_br = NULL;
        }
    }

    BEGIN_MSG_MAP(CPaintBackground)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
    END_MSG_MAP()
    LRESULT OnEraseBkgnd(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        T* p = static_cast<T*>(this);
        HDC dc = (HDC)wParam;
        RECT rc;
        p->GetClientRect(&rc);
        FillRect(dc, &rc, m_br);
        return TRUE;
    }
protected:
    HBRUSH m_br;
};

#define BACKGNDCLR RGB(255, 0, 0)
class MyWindow :
    public CWindowImpl<MyWindow, CWindow, EdyTraits>, 
    public CPaintBackground<MyWindow, BACKGNDCLR> {
public:
    DECLARE_WND_CLASS(_T("Edy Window Class"));
    typedef CPaintBackground<MyWindow, BACKGNDCLR> CPaintBkgndBase;
    BEGIN_MSG_MAP(MyWindow)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)     
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        COMMAND_ID_HANDLER(ID_HELLO_WORLD, OnAbout)
        CHAIN_MSG_MAP(CPaintBkgndBase)
    END_MSG_MAP()

    LRESULT OnCreate(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        HMENU hMenu = LoadMenu(gModule.GetResourceInstance(), MAKEINTRESOURCE(IDR_ABOUT));
        SetMenu(hMenu);
        return 0;
    }

    LRESULT OnClose(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        DestroyWindow();
        return 0;
    }
    LRESULT OnDestroy(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
        PostQuitMessage(0);
        return 0;
    }

    LRESULT OnAbout(UINT wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled) {
        OutputDebugString(_T("OnAbout called\r\n"));
        CAboutDlg dlg;
        dlg.DoModal();
        return 0;
    }
};

template<class T>
class Edy {
public:
    void show() {
        T* p = static_cast<T*>(this);
        p->Name();
    }
protected:
    void Name() {
        std::cout << "Edy" << std::endl;
    }
};

class Sub :public Edy<Sub> {
public:
    void Name() {
        std::cout << "Sub" << std::endl;
    }
};

class Sub2 :public Edy<Sub2> {
};

class CEDYWin : public CFrameWindowImpl<CEDYWin> {
public:
    DECLARE_FRAME_WND_CLASS(_T("Edy WTL Window"), IDR_MAINFRAME);
    BEGIN_MSG_MAP_EX(CEDYWin)
        MSG_WM_CREATE(OnCreate)
        CHAIN_MSG_MAP(CFrameWindowImpl<CEDYWin>)
    END_MSG_MAP();
    LRESULT OnCreate(LPCREATESTRUCT lpcs) {
        // TODO
        SetMsgHandled(false);
        return 0;
    }
};

//int main()
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    Sub sub;
    Sub2 sub2;
    sub.show();
    sub2.show();
    HRESULT hRes = gModule.Init(NULL, hInstance);
    if (hRes != 0) {
        std::cout << hRes << std::endl;
    }
    //MyWindow win;
    //HWND hWnd = win.Create(NULL, CWindow::rcDefault, _T("edy atl window"));

    CEDYWin win;
    HWND hWnd = win.CreateEx();
    if (hWnd == NULL) {
        std::cout << "create window failed\r\n";
    }
    win.ShowWindow(nCmdShow);
    win.UpdateWindow();
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    gModule.Term();
    return 0;
}