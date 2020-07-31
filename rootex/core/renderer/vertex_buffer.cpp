#include "vertex_buffer.h"

#include "rendering_device.h"

VertexBuffer::VertexBuffer(const Vector<VertexData>& buffer)
    : m_Stride(sizeof(VertexData))
    , m_Count(buffer.size())
{
	D3D11_BUFFER_DESC vbd = { 0 };
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0u;
	vbd.ByteWidth = sizeof(VertexData) * buffer.size();
	vbd.StructureByteStride = sizeof(VertexData);
	D3D11_SUBRESOURCE_DATA vsd = { 0 };
	vsd.pSysMem = buffer.data();
	
	const UINT offset = 0u;
	m_VertexBuffer = RenderingDevice::GetSingleton()->createVertexBuffer(&vbd, &vsd, &m_Stride, &offset);
}

VertexBuffer::VertexBuffer(const Vector<UIVertexData>& buffer)
    : m_Stride(sizeof(UIVertexData))
    , m_Count(buffer.size())
{
	D3D11_BUFFER_DESC vbd = { 0 };
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0u;
	vbd.ByteWidth = sizeof(UIVertexData) * buffer.size();
	vbd.StructureByteStride = sizeof(UIVertexData);
	D3D11_SUBRESOURCE_DATA vsd = { 0 };
	vsd.pSysMem = buffer.data();

	const UINT offset = 0u;
	m_VertexBuffer = RenderingDevice::GetSingleton()->createVertexBuffer(&vbd, &vsd, &m_Stride, &offset);
}

VertexBuffer::VertexBuffer(const Vector<AnimatedVertexData>& buffer)
    : m_Stride(sizeof(AnimatedVertexData))
    , m_Count(buffer.size())
{
	D3D11_BUFFER_DESC vbd = { 0 };
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0u;
	vbd.ByteWidth = sizeof(AnimatedVertexData) * buffer.size();
	vbd.StructureByteStride = sizeof(AnimatedVertexData);
	D3D11_SUBRESOURCE_DATA vsd = { 0 };
	vsd.pSysMem = buffer.data();

	const UINT offset = 0u;
	m_VertexBuffer = RenderingDevice::GetSingleton()->createVertexBuffer(&vbd, &vsd, &m_Stride, &offset);
}

VertexBuffer::VertexBuffer(const Vector<float>& buffer)
    : m_Stride(3 * sizeof(float))
    , m_Count(buffer.size() / 3)
{
	D3D11_BUFFER_DESC vbd = { 0 };
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0u;
	vbd.ByteWidth = sizeof(float) * buffer.size();
	vbd.StructureByteStride = sizeof(float);
	D3D11_SUBRESOURCE_DATA vsd = { 0 };
	vsd.pSysMem = buffer.data();

	const UINT offset = 0u;
	m_VertexBuffer = RenderingDevice::GetSingleton()->createVertexBuffer(&vbd, &vsd, &m_Stride, &offset);
}

void VertexBuffer::bind() const
{
	const UINT offset = 0u;
	RenderingDevice::GetSingleton()->bind(m_VertexBuffer.Get(), &m_Stride, &offset);
}
