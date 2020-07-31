#pragma once

#include "common/common.h"
#include "bone_data.h"

/// Data to be sent in a vertex
struct VertexData
{
	Vector3 m_Position;
	Vector3 m_Normal;
	Vector2 m_TextureCoord;
};

struct UIVertexData
{
	Vector2 m_Position;
	char m_Color[4];
	Vector2 m_TextureCoord;
};

struct AnimatedVertexData : public VertexData
{
	Vector<VertexBoneData> m_VertexBoneData;
};
