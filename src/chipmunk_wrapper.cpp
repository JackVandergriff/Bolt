//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "chipmunk_wrapper.h"

#include <chipmunk/chipmunk.h>
#include <iostream>
#include <algorithm>
//#include <chipmunk/chipmunk_structs.h>

using namespace Bolt;

cpVect cp(vec2f input) {
    return {input.x, input.y};
}

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

double RigidBody::getMass() const {
    return cpBodyGetMass(body.get());
}

void RigidBody::setMass(double mass) {
    cpBodySetMass(body.get(), mass);
}

double RigidBody::getMoment() const {
    return cpBodyGetMoment(body.get());
}

void RigidBody::setMoment(double moment) {
    cpBodySetMoment(body.get(), moment);
}

vec2f RigidBody::getCenterOfGravity() const {
    auto cog = cpBodyGetCenterOfGravity(body.get());
    return {cog.x, cog.y};
}

void RigidBody::setCenterOfGravity(vec2f center_of_gravity) {
    cpBodySetCenterOfGravity(body.get(), cp(center_of_gravity));
}

vec2f RigidBody::getPosition() const {
    auto pos = cpBodyGetPosition(body.get());
    return {pos.x, pos.y};
}

double RigidBody::getAngle() const {
    return cpBodyGetAngle(body.get());
}

vec2f RigidBody::getVelocity() const {
    auto vel = cpBodyGetVelocity(body.get());
    return {vel.x, vel.y};
}

void RigidBody::setVelocity(vec2f velocity) {
    cpBodySetVelocity(body.get(), cp(velocity));
}

vec2f RigidBody::getForce() const {
    auto force = cpBodyGetForce(body.get());
    return {force.x, force.y};
}

void RigidBody::setForce(vec2f force) {
    cpBodySetForce(body.get(), cp(force));
}

double RigidBody::getAngularVelocity() const {
    return cpBodyGetAngularVelocity(body.get());
}

void RigidBody::setAngularVelocity(double angular_velocity) {
    cpBodySetAngularVelocity(body.get(), angular_velocity);
}

double RigidBody::getTorque() const {
    return cpBodyGetTorque(body.get());
}

void RigidBody::setTorque(double torque) {
    cpBodySetTorque(body.get(), torque);
}

vec2f RigidBody::getVelocityAtPoint(vec2f global_point) const {
    auto vel = cpBodyGetVelocityAtWorldPoint(body.get(), cp(global_point));
    return {vel.x, vel.y};
}

void RigidBody::applyForceAtPoint(vec2f force, vec2f global_point) {
    cpBodyApplyForceAtWorldPoint(body.get(), cp(force), cp(global_point));
}

void RigidBody::applyForce(vec2f force) {
    cpBodyApplyForceAtLocalPoint(body.get(), cp(force), {0, 0});
}

void RigidBody::applyImpulseAtPoint(vec2f impulse, vec2f global_point) {
    cpBodyApplyImpulseAtWorldPoint(body.get(), cp(impulse), cp(global_point));
}

void RigidBody::applyImpulse(vec2f impulse) {
    cpBodyApplyImpulseAtLocalPoint(body.get(), cp(impulse), {0, 0});
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

PhysicsSpace &RigidBody::getSpace() const {
    // TODO
}

PhysicsShape::PhysicsShape(RigidBody &body, double radius, vec2f offset_from_cog) : type(ShapeTypes::CIRCLE) {
    shape = std::shared_ptr<cpShape>(cpCircleShapeNew(body.body.get(), radius, cp(offset_from_cog)), [](cpShape* s){
        cpShapeFree(s);
    });
}

PhysicsShape::PhysicsShape(RigidBody &body, std::pair<vec2f, vec2f> endpoints, double thickness) : type(ShapeTypes::SEGMENT) {
    shape = std::shared_ptr<cpShape>(cpSegmentShapeNew(body.body.get(), cp(endpoints.first), cp(endpoints.second), thickness), [](cpShape* s){
        cpShapeFree(s);
    });
}

PhysicsShape::PhysicsShape(RigidBody &body, std::vector<vec2f> points) : type(ShapeTypes::POLYGON), polygon_vertices(points) {
    std::vector<cpVect> cp_verts;
    std::transform(polygon_vertices.begin(), polygon_vertices.end(), cp_verts.begin(), cp);
    shape = std::shared_ptr<cpShape>(cpPolyShapeNew(body.body.get(), cp_verts.size(), cp_verts.data(), cpTransformIdentity, PHYSICS_BOX_RADIUS), [](cpShape* s){
        cpShapeFree(s);
    });
}

PhysicsShape::PhysicsShape(RigidBody &body, rectf box) : type(ShapeTypes::POLYGON) {
    polygon_vertices = {box.getTopLeft(), box.getTopLeft() + vec2f{box.w, 0}, box.getBottomRight(), box.getTopLeft() + vec2f{0, box.h}};
    shape = std::shared_ptr<cpShape>(cpBoxShapeNew2(body.body.get(), cpBBNew(box.x, box.y, box.x + box.w, box.y + box.h), PHYSICS_BOX_RADIUS), [](cpShape* s){
        cpShapeFree(s);
    });
}

ShapeTypes PhysicsShape::getType() const {
    return type;
}

RigidBody &PhysicsShape::getBody() const {
    // TODO
}

void PhysicsShape::setBody(RigidBody &body) {
    cpShapeSetBody(shape.get(), body.body.get());
}

bool PhysicsShape::isSensor() const {
    return cpShapeGetSensor(shape.get());
}

void PhysicsShape::setSensor(bool is_sensor) {
    cpShapeSetSensor(shape.get(), is_sensor);
}

double PhysicsShape::getElasticity() const {
    return cpShapeGetElasticity(shape.get());
}

void PhysicsShape::setElasticity(double elasticity) {
    cpShapeSetElasticity(shape.get(), elasticity);
}

double PhysicsShape::getFriction() const {
    return cpShapeGetFriction(shape.get());
}

void PhysicsShape::setFriction(double friction) {
    cpShapeSetFriction(shape.get(), friction);
}

vec2f PhysicsShape::getSurfaceVelocity() const {
    auto vel = cpShapeGetSurfaceVelocity(shape.get());
    return {vel.x, vel.y};
}

void PhysicsShape::setSurfaceVelocity(vec2f velocity) {
    cpShapeSetSurfaceVelocity(shape.get(), cp(velocity));
}

CollisionFilter PhysicsShape::getCollisionFilter() const {
    // TODO
    return {};
}

void PhysicsShape::setCollisionFilter(CollisionFilter filter) {
    // TODO
}

PhysicsSpace &PhysicsShape::getSpace() const {
    // TODO
}

vec2f PhysicsShape::circleGetOffset() const {
    if (type != ShapeTypes::CIRCLE) throw "This ain't a circle nor a good error message";
    auto off = cpCircleShapeGetOffset(shape.get());
    return {off.x, off.y};
}

double PhysicsShape::circleGetRadius() const {
    if (type != ShapeTypes::CIRCLE) throw "This ain't a circle nor a good error message";
    return cpCircleShapeGetRadius(shape.get());
}

std::tuple<vec2f, vec2f> PhysicsShape::segmentGetEndpoints() const {
    if (type != ShapeTypes::SEGMENT) throw "This ain't a segment nor a good error message";
    auto A = cpSegmentShapeGetA(shape.get());
    auto B = cpSegmentShapeGetB(shape.get());
    return {{A.x, A.y}, {B.x, B.y}};
}

vec2f PhysicsShape::segmentGetNormalVector() const {
    if (type != ShapeTypes::SEGMENT) throw "This ain't a segment nor a good error message";
    auto norm = cpSegmentShapeGetNormal(shape.get());
    return {norm.x, norm.y};
}

double PhysicsShape::segmentGetThickness() const {
    if (type != ShapeTypes::SEGMENT) throw "This ain't a segment nor a good error message";
    return cpSegmentShapeGetRadius(shape.get());
}

void PhysicsShape::segmentSetNeighborPoint(vec2f previous, vec2f next) {
    if (type != ShapeTypes::SEGMENT) throw "This ain't a segment nor a good error message";
    cpSegmentShapeSetNeighbors(shape.get(), cp(previous), cp(next));
}

const std::vector<vec2f> &PhysicsShape::polygonGetPoints() const {
    if (type != ShapeTypes::POLYGON) throw "This ain't a polygon nor a good error message";
    return polygon_vertices;
}

vec2f PhysicsShape::polygonGetCentroid() const {
    std::vector<cpVect> cp_verts;
    std::transform(polygon_vertices.begin(), polygon_vertices.end(), cp_verts.begin(), cp);
    auto cent = cpCentroidForPoly(cp_verts.size(), cp_verts.data());
    return {cent.x, cent.y};
}


