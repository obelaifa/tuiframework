/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//   Creator:: Manfred Rieck                    (C) Mewes & Partner GmbH   //
//                                                                         //
//  $Archive:: /Manfred/WinMOD/Driver/MEM_Y200/Y200SDK/Y200Clnt/Y200Clnt $ //
// $Revision:: 5                                                         $ //
//   $Author:: Manfred                                                   $ //
//     $Date:: 5.07.07 17:31                                             $ //
//                                                                         //
//$NoKeywords: $/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//
// Datei: Y200Clnt.h
// C/C++ Header fuer die Dynamic Link Library Y200Clnt.dll
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(_Y200CLNT_INCLUDED_)
#define _Y200CLNT_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////////////////////////////////
// spezielle Typ- bzw. Macros-Definitionen 
/////////////////////////////////////////////////////////////////////////////

#ifndef LONG
typedef long LONG;
#endif

#ifndef HRESULT
typedef LONG HRESULT;
#endif

#ifndef MAKE_HRESULT
#define MAKE_HRESULT(sev,fac,code) \
    ((HRESULT) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16) | ((unsigned long)(code))) )
#endif

#define Y200CLNT_API __stdcall

// Handle fuer den typsicheren Zugriff auf die DLL-Funktionen
struct WMY200RANGEHANDLEtag {int unused;};
typedef struct WMY200RANGEHANDLEtag *WMY200RANGEHANDLE;

#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))


/////////////////////////////////////////////////////////////////////////////
// Definition der Fehlercodes (HRESULT)
/////////////////////////////////////////////////////////////////////////////

#define WM_Y200_E_BASE					(0x200)
#define WM_Y200_S_OK					((HRESULT)0x00000000L)							// alles OK
#define WM_Y200_E_INVALID_HANDLE		MAKE_HRESULT(1,FACILITY_ITF,WM_Y200_E_BASE+1)	// kein gültiges Range-Objekt Handle
#define WM_Y200_E_NO_SHARED_MEM			MAKE_HRESULT(1,FACILITY_ITF,WM_Y200_E_BASE+2)	// keine Verbindung zum IPC
#define WM_Y200_E_INVALID_PARAM			MAKE_HRESULT(1,FACILITY_ITF,WM_Y200_E_BASE+3)	// ungültiger Parameter
#define WM_Y200_E_INVALID_READ_PARAM	MAKE_HRESULT(1,FACILITY_ITF,WM_Y200_E_BASE+4)	// ungültiger Lesebereich
#define WM_Y200_E_INVALID_WRITE_PARAM	MAKE_HRESULT(1,FACILITY_ITF,WM_Y200_E_BASE+5)	// ungültiger Schreibbereich
#define WM_Y200_E_TREAD_FAIL			MAKE_HRESULT(1,FACILITY_ITF,WM_Y200_E_BASE+6)	// Starten des Notify-Threads fehlgeschlagen
#define WM_Y200_E_TREAD_SYNC_FAIL		MAKE_HRESULT(1,FACILITY_ITF,WM_Y200_E_BASE+7)	// Event für die Synchronisation des Notify-Thread konnte nicht initialisiert werden
#define WM_Y200_E_INVALID_IPC_NAME		MAKE_HRESULT(1,FACILITY_ITF,WM_Y200_E_BASE+8)	// ungültiger IPC-Name

#define WM_Y200_E_INVALID_IMAGE_SIZE	MAKE_HRESULT(1,FACILITY_WIN32,ERROR_ALREADY_EXISTS)	// Prozessdatenabbild existierte bereits mit einer zu geringen Größe

/////////////////////////////////////////////////////////////////////////////
// Funktionsdeklarationen
/////////////////////////////////////////////////////////////////////////////

HRESULT Y200CLNT_API WMY200SetIPCProcImgSize(LPCTSTR pszIPCName, size_t nProcImgSize);
// benötigte Größe des Prozessdatenabbildes für einen shared memory anmelden
// Kann optional genutzt werden, um bereits vor dem Erzeugen des 1. Range-Objekts mit WMY200CreateIPCRange festzulegen,
// welche Größe des Prozessdatenabbildes beim Erzeugen des shared memory angefordert werden soll.
// Ansonsten wird die benötigten Größe aus den an WMY200CreateIPCRange übergebenen Parametern automatisch ermitteln.

HRESULT Y200CLNT_API WMY200CreateIPCRange(LPCTSTR pszIPCName,UINT uReadOffs,UINT uReadSize,UINT uWriteOffs,UINT uWriteSize,WMY200RANGEHANDLE* pHandle);
// Range-Objekt erzeugen und bei Erfolg ein Handle auf das Range-Objekt zurückgeben
// uReadOffs gibt den Offset und uReadSize die Grösse des Lesebereichs in Bytes an
// uWriteOffs gibt den Offset und uWriteSize die Grösse des Schreibbereichs in Bytes an
// die Offsets beziehen sich auf den Anfang des Prozessdatenabbildes im shared memory
// die Summe aus Offset- und Size-Parameter muss jeweils kleiner oder gleich MEM_Y200_SIZE_MAX sein
// Bei Erfolg liefert die Funktion im Rückgabeparameter *pHandle ein Handle auf das neue Range-Objekt zurück,
// ansonsten ist *pHandle NULL.

// Die erforderliche Größe des Prozessdatenabbildes wird beim Erzeugen des 1. Range-Objekts
// aus der größten Adresse des Lese- bzw. Schreibbereichs ermittelt und festgelegt. (Granularität: 1KByte)
// Die ermittelte Größe legt für alle nachfolgend erzeugten Range-Objekte die Obergrenze
// für den Lese- bzw. Schreibbereich fest. (kann mit WMY200GetIPCMapSize abgefragt werden)

HRESULT Y200CLNT_API WMY200DestroyIPCRange(WMY200RANGEHANDLE hRange);
// Range-Objekt zerstören

HRESULT Y200CLNT_API WMY200GetIPCName(WMY200RANGEHANDLE hRange,LPTSTR lpBuffer,DWORD* lpnSize);
// liefert den Namen des IPC (shared memory), dass dem Range-Objekt zugeordnet ist 

HRESULT Y200CLNT_API WMY200GetIPCMapSize(WMY200RANGEHANDLE hRange,size_t *pnMapSize);
// liefert die Größe des gemappten Prozessdatenabbildes des IPC (shared memory), dass dem Range-Objekt zugeordnet ist 

HRESULT Y200CLNT_API WMY200GetIPCProcImgSize(WMY200RANGEHANDLE hRange,size_t *pnProcImgSize);
// liefert die Größe des gesamten Prozessdatenabbildes des IPC (shared memory), dass dem Range-Objekt zugeordnet ist 

HRESULT Y200CLNT_API WMY200GetIPCEvent(WMY200RANGEHANDLE hRange,HANDLE* phEvent);
// Liefert ein Handle auf das Event-Objekt, dass immer dann gesetzt wird, wenn vom Y200-Treiber WinMOD-Daten
// in das Prozessdatenabbild des IPC (shared memory) geschrieben wurden.
// Das Handle muss mit ::CloseHandle(...) wieder frei gegeben werden!!!

HRESULT Y200CLNT_API WMY200SetEventWindow(WMY200RANGEHANDLE hRange, HANDLE hWnd, UINT nMsg);
// Fensterhandle und Message für die Benachrichtigung anmelden

HRESULT Y200CLNT_API WMY200SetNotifyEnable(WMY200RANGEHANDLE hRange, BOOL bNotify);
// Benachrichtigung durch das Range-Objekt aktivieren bzw. deaktivieren (default: aktiviert)

HRESULT Y200CLNT_API WMY200IsNotifyEnable(WMY200RANGEHANDLE hRange, BOOL *pbNotify);
// Ist Benachrichtigung aktiviert (default: TRUE==aktiviert)

HRESULT Y200CLNT_API WMY200SetWinMODEventNotify(WMY200RANGEHANDLE hRange, BOOL bNotify);
// Benachrichtigung durch WinMOD-Treiber Events aktivieren bzw. deaktivieren (default: aktiviert)

HRESULT Y200CLNT_API WMY200IsWinMODEventNotify(WMY200RANGEHANDLE hRange, BOOL *pbNotify);
// Ist die Benachrichtigung durch WinMOD-Treiber Events aktiviert (default: TRUE==aktiviert)

HRESULT Y200CLNT_API WMY200SetEventTimeout(WMY200RANGEHANDLE hRange, DWORD dwTimeout);
// setzen des Timeouts (ms) nachdem eine Benachrichtigung erfolgen soll (default: INFINITE)

HRESULT Y200CLNT_API WMY200GetEventTimeout(WMY200RANGEHANDLE hRange, DWORD *pdwTimeout);
// liefert den z.Zt. eingestellten EventTimeout in ms

HRESULT Y200CLNT_API WMY200SetMutexTimeout(WMY200RANGEHANDLE hRange, DWORD dwTimeout);
// setzen der max. Zeit, die beim Zugriff auf den shared memory gewartet wird (default: 100ms)

HRESULT Y200CLNT_API WMY200GetMutexTimeout(WMY200RANGEHANDLE hRange, DWORD *pdwTimeout);
// liefert den z.Zt. eingestellten MutexTimeout in ms

HRESULT Y200CLNT_API WMY200GetTickCount(WMY200RANGEHANDLE hRange, DWORD *pdwCount);
// liefert den aktuellen TickCount aus dem shared memory (MEM_Y200_MAP.dwWmTickCount)

HRESULT Y200CLNT_API WMY200GetCycleCount(WMY200RANGEHANDLE hRange, DWORD *pdwCount);
// liefert den aktuellen CycleCount aus dem shared memory (MEM_Y200_MAP.dwWmCyclCount)


/////////////////////////////////////////////////////////////////////////////
// Funktionen zum Lesen bzw. Schreiben zusammenhängender Blöcke
/////////////////////////////////////////////////////////////////////////////

// WMY200ReadBlock... liest Daten aus dem Prozessdatenabbild in ein in pDest zu übergebenden typisierten Array,
// dabei kann nur auf Daten innerhalb des angemeldeten Lesebereichs zugegriffen werden.
// hRange		- Handle auf das Range-Objekt
// pDest		- Zeiger auf ein Array entsprechenden Typs, das die gelesenen Daten zurückliefert
// uElemOffs	- Element-Offset relativ zum Anfang des Lesebereichs
// uElemCount	- Anzahl der zu lesenden Elemente

// WMY200WriteBlock... schreibt Daten aus dem in pSrc übergebenen Array in das Prozessdatenabbild,
// dabei kann nur auf Daten innerhalb des angemeldeten Schreibbereichs zugegriffen werden.
// hRange		- Handle auf das Range-Objekt
// pSrc			- Zeiger auf ein Array entsprechenden Typs, das die zu schreibenden Daten enthält
// uElemOffs	- Element-Offset relativ zum Anfang des Schreibbereichs
// uElemCount	- Anzahl der zu schreibenden Elemente

HRESULT Y200CLNT_API WMY200ReadBlock8(WMY200RANGEHANDLE hRange, BYTE* pDest, UINT uElemOffs, UINT uElemCount);
HRESULT Y200CLNT_API WMY200WriteBlock8(WMY200RANGEHANDLE hRange, const BYTE* pSrc, UINT uElemOffs, UINT uElemCount);
HRESULT Y200CLNT_API WMY200ReadBlock16(WMY200RANGEHANDLE hRange, WORD* pDest, UINT uElemOffs, UINT uElemCount);
HRESULT Y200CLNT_API WMY200WriteBlock16(WMY200RANGEHANDLE hRange, const WORD* pSrc, UINT uElemOffs, UINT uElemCount);
HRESULT Y200CLNT_API WMY200ReadBlock32(WMY200RANGEHANDLE hRange, DWORD* pDest, UINT uElemOffs, UINT uElemCount);
HRESULT Y200CLNT_API WMY200WriteBlock32(WMY200RANGEHANDLE hRange, const DWORD* pSrc, UINT uElemOffs, UINT uElemCount);
HRESULT Y200CLNT_API WMY200ReadBlockFloat(WMY200RANGEHANDLE hRange, float* pDest, UINT uElemOffs, UINT uElemCount);
HRESULT Y200CLNT_API WMY200WriteBlockFloat(WMY200RANGEHANDLE hRange, const float* pSrc, UINT uElemOffs, UINT uElemCount);


/////////////////////////////////////////////////////////////////////////////
// Funktionen zum Lesen bzw. Schreiben von Einzelwerten
/////////////////////////////////////////////////////////////////////////////

// WMY200Read... liest Daten aus dem Prozessdatenabbild in ein in pDest zu übergebenden Puffer,
// dabei kann nur auf Daten innerhalb des angemeldeten Lesebereichs zugegriffen werden.
// hRange		- Handle auf das Range-Objekt
// pDest		- Zeiger auf einen Puffer entsprechenden Typs, zur Rückgabe des gelesenen Wertes
// uElemOffs	- Element-Offset relativ zum Anfang des Lesebereichs

// WMY200Write... schreibt den in Src übergebenen Wert in das Prozessdatenabbild,
// dabei kann nur auf Daten innerhalb des angemeldeten Schreibbereichs zugegriffen werden.
// hRange		- Handle auf das Range-Objekt
// Value		- zu schreibender Wert
// uElemOffs	- Element-Offset relativ zum Anfang des Schreibbereichs

HRESULT Y200CLNT_API WMY200Read8(WMY200RANGEHANDLE hRange, BYTE* pDest, UINT uElemOffs);
HRESULT Y200CLNT_API WMY200Write8(WMY200RANGEHANDLE hRange, BYTE byValue, UINT uElemOffs);
HRESULT Y200CLNT_API WMY200Read16(WMY200RANGEHANDLE hRange, WORD* pDest, UINT uElemOffs);
HRESULT Y200CLNT_API WMY200Write16(WMY200RANGEHANDLE hRange, WORD wValue, UINT uElemOffs);
HRESULT Y200CLNT_API WMY200Read32(WMY200RANGEHANDLE hRange, DWORD* pDest, UINT uElemOffs);
HRESULT Y200CLNT_API WMY200Write32(WMY200RANGEHANDLE hRange, DWORD dwValue, UINT uElemOffs);
HRESULT Y200CLNT_API WMY200ReadFloat(WMY200RANGEHANDLE hRange, float* pDest, UINT uElemOffs);
HRESULT Y200CLNT_API WMY200WriteFloat(WMY200RANGEHANDLE hRange, float fltValue, UINT uElemOffs);

#ifdef __cplusplus
}
#endif

#endif // #if !defined(_Y200CLNT_INCLUDED_)