//-----------------------------------------------------------------------------
// File: Meshes.cpp
//
// Desc: For advanced geometry, most apps will prefer to load pre-authored
//       Meshes from a file. Fortunately, when using Meshes, D3DX does most of
//       the work for this, parsing a geometry file and creating vertx buffers
//       (and index buffers) for us. This tutorial shows how to use a D3DXMESH
//       object, including loading it from a file and rendering it. One thing
//       D3DX does not handle for us is the materials and textures for a mesh,
//       so note that we have to handle those manually.
//
//       Note: one advanced (but nice) feature that we don't show here is that
//       when cloning a mesh we can specify the FVF. So, regardless of how the
//       mesh was authored, we can add/remove normals, add more texture
//       coordinate sets (for multi-texturing), etc.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include "App/Mahjong.h"
#include "Table.h"
#include "JanpaiManager.h"
#include "Graphics.h"
#include "KeyInput.h"
#include "DebugFont.h"
//#include "Textures.h"
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <cassert>
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }
#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

Mahjong* pMahjong = NULL;


//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{	
//	FileMeshƒNƒ‰ƒX‚Å‰ð•úÏ‚Ý‚È‚Ì‚ÅŒÄ‚ñ‚Å‚Í‚¢‚¯‚È‚¢B
//	Textures::GetInstance()->DestroyTextures();

	DebugFont::GetInstance()->Terminate();

	KeyInput::GetInstance()->DestroyKeyInput();

	Graphics::GetInstance()->DestroyGraphicsDevice();

	Graphics::GetInstance()->DestroyGraphicsObject();

}


VOID Run()
{
	Graphics::GetInstance()->BeginScene();
	pMahjong->Update();
	pMahjong->Draw();
	Graphics::GetInstance()->EndScene();
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    UNREFERENCED_PARAMETER( hInst );

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        L"D3D Tutorial", NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"D3D Tutorial", L"D3D Tutorial 06: Meshes",
		WS_OVERLAPPEDWINDOW, 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
                              NULL, NULL, wc.hInstance, NULL );

	

    // Initialize Direct3D
	if (SUCCEEDED(Graphics::GetInstance()->InitGraphics(hWnd)))
    {
		if (SUCCEEDED(KeyInput::GetInstance()->InitKeyInput(hWnd))) {
			pMahjong = new Mahjong();
			assert(pMahjong != NULL);
            
			if (SUCCEEDED(DebugFont::GetInstance()->Initialize(2500, 1024))) {
				// Show the window
				ShowWindow(hWnd, SW_SHOWDEFAULT);
				UpdateWindow(hWnd);

				// Enter the message loop
				MSG msg;
				ZeroMemory(&msg, sizeof(msg));
				while (msg.message != WM_QUIT) {
					if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
					else Run();
				}
			}
			
			SAFE_DELETE(pMahjong);
		}
    }



    UnregisterClass( L"D3D Tutorial", wc.hInstance );
    return 0;
}



