
// MicMuteMfc.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMicMuteMfcApp:
// このクラスの実装については、MicMuteMfc.cpp を参照してください
//

class CMicMuteMfcApp : public CWinApp
{
public:
	CMicMuteMfcApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMicMuteMfcApp theApp;
