//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "chipmunk_wrapper.h"

#include <chipmunk/chipmunk.h>
//#include <chipmunk/chipmunk_structs.h>

using namespace Bolt;

auto RigidBody::makeRigidBody(RBTypes type) {
    switch (type) {
        case RBTypes::DYNAMIC:
            return std::shared_ptr<cpBody>(cpBodyNew(0, 0), [](cpBody* b) {
                cpBodyFree(b);
            }); // Is RAII really that hard??
        case RBTypes::KINEMATIC:
            return std::shared_ptr<cpBody>(cpBodyNewKinematic(), [](cpBody* b) {
                cpBodyFree(b);
            }); // Like I get you want to write it in C
        case RBTypes::STATIC:
            return std::shared_ptr<cpBody>(cpBodyNewStatic(), [](cpBody* b) {
                cpBodyFree(b);
            }); // But a simple C++ wrapper in at least C++11 would be cool
    }
}

RigidBody::RigidBody() : RigidBody(RBTypes::DYNAMIC) {}

RigidBody::RigidBody(RBTypes type) : body(makeRigidBody(type)) {}

void RigidBody::onUpdate() {
    transform->local_geometry = applyGeometry(
            Geometry{getPosition(), getAngle(), 1},
            owner->getOwner()->getTransform()->globalGeometry());
}

RBTypes RigidBody::getType() const {
    switch (cpBodyGetType(body.get())) {
        case CP_BODY_TYPE_DYNAMIC:
            return RBTypes::DYNAMIC;
        case CP_BODY_TYPE_KINEMATIC:
            return RBTypes::KINEMATIC;
        case CP_BODY_TYPE_STATIC:
            return RBTypes::STATIC;
    }
}

void RigidBody::setType(RBTypes type) {
    switch (type) {
        case RBTypes::DYNAMIC:
            cpBodySetType(body.get(), CP_BODY_TYPE_DYNAMIC);
            break;
        case RBTypes::KINEMATIC:
            cpBodySetType(body.get(), CP_BODY_TYPE_KINEMATIC);
            break;
        case RBTypes::STATIC:
            cpBodySetType(body.get(), CP_BODY_TYPE_STATIC);
            break;
    }
}

float RigidBody::getMass() const {
    return cpBodyGetMass(body.get());
}

void RigidBody::setMass(float mass) {
    cpBodySetMass(body.get(), mass);
}

float RigidBody::getMoment() const {
    return cpBodyGetMoment(body.get());
}

void RigidBody::setMoment(float moment) {
    cpBodySetMoment(body.get(), moment);
}

vec2f RigidBody::getCenterOfGravity() const {
    auto cog = cpBodyGetCenterOfGravity(body.get());
    return {cog.x, cog.y};
}

void RigidBody::setCenterOfGravity(vec2f center_of_gravity) {
    cpBodySetCenterOfGravity(body.get(), {center_of_gravity.x, center_of_gravity.y});
}

vec2f RigidBody::getPosition() const {
    auto pos = cpBodyGetPosition(body.get());
    return {pos.x, pos.y};
}

float RigidBody::getAngle() const {
    return cpBodyGetAngle(body.get());
}

vec2f RigidBody::getVelocity() const {
    auto vel = cpBodyGetVelocity(body.get());
    return {vel.x, vel.y};
}

void RigidBody::setVelocity(vec2f velocity) {
    cpBodySetVelocity(body.get(), {velocity.x, velocity.y});
}

vec2f RigidBody::getForce() const {
    auto force = cpBodyGetForce(body.get());
    return {force.x, force.y};
}

void RigidBody::setForce(vec2f force) {
    cpBodySetForce(body.get(), {force.x, force.y});
}

float RigidBody::getAngularVelocity() const {
    return cpBodyGetAngularVelocity(body.get());
}

void RigidBody::setAngularVelocity(float angular_velocity) {
    cpBodySetAngularVelocity(body.get(), angular_velocity);
}

float RigidBody::getTorque() const {
    return cpBodyGetTorque(body.get());
}

void RigidBody::setTorque(float torque) {
    cpBodySetTorque(body.get(), torque);
}

vec2f RigidBody::getVelocityAtPoint(vec2f global_point) const {
    auto vel = cpBodyGetVelocityAtWorldPoint(body.get(), {global_point.x, global_point.y});
    return {vel.x, vel.y};
}

void RigidBody::applyForceAtPoint(vec2f force, vec2f global_point) {
    cpBodyApplyForceAtWorldPoint(body.get(), {force.x, force.y}, {global_point.x, global_point.y});
}

void RigidBody::applyForce(vec2f force) {
    cpBodyApplyForceAtLocalPoint(body.get(), {force.x, force.y}, {0, 0});
}

void RigidBody::applyImpulseAtPoint(vec2f impulse, vec2f global_point) {
    cpBodyApplyImpulseAtWorldPoint(body.get(), {impulse.x, impulse.y}, {global_point.x, global_point.y});
}

void RigidBody::applyImpulse(vec2f impulse) {
    cpBodyApplyImpulseAtLocalPoint(body.get(), {impulse.x, impulse.y}, {0, 0});
}

bool RigidBody::isAsleep() const {
    return cpBodyIsSleeping(body.get());
}

void RigidBody::wake() {
    if (getType() == RBTypes::STATIC) {
        cpBodyActivateStatic(body.get(), nullptr);
    } else {
        cpBodyActivate(body.get());
    }
}

void RigidBody::sleep() {
    cpBodySleep(body.get());
}
