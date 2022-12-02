#pragma once
#include <memory>
#include "BulletCommon.hpp"
#include "DynamicsWorldDetail.hpp"
#include "BulletBody.hpp"

class DynamicsWorld {
	std::shared_ptr<DynamicsWorldDetail> m_impl = nullptr;

public:
	DynamicsWorld(const Vec3& gravity = { 0, -9.8, 0 }) :
		m_impl{ std::make_shared<DynamicsWorldDetail>(gravity) } {

	}

	void update(double dt = Scene::DeltaTime(), double maxTime = Scene::GetMaxDeltaTime()) {
		m_impl->world->stepSimulation(dt, 1);
	}

	void add(BulletBody& body) {
		m_impl->add(body.getRigidBody());
	}

	void remove(BulletBody& body) {
		m_impl->remove(body.getRigidBody());
	}


	BulletBody createSphere(const Vec3& center, double r, double mass) {
		BulletBody body{ m_impl, center, Sphere{ r }, mass };

		add(body);

		return body;
	}

	BulletBody createBox(const Vec3& center, const Vec3& size, double mass) {
		BulletBody body{ m_impl, center, Box{ size }, mass };

		add(body);

		return body;
	}

	BulletBody createCylinder(const Vec3& center, double r, double h, double mass) {
		BulletBody body{ m_impl, center, Cylinder{ r, h }, mass };

		add(body);

		return body;
	}

	BulletBody createCone(const Vec3& center, double r, double h, double mass) {
		BulletBody body{ m_impl, center, Cone{ r, h }, mass };

		add(body);

		return body;
	}
};
