#pragma once
#include <memory>
#include "BulletCommon.hpp"
#include "BulletBodyDetail.hpp"
#include "DynamicsWorldDetail.hpp"

class BulletBody {
	std::shared_ptr<BulletBodyDetail> m_impl = nullptr;

public:
	BulletBody(const std::shared_ptr<DynamicsWorldDetail>& world, const Vec3& center, const Sphere& sivSphere, double mass) :
		m_impl{ std::make_shared<BulletBodyDetail>(world, center, sivSphere, mass) } {

	}
	BulletBody(const std::shared_ptr<DynamicsWorldDetail>& world, const Vec3& center, const Box& sivBox, double mass) :
		m_impl{ std::make_shared<BulletBodyDetail>(world, center, sivBox, mass) } {

	}
	BulletBody(const std::shared_ptr<DynamicsWorldDetail>& world, const Vec3& center, const Cylinder& sivCylinder, double mass) :
		m_impl{ std::make_shared<BulletBodyDetail>(world, center, sivCylinder, mass) } {

	}
	BulletBody(const std::shared_ptr<DynamicsWorldDetail>& world, const Vec3& center, const Cone& sivCone, double mass) :
		m_impl{ std::make_shared<BulletBodyDetail>(world, center, sivCone, mass) } {

	}

	void draw(Color color = Palette::White) const {
		btCollisionShape* collisionShape = m_impl->body->getCollisionShape();
		int32 shapeType = collisionShape->getShapeType();

		if		(shapeType == SPHERE_SHAPE_PROXYTYPE) {
			btSphereShape* shape = static_cast<btSphereShape*>(collisionShape);
			Sphere{ getCenter(), shape->getRadius() }.draw(color);
		}

		else if (shapeType == BOX_SHAPE_PROXYTYPE) {
			btBoxShape* shape = static_cast<btBoxShape*>(collisionShape);
			Box{ getCenter(), fromBTVec3(shape->getHalfExtentsWithMargin()) * 2 }.draw(color);
		}

		else if (shapeType == CYLINDER_SHAPE_PROXYTYPE) {
			btCylinderShape* shape = static_cast<btCylinderShape*>(collisionShape);
			btVector3 halfExtents = shape->getHalfExtentsWithMargin();
			Cylinder{ getCenter(), halfExtents.x(), halfExtents.y() * 2 }.draw(color);
		}

		else if (shapeType == CONE_SHAPE_PROXYTYPE) {
			btConeShape* shape = static_cast<btConeShape*>(collisionShape);
			Cone{ getCenter() - Vec3{ 0, shape->getHeight() / 2, 0 }, shape->getRadius(), shape->getHeight() }.draw(color);
		}
	}

	btRigidBody* getRigidBody() {
		return m_impl->body;
	}
	btRigidBody* getRigidBody() const {
		return m_impl->body;
	}

	Vec3 getCenter() const {
		return fromBTVec3(m_impl->body->getCenterOfMassPosition());
	}

	void setCenter(const Vec3& center) {
		m_impl->body->setCenterOfMassTransform(btTransform{ m_impl->body->getCenterOfMassTransform().getRotation(), toBTVec3(center) });
	}

	bool interact(const BulletBody& other) {
		
	}
};
