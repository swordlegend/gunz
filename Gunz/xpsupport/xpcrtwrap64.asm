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

AfxGetTickCount64 PROTO 
AfxIsValidLocaleName PROTO  :QWORD
AfxLCMapStringEx PROTO  :QWORD,:DWORD,:QWORD,:DWORD,:QWORD,:DWORD,:QWORD,:QWORD,:QWORD
AfxCompareStringEx PROTO  :QWORD,:DWORD,:QWORD,:DWORD,:QWORD,:DWORD,:QWORD,:QWORD,:QWORD
AfxGetLocaleInfoEx PROTO  :QWORD,:DWORD,:QWORD,:DWORD
AfxGetUserDefaultLocaleName PROTO  :QWORD,:DWORD
AfxEnumSystemLocalesEx PROTO  :DWORD,:DWORD,:DWORD,:QWORD

AfxFlsAlloc PROTO :QWORD
AfxFlsFree PROTO  :DWORD
AfxFlsSetValue PROTO  :DWORD,:QWORD
AfxFlsGetValue PROTO  :DWORD

AfxGetCurrentProcessorNumber PROTO 
AfxFlushProcessWriteBuffers PROTO 
AfxCreateSemaphoreExW PROTO  :QWORD,:DWORD,:DWORD,:QWORD,:DWORD,:DWORD
AfxGetTimeFormatEx PROTO   :QWORD,:DWORD,:QWORD,:QWORD,:QWORD,:DWORD
AfxGetDateFormatEx PROTO   :QWORD,:DWORD,:QWORD,:QWORD,:QWORD,:DWORD,:QWORD
AfxSetThreadStackGuarantee PROTO  :QWORD

AfxInitializeCriticalSectionEx PROTO :QWORD,:DWORD,:DWORD
AfxCreateSymbolicLinkA PROTO :QWORD,:QWORD,:DWORD
AfxCreateSymbolicLinkW PROTO :QWORD,:QWORD,:DWORD
AfxGetLogicalProcessorInformation PROTO :QWORD,:QWORD
AfxInitOnceExecuteOnce PROTO :QWORD,:QWORD,:QWORD,:QWORD

AfxGetVersionExW PROTO :DWORD

AfxCloseThreadpoolTimer PROTO STDCALL :QWORD
AfxCloseThreadpoolWait PROTO STDCALL :QWORD
AfxCreateThreadpoolTimer PROTO STDCALL :QWORD,:QWORD,:QWORD
AfxCreateThreadpoolWait PROTO STDCALL :QWORD,:QWORD,:QWORD
AfxFreeLibraryWhenCallbackReturns PROTO STDCALL :QWORD,:QWORD
AfxSetThreadpoolTimer PROTO STDCALL :QWORD,:QWORD,:DWORD,:DWORD
AfxSetThreadpoolWait PROTO STDCALL :QWORD,:QWORD,:QWORD
AfxWaitForThreadpoolTimerCallbacks PROTO STDCALL :QWORD,:DWORD
 
.data
 __imp_GetTickCount64 dq AfxGetTickCount64
 __imp_IsValidLocaleName dq AfxIsValidLocaleName
 __imp_LCMapStringEx dq AfxLCMapStringEx
 __imp_CompareStringEx dq AfxCompareStringEx
 __imp_GetLocaleInfoEx dq AfxGetLocaleInfoEx
 __imp_GetUserDefaultLocaleName dq AfxGetUserDefaultLocaleName
 __imp_EnumSystemLocalesEx dq AfxEnumSystemLocalesEx

 __imp_FlsAlloc dq AfxFlsAlloc
 __imp_FlsFree dq AfxFlsFree
 __imp_FlsSetValue dq AfxFlsSetValue
 __imp_FlsGetValue dq AfxFlsGetValue

 __imp_GetCurrentProcessorNumber dq AfxGetCurrentProcessorNumber
 __imp_FlushProcessWriteBuffers dq AfxFlushProcessWriteBuffers
 __imp_CreateSemaphoreExW dq AfxCreateSemaphoreExW
 __imp_GetTimeFormatEx dq AfxGetTimeFormatEx
 __imp_GetDateFormatEx dq AfxGetDateFormatEx
 __imp_SetThreadStackGuarantee dq AfxSetThreadStackGuarantee

 __imp_InitializeCriticalSectionEx dq AfxInitializeCriticalSectionEx
 __imp_CreateSymbolicLinkA dq AfxCreateSymbolicLinkA
 __imp_CreateSymbolicLinkW dq AfxCreateSymbolicLinkW
 __imp_GetLogicalProcessorInformation dq AfxGetLogicalProcessorInformation
 
 __imp_InitOnceExecuteOnce dq AfxInitOnceExecuteOnce

 __imp_GetVersionExW dq AfxGetVersionExW

 __imp_CloseThreadpoolTimer dq AfxCloseThreadpoolTimer 
 __imp_CloseThreadpoolWait dq AfxCloseThreadpoolWait 
 __imp_CreateThreadpoolTimer dq AfxCreateThreadpoolTimer
 __imp_CreateThreadpoolWait dq AfxCreateThreadpoolWait
 __imp_FreeLibraryWhenCallbackReturns dq	AfxFreeLibraryWhenCallbackReturns 
 __imp_SetThreadpoolTimer dq AfxSetThreadpoolTimer
 __imp_SetThreadpoolWait dq	AfxSetThreadpoolWait
 __imp_WaitForThreadpoolTimerCallbacks dq AfxWaitForThreadpoolTimerCallbacks
 
 EXTERNDEF __imp_GetTickCount64 : QWORD
 EXTERNDEF __imp_IsValidLocaleName : DWORD
 EXTERNDEF __imp_LCMapStringEx : DWORD
 EXTERNDEF __imp_CompareStringEx : DWORD
 EXTERNDEF __imp_GetLocaleInfoEx : DWORD
 EXTERNDEF __imp_GetUserDefaultLocaleName : DWORD
 EXTERNDEF __imp_EnumSystemLocalesEx : DWORD

 EXTERNDEF __imp_FlsAlloc : DWORD
 EXTERNDEF __imp_FlsFree : DWORD
 EXTERNDEF __imp_FlsSetValue : DWORD
 EXTERNDEF __imp_FlsGetValue : DWORD 

 EXTERNDEF __imp_GetCurrentProcessorNumber : DWORD
 EXTERNDEF __imp_FlushProcessWriteBuffers :
 EXTERNDEF __imp_CreateSemaphoreExW : DWORD
 EXTERNDEF __imp_GetTimeFormatEx : DWORD
 EXTERNDEF __imp_GetDateFormatEx : DWORD
 EXTERNDEF __imp_SetThreadStackGuarantee : DWORD

 EXTERNDEF __imp_InitializeCriticalSectionEx : DWORD
 EXTERNDEF __imp_CreateSymbolicLinkA : BYTE
 EXTERNDEF __imp_CreateSymbolicLinkW : BYTE
 EXTERNDEF __imp_GetLogicalProcessorInformation : DWORD
 EXTERNDEF __imp_InitOnceExecuteOnce : DWORD

 EXTERNDEF __imp_GetVersionExW : DWORD

 EXTERNDEF __imp_CloseThreadpoolTimer : 
 EXTERNDEF __imp_CloseThreadpoolWait :
 EXTERNDEF __imp_CreateThreadpoolTimer : QWORD
 EXTERNDEF __imp_CreateThreadpoolWait  : QWORD
 EXTERNDEF __imp_FreeLibraryWhenCallbackReturns :
 EXTERNDEF __imp_SetThreadpoolTimer :
 EXTERNDEF __imp_SetThreadpoolWait :
 EXTERNDEF __imp_WaitForThreadpoolTimerCallbacks :

.code

ENDIF
 
end

