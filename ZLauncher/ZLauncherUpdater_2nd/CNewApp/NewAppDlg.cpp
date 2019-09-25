
#include "stdafx.h"
#include "NewAppDlg.h"
#include <Mmsystem.h>
#include <Tlhelp32.h>



// Defines
#define LAUNCHER_FILENAME			"GunzLauncher.exe"					// 건즈 런쳐 실행 파일 이름



// DoDataExchange
void CNewAppDlg::DoDataExchange( CDataExchange* pDX)
{
	CDDBDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewAppDlg)
	DDX_Control(pDX, IDOK, m_cOK);
	//}}AFX_DATA_MAP
}


// Message map
BEGIN_MESSAGE_MAP( CNewAppDlg, CDDBDialog)
	//{{AFX_MSG_MAP(CNewAppDlg)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/************************************************************************************
  Dialog
*************************************************************************************/
// 클래스 생성자
CNewAppDlg::CNewAppDlg( CWnd* pParent) : CDDBDialog( IDD_DIALOG_MAINDLG, pParent)
{
	// 이곳에서 생성할 다이얼로그의 정보를 입력한다
	// 좀 더 자세한 설명을 원하면 CDDBDialog.h 화일의 Structure of CDDBDIALOGINFO 내용을 참고한다
	CDDBDLGINFO DlgInfo;
	DlgInfo.nWidth  = 300;
	DlgInfo.nHeight = 200;
	DlgInfo.IDSkinResource = IDR_BMP_MAINDLG;
	DlgInfo.IDIconResource = IDR_ICO_MAINFRAME;
	DlgInfo.nTextColor = RGB( 38, 38, 38);
	DlgInfo.nTextBkColor = RGB( 182, 182, 182);

#ifdef LOCALE_NHNUSA
	DlgInfo.nTextColor = RGB( 150, 150, 150);
	DlgInfo.nTextBkColor = RGB( 38, 38, 38);
#else
	DlgInfo.bUseTitlebar = true;
#endif

	SetDialogInfo( DlgInfo);
}


CNewAppDlg::~CNewAppDlg()
{
}


/************************************************************************************
  클래스 메세지 핸들러
*************************************************************************************/
// OnInitDialog : 다이얼로그를 초기화는 함수
BOOL CNewAppDlg::OnInitDialog() 
{
	CDDBDialog::OnInitDialog();
	

	// 다이얼로그 타이틀 변경
	SetWindowText( "GunZ Updater");


#ifdef LOCALE_NHNUSA
	GetScreen()->PutText( 1, 3, GetWidth(), 20, 16, "Arial", "GunZ Updater", RGB( 20, 20, 20), TS_BOLD, DT_CENTER);
	GetScreen()->PutText( 0, 2, GetWidth(), 20, 16, "Arial", "GunZ Updater", RGB( 200, 200, 200), TS_BOLD, DT_CENTER);
	GetScreen()->PutBox( 12, 24, GetWidth() - 24, GetHeight() - 68, RGB( 80, 80, 80));
#endif


	// 다이얼로그 위치 이동 및 크기 조절
	CRect rect; 
	GetWindowRect( &rect);
	int nWidth = rect.Width(), nHeight = rect.Height();
	rect.right  = rect.left + nWidth;
	rect.bottom = rect.top  + nHeight;
	MoveWindow( rect, true);


	// 메시지 표시
	((CListBox*)GetDlgItem( IDC_OUTPUT))->ResetContent();
	((CListBox*)GetDlgItem( IDC_OUTPUT))->MoveWindow( 13, 25, GetWidth() - 26, GetHeight() - 70);
	OutputMsg( "Ready...");


	// 버튼 초기화
	m_cOK.InitDDBButton( IDR_BMP_BUTTON, NULL);
	m_cOK.MoveWindow( GetWidth() / 2 - m_cOK.GetWidth() / 2, GetHeight() - 35);
	m_cOK.EnableWindow( FALSE);


	// 타이머 개시
	SetTimer( 0, 200, NULL);


	return true;
}


/************************************************************************************
  타이머
*************************************************************************************/
void CNewAppDlg::OnTimer(UINT nIDEvent)
{
	// 업데이트 타이머
	if ( nIDEvent == 0)
	{
		static DWORD tStartTime = timeGetTime();
		DWORD currTime = timeGetTime() - tStartTime;


		// 런쳐 프로세스가 종료되는 것을 확인한다
		static bool bClosedLauncher = false;
		if ( !bClosedLauncher && (currTime > 500))
		{
			bClosedLauncher = FindLauncherProcess();
		}


		// 파일 패치
		if ( bClosedLauncher)
		{
			static int nPatchCount = 0;
			static int nErrorCount = 0;
			switch ( nPatchCount)
			{
				case 0 :
					nPatchCount++;
					if ( PatchFile( ".\\PATCH\\GunzLauncher.exe_", ".\\GunzLauncher.exe") == false)
						nErrorCount++;
					break;

				case 1 :
					nPatchCount++;
					if ( PatchFile( ".\\PATCH\\HanAuthForClient.dll_", ".\\HanAuthForClient.dll") == false)
						nErrorCount++;
					break;

				case 2 :
					nPatchCount++;
					if ( PatchFile( ".\\PATCH\\HanReportForClient.dll_", ".\\HanReportForClient.dll") == false)
						nErrorCount++;
					break;

				case 3 :
					nPatchCount++;

					if ( nErrorCount)
					{
						((CListBox*)GetDlgItem( IDC_OUTPUT))->ShowScrollBar( SB_HORZ);
						((CListBox*)GetDlgItem( IDC_OUTPUT))->SetHorizontalExtent( 1000);
						
						char szMsg[ 512];
						sprintf( szMsg, "%d error has been found.", nErrorCount);
						OutputMsg( szMsg);
					}
					else
						OutputMsg( "Patch successfully completed.");
					
					tStartTime = timeGetTime();
					m_cOK.EnableWindow( TRUE);
					break;

				// 윈도우 종료
				case 4 :
					if ( (nErrorCount == 0) && (currTime > 2000))
						OnOK();
					break;

				default :
					break;
			}
		}
	}


	CDDBDialog::OnTimer(nIDEvent);
}


/************************************************************************************
  메시지 출력하는 함수
*************************************************************************************/
void CNewAppDlg::OutputMsg( const char* pszMsg)
{
	((CListBox*)GetDlgItem( IDC_OUTPUT))->AddString( pszMsg);
	((CListBox*)GetDlgItem( IDC_OUTPUT))->SetCaretIndex( ((CListBox*)GetDlgItem( IDC_OUTPUT))->GetCount());
}


/************************************************************************************
  종료 처리
*************************************************************************************/
void CNewAppDlg::OnOK()
{
	// 런쳐를 다시 시작한다.
	char szCmdLine[ 4096] = { 0,};
	sprintf( szCmdLine, ".\\GunzLauncher.exe \"%s\"", GetCommandLine());
	WinExec( szCmdLine, SW_SHOW);


	// 윈도우 종료
	CDialog::OnOK();
}

void CNewAppDlg::OnCancel()
{
}


/************************************************************************************
  패치 시작
*************************************************************************************/
bool CNewAppDlg::FindLauncherProcess()
{
	// 런쳐가 아직 실행중인지 확인한다
	if ( FindProcess( LAUNCHER_FILENAME) != NULL)
		return false;


	// 만약을 위해서 1초 정도 기다린다
	Sleep( 1000);

	return true;
}


/************************************************************************************
  파일 패치
*************************************************************************************/
bool CNewAppDlg::PatchFile( const char* szPatchFileName, const char* szFileName)
{
	// 업데이트 파일을 찾는다
	WIN32_FIND_DATA FindData;
	HANDLE hFind = FindFirstFile( _T( szPatchFileName), &FindData);
	if ( hFind != INVALID_HANDLE_VALUE)		// 파일이 있으면...
	{
		FindClose( hFind);


		// 업데이트 파일을 복사한다.
		if ( CopyFile( _T( szPatchFileName), _T( szFileName), false) == TRUE)	// 복사 했으면...
		{
			// 업데이트 파일을 삭제한다.
			DeleteFile( _T( szPatchFileName));


			// 출력 메시지 작성
			char szMsg[ 512];
			sprintf( szMsg, "%s : Patched", szFileName);
			OutputMsg( szMsg);

			return true;
		}

		// 복사 실패이면...
		else
		{
			// 에러 코드
			LPVOID lpMsgBuf;
			DWORD error = GetLastError();
			FormatMessage(	FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
							NULL, error, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT),
							(LPTSTR)&lpMsgBuf, 0, NULL);

			// 출력 메시지 작성
			char szMsg[ 512];
			sprintf( szMsg, "%s : Failed (%s)\n", szFileName, lpMsgBuf);
			OutputMsg( szMsg);

			LocalFree( lpMsgBuf);

			return false;
		}
	}


	return true;
}


/************************************************************************************
  해당 프로세스의 핸들을 구한다
*************************************************************************************/
/* 98에서 동작 안함... =_=
HANDLE CNewAppDlg::FindProcess( const char* pszFileName)
{
	DWORD ProcessIDList[ 1024], cbNeeded;

	if ( !EnumProcesses( ProcessIDList, sizeof( ProcessIDList), &cbNeeded))
		return NULL;

	// Calculate how many process identifiers were returned.
	int nProcessCount = cbNeeded / sizeof( DWORD);

	for ( int i = 0;  i < nProcessCount;  i++)
	{
		DWORD nProcessID = ProcessIDList[ i];

		char szProcessName[ MAX_PATH] = "unknown";
		char szProcessPath[ MAX_PATH] = "unknown";

		// Get a handle to the process.
		HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, TRUE, nProcessID);
		if ( NULL != hProcess)		// Get the process name.
		{
			HMODULE hMod;
			DWORD cbNeeded;

			if ( EnumProcessModules( hProcess, &hMod, sizeof( hMod), &cbNeeded))
			{
				GetModuleBaseName( hProcess, hMod, szProcessName, sizeof( szProcessName));
				GetModuleFileNameEx( hProcess, hMod, szProcessPath, sizeof( szProcessPath));

				// 파일 이름만 비교
				if ( stricmp( pszFileName, szProcessName) == 0)
					return hProcess;

				// 전체 경로까지 비교
				else if ( stricmp( pszFileName, szProcessPath) == 0)
					return hProcess;
			}

			CloseHandle( hProcess);
		}
	}

	return NULL;
}
*/

HANDLE CNewAppDlg::FindProcess( const char* pszFileName)
{
	// Take a snapshot of all processes in the system.
	HANDLE hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0);
	if ( hProcessSnap == INVALID_HANDLE_VALUE)
		return NULL;


	// Set the size of the structure before using it.
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof( PROCESSENTRY32);


	// Retrieve information about the first process, and exit if unsuccessful
	if ( !Process32First( hProcessSnap, &pe32))
	{
		CloseHandle( hProcessSnap);
		return NULL;
	}


	// Now walk the snapshot of processes, and
	// display information about each process in turn
	do
	{
		// Retrieve the priority class.
		DWORD dwPriorityClass = 0;
		HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);

		if ( hProcess == NULL)
			continue;


		// Get module name
		char szModuleName[ 256];
		strcpy( szModuleName, (LPCTSTR)pe32.szExeFile);

		if ( stricmp( pszFileName, szModuleName) == 0)
		{
			// Find module
			CloseHandle( hProcess);
			CloseHandle( hProcessSnap);

			return hProcess;
		}

		CloseHandle( hProcess);

	} while( Process32Next( hProcessSnap, &pe32));


	CloseHandle( hProcessSnap);

	return NULL;
}
