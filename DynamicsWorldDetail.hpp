#pragma once
#include <memory>
#include "BulletCommon.hpp"

struct DynamicsWorldDetail {
	btDynamicsWorld* world = nullptr;

	DynamicsWorldDetail(const Vec3& gravity = { 0, -9.8, 0 }) {
		btCollisionConfiguration* config = new btDefaultCollisionConfiguration{ };

		btCollisionDispatcher* dispatcher = new btCollisionDispatcher{ config };

		btDbvtBroadphase* broadphase = new btDbvtBroadphase{ };

		btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver{ };

		world = new btDiscreteDynamicsWorld{ dispatcher, broadphase, solver, config };

		world->setGravity(toBTVec3(gravity));
	}

	~DynamicsWorldDetail() {
		delete world->getDispatcher();
		delete world->getBroadphase();
		delete world->getConstraintSolver();
		delete world;
	}

	void add(btRigidBody* body) {
		world->addRigidBody(body);
	}

	void remove(btRigidBody* body) {
		world->removeRigidBody(body);
	}
};
