#include "stdafx.h"
#include "Tetrisinput.h"


LPDIRECTINPUT8       g_pDI       = NULL;         
LPDIRECTINPUTDEVICE8 g_pKeyboard = NULL;   
 

VOID AccquireInput() {
    if (g_pKeyboard)
        g_pKeyboard->Acquire();
}

VOID UnaccquireInput() {
    if (g_pKeyboard)
        g_pKeyboard->Unacquire();
}

VOID FreeDirectInput()
{
    if( g_pKeyboard ) 
        g_pKeyboard->Unacquire();
    
    SAFE_RELEASE( g_pKeyboard );
    SAFE_RELEASE( g_pDI );
}

HRESULT InitDirectInput( HWND hwnd )
{
    HRESULT hr;
    BOOL    bExclusive;
    BOOL    bForeground;
    BOOL    bImmediate;

    DWORD   dwCoopFlags;

    FreeDirectInput();

    bExclusive         = FALSE;
    bForeground        = FALSE;
    bImmediate         = FALSE;

    if( bExclusive )
        dwCoopFlags = DISCL_EXCLUSIVE;
    else
        dwCoopFlags = DISCL_NONEXCLUSIVE;

    if( bForeground )
        dwCoopFlags |= DISCL_FOREGROUND;
    else
        dwCoopFlags |= DISCL_BACKGROUND;
    if( FAILED( hr = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
                                         IID_IDirectInput8, (VOID**)&g_pDI, NULL ) ) )
        return hr;
    
    if( FAILED( hr = g_pDI->CreateDevice( GUID_SysKeyboard, &g_pKeyboard, NULL ) ) )
        return hr;
    
    if( FAILED( hr = g_pKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
        return hr;
    
    hr = g_pKeyboard->SetCooperativeLevel( hwnd, dwCoopFlags );
    if( hr == DIERR_UNSUPPORTED && !bForeground && bExclusive )
    {
        FreeDirectInput();
        MessageBox( hwnd, _T("SetCooperativeLevel() returned DIERR_UNSUPPORTED.\n")
                          _T("For security reasons, background exclusive keyboard\n")
                          _T("access is not allowed."), _T("Keyboard"), MB_OK );
        return S_OK;
    }

    if( FAILED(hr) )
        return hr;

    if( !bImmediate )
    {
        DIPROPDWORD dipdw;

        dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
        dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
        dipdw.diph.dwObj        = 0;
        dipdw.diph.dwHow        = DIPH_DEVICE;
        dipdw.dwData            = DINPUT_BUFFER_SIZE; // Arbitary buffer size

        if( FAILED( hr = g_pKeyboard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) )
            return hr;
    }

    g_pKeyboard->Acquire();


    return S_OK;
}

HRESULT ReadBufferedData(DIDEVICEOBJECTDATA *didod, DWORD& dwElements)
{
    HRESULT            hr;

    if( NULL == g_pKeyboard ) 
        return S_OK;
    
    dwElements = DINPUT_BUFFER_SIZE;
    hr = g_pKeyboard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA),
                                     didod, &dwElements, 0 );
    if( hr != DI_OK ) 
    {
        hr = g_pKeyboard->Acquire();
        while( hr == DIERR_INPUTLOST ) 
            hr = g_pKeyboard->Acquire();

        return S_OK; 
    }

    return S_OK;
}
