#pragma once

#include "physics_collider_component.h"

#include "btBulletDynamicsCommon.h"

/// Creates sphere shaped collider.
/// Takes box's dimensions and material type as arguments.
class BoxColliderComponent : public PhysicsColliderComponent
{
	static Component* Create(const JSON::json& boxComponentData);
	static Component* CreateDefault();

	Vector3 m_Dimensions;
	Ref<btBoxShape> m_BoxShape;

	friend class EntityFactory;

public:
	static const ComponentID s_ID = (ComponentID)ComponentIDs::BoxColliderComponent;

	BoxColliderComponent(const Vector3& dimensions, const String& matName, const Vector3& gravity, bool isMoveable, bool generatesHitEvents);

	Vector3 getDimensions() const { return m_Dimensions; }
	virtual String getName() const override { return "BoxColliderComponent"; };
	virtual JSON::json getJSON() const override;
	virtual ComponentID getComponentID() const override { return s_ID; }

	void setDimensions(const Vector3& dimensions);

#ifdef ROOTEX_EDITOR
	void draw() override;
#endif // ROOTEX_EDITOR 
};
