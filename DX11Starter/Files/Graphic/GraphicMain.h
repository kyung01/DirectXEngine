#pragma once
#include <map>
#include "Model.h"
#include "Shader.h"
#include "Camera.h"

#include "SimpleShader.h"
#include "RenderTexture.h"
#include "DepthTexture.h"
#include "Graphic\Scene\Light.h"
#include <list>
#include <map>
#include <memory>
#include <d3d11.h>

#include <SimpleMath.h>
#include <WICTextureLoader.h>
#include <Graphic\Asset\Asset.h>
#include <Graphic\Asset\Mesh.h>// TODO delete this
#include <Graphic\Enum.h>
#include <Graphic\RenderStateStack.h>
#include <Graphic\Buffer\KDynamicBuffer.h>
#include <Graphic\Buffer\LightParameter.h>
#include <Game\Context.h>

#include <Graphic\Scene\Scene.h>


namespace NGraphic {
	
	//TODO hlsl files are stroed in debug folder once they are built with extention .cso You need grasp them
	struct LightInfo{
		std::shared_ptr<RenderTexture>	position;
		std::shared_ptr<DepthTexture>	depth;
	};

	class GraphicMain {
	private:
		static float RATIO_LIGHT_INNER;
		int m_width, m_height;
		DirectX::XMMATRIX	orthoView, orthoMVP;
		RenderStateStack	m_renderStackStack;
		RenderTexture		m_renderTextureDummy;
		DepthTexture		m_depthTextureDummy;
		int					m_rsm_flux_eye_perspective_width, 
							m_rsm_flux_eye_perspective_height;
	
		std::shared_ptr<NBuffer::KDynamicBuffer<NBuffer::LightParameter>> m_lightBuffer;


		DirectX::XMMATRIX getOrthogonalMatrixProj();
		DirectX::XMMATRIX getOrthogonalMatrixView();
		void rendering(NScene::Scene scene);
		void processObject(NScene::Object obj);

		LightInfo getLightInfo(ID3D11Device *device);
		bool initTextures		(ID3D11Device* device, ID3D11DeviceContext *context, int width, int height, int textureIndirectLightWidth, int textureIndirectLightHeight);
		
		
	protected:
		//glm::mat4 matProjection, matView, matModel;
		void processCamera(NScene::Camera cam);// = 0;
		void beginRendering(ID3D11DeviceContext *context);// = 0;
		void endRendering(ID3D11DeviceContext *context);// = 0;
		void getScreenWidth(int &w, int &h);// = 0;

		
	public:
		Frustum				m_frustum;


		std::map<int, LightInfo> m_lightInfos;
		std::map<KEnum, std::shared_ptr<RenderTexture>>	m_renderTextures;
		std::map<KEnum, std::shared_ptr<DepthTexture>>	m_depthTextures;

		std::map<int, Shader*> shaders;
		// Width and hieght is for the resolution in wihich this graphic main will adjust to render things onto
		GraphicMain();
		bool init(ID3D11Device *device, ID3D11DeviceContext *context, int textureWidth, int textureHeight, int textureIndirectLightWidth, int textureIndirectLightHeight);
		void update(ID3D11Device * device, ID3D11DeviceContext * context, float deltaTime, float totalTime, NScene::Scene & scene);
		

		

		void render(
			ID3D11Device * device, ID3D11DeviceContext * context,
			ID3D11RenderTargetView * target, ID3D11DepthStencilView * targetDepth, D3D11_VIEWPORT & viewport,
			Asset& asset, NGame::Context &game);
		
	
	};
}
/*
Implement the following function later 
void renderSkyboxReflection(
ID3D11Device * device, ID3D11DeviceContext *context,
RenderTexture& renderTexture, DepthTexture& depthTexture,
Asset& asset,
Vector3 eyePos,
ID3D11ShaderResourceView *skybox, ID3D11ShaderResourceView * worldPos, ID3D11ShaderResourceView * normalTexture);


void NGraphic::GraphicMain::renderSkyboxReflection(
ID3D11Device * device, ID3D11DeviceContext * context, RenderTexture & renderTexture, DepthTexture & depthTexture,
Asset & asset,
Vector3 eyePos,
ID3D11ShaderResourceView *skybox, ID3D11ShaderResourceView * worldPos, ID3D11ShaderResourceView * normalTexture)
{
beginRendering(context);

context->OMSetBlendState(asset.BLEND_STATE_TRANSPARENT, 0, 0xffffffff);

DirectX::XMFLOAT4X4 matrixStore;
NGraphic::Mesh& mesh = *asset.m_meshes[MESH_ID_PLANE];
SimpleVertexShader&		shaderVert = *asset.m_shadersVert[RENDER_SKYBOX_REFLECTION];
SimpleFragmentShader&	shaderFrag = *asset.m_shadersFrag[RENDER_SKYBOX_REFLECTION];

renderTexture.setRenderTarget(context, depthTexture.getDepthStencilView());

DirectX::XMStoreFloat4x4(&matrixStore, XMMatrixTranspose(orthoMVP)); // Transpose for HLSL!
shaderVert.SetMatrix4x4("matMVP", matrixStore);

shaderFrag.SetSamplerState("samplerBoarderZero", asset.m_samplers[SAMPLER_ID_BORDER_ZERO]);
shaderFrag.SetShaderResourceView("textureSky", skybox);
shaderFrag.SetShaderResourceView("textureWorld", worldPos);
shaderFrag.SetShaderResourceView("textureNormal", normalTexture);
shaderFrag.SetFloat3("eyePos", eyePos);

shaderVert.SetShader();
shaderFrag.SetShader();
shaderVert.CopyAllBufferData();
shaderFrag.CopyAllBufferData();

UINT stride = sizeof(Vertex);
UINT offset = 0;
context->IASetVertexBuffers(0, 1, &mesh.getBufferVertexRef(), &stride, &offset);
context->IASetIndexBuffer(mesh.getBufferIndex(), DXGI_FORMAT_R32_UINT, 0);
context->DrawIndexed(
mesh.getBufferIndexCount(),     // The number of indices to use (we could draw a subset if we wanted)
0,     // Offset to the first index we want to use
0);    // Offset to add to each index when looking up vertices

//clean up bindings
shaderFrag.SetShaderResourceView("textureFrustumFront", 0);
shaderFrag.SetShaderResourceView("textureFrustumBack", 0);
shaderFrag.SetShaderResourceView("textureShadow", 0);
shaderFrag.SetShaderResourceView("textureWorld", 0);

endRendering(context);
}

*/