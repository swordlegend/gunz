/* Copyright (c) 2012 Mike Ryan

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */


// XPSupport MFC 11 Wrappers
// Written by Mike Ryan (aka Ted.)
// http://tedwvc.wordpress.com
// see also http://connect.microsoft.com/VisualStudio/feedback/details/690617/

// Version History
// 1.0  2012-03-11 Initial Release 
// 1.01 (CRT update)
// 1.02 2012-03-15 added DwmExtendFrameIntoClientArea
// 1.03 (CRT update)
// 1.04 2012-03-16 added PSGetPropertyDescriptionListFromString
// 1.05-1.07 (CRT updates)
// 1.08 2012-05-26 added XP/2003 x64 edition support (in xpmfcwrap64.asm)
// - thanks to Antony Vennard (https://vennard.org.uk) for testing and correcting several errors in my initial test x64 release
// 1.09 (CRT update)
// 1.10 added MIT license

// A quick note about the MFC 11 wrappers
// no attempt has been made to provide fallback functionality on XP
// However I have found that in all cases, extra special fallback behaviour is not needed to have a fully functioning MFC app including feature pack on XP.
// This illustrates that the Microsoft removing of XP support from MFC was not a technical requirement
// note: I did not provide any fallback for the property system (PROPSYS.DLL) function in this release.  If your app uses or requires them, feel free to add/contribute your own wrappers

// wrappers provided for:
// - restart manager functions (kernel32.dll)
// - preferred UI languages (kernel32.dll)
// - message filter (user32.dll)
// - uxtheme Vista only functions (uxtheme.dll)
// - Desktop composition APIs (DWMAPI.DLL)
// - Property system (PROPSYS.DLL) 
//   - note, as an alternative http://support.microsoft.com/kb/917013 has downloads to installers for Windows Desktop
//   Search 3.0 (XP and 2003) which includes PROPSYS.DLL. I don't recommend you rely on these always being installed

#include "stdafx.h"

static BOOL IsVista = ((BYTE)::GetVersion() >= 6);

typedef VOID (WINAPI *pApplicationRecoveryFinished)(__in  BOOL bSuccess);

extern "C" VOID WINAPI AfxApplicationRecoveryFinished(__in  BOOL bSuccess)
{
	static pApplicationRecoveryFinished ApplicationRecoveryFinished_p = NULL;

	if (IsVista) { // Vista or higher
		if (!ApplicationRecoveryFinished_p) { 
			HMODULE mod = GetModuleHandle( _T("KERNEL32.DLL"));
			if (mod) 
				ApplicationRecoveryFinished_p = (pApplicationRecoveryFinished) GetProcAddress(mod, "ApplicationRecoveryFinished");
		}
		ApplicationRecoveryFinished_p(bSuccess);

	} 
}

typedef HRESULT (WINAPI *pApplicationRecoveryInProgress)(__out  PBOOL pbCanceled);

extern "C" HRESULT WINAPI AfxApplicationRecoveryInProgress(__out  PBOOL pbCanceled)
{
	static pApplicationRecoveryInProgress ApplicationRecoveryInProgress_p = NULL;

	if (IsVista) { // Vista or higher
		if (!ApplicationRecoveryInProgress_p) { 
			HMODULE mod = GetModuleHandle( _T("KERNEL32.DLL"));
			if (mod) 
				ApplicationRecoveryInProgress_p = (pApplicationRecoveryInProgress) GetProcAddress(mod, "ApplicationRecoveryInProgress");
		}
		return ApplicationRecoveryInProgress_p(pbCanceled);
	} 
	return S_OK;
}

typedef HRESULT (WINAPI *pRegisterApplicationRecoveryCallback)(__in APPLICATION_RECOVERY_CALLBACK pRecoveryCallback,
												   __in_opt  PVOID pvParameter, __in DWORD dwPingInterval, __in DWORD dwFlags);


extern "C" HRESULT WINAPI AfxRegisterApplicationRecoveryCallback(__in APPLICATION_RECOVERY_CALLBACK pRecoveryCallback,
												   __in_opt  PVOID pvParameter, __in DWORD dwPingInterval, __in DWORD dwFlags)
{
	static pRegisterApplicationRecoveryCallback RegisterApplicationRecoveryCallback_p = NULL;

	if (IsVista) { // Vista or higher
		if (!RegisterApplicationRecoveryCallback_p) { 
			HMODULE mod = GetModuleHandle( _T("KERNEL32.DLL"));
			if (mod) 
				RegisterApplicationRecoveryCallback_p = (pRegisterApplicationRecoveryCallback) GetProcAddress(mod, "RegisterApplicationRecoveryCallback");
		}
		return RegisterApplicationRecoveryCallback_p(pRecoveryCallback, pvParameter, dwPingInterval, dwFlags);

	} 
	return S_OK;

}


typedef HRESULT (WINAPI *pRegisterApplicationRestart)(__in_opt  PCWSTR pwzCommandline, __in      DWORD dwFlags);

extern "C" HRESULT WINAPI AfxRegisterApplicationRestart(__in_opt  PCWSTR pwzCommandline, __in      DWORD dwFlags)
{
	static pRegisterApplicationRestart RegisterApplicationRestart_p = NULL;

	if (IsVista) { // Vista or higher
		if (!RegisterApplicationRestart_p) { 
			HMODULE mod = GetModuleHandle( _T("KERNEL32.DLL"));
			if (mod) 
				RegisterApplicationRestart_p = (pRegisterApplicationRestart) GetProcAddress(mod, "RegisterApplicationRestart");
		}
		return RegisterApplicationRestart_p(pwzCommandline, dwFlags);

	} 
	return S_OK;
}

typedef BOOL (WINAPI *pGetThreadPreferredUILanguages)(__in DWORD dwFlags, __out PULONG pulNumLanguages, __out_opt PZZWSTR pwszLanguagesBuffer, __inout PULONG pcchLanguagesBuffer);

extern "C" BOOL WINAPI AfxGetThreadPreferredUILanguages(__in DWORD dwFlags, __out PULONG pulNumLanguages, __out_opt PZZWSTR pwszLanguagesBuffer, __inout PULONG pcchLanguagesBuffer)
{
	static pGetThreadPreferredUILanguages GetThreadPreferredUILanguages_p = NULL;

	if (IsVista) { // Vista or higher
		if (!GetThreadPreferredUILanguages_p) { 
			HMODULE mod = GetModuleHandle( _T("KERNEL32.DLL"));
			if (mod) 
				GetThreadPreferredUILanguages_p = (pGetThreadPreferredUILanguages) GetProcAddress(mod, "GetThreadPreferredUILanguages");
		}
		return GetThreadPreferredUILanguages_p(dwFlags, pulNumLanguages, pwszLanguagesBuffer, pcchLanguagesBuffer);
	} 
	return FALSE;
}

// shell32 functions 

typedef HRESULT (WINAPI *pSHGetKnownFolderPath)(__in   REFKNOWNFOLDERID rfid, __in   DWORD dwFlags,  __in   HANDLE hToken, __out  PWSTR *ppszPath);

// SHGetKnownFolderPath is special in that it doesn't allow me to link to the __imp version of the function from the assembly wrapper
// luckily, if I export the name SHGetKnownFolderPath directly from here (instead of what I normally do which is export an Afx function), 
// it allows me to link successfully with no duplicate symbol linker errors!

extern "C" HRESULT WINAPI SHGetKnownFolderPath(__in   REFKNOWNFOLDERID rfid, __in   DWORD dwFlags,  __in   HANDLE hToken, __out  PWSTR *ppszPath)
{
	static pSHGetKnownFolderPath SHGetKnownFolderPath_p = NULL;

	if (IsVista) { // Vista or higher
		if (!SHGetKnownFolderPath_p) { 
			HMODULE mod = GetModuleHandle( _T("SHELL32.DLL"));
			if (mod) 
				SHGetKnownFolderPath_p = (pSHGetKnownFolderPath) GetProcAddress(mod, "SHGetKnownFolderPath");
		}
		return SHGetKnownFolderPath_p(rfid, dwFlags, hToken, ppszPath);
	} 
	return E_FAIL;

}

typedef HRESULT (WINAPI *pSHCreateItemFromParsingName)(__in PCWSTR pszPath, __in   IBindCtx *pbc, __in   REFIID riid, __out  void **ppv);

extern "C" HRESULT WINAPI AfxSHCreateItemFromParsingName(__in PCWSTR pszPath, __in   IBindCtx *pbc, __in   REFIID riid, __out  void **ppv)
{
	static pSHCreateItemFromParsingName SHCreateItemFromParsingName_p = NULL;

	if (IsVista) { // Vista or higher
		if (!SHCreateItemFromParsingName_p) { 
			HMODULE mod = GetModuleHandle( _T("SHELL32.DLL"));
			if (mod) 
				SHCreateItemFromParsingName_p = (pSHCreateItemFromParsingName) GetProcAddress(mod, "SHCreateItemFromParsingName");
		}
		return SHCreateItemFromParsingName_p(pszPath, pbc, riid, ppv);
	} 
	return E_FAIL;

}

typedef BOOL (WINAPI *pInitNetworkAddressControl)(void);

extern "C" BOOL WINAPI AfxInitNetworkAddressControl(void)
{
	static pInitNetworkAddressControl InitNetworkAddressControl_p = NULL;

	if (IsVista) { // Vista or higher
		if (!InitNetworkAddressControl_p) { 
			HMODULE mod = GetModuleHandle( _T("SHELL32.DLL"));
			if (mod) 
				InitNetworkAddressControl_p = (pInitNetworkAddressControl) GetProcAddress(mod, "InitNetworkAddressControl");
		}
		return InitNetworkAddressControl_p();
	} 
	return FALSE;

}

// user32 functions

typedef BOOL (WINAPI *pChangeWindowMessageFilter)(__in  UINT message, __in  DWORD dwFlag);

extern "C" BOOL WINAPI AfxChangeWindowMessageFilter(__in  UINT message, __in  DWORD dwFlag)
{
	static pChangeWindowMessageFilter ChangeWindowMessageFilter_p = NULL;

	if (IsVista) { // Vista or higher
		if (!ChangeWindowMessageFilter_p) { 
			HMODULE mod = GetModuleHandle( _T("USER32.DLL"));
			if (mod) 
				ChangeWindowMessageFilter_p = (pChangeWindowMessageFilter) GetProcAddress(mod, "ChangeWindowMessageFilter");
		}
		return ChangeWindowMessageFilter_p(message, dwFlag);
	} 
	return FALSE;
}

// uxtheme functions

typedef HRESULT (WINAPI *pDrawThemeTextEx)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, 
								    __in     DWORD dwFlags, __inout  LPRECT pRect,__in     const DTTOPTS *pOptions);


extern "C" HRESULT WINAPI AfxDrawThemeTextEx(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, 
								    __in     DWORD dwFlags, __inout  LPRECT pRect,__in     const DTTOPTS *pOptions)
{
	static pDrawThemeTextEx DrawThemeTextEx_p = NULL;

	if (IsVista) { // Vista or higher
		if (!DrawThemeTextEx_p) { 
			HMODULE mod = GetModuleHandle( _T("UXTHEME.DLL"));
			if (mod) 
				DrawThemeTextEx_p = (pDrawThemeTextEx) GetProcAddress(mod, "DrawThemeTextEx");
		}
		return DrawThemeTextEx_p(hTheme, hdc, iPartId, iStateId, pszText, iCharCount, dwFlags, pRect, pOptions);
	} 
	return FALSE;

}


typedef HRESULT (WINAPI *pBufferedPaintInit)(void);

extern "C" HRESULT WINAPI AfxBufferedPaintInit()
{
	static pBufferedPaintInit BufferedPaintInit_p = NULL;

	if (IsVista) { // Vista or higher
		if (!BufferedPaintInit_p) { 
			HMODULE mod = GetModuleHandle( _T("UXTHEME.DLL"));
			if (mod) 
				BufferedPaintInit_p = (pBufferedPaintInit) GetProcAddress(mod, "BufferedPaintInit");
		}
		return BufferedPaintInit_p();
	} 
	return S_OK;

}

typedef HRESULT (WINAPI *pBufferedPaintUnInit)(void);

extern "C" HRESULT WINAPI AfxBufferedPaintUnInit()
{
	static pBufferedPaintUnInit BufferedPaintUnInit_p = NULL;

	if (IsVista) { // Vista or higher
		if (!BufferedPaintUnInit_p) { 
			HMODULE mod = GetModuleHandle( _T("UXTHEME.DLL"));
			if (mod) 
				BufferedPaintUnInit_p = (pBufferedPaintUnInit) GetProcAddress(mod, "BufferedPaintUnInit");
		}
		return BufferedPaintUnInit_p();
	} 
	return S_OK;

}

typedef HPAINTBUFFER (WINAPI *pBeginBufferedPaint)(HDC hdcTarget, const RECT* prcTarget, BP_BUFFERFORMAT dwFormat, __in_opt BP_PAINTPARAMS *pPaintParams, __out HDC *phdc);

extern "C" HPAINTBUFFER WINAPI AfxBeginBufferedPaint(HDC hdcTarget, const RECT* prcTarget, BP_BUFFERFORMAT dwFormat, __in_opt BP_PAINTPARAMS *pPaintParams, __out HDC *phdc)
{
	static pBeginBufferedPaint BeginBufferedPaint_p = NULL;

	if (IsVista) { // Vista or higher
		if (!BeginBufferedPaint_p) { 
			HMODULE mod = GetModuleHandle( _T("UXTHEME.DLL"));
			if (mod) 
				BeginBufferedPaint_p = (pBeginBufferedPaint) GetProcAddress(mod, "BeginBufferedPaint");
		}
		return BeginBufferedPaint_p(hdcTarget, prcTarget, dwFormat, pPaintParams, phdc);
	} 
	return 0;
}

typedef HRESULT (WINAPI *pEndBufferedPaint)(HPAINTBUFFER hBufferedPaint, BOOL fUpdateTarget);

extern "C" HRESULT WINAPI AfxEndBufferedPaint(HPAINTBUFFER hBufferedPaint, BOOL fUpdateTarget)
{
	static pEndBufferedPaint EndBufferedPaint_p = NULL;

	if (IsVista) { // Vista or higher
		if (!EndBufferedPaint_p) { 
			HMODULE mod = GetModuleHandle( _T("UXTHEME.DLL"));
			if (mod) 
				EndBufferedPaint_p = (pEndBufferedPaint) GetProcAddress(mod, "EndBufferedPaint");
		}
		return EndBufferedPaint_p(hBufferedPaint, fUpdateTarget);
	} 
	return S_OK;
}

// dwmapi

typedef HRESULT (WINAPI *pDwmIsCompositionEnabled)(__out  BOOL *pfEnabled);

extern "C" HRESULT WINAPI AfxDwmIsCompositionEnabled(__out  BOOL *pfEnabled)
{
	static pDwmIsCompositionEnabled DwmIsCompositionEnabled_p = NULL;

	if (IsVista) { // Vista or higher
		if (!DwmIsCompositionEnabled_p) { 
			HMODULE mod = GetModuleHandle( _T("DWMAPI.DLL"));
			if (mod) 
				DwmIsCompositionEnabled_p = (pDwmIsCompositionEnabled) GetProcAddress(mod, "DwmIsCompositionEnabled");
		}
		return DwmIsCompositionEnabled_p(pfEnabled);
	} 

	// return false for XP
	if (pfEnabled)
		*pfEnabled = FALSE;

	return S_OK;
}


typedef LRESULT (WINAPI *pDwmDefWindowProc)(HWND hWnd, UINT message, WPARAM wp, LPARAM lp);

extern "C" LRESULT WINAPI AfxDwmDefWindowProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	static pDwmDefWindowProc DwmDefWindowProc_p = NULL;

	if (IsVista) { // Vista or higher
		if (!DwmDefWindowProc_p) { 
			HMODULE mod = GetModuleHandle( _T("DWMAPI.DLL"));
			if (mod) 
				DwmDefWindowProc_p = (pDwmDefWindowProc) GetProcAddress(mod, "DwmDefWindowProc");
		}
		return DwmDefWindowProc_p(hWnd, message, wp, lp);
	} 

	return FALSE;
}

typedef HRESULT (WINAPI *pDwmSetWindowAttribute)(__in  HWND hwnd, __in  DWORD dwAttribute, __in  LPCVOID pvAttribute, __in  DWORD cbAttribute);


extern "C" HRESULT WINAPI AfxDwmSetWindowAttribute(__in  HWND hwnd, __in  DWORD dwAttribute, __in  LPCVOID pvAttribute, __in  DWORD cbAttribute)
{
	static pDwmSetWindowAttribute DwmSetWindowAttribute_p = NULL;

	if (IsVista) { // Vista or higher
		if (!DwmSetWindowAttribute_p) { 
			HMODULE mod = GetModuleHandle( _T("DWMAPI.DLL"));
			if (mod) 
				DwmSetWindowAttribute_p = (pDwmSetWindowAttribute) GetProcAddress(mod, "DwmSetWindowAttribute");
		}
		return DwmSetWindowAttribute_p(hwnd, dwAttribute, pvAttribute, cbAttribute);
	} 

	return S_OK;
}

typedef HRESULT (WINAPI *pDwmExtendFrameIntoClientArea)(HWND hWnd, __in  const MARGINS *pMarInset);

extern "C" HRESULT WINAPI AfxDwmExtendFrameIntoClientArea(HWND hWnd, __in  const MARGINS *pMarInset)
{
	static pDwmExtendFrameIntoClientArea DwmExtendFrameIntoClientArea_p = NULL;

	if (IsVista) { // Vista or higher
		if (!DwmExtendFrameIntoClientArea_p) { 
			HMODULE mod = GetModuleHandle( _T("DWMAPI.DLL"));
			if (mod) 
				DwmExtendFrameIntoClientArea_p = (pDwmExtendFrameIntoClientArea) GetProcAddress(mod, "DwmExtendFrameIntoClientArea");
		}
		return DwmExtendFrameIntoClientArea_p(hWnd, pMarInset);
	} 

	return S_OK;
}

// PROPSYS.DLL

typedef HRESULT (WINAPI *pPSGetPropertyDescriptionListFromString)(__in   LPCWSTR pszPropList, __in   REFIID riid, __out  void **ppv);

extern "C" HRESULT WINAPI AfxPSGetPropertyDescriptionListFromString(__in   LPCWSTR pszPropList, __in   REFIID riid, __out  void **ppv)
{
	static pPSGetPropertyDescriptionListFromString PSGetPropertyDescriptionListFromString_p = NULL;
	static BOOL looked = FALSE;

	// native version of this function available on Vista and Server 2003
	if (!looked && !PSGetPropertyDescriptionListFromString_p) { 
		HMODULE mod = GetModuleHandle( _T("KERNEL32.DLL"));
		if (mod) 
			PSGetPropertyDescriptionListFromString_p = (pPSGetPropertyDescriptionListFromString) GetProcAddress(mod, "PSGetPropertyDescriptionListFromString");
		else
			looked = TRUE;
	}
	if (PSGetPropertyDescriptionListFromString_p)
		return PSGetPropertyDescriptionListFromString_p(pszPropList, riid, ppv);
	else
		return S_OK;  // no fallback yet
}


