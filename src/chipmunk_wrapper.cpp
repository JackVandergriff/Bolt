//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "chipmunk_wrapper.h"
#include "window_manager.h"

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
            return std::unique_ptr<cpBody, Deleter>(cpBodyNew(1, 1), Deleter{});
        case RBTypes::KINEMATIC:
            return std::unique_ptr<cpBody, Deleter>(cpBodyNewKinematic(), Deleter{});
        case RBTypes::STATIC:
            return std::unique_ptr<cpBody, Deleter>(cpBodyNewStatic(), Deleter{});
    }
}

RigidBody::RigidBody() : RigidBody(WindowManager::getPhysicsSpace(), RBTypes::DYNAMIC) {}

RigidBody::RigidBody(RBTypes type) : RigidBody(WindowManager::getPhysicsSpace(), type) {}

RigidBody::RigidBody(PhysicsSpace& space, RBTypes type) : body(makeRigidBody(type)) {
    lookup.insert({body.get(), *this});
    cpSpaceAddBody(space.space.get(), body.get());
}

RigidBody::~RigidBody() {
    lookup.erase(body.get());
}

void RigidBody::onUpdate() {
    double scale = transform->local_geometry.scale;
    transform->setGlobalGeometry({getPosition(), getAngle(), 1});
    transform->local_geometry.scale = scale;
}

void RigidBody::onAttach() {
    cpBodySetPosition(body.get(), cp(transform->globalGeometry().offset));
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
    return PhysicsSpace::lookup.at(cpBodyGetSpace(body.get()));
}

PhysicsShape &RigidBody::getShape(int index) {
    return shapes[index];
}

std::vector<PhysicsShape> &RigidBody::getShapes() {
    return shapes;
}

RigidBody::RigidBody(const RigidBody &other) : RigidBody(other.getSpace(), other.getType()) {
    setAngularVelocity(other.getAngularVelocity());
    setVelocity(other.getVelocity());
    setCenterOfGravity(other.getCenterOfGravity());
    setMass(other.getMass());
    setMoment(other.getMoment());
    setForce(other.getForce());
    setTorque(other.getTorque());

    std::copy(other.shapes.cbegin(), other.shapes.cend(), std::back_inserter(shapes));
    for (auto& shape : shapes) {
        shape.setBody(*this);
    }
}

RigidBody &RigidBody::operator=(RigidBody other) {
    swap(other, *this);
    return *this;
}

void Bolt::swap(RigidBody &first, RigidBody &second) noexcept {
    using std::swap;

    swap(first.body, second.body);
    swap(first.shapes, second.shapes);
}

PhysicsShape::PhysicsShape(RigidBody &body, double radius, vec2f offset_from_cog) : type(ShapeTypes::CIRCLE) {
    shape = std::unique_ptr<cpShape, Deleter>(cpCircleShapeNew(body.body.get(), radius, cp(offset_from_cog)), Deleter{});
    addToSpaceOfBody(body);
}

PhysicsShape::PhysicsShape(RigidBody &body, std::pair<vec2f, vec2f> endpoints, double thickness) : type(ShapeTypes::SEGMENT) {
    shape = std::unique_ptr<cpShape, Deleter>(cpSegmentShapeNew(body.body.get(), cp(endpoints.first), cp(endpoints.second), thickness), Deleter{});
    addToSpaceOfBody(body);
}

PhysicsShape::PhysicsShape(RigidBody &body, std::vector<vec2f> points) : type(ShapeTypes::POLYGON), polygon_vertices(points) {
    std::vector<cpVect> cp_verts;
    std::transform(polygon_vertices.cbegin(), polygon_vertices.cend(), std::back_inserter(cp_verts), cp);
    shape = std::unique_ptr<cpShape, Deleter>(cpPolyShapeNew(body.body.get(), cp_verts.size(), cp_verts.data(), cpTransformIdentity, PHYSICS_BOX_RADIUS), Deleter{});
    addToSpaceOfBody(body);
}

PhysicsShape::PhysicsShape(RigidBody &body, rectf box) : type(ShapeTypes::POLYGON) {
    polygon_vertices = {box.getTopLeft(), box.getTopLeft() + vec2f{box.w, 0}, box.getBottomRight(), box.getTopLeft() + vec2f{0, box.h}};
    shape = std::unique_ptr<cpShape, Deleter>(cpBoxShapeNew2(body.body.get(), cpBBNew(box.x, box.y, box.x + box.w, box.y + box.h), PHYSICS_BOX_RADIUS), Deleter{});
    addToSpaceOfBody(body);
}

ShapeTypes PhysicsShape::getType() const {
    return type;
}

RigidBody &PhysicsShape::getBody() const {
    return RigidBody::lookup.at(cpShapeGetBody(shape.get()));
}

void PhysicsShape::setBody(RigidBody &body) {
    cpSpaceRemoveShape(getSpace().space.get(), shape.get());
    cpShapeSetBody(shape.get(), body.body.get());
    cpSpaceAddShape(body.getSpace().space.get(), shape.get());
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
    return PhysicsSpace::lookup.at(cpShapeGetSpace(shape.get()));
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

void PhysicsShape::addToSpaceOfBody(RigidBody &body) {
    cpSpaceAddShape(body.getSpace().space.get(), shape.get());
}

PhysicsShape::PhysicsShape(const PhysicsShape &other) : type(other.getType()) {
    if (!other.polygon_vertices.empty()) {
        std::copy(other.polygon_vertices.cbegin(), other.polygon_vertices.cend(), std::back_inserter(polygon_vertices));
    }

    if (type == ShapeTypes::CIRCLE) {
        shape = std::unique_ptr<cpShape, Deleter>(
                cpCircleShapeNew(other.getBody().body.get(), other.circleGetRadius(), cp(other.circleGetOffset())),
                Deleter{});
    } else if (type == ShapeTypes::SEGMENT) {
        auto [first, second] = other.segmentGetEndpoints();
        shape = std::unique_ptr<cpShape, Deleter>(
                cpSegmentShapeNew(other.getBody().body.get(), cp(first), cp(second), other.segmentGetThickness()),
                Deleter{});
    } else if (type == ShapeTypes::POLYGON) {
        std::vector<cpVect> cp_verts;
        std::transform(polygon_vertices.cbegin(), polygon_vertices.cend(), std::back_inserter(cp_verts), cp);
        shape = std::unique_ptr<cpShape, Deleter>(
                cpPolyShapeNew(other.getBody().body.get(), cp_verts.size(), cp_verts.data(), cpTransformIdentity, PHYSICS_BOX_RADIUS),
                Deleter{});
    }

    addToSpaceOfBody(other.getBody());
}

void Bolt::swap(PhysicsShape& first, PhysicsShape& second) {
    using std::swap;

    swap(first.type, second.type);
    swap(first.shape, second.shape);
    swap(first.polygon_vertices, second.polygon_vertices);
}

PhysicsShape &PhysicsShape::operator=(PhysicsShape other) {
    swap(other, *this);
    return *this;
}


PhysicsSpace::PhysicsSpace() : space(cpSpaceNew(), [](cpSpace* s){cpSpaceFree(s);}) {
    lookup.insert({space.get(), *this});
}

PhysicsSpace::~PhysicsSpace() {
    lookup.erase(space.get());
}

void PhysicsSpace::update() {
    cpSpaceStep(space.get(), time_delta);
}

int PhysicsSpace::getAccuracy() const {
    return cpSpaceGetIterations(space.get());
}

void PhysicsSpace::setAccuracy(int accuracy) {
    cpSpaceSetIterations(space.get(), accuracy);
}

vec2f PhysicsSpace::getGravity() const {
    auto grav = cpSpaceGetGravity(space.get());
    return {grav.x, grav.y};
}

void PhysicsSpace::setGravity(vec2f gravity) {
    cpSpaceSetGravity(space.get(), cp(gravity));
}

double PhysicsSpace::getDamping() const {
    return cpSpaceGetDamping(space.get());
}

void PhysicsSpace::setDamping(double damping) {
    cpSpaceSetDamping(space.get(), damping);
}

double PhysicsSpace::getMaxIdleSpeed() const {
    return cpSpaceGetIdleSpeedThreshold(space.get());
}

void PhysicsSpace::setMaxIdleSpeed(double speed) {
    cpSpaceSetIdleSpeedThreshold(space.get(), speed);
}

double PhysicsSpace::getIdleSleepTime() const {
    return cpSpaceGetSleepTimeThreshold(space.get());
}

void PhysicsSpace::setIdleSleepTime(double time) {
    cpSpaceSetSleepTimeThreshold(space.get(), time);
}

double PhysicsSpace::getMaxOverlap() const {
    return cpSpaceGetCollisionSlop(space.get());
}

void PhysicsSpace::setMaxOverlap(double overlap) {
    cpSpaceSetCollisionSlop(space.get(), overlap);
}

double PhysicsSpace::getCollisionBias() const {
    return cpSpaceGetCollisionBias(space.get());
}

void PhysicsSpace::setCollisionBias(double bias) {
    cpSpaceSetCollisionBias(space.get(), bias);
}

double PhysicsSpace::getTimeStep() const {
    return cpSpaceGetCurrentTimeStep(space.get());
}

void RigidBody::Deleter::operator()(cpBody* to_free) {
    if (to_free)
        cpBodyFree(to_free);
}

void PhysicsShape::Deleter::operator()(cpShape* to_free) {
    if (to_free)
        cpShapeFree(to_free);
}
