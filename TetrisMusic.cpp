#include "stdafx.h"
#include "Tetris.h"
#include "Tetrismusic.h"

CMusicManager*			g_pMusicManager = NULL;
CMusicSegment*          g_pSound[MAX_SOUND]		={NULL};	//在tetris_game类中进行初始化NULL
CMusicSegment*          g_pMusic[MAX_MUSIC]		={NULL};
IDirectMusicAudioPath*  g_p3DAudiopath           = NULL;
 
HRESULT InitDirectMusic( HWND hwnd )
{
	HRESULT hr; 

	g_pMusicManager = new CMusicManager();

	if( FAILED( hr = g_pMusicManager->Initialize( hwnd ) ) )
		return DXTRACE_ERR( TEXT("Initialize"), hr );

	// Create a 3D Audiopath. This creates a synth port that feeds a 3d buffer.
	// We can then play all segments into this buffer and directly control its
	// 3D parameters.
	IDirectMusicPerformance8* pPerformance = g_pMusicManager->GetPerformance();
	if( FAILED( hr = pPerformance->CreateStandardAudioPath( DMUS_APATH_DYNAMIC_3D, 128, 
															TRUE, &g_p3DAudiopath ) ) )
		return DXTRACE_ERR( TEXT("CreateStandardAudioPath"), hr );

	// Create the segments from resource
    for( int i=0; i<MAX_SOUND; i++ )
		g_pMusicManager->CreateSegmentFromResource(g_pSound+i, MAKEINTRESOURCE(IDR_WAVE_BOTTOM+i), _T("WAVE"));

    for(int i=0; i<MAX_MUSIC; i++ )
	{
		g_pMusicManager->CreateSegmentFromResource(g_pMusic+i, MAKEINTRESOURCE(IDR_MIDI_LEVEL00+i), _T("MIDI"));
		g_pMusic[i]->SetRepeats(DMUS_SEG_REPEAT_INFINITE);
	}

	// Get the listener from the in the Audiopath.
	IDirectSound3DListener* pDSListener = NULL;
	if( FAILED( hr = g_p3DAudiopath->GetObjectInPath( 0, DMUS_PATH_PRIMARY_BUFFER, 0,
													  GUID_NULL, 0, IID_IDirectSound3DListener, 
													  (LPVOID*) &pDSListener ) ) )
		return DXTRACE_ERR( TEXT("GetObjectInPath"), hr );

	// Set a new rolloff factor (1.0f is default)
	if( FAILED( hr = pDSListener->SetRolloffFactor( 0.25f, DS3D_IMMEDIATE ) ) )
		return DXTRACE_ERR( TEXT("SetRolloffFactor"), hr );       

	// Release the listener since we are done with it.
	SAFE_RELEASE( pDSListener );

	return S_OK;
}

VOID    FreeDirectMusic()
{
    SAFE_RELEASE( g_p3DAudiopath );

    for( int i=0; i<MAX_SOUND; i++ )
        SAFE_DELETE( g_pSound[i] );

    for( int i=0; i<MAX_MUSIC; i++ )
        SAFE_DELETE( g_pMusic[i] );

    SAFE_DELETE( g_pMusicManager );
}
