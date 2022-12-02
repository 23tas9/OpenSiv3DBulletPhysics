#pragma once
#include "BulletCommon.hpp"
#include "DynamicsWorldDetail.hpp"

struct BulletBodyDetail {
	std::shared_ptr<DynamicsWorldDetail> world = nullptr;

	btRigidBody* body = nullptr;

	BulletBodyDetail(const std::shared_ptr<DynamicsWorldDetail>& _world, const Vec3& center, const Sphere& sivShape, double mass) :
		world{ _world } {
		btCollisionShape* shape = new btSphereShape{ sivShape.r };
		btMotionState* motionState = new btDefaultMotionState{ btTransform{ btQuaternion::getIdentity(), toBTVec3(center) } };

		body = new btRigidBody{ mass, motionState, shape, toBTVec3(center) };
	}

	BulletBodyDetail(const std::shared_ptr<DynamicsWorldDetail>& _world, const Vec3& center, const Box& sivBox, double mass) :
		world{ _world } {
		btCollisionShape* shape = new btBoxShape{ toBTVec3(sivBox.size) };
		btMotionState* motionState = new btDefaultMotionState{ btTransform{ btQuaternion::getIdentity(), toBTVec3(center) } };

		body = new btRigidBody{ mass, motionState, shape, toBTVec3(center) };
	}

	BulletBodyDetail(const std::shared_ptr<DynamicsWorldDetail>& _world, const Vec3& center, const Cylinder& sivCylinder, double mass) :
		world{ _world } {
		btCollisionShape* shape = new btCylinderShape{ btVector3{ sivCylinder.r, sivCylinder.h / 2, sivCylinder.r } };
		btMotionState* motionState = new btDefaultMotionState{ btTransform{ btQuaternion::getIdentity(), toBTVec3(center) } };

		body = new btRigidBody{ mass, motionState, shape, toBTVec3(center) };
	}

	BulletBodyDetail(const std::shared_ptr<DynamicsWorldDetail>& _world, const Vec3& center, const Cone& sivCone, double mass) :
		world{ _world } {
		btCollisionShape* shape = new btConeShape{ sivCone.r, sivCone.h };
		btMotionState* motionState = new btDefaultMotionState{ btTransform{ btQuaternion::getIdentity(), toBTVec3(center) } };

		body = new btRigidBody{ mass, motionState, shape, toBTVec3(center) };
	}

	~BulletBodyDetail() {
		world->remove(body);

		delete body->getCollisionShape();
		delete body->getMotionState();
		delete body;
	}
};
