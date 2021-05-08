#include "stdafx.h"
#include "Tetris.h"
#include "Tetris_Game.h"
#include <iostream>

HRESULT CTetris_Game::InitDeviceObjects()
{
	D3DXCreateTextureFromResource( m_pd3dDevice, NULL, MAKEINTRESOURCE(IDR_BLOCKS), &m_Texture_Block);
	D3DXCreateTextureFromResource( m_pd3dDevice, NULL, MAKEINTRESOURCE(IDR_BACKGROUND), &m_Texture_Background);
	D3DXCreateTextureFromResource( m_pd3dDevice, NULL, MAKEINTRESOURCE(IDR_SCORE), &m_Texture_Score);
	D3DXCreateTextureFromResource( m_pd3dDevice, NULL, MAKEINTRESOURCE(IDR_LEVEL), &m_Texture_Level);
	D3DXCreateTextureFromResource( m_pd3dDevice, NULL, MAKEINTRESOURCE(IDR_NFLOOR), &m_Texture_NFloor);
	D3DXCreateTextureFromResource( m_pd3dDevice, NULL, MAKEINTRESOURCE(IDR_GRAYBLOCK), &m_Texture_GrayBlock);
	D3DXCreateTextureFromResource( m_pd3dDevice, NULL, MAKEINTRESOURCE(IDR_GAMEPAUSED), &m_Texture_GamePaused);
	D3DXCreateTextureFromResource( m_pd3dDevice, NULL, MAKEINTRESOURCE(IDR_SUBTITLE), &m_Texture_Subtitle);
	D3DXCreateTextureFromResource( m_pd3dDevice, NULL, MAKEINTRESOURCE(IDR_CHANGEWHITE), &m_Texture_Changewhite);
	D3DXCreateTextureFromResource( m_pd3dDevice, NULL, MAKEINTRESOURCE(IDR_CRASH), &m_Texture_Crash);
	D3DXCreateTextureFromResource( m_pd3dDevice, NULL, MAKEINTRESOURCE(IDR_EXPLODE), &m_Texture_Explode);
    return S_OK;
}

HRESULT CTetris_Game::RestoreDeviceObjects()
{
	// Setup a material
	D3DUtil_InitMaterial( mtrl, 0.0f, 0.0f, 0.0f );
	mtrl.Emissive.r = 1.0f;
	mtrl.Emissive.g = 1.0f;
	mtrl.Emissive.b = 1.0f;
	m_pd3dDevice->SetMaterial( &mtrl );

	m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSW,  D3DSAMP_ADDRESSW );
	m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );

	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

	// Set up the textures
	m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,   TRUE );
	m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	// Set miscellaneous render states
	m_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE,   FALSE );
	m_pd3dDevice->SetRenderState( D3DRS_SPECULARENABLE, FALSE );
	m_pd3dDevice->SetRenderState( D3DRS_ZENABLE,		D3DZB_FALSE);

	D3DXMATRIX matOrtho; 
	D3DXMATRIX matIdentity;
	D3DXMATRIX matworld;

	//Setup the orthogonal projection matrix and the default world/view matrix
	D3DXMatrixOrthoLH(&matOrtho, (float)BG_WIDTH, (float)BG_HEIGHT, 0.0f, 1.0f);
	D3DXMatrixIdentity(&matIdentity);
	D3DXMatrixRotationX(&matworld, -PI);
	matworld._41=-BG_WIDTH/2;	matworld._42=BG_HEIGHT/2;
	m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matOrtho);
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matworld);
	m_pd3dDevice->SetTransform(D3DTS_VIEW, &matIdentity);

	m_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );

	return S_OK;
}

void CTetris_Game::SetTextureRect(RECT3D& rect3d, float left, float top, float right, float bottom, int cx, int cy, BOOL CCW)
{
	if(CCW)
	{
		rect3d.point[0].tu = left;
		rect3d.point[0].tv = top;
		rect3d.point[1].tu = left;
		rect3d.point[1].tv = bottom;
		rect3d.point[2].tu = right;
		rect3d.point[2].tv = top;
		rect3d.point[3].tu = right;
		rect3d.point[3].tv = bottom;
	}
	else
	{
		rect3d.point[0].tu = left;
		rect3d.point[0].tv = top;
		rect3d.point[2].tu = left;
		rect3d.point[2].tv = bottom;
		rect3d.point[1].tu = right;
		rect3d.point[1].tv = top;
		rect3d.point[3].tu = right;
		rect3d.point[3].tv = bottom;
	}
	rect3d.width=cx;
	rect3d.height=cy;
}

HRESULT CTetris_Game::DeleteDeviceObjects()
{
	SAFE_RELEASE(m_Texture_Block);
	SAFE_RELEASE(m_Texture_Background);
	SAFE_RELEASE(m_Texture_Score);
	SAFE_RELEASE(m_Texture_Level);
	SAFE_RELEASE(m_Texture_NFloor);
	SAFE_RELEASE(m_Texture_GrayBlock);
	SAFE_RELEASE(m_Texture_GamePaused);
	SAFE_RELEASE(m_Texture_Subtitle);
	SAFE_RELEASE(m_Texture_Changewhite);
	SAFE_RELEASE(m_Texture_Crash);
 	SAFE_RELEASE(m_Texture_Explode);
	return S_OK;
}

void CTetris_Game::Blt3D( DWORD x, DWORD y, LPDIRECT3DTEXTURE9 pTexture, RECT3D* prc)
{
	prc->point[0].position = D3DXVECTOR3((float)x, (float)y, 0.0f );
	prc->point[1].position = D3DXVECTOR3((float)x, (float)y+prc->height, 0.0f );
	prc->point[2].position = D3DXVECTOR3((float)x+prc->width, (float)y, 0.0f );
	prc->point[3].position = D3DXVECTOR3((float)x+prc->width, (float)y+prc->height, 0.0f );
	m_pd3dDevice->SetTexture(0, pTexture);
	m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, prc->point, sizeof(CUSTOMVERTEX));

}

void CTetris_Game::Blt3D(DWORD x, DWORD y, LPDIRECT3DTEXTURE9 pTexture, int width, int height)
{
	RECT3D rect3d;
	rect3d.point[0].tu = 0.0f;
	rect3d.point[0].tv = 0.0f;
	rect3d.point[1].tu = 0.0f;
	rect3d.point[1].tv = 1.0f;
	rect3d.point[2].tu = 1.0f;
	rect3d.point[2].tv = 0.0f;
	rect3d.point[3].tu = 1.0f;
	rect3d.point[3].tv = 1.0f;
	rect3d.width=width;
	rect3d.height=height;
	Blt3D(x, y, pTexture, &rect3d);
}

HRESULT CTetris_Game::Render()
{
	m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET, 0x00000000, 1.0f, 0L );
	
    //if( FAILED( m_pd3dDevice->TestCooperativeLevel() ) )
    //    ForceWindowed();
	float width = DXUTGetWindowWidth();
	float height = DXUTGetWindowHeight();

	float ratio = (float)BG_HEIGHT / BG_WIDTH;
	float ratio2 = height / width;
	if (ratio2 > ratio)
	{
		width = BG_WIDTH;
		height = BG_WIDTH * ratio2;
	}
	else
	{
		width = BG_HEIGHT / ratio2;
		height = BG_HEIGHT;
	}
	D3DXMATRIX matOrtho, matworld;
	D3DXMatrixOrthoLH(&matOrtho, (float)width, (float)height, 0.0f, 1.0f);
	m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matOrtho);

	// Begin the scene
	if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
	{
		if(m_bWindowRendering[0]||m_bWindowRendering[1])
		{
			if(m_bIsPaused)
			{
				Display();
				Blt3D((BG_WIDTH-GAMEPAUSED_WIDTH)/2, (BG_HEIGHT-GAMEPAUSED_HEIGHT)/2, m_Texture_GamePaused, GAMEPAUSED_WIDTH, GAMEPAUSED_HEIGHT);
			}
			else
				Display();
		}
		else
			Blt3D(0, 0, m_Texture_Background, BG_WIDTH, BG_HEIGHT);

//		Blt3D(0, 0, m_Texture_GrayBlock, BG_WIDTH, BG_HEIGHT);
		m_pd3dDevice->EndScene();// End the scene.
	}
	//RECT rect = DXUTGetWindowClientRect();
	//if (!DXUTIsWindowed())
	//{
	//	//D3DVIEWPORT9 vp;
	//	//m_pd3dDevice->GetViewport(&vp);
	//	//rect.right = vp.Width;
	//	//rect.bottom = vp.Height;
	//}
	//float ratio = (float)BG_HEIGHT / BG_WIDTH;
	//if ((float)rect.bottom / rect.right > ratio)
	//{
	//	int cliph = (rect.bottom - (int)(rect.right * ratio)) / 2;
	//	rect.top += cliph;
	//	rect.bottom -= cliph;
	//}
	//else
	//{
	//	int clipw = (rect.right - (int)(rect.bottom / ratio)) / 2;
	//	rect.left += clipw;
	//	rect.right -= clipw;
	//}

	m_pd3dDevice->Present( NULL, NULL, NULL, NULL );
	return S_OK;
}

void CTetris_Game::Destroy()
{
	DXUTShutdown();
	FreeDirectInput();
	//Cleanup3DEnvironment();
}
