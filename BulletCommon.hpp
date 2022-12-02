#pragma once
#include <Siv3D.hpp>
#include <btBulletDynamicsCommon.h>

Vec3 fromBTVec3(const btVector3& v) {
	return { v.x(), v.y(), v.z() };
}
btVector3 toBTVec3(const Vec3& v) {
	return { v.x, v.y, v.z };
}

Quaternion fromBTQuat(const btQuaternion& q) {
	return { q.x(), q.y(), q.z(), q.w()	};
}

btQuaternion toBTQuat(const Quaternion& q) {
	return { q.getX(), q.getY(), q.getZ(), q.getW() };
}
