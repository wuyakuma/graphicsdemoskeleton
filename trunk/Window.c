////////////////////////////////////////////////////////////////////////
//
// Skeleton Intro Coding
//
// by Wolfgang Engel 
// Last time modified: 02/04/2007
//
///////////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <sal.h>
#include <rpcsal.h>

//#define __VISUALSTUDIO 


// name the GUID's here ... otherwise with INITGUID you will have all the GUID's in the constant table

//#ifndef __VISUALSTUDIO
//#define DECLSPEC_SELECTANY 
//#endif

#define DEFINE_GUIDW(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) EXTERN_C const GUID DECLSPEC_SELECTANY name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
DEFINE_GUIDW(IID_ID3D10Texture2D,0x9B7E4C04,0x342C,0x4106,0xA1,0x9F,0x4F,0x27,0x04,0xF6,0x89,0xF0);

#include <d3d10.h>

// define the size of the window
#define WINWIDTH 800 
#define WINHEIGHT 600


// makes the applicaton behave well with windows
// allows to remove some system calls to reduce size
#define WELLBEHAVIOUR

// D3D 10 device variables
// Global Variables:
ID3D10Device *g_pd3dDevice;
IDXGISwapChain *g_pSwapChain ;
ID3D10RenderTargetView *g_pRenderTargetView ;

// timer global variables
DWORD		g_StartTime;
DWORD		g_CurrentTime;

// keep track if the game loop is still running
BOOL		g_BRunning;

// this is a simplified entry point ...
void __cdecl WinMainCRTStartup()
{
    ExitProcess(WinMain(GetModuleHandle(NULL), NULL, NULL, 0));
}

// this is the main windows entry point ... the assembly version is in crt0gui.asm
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// the most simple window
	HWND hWnd = CreateWindowEx(WS_EX_TOPMOST, 
								"STATIC", 
								0, 
								WS_POPUP | WS_VISIBLE, 
								0, 0, 
								WINWIDTH, WINHEIGHT, 
								0, 0, 0, 0);

	// don't show the cursor
	ShowCursor(FALSE);

    DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferCount = 1;
	sd.BufferDesc.Width = WINWIDTH;
	sd.BufferDesc.Height = WINHEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	// full-screen or not
	sd.Windowed = TRUE;
 
	D3D10CreateDeviceAndSwapChain( NULL, 
									D3D10_DRIVER_TYPE_HARDWARE, 
									NULL,
									D3D10_CREATE_DEVICE_DEBUG ,
									D3D10_SDK_VERSION, 
									&sd,
									&g_pSwapChain,
									&g_pd3dDevice );


	// Create a render target view
	ID3D10Texture2D *pBackBuffer;
	g_pSwapChain->lpVtbl->GetBuffer( g_pSwapChain, 0, (REFIID ) &IID_ID3D10Texture2D, (LPVOID*)&(pBackBuffer) ) ;
	
	g_pd3dDevice->lpVtbl->CreateRenderTargetView( g_pd3dDevice, (struct ID3D10Resource *)pBackBuffer, NULL, &g_pRenderTargetView );
	
	g_pd3dDevice->lpVtbl->OMSetRenderTargets( g_pd3dDevice, 1, &g_pRenderTargetView, NULL );

	// Setup the viewport
	D3D10_VIEWPORT vp;
	vp.Width = WINWIDTH;
	vp.Height = WINHEIGHT;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pd3dDevice->lpVtbl->RSSetViewports( g_pd3dDevice, 1, &vp );

	// setup timer 
	g_StartTime = GetTickCount();
	g_CurrentTime = 0;	

	// set the game loop to running by default
	g_BRunning = TRUE;
	MSG msg;

	while (g_BRunning)
	{
#if defined(WELLBEHAVIOUR)
		// Just remove the message
		PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE);
#endif
		// Calculate the current demo time
		g_CurrentTime = GetTickCount() - g_StartTime;

		// go out of game loop and shutdown
		if (g_CurrentTime > 1300) 
			g_BRunning = FALSE;

   		float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
		g_pd3dDevice->lpVtbl->ClearRenderTargetView(g_pd3dDevice, g_pRenderTargetView, ClearColor );

		g_pSwapChain->lpVtbl->Present( g_pSwapChain, 0, 0 );
	}

	// release all D3D device related resources
#if defined(WELLBEHAVIOUR)
	    if( g_pd3dDevice ) g_pd3dDevice->lpVtbl->ClearState(g_pd3dDevice);
	    if( g_pd3dDevice ) g_pd3dDevice->lpVtbl->Release(g_pd3dDevice);
	    if( g_pRenderTargetView ) g_pRenderTargetView->lpVtbl->Release(g_pRenderTargetView);
	    if( g_pSwapChain ) g_pSwapChain->lpVtbl->Release(g_pSwapChain);	 
	    if( pBackBuffer ) pBackBuffer->lpVtbl->Release(pBackBuffer);	
#endif

    return (int) msg.wParam;
}
