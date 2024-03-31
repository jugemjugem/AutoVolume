
// MicMuteMfcDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MicMuteMfc.h"
#include "MicMuteMfcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMicMuteMfcDlg ダイアログ



CMicMuteMfcDlg::CMicMuteMfcDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MICMUTEMFC_DIALOG, pParent)
	, m_bAudioMute(FALSE)
	, m_bMicMute(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMicMuteMfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_AUDIO_MUTE_CHECK, m_bAudioMute);
	DDX_Check(pDX, IDC_MIC_MUTE_CHECK, m_bMicMute);
}

BEGIN_MESSAGE_MAP(CMicMuteMfcDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_AUDIO_MUTE_CHECK, &CMicMuteMfcDlg::OnAudioMuteCheckClicked)
	ON_BN_CLICKED(IDC_MIC_MUTE_CHECK, &CMicMuteMfcDlg::OnBnClickedMicMuteCheck)
END_MESSAGE_MAP()


// CMicMuteMfcDlg メッセージ ハンドラー

BOOL CMicMuteMfcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	
	// ---------------------------
	HRESULT hr;
	hr = pEnumerator.CoCreateInstance(
		__uuidof(MMDeviceEnumerator),
		nullptr,
		CLSCTX_INPROC_SERVER
	);
	if (FAILED(hr)) {
		this->EndDialog(hr);
		return TRUE;
	}

	CComPtr<IMMDevice> pDefaultMic;
	CComPtr<IMMDevice> pDefaultAudio;
	
	//デフォルトデバイスを取得
	//ToDo：デフォルト以外も選択できるようにする(Zoomで既定以外のデバイス選択に対応)
	//ToDo：TARGET_ROLE(eConsole,eCommunication,eMultimedia)選択に対応
	hr = pEnumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &pDefaultMic);
	if (FAILED(hr)) {
		pDefaultMic.Release();
	}
	hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDefaultAudio);
	if (FAILED(hr)) {
		pDefaultAudio.Release();
	}
	if (pDefaultMic) {
		hr = pDefaultMic->Activate(
			__uuidof(IAudioEndpointVolume),
			CLSCTX_ALL,
			NULL,
			(void**)&m_pEndPointMic);
	}
	if (pDefaultAudio) {
		hr = pDefaultAudio->Activate(
			__uuidof(IAudioEndpointVolume),
			CLSCTX_ALL,
			NULL,
			(void**)&m_pEndPointAudio);
	}
	if (m_pEndPointAudio) {
		hr = m_pEndPointAudio->GetMute(&m_bAudioMute);
	}
	if (m_pEndPointMic) {
		hr = m_pEndPointMic->GetMute(&m_bMicMute);
	}

	UpdateData(FALSE);

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CMicMuteMfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMicMuteMfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMicMuteMfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMicMuteMfcDlg::OnAudioMuteCheckClicked()
{
	if (m_pEndPointAudio) {
		m_bAudioMute = !m_bAudioMute;
		m_pEndPointAudio->SetMute(m_bAudioMute, &GUID_NULL);
	}
	UpdateData(FALSE);
}


void CMicMuteMfcDlg::OnBnClickedMicMuteCheck()
{
	if (m_pEndPointMic) {
		m_bMicMute = !m_bMicMute;
		m_pEndPointMic->SetMute(m_bMicMute, &GUID_NULL);
	}
	UpdateData(FALSE);
}
