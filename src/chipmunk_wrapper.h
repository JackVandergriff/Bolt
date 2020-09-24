//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_CHIPMUNK_WRAPPER_H
#define BOLT_CHIPMUNK_WRAPPER_H

#include <memory>
#include <utility>
#include <vector>

#include "transform.h"
#include "utility.h"

class cpBody;
class cpShape;

namespace Bolt {

    const static inline float PHYSICS_BOX_RADIUS = 0.1f;

    enum class RBTypes {
        DYNAMIC, KINEMATIC, STATIC
    };

    enum class ShapeTypes {
        CIRCLE, SEGMENT, POLYGON
    };

    class PhysicsSpace;

    struct CollisionFilter {
        // TODO
    };

    class RigidBody : Component {
    private:
        std::shared_ptr<cpBody> body;
        auto makeRigidBody(RBTypes type);
    public:
        friend class PhysicsShape;
        RigidBody();
        RigidBody(RBTypes type);
        void onUpdate() override;

        RBTypes getType() const;
        void setType(RBTypes type);
        PhysicsSpace& getSpace() const; // TODO
        float getMass() const;
        void setMass(float mass);
        float getMoment() const;
        void setMoment(float moment);
        vec2f getCenterOfGravity() const;
        void setCenterOfGravity(vec2f center_of_gravity);
        vec2f getPosition() const;
        float getAngle() const;
        vec2f getVelocity() const;
        void setVelocity(vec2f velocity);
        vec2f getForce() const;
        void setForce(vec2f force);
        float getAngularVelocity() const;
        void setAngularVelocity(float angular_velocity);
        float getTorque() const;
        void setTorque(float torque);

        vec2f getVelocityAtPoint(vec2f global_point) const;
        void applyForceAtPoint(vec2f force, vec2f global_point);
        void applyForce(vec2f force);
        void applyImpulseAtPoint(vec2f impulse, vec2f global_point);
        void applyImpulse(vec2f impulse);

        bool isAsleep() const;
        void wake();
        void sleep();
    };

    class PhysicsShape {
    private:
        std::shared_ptr<cpShape> shape;
        const ShapeTypes type;
        std::vector<vec2f> polygon_vertices;
    public:
        PhysicsShape() = delete; // It's either this or breaking if someone tries to use it uninitialized
        PhysicsShape(RigidBody& body, float radius, vec2f offset_from_cog); // Circle constructor
        PhysicsShape(RigidBody& body, std::pair<vec2f, vec2f> endpoints, float thickness); // Segment constructor
        PhysicsShape(RigidBody& body, std::vector<vec2f> points); // Polygon constructor
        PhysicsShape(RigidBody& body, rectf box); // Box constructor

        ShapeTypes getType() const;
        RigidBody& getBody() const; // TODO
        void setBody(RigidBody& body);
        bool isSensor() const;
        void setSensor(bool is_sensor);
        float getElasticity() const;
        void setElasticity(float elasticity);
        float getFriction() const;
        void setFriction(float friction);
        vec2f getSurfaceVelocity() const;
        void setSurfaceVelocity(vec2f velocity);
        CollisionFilter getCollisionFilter() const; // TODO
        void setCollisionFilter(CollisionFilter filter); // TODO
        PhysicsSpace& getSpace() const; // TODO

        // Circle methods
        vec2f circleGetOffset() const;
        float circleGetRadius() const;

        // Segment methods
        std::tuple<vec2f, vec2f> segmentGetEndpoints() const;
        vec2f segmentGetNormalVector() const;
        float segmentGetThickness() const;
        void segmentSetNeighborPoint(vec2f previous, vec2f next);

        // Polygon methods
        const std::vector<vec2f>& polygonGetPoints() const;
        // float polygonGetScale() const; Pretty sure this isn't really what radius is, needs testing TODO
        vec2f polygonGetCentroid() const;
    };

    class PhysicsSpace {

    };
}

#endif //BOLT_CHIPMUNK_WRAPPER_H