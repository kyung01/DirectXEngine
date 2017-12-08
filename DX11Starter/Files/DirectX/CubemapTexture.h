/*
Original Filename: rendertextureclass.h
from http://www.rastertek.com/dx11tut22.html
modified for my personal usage 
*/

#pragma once

#include <d3d11.h>

namespace NDirectX {
	class CubemapTexture
	{
	private:
		void init();

		bool m_isInitialized;
		int m_width, m_height;
		D3D11_VIEWPORT viewport;
		ID3D11RenderTargetView** m_renderTargetViews; // 6 rendertargetview
		ID3D11ShaderResourceView* m_shaderResourceView;
		ID3D11Texture2D* m_renderTargetTexture;
	public:
		CubemapTexture();
		CubemapTexture(const CubemapTexture&);
		~CubemapTexture();

		//bool init(ID3D11Device*, IDXGISwapChain* chain, int, int);
		//bool init(ID3D11Device*, int, int);
		bool initCube(ID3D11Device*, int, int, void* data = 0);
		//bool initCubeArray(ID3D11Device*, int, int, int, void* data = 0);
		void release();

		//void setRenderTarget(ID3D11DeviceContext*, ID3D11DepthStencilView*);
		void clear(ID3D11DeviceContext*, float, float, float, float);
		ID3D11Texture2D* getShaderResource();
		ID3D11ShaderResourceView* getShaderResourceView();
		ID3D11RenderTargetView *& getRenderTargetView(int index);

		int getWidth();
		int getHeight();
		//void setViewport(D3D11_VIEWPORT viewport);
		//void setRenderTargetView(ID3D11RenderTargetView* view, D3D11_VIEWPORT& viewport);
		D3D11_VIEWPORT getViewport();
	};


}
