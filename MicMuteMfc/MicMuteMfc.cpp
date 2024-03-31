﻿
// MicMuteMfc.cpp : アプリケーションのクラス動作を定義します。
//

#include "pch.h"
#include "framework.h"
#include "MicMuteMfc.h"
#include "MicMuteMfcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMicMuteMfcApp

BEGIN_MESSAGE_MAP(CMicMuteMfcApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMicMuteMfcApp の構築

CMicMuteMfcApp::CMicMuteMfcApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CMicMuteMfcApp オブジェクト

CMicMuteMfcApp theApp;


// CMicMuteMfcApp の初期化

BOOL CMicMuteMfcApp::InitInstance()
{
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();



	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));
  {
    CMicMuteMfcDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
      // TODO: ダイアログが <OK> で消された時のコードを
      //  記述してください。
    }
    else if (nResponse == IDCANCEL)
    {
      // TODO: ダイアログが <キャンセル> で消された時のコードを
      //  記述してください。
    }
    else if (nResponse == -1)
    {
      TRACE(traceAppMsg, 0, "警告: ダイアログの作成に失敗しました。アプリケーションは予期せずに終了します。\n");
    }
		m_pMainWnd = nullptr;
  }


#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	//  アプリケーションを終了するために FALSE を返してください。
	CoUninitialize();
	return FALSE;
}

