#include <Engine\Systems\RenderSystem.h>
using namespace KEngine;
using namespace KEngine::KSystem;
void RenderSystem::setMatrix(ISimpleShader * shader, std::string name, DirectX::XMMATRIX matrix) {

	DirectX::XMStoreFloat4x4(&matTemp, XMMatrixTranspose(matrix));
	shader->SetMatrix4x4(name, matTemp);
}

void RenderSystem::setRenderTarget(
	ID3D11DeviceContext* deviceContext,
	ID3D11RenderTargetView *renderTargetView, ID3D11DepthStencilView* depthStencilView, D3D11_VIEWPORT & viewport)
{
	// Bind the render target view and depth stencil buffer to the output render pipeline.
	deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
	deviceContext->RSSetViewports(1, &viewport);
}
void RenderSystem::renderMesh(ID3D11DeviceContext * context, Mesh & mesh, UINT offsetBegin, UINT stride)
{
	context->IASetVertexBuffers(0, 1, &mesh.getBufferVertexRef(), &stride, &offsetBegin);
	context->IASetIndexBuffer(mesh.getBufferIndex(), DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(mesh.getBufferIndexCount(), 0, 0);
}

void RenderSystem::render(
	ID3D11Device * device, ID3D11DeviceContext * context,
	ID3D11RenderTargetView *renderTargetView, ID3D11DepthStencilView* depthStencilView, D3D11_VIEWPORT & viewport,
	ID3D11RasterizerState *cullBackFace,
	SimpleVertexShader & vertexShader, SimpleFragmentShader & fragmentShader,
	std::map<KEnum, Mesh> &meshes
)
{
	float colorClean[4] = {0.1f,0.1f,0.1f,1};
	context->ClearRenderTargetView(renderTargetView, colorClean);
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	context->RSSetState(cullBackFace);
	setRenderTarget(context, renderTargetView, depthStencilView, viewport);
	vertexShader.SetShader();
	fragmentShader.SetShader();
	setMatrix(&vertexShader, "view", m_camera.getViewMatrix());
	setMatrix(&vertexShader, "proj", m_camera.getProjMatrix());
	for (auto it = m_components.begin(); it != m_components.end(); it++) {

		Mesh& mesh = meshes.find(it->meshId)->second;
		//create model matrix
		setMatrix(&vertexShader, "world", it->getWorldMatrix());
		vertexShader.CopyAllBufferData();
		fragmentShader.CopyAllBufferData();
		UINT stride = sizeof(Vertex); 
		UINT offset = 0; 
		context->IASetVertexBuffers(0, 1, &mesh.getBufferVertexRef(), &stride, &offset); 
		context->IASetIndexBuffer(mesh.getBufferIndex(), DXGI_FORMAT_R32_UINT, 0); 
		context->DrawIndexed(mesh.getBufferIndexCount(), 0, 				0); 
		//std::cout << "RENDERING AT " << it->getPosition().x << " , " << it->getPosition().y << " , " << it->getPosition().z << "\n";
		//send the new world matrix information
										//renderMesh(context, mesh, 0, sizeof(Vertex));
	}

}

void RenderSystem::addEntity(KEngine::Entity &entity) {
	m_components.resize(m_components.size() + 1);
	Renderable& renderable = m_components[m_components.size() - 1];
	//link
	renderable.m_entity = &entity;
	entity.m_renderable = &renderable;
}
void RenderSystem::update(float time)
{
	Vector3 dirForward = m_camera.getLookDir();
	Vector3 dirRight = Vector3(0, 1, 0).Cross( dirForward );
	Vector3 moveDir;
	if (GetAsyncKeyState('W'))
	{
		moveDir += dirForward;
	}
	if (GetAsyncKeyState('S'))
	{
		moveDir -= dirForward;
	}
	if (GetAsyncKeyState('D'))
	{
		moveDir += dirRight;
	}
	if (GetAsyncKeyState('A'))
	{
		moveDir -= dirRight;
	}
	moveDir.Normalize();
	m_camera.setPosition(m_camera.getPosition() + moveDir * time );
	std::cout << m_camera.getPosition().x << " , " << m_camera.getPosition().y << " , " << m_camera.getPosition().z << "\n";
	//pri
}
Renderable & RenderSystem::getComponent(int n)
{
	return m_components[n];
}

/*



*/