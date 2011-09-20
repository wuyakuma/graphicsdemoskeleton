////////////////////////////////////////////////////////////////////////
//
// Skeleton Intro Coding
//
// by Wolfgang Engel 
// Last time modified: 09/20/2011 (started sometime in 2003 or maybe much longer ago)
//
///////////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#define DEFINE_GUIDW(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) const GUID DECLSPEC_SELECTANY name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
DEFINE_GUIDW(IID_ID3D10Texture2D,0x9B7E4C04,0x342C,0x4106,0xA1,0x9F,0x4F,0x27,0x04,0xF6,0x89,0xF0);

#include <d3d10.h>

// define the size of the window
#define WINWIDTH 800 
#define WINHEIGHT 600
#define WINPOSX 200 
#define WINPOSY 200

// makes the applicaton behave well with windows
// allows to remove some system calls to reduce size
#define WELLBEHAVIOUR

// this is a simplified entry point ...
void __stdcall WinMainCRTStartup()
{
    ExitProcess(WinMain(GetModuleHandle(NULL), NULL, NULL, 0));
}

// this is the main windows entry point ... 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// D3D 10 device variables
	// Global Variables:
	ID3D10Device *pd3dDevice;
	IDXGISwapChain *pSwapChain;
	ID3D10RenderTargetView *pRenderTargetView;

	// timer global variables
	DWORD		StartTime;
	DWORD		CurrentTime;

	// keep track if the game loop is still running
	BOOL		BRunning;

	// the most simple window
	HWND hWnd = CreateWindowEx(WS_EX_TOPMOST, 
								"EDIT", 
								0, 
								WS_POPUP | WS_VISIBLE, 
								WINPOSX, WINPOSY, 
								WINWIDTH, WINHEIGHT, 
								0, 0, 0, 0);


	// don't show the cursor
	ShowCursor(FALSE);

	const static DXGI_SWAP_CHAIN_DESC sd = {{WINWIDTH, WINHEIGHT, {60, 1}, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 0}, {1, 0}, DXGI_USAGE_RENDER_TARGET_OUTPUT, 1, NULL, TRUE, DXGI_SWAP_EFFECT_SEQUENTIAL, 0};
	
	//
	DXGI_SWAP_CHAIN_DESC temp = sd;
	temp.OutputWindow = hWnd;

 	D3D10CreateDeviceAndSwapChain(NULL,
			D3D10_DRIVER_TYPE_HARDWARE,
			NULL, D3D10_CREATE_DEVICE_DEBUG,
			D3D10_SDK_VERSION,
			(DXGI_SWAP_CHAIN_DESC*)&temp,
			&pSwapChain,
			&pd3dDevice);


	// Create a back buffer render target, get a view on it to clear it later
	ID3D10Texture2D *pBackBuffer;
	pSwapChain->lpVtbl->GetBuffer( pSwapChain, 0, (REFIID ) &IID_ID3D10Texture2D, (LPVOID*)&(pBackBuffer) ) ;
	pd3dDevice->lpVtbl->CreateRenderTargetView( pd3dDevice, (struct ID3D10Resource *)pBackBuffer, NULL, &pRenderTargetView );
	pd3dDevice->lpVtbl->OMSetRenderTargets( pd3dDevice, 1, &pRenderTargetView, NULL );

	const static D3D10_VIEWPORT vp = {0, 0, WINWIDTH, WINHEIGHT, 0, 1}; 
	pd3dDevice->lpVtbl->RSSetViewports( pd3dDevice, 1, &vp );

	// setup timer 
	StartTime = GetTickCount();
	CurrentTime = 0;	

	// set the game loop to running by default
	BRunning = TRUE;
	MSG msg;

	while (BRunning)
	{
#if defined(WELLBEHAVIOUR)
		// Just remove the message
		PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE);
#endif
		// Calculate the current demo time
		CurrentTime = GetTickCount() - StartTime;

		// go out of game loop and shutdown
		if (CurrentTime > 3300 || GetAsyncKeyState(VK_ESCAPE)) 
			BRunning = FALSE;

   		static const float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
		pd3dDevice->lpVtbl->ClearRenderTargetView(pd3dDevice, pRenderTargetView, ClearColor );

		// 
		pSwapChain->lpVtbl->Present( pSwapChain, 0, 0 );
	}

	// release all D3D device related resources
#if defined(WELLBEHAVIOUR)
	    pd3dDevice->lpVtbl->ClearState(pd3dDevice);
	    pd3dDevice->lpVtbl->Release(pd3dDevice);
	    pRenderTargetView->lpVtbl->Release(pRenderTargetView);
	    pSwapChain->lpVtbl->Release(pSwapChain);	 
	    pBackBuffer->lpVtbl->Release(pBackBuffer);	
#endif

    return (int) msg.wParam;
}
