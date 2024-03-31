
// MicMuteMfcDlg.h : ヘッダー ファイル
//

#pragma once


// CMicMuteMfcDlg ダイアログ
class CMicMuteMfcDlg : public CDialog
{
// コンストラクション
public:
	CMicMuteMfcDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MICMUTEMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート
	
	CComPtr<IMMDeviceEnumerator> pEnumerator;

	CComPtr<IAudioEndpointVolume> m_pEndPointMic;
	CComPtr<IAudioEndpointVolume> m_pEndPointAudio;

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Audio Mute state.
	BOOL m_bAudioMute;
	// Mic Mute state.
	BOOL m_bMicMute;
	afx_msg void OnAudioMuteCheckClicked();
	afx_msg void OnBnClickedMicMuteCheck();
};
