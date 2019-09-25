

#pragma once

#include "resource.h"
#include "CDDBDialog.h"


/////////////////////////////////////////////////////////////////////////////
// Dialog
class CNewAppDlg : public CDDBDialog
{
// Variables
protected:
	//{{AFX_DATA(CNewAppDlg)
	CDDBButton		m_cOK;
	//}}AFX_DATA


// Functions
public:
	CNewAppDlg(CWnd* pParent = NULL);
	virtual ~CNewAppDlg();

	bool FindLauncherProcess();
	bool PatchFile( const char* szPatchFileName, const char* szFileName);

	void OutputMsg( const char* pszMsg);

	HANDLE FindProcess( const char* pszFileName);

protected:
	//{{AFX_VIRTUAL(CNewAppDlg)
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNewAppDlg)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOK();
	afx_msg void OnCancel();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
