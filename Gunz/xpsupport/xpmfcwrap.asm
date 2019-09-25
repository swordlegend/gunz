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
ELSE

.model flat, C

AfxApplicationRecoveryFinished PROTO STDCALL :DWORD
AfxApplicationRecoveryInProgress PROTO STDCALL :DWORD
AfxRegisterApplicationRecoveryCallback PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD
AfxRegisterApplicationRestart PROTO STDCALL :DWORD,:DWORD
AfxGetThreadPreferredUILanguages PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD

AfxSHCreateItemFromParsingName PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD
AfxInitNetworkAddressControl PROTO STDCALL

AfxChangeWindowMessageFilter PROTO STDCALL :DWORD,:DWORD

AfxDrawThemeTextEx PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
AfxBufferedPaintInit PROTO STDCALL
AfxBufferedPaintUnInit PROTO STDCALL
AfxBeginBufferedPaint PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
AfxEndBufferedPaint PROTO STDCALL :DWORD,:DWORD

AfxDwmIsCompositionEnabled PROTO STDCALL :DWORD
AfxDwmDefWindowProc PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD
AfxDwmSetWindowAttribute PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD
AfxDwmExtendFrameIntoClientArea PROTO STDCALL :DWORD,:DWORD

AfxPSGetPropertyDescriptionListFromString PROTO STDCALL :DWORD,:DWORD,:DWORD

.data
 __imp__ApplicationRecoveryFinished@4 dd AfxApplicationRecoveryFinished
 __imp__ApplicationRecoveryInProgress@4 dd AfxApplicationRecoveryInProgress
 __imp__RegisterApplicationRecoveryCallback@16 dd AfxRegisterApplicationRecoveryCallback
 __imp__RegisterApplicationRestart@8 dd AfxRegisterApplicationRestart
 __imp__GetThreadPreferredUILanguages@16 dd AfxGetThreadPreferredUILanguages

 __imp__SHCreateItemFromParsingName@16 dd AfxSHCreateItemFromParsingName
 __imp__InitNetworkAddressControl@0 dd AfxInitNetworkAddressControl

 __imp__ChangeWindowMessageFilter@8 dd AfxChangeWindowMessageFilter

 __imp__DrawThemeTextEx@36 dd AfxDrawThemeTextEx      
 __imp__BufferedPaintInit@0 dd AfxBufferedPaintInit
 __imp__BufferedPaintUnInit@0 dd AfxBufferedPaintUnInit
 __imp__BeginBufferedPaint@20 dd AfxBeginBufferedPaint
 __imp__EndBufferedPaint@8 dd AfxEndBufferedPaint

__imp__DwmIsCompositionEnabled@4 dd AfxDwmIsCompositionEnabled
__imp__DwmDefWindowProc@20 dd AfxDwmDefWindowProc
__imp__DwmSetWindowAttribute@16 dd AfxDwmSetWindowAttribute
__imp__DwmExtendFrameIntoClientArea@8 dd AfxDwmExtendFrameIntoClientArea

__imp__PSGetPropertyDescriptionListFromString@12 dd AfxPSGetPropertyDescriptionListFromString

 EXTERNDEF __imp__ApplicationRecoveryFinished@4 :
 EXTERNDEF __imp__ApplicationRecoveryInProgress@4 : DWORD
 EXTERNDEF __imp__RegisterApplicationRecoveryCallback@16 : DWORD
 EXTERNDEF __imp__RegisterApplicationRestart@8 : DWORD
 EXTERNDEF __imp__GetThreadPreferredUILanguages@16 : DWORD
 EXTERNDEF __imp__SHCreateItemFromParsingName@16  : DWORD
 EXTERNDEF __imp__InitNetworkAddressControl@0 : DWORD
 EXTERNDEF __imp__ChangeWindowMessageFilter@8 : DWORD

 EXTERNDEF __imp__DrawThemeTextEx@36 : DWORD
 EXTERNDEF __imp__BufferedPaintInit@0 : DWORD
 EXTERNDEF __imp__BufferedPaintUnInit@0 : DWORD
 EXTERNDEF __imp__BeginBufferedPaint@20 : DWORD
 EXTERNDEF __imp__EndBufferedPaint@8 : DWORD

 EXTERNDEF __imp__DwmIsCompositionEnabled@4 : DWORD
 EXTERNDEF __imp__DwmDefWindowProc@20 : DWORD
 EXTERNDEF __imp__DwmSetWindowAttribute@16 : DWORD
 EXTERNDEF __imp__DwmExtendFrameIntoClientArea@8 : DWORD

 EXTERNDEF __imp__PSGetPropertyDescriptionListFromString@12 : DWORD
  
.code
ENDIF
end
