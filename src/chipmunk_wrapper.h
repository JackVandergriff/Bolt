//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_CHIPMUNK_WRAPPER_H
#define BOLT_CHIPMUNK_WRAPPER_H

#include <memory>
#include <utility>
#include <vector>
#include <map>
#include <functional>

#include "transform.h"
#include "utility.h"

class cpBody;
class cpShape;
class cpSpace;

namespace Bolt {

    BOLT_EXPORT const static inline double PHYSICS_BOX_RADIUS = 0.1f;

    enum class BOLT_EXPORT RBTypes {
        DYNAMIC, KINEMATIC, STATIC
    };

    enum class BOLT_EXPORT ShapeTypes {
        CIRCLE, SEGMENT, POLYGON
    };

    class PhysicsSpace;
    class PhysicsShape;

    struct BOLT_EXPORT CollisionFilter {
        // TODO
    };

    class BOLT_EXPORT RigidBody : public CustomComponent<RigidBody> {
    private:
        struct Deleter {
            void operator()(cpBody* to_free); // Can't use lambda, have to keep cpBodyFree out of header
        };

        std::unique_ptr<cpBody, Deleter> body;
        std::vector<PhysicsShape> shapes;
        static inline std::map<cpBody*, RigidBody&> lookup;
        auto makeRigidBody(RBTypes type);
        void copy(const RigidBody& other);
    public:
        friend class PhysicsShape;
        friend void swap(RigidBody& first, RigidBody& second) noexcept;
        RigidBody();
        RigidBody(RBTypes type);
        RigidBody(PhysicsSpace& space, RBTypes type=RBTypes::DYNAMIC);
        ~RigidBody();
        RigidBody(const RigidBody& other);
        RigidBody& operator=(const RigidBody& other);
        RigidBody(RigidBody&& other) = default;
        RigidBody& operator=(RigidBody&&) = default;
        void onAttach() override;
        void onUpdate() override;

        template<class... Args> void addShape(Args&&... args) {
            shapes.push_back({*this, std::forward<Args>(args)...}); // And the winner for confusing syntax goes to!
        }
        PhysicsShape& getShape(int index);
        std::vector<PhysicsShape>& getShapes();

        RBTypes getType() const;
        void setType(RBTypes type);
        PhysicsSpace& getSpace() const;
        double getMass() const;
        void setMass(double mass);
        double getMoment() const;
        void setMoment(double moment);
        vec2f getCenterOfGravity() const;
        void setCenterOfGravity(vec2f center_of_gravity);
        vec2f getPosition() const;
        double getAngle() const;
        vec2f getVelocity() const;
        void setVelocity(vec2f velocity);
        vec2f getForce() const;
        void setForce(vec2f force);
        double getAngularVelocity() const;
        void setAngularVelocity(double angular_velocity);
        double getTorque() const;
        void setTorque(double torque);

        vec2f getVelocityAtPoint(vec2f global_point) const;
        void applyForceAtPoint(vec2f force, vec2f global_point);
        void applyForce(vec2f force);
        void applyImpulseAtPoint(vec2f impulse, vec2f global_point);
        void applyImpulse(vec2f impulse);

        bool isAsleep() const;
        void wake();
        void sleep();
    };

    class BOLT_EXPORT PhysicsShape {
    private:
        struct Deleter {
            void operator()(cpShape* to_free); // Can't use lambda, have to keep cpShapeFree out of header
        };

        std::unique_ptr<cpShape, Deleter> shape;
        ShapeTypes type;
        std::vector<vec2f> polygon_vertices;

        void addToSpaceOfBody(RigidBody& body);
    public:
        friend void swap(PhysicsShape& first, PhysicsShape& second);

        PhysicsShape() = delete; // It's either this or breaking if someone tries to use it uninitialized
        PhysicsShape(RigidBody& body, double radius, vec2f offset_from_cog); // Circle constructor
        PhysicsShape(RigidBody& body, std::pair<vec2f, vec2f> endpoints, double thickness); // Segment constructor
        PhysicsShape(RigidBody& body, std::vector<vec2f> points); // Polygon constructor
        PhysicsShape(RigidBody& body, rectf box); // Box constructor
        PhysicsShape(const PhysicsShape& other);
        PhysicsShape& operator=(PhysicsShape other);
        PhysicsShape(PhysicsShape&& other) = default;
        PhysicsShape& operator=(PhysicsShape&& other) = default;

        ShapeTypes getType() const;
        RigidBody& getBody() const;
        void setBody(RigidBody& body);
        bool isSensor() const;
        void setSensor(bool is_sensor);
        double getElasticity() const;
        void setElasticity(double elasticity);
        double getFriction() const;
        void setFriction(double friction);
        vec2f getSurfaceVelocity() const;
        void setSurfaceVelocity(vec2f velocity);
        CollisionFilter getCollisionFilter() const; // TODO
        void setCollisionFilter(CollisionFilter filter); // TODO
        PhysicsSpace& getSpace() const;

        // Circle methods
        vec2f circleGetOffset() const;
        double circleGetRadius() const;

        // Segment methods
        std::tuple<vec2f, vec2f> segmentGetEndpoints() const;
        vec2f segmentGetNormalVector() const;
        double segmentGetThickness() const;
        void segmentSetNeighborPoint(vec2f previous, vec2f next);

        // Polygon methods
        const std::vector<vec2f>& polygonGetPoints() const;
        // double polygonGetScale() const; Pretty sure this isn't really what radius is, needs testing TODO
        vec2f polygonGetCentroid() const;
    };

    class BOLT_EXPORT PhysicsSpace {
    private:
        std::unique_ptr<cpSpace, std::function<void(cpSpace*)>> space; // This is literal magic, right?
        static inline std::map<cpSpace*, PhysicsSpace&> lookup;
    public:
        friend class PhysicsShape;
        friend class RigidBody;
        double time_delta = 1/60.;
        PhysicsSpace();
        ~PhysicsSpace();
        void update();
        int getAccuracy() const;
        void setAccuracy(int accuracy);
        vec2f getGravity() const;
        void setGravity(vec2f gravity);
        double getDamping() const;
        void setDamping(double damping);
        double getMaxIdleSpeed() const;
        void setMaxIdleSpeed(double speed);
        double getIdleSleepTime() const;
        void setIdleSleepTime(double time);
        double getMaxOverlap() const;
        void setMaxOverlap(double overlap);
        double getCollisionBias() const;
        void setCollisionBias(double bias);
        double getTimeStep() const;
    };

}

#endif //BOLT_CHIPMUNK_WRAPPER_H
