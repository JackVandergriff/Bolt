//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_CHIPMUNK_WRAPPER_H
#define BOLT_CHIPMUNK_WRAPPER_H

#include <memory>

#include "transform.h"
#include "utility.h"

class cpBody;

namespace Bolt {

    enum class RBTypes {
        DYNAMIC, KINEMATIC, STATIC
    };

    class PhysicsSpace;

    class RigidBody : Component {
    private:
        std::shared_ptr<cpBody> body;
        auto makeRigidBody(RBTypes type);
    public:
        RigidBody();
        RigidBody(RBTypes type);
        void onUpdate() override;

        RBTypes getType() const;
        void setType(RBTypes type);
        const PhysicsSpace& getSpace() const;
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

    class PhysicsSpace {

    };
}

#endif //BOLT_CHIPMUNK_WRAPPER_H
