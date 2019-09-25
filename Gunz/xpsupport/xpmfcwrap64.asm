;Copyright (c) 2012 Mike Ryan

;Permission is hereby granted, free of charge, to any person obtaining a copy of this software
;and associated documentation files (the "Software"), to deal in the Software without restriction,
;including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
;and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
;subject to the following conditions:

;The above copyright notice and this permission notice shall be included in all copies or substantial
;portions of the Software.

;THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
;LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
;IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
;WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
;OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 

__ML_64 = OPATTR rax

IF __ML_64

AfxApplicationRecoveryFinished PROTO  :DWORD
AfxApplicationRecoveryInProgress PROTO  :QWORD
AfxRegisterApplicationRecoveryCallback PROTO  :QWORD,:QWORD,:DWORD,:DWORD
AfxRegisterApplicationRestart PROTO  :QWORD,:DWORD
AfxGetThreadPreferredUILanguages PROTO  :DWORD,:QWORD,:QWORD,:QWORD

AfxSHCreateItemFromParsingName PROTO  :QWORD,:DWORD,:QWORD,:QWORD
AfxInitNetworkAddressControl PROTO 

AfxChangeWindowMessageFilter PROTO  :DWORD,:DWORD

AfxDrawThemeTextEx PROTO  :DWORD,:DWORD,:DWORD,:DWORD,:QWORD,:DWORD,:DWORD,:QWORD,:QWORD
AfxBufferedPaintInit PROTO 
AfxBufferedPaintUnInit PROTO 
AfxBeginBufferedPaint PROTO  :DWORD,:QWORD,:DWORD,:QWORD,:QWORD
AfxEndBufferedPaint PROTO  :DWORD,:DWORD

AfxDwmIsCompositionEnabled PROTO  :QWORD
AfxDwmDefWindowProc PROTO  :DWORD,:DWORD,:DWORD,:DWORD
AfxDwmSetWindowAttribute PROTO  :DWORD,:DWORD,:QWORD,:DWORD
AfxDwmExtendFrameIntoClientArea PROTO :DWORD,:QWORD

AfxPSGetPropertyDescriptionListFromString PROTO :QWORD,:DWORD,:QWORD

.data
 __imp_ApplicationRecoveryFinished dq AfxApplicationRecoveryFinished
 __imp_ApplicationRecoveryInProgress dq AfxApplicationRecoveryInProgress
 __imp_RegisterApplicationRecoveryCallback dq AfxRegisterApplicationRecoveryCallback
 __imp_RegisterApplicationRestart dq AfxRegisterApplicationRestart
 __imp_GetThreadPreferredUILanguages dq AfxGetThreadPreferredUILanguages

 __imp_SHCreateItemFromParsingName dq AfxSHCreateItemFromParsingName
 __imp_InitNetworkAddressControl dq AfxInitNetworkAddressControl

 __imp_ChangeWindowMessageFilter dq AfxChangeWindowMessageFilter

 __imp_DrawThemeTextEx dq AfxDrawThemeTextEx      
 __imp_BufferedPaintInit dq AfxBufferedPaintInit
 __imp_BufferedPaintUnInit dq AfxBufferedPaintUnInit
 __imp_BeginBufferedPaint dq AfxBeginBufferedPaint
 __imp_EndBufferedPaint dq AfxEndBufferedPaint

__imp_DwmIsCompositionEnabled dq AfxDwmIsCompositionEnabled
__imp_DwmDefWindowProc dq AfxDwmDefWindowProc
__imp_DwmSetWindowAttribute dq AfxDwmSetWindowAttribute
__imp_DwmExtendFrameIntoClientArea dq AfxDwmExtendFrameIntoClientArea

__imp_PSGetPropertyDescriptionListFromString dq AfxPSGetPropertyDescriptionListFromString

 EXTERNDEF __imp_ApplicationRecoveryFinished :
 EXTERNDEF __imp_ApplicationRecoveryInProgress : DWORD
 EXTERNDEF __imp_RegisterApplicationRecoveryCallback : DWORD
 EXTERNDEF __imp_RegisterApplicationRestart : DWORD
 EXTERNDEF __imp_GetThreadPreferredUILanguages : DWORD
 EXTERNDEF __imp_SHCreateItemFromParsingName  : DWORD
 EXTERNDEF __imp_InitNetworkAddressControl : DWORD
 EXTERNDEF __imp_ChangeWindowMessageFilter : DWORD

 EXTERNDEF __imp_DrawThemeTextEx : DWORD
 EXTERNDEF __imp_BufferedPaintInit : DWORD
 EXTERNDEF __imp_BufferedPaintUnInit : DWORD
 EXTERNDEF __imp_BeginBufferedPaint : DWORD
 EXTERNDEF __imp_EndBufferedPaint : DWORD

 EXTERNDEF __imp_DwmIsCompositionEnabled : DWORD
 EXTERNDEF __imp_DwmDefWindowProc : DWORD
 EXTERNDEF __imp_DwmSetWindowAttribute : DWORD
 EXTERNDEF __imp_DwmExtendFrameIntoClientArea : DWORD

 EXTERNDEF __imp_PSGetPropertyDescriptionListFromString : DWORD

.code
ENDIF
end

