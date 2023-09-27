#include <Box2D/Box2D.h>
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//Crear una pelota lanzada con un angulo de 75 grados con una velocidad de 20 km/h.

int main() {
    // Define the gravity vector
    b2Vec2 gravity(0.0f, -9.8f);

    // Construct a world object, which will hold and simulate the rigid bodies
    b2World world(gravity);

    // Create a Sphere
    b2BodyDef sphereBodyDef;
    sphereBodyDef.type = b2_dynamicBody; // Making the Sphere a dynamic body
    sphereBodyDef.position.Set(0.0f, 0.0f);
    b2Body* sphereBody = world.CreateBody(&sphereBodyDef);

    b2CircleShape sphereShape;
    sphereShape.m_radius = 1.0f; // size of the Sphere

    b2FixtureDef sphereFixtureDef;
    sphereFixtureDef.shape = &sphereShape;
    sphereFixtureDef.density = 1.0f;
    sphereBody->CreateFixture(&sphereFixtureDef);

    // create a sphere position and velocity
    float angle = 75.0f; // Angle in degrees
    float rad_angle = angle * (M_PI / 180.0f); // Convert an angle to radians
    float speed = 5.55f; // Speed in m/s
    b2Vec2 velocity(speed * std::cos(rad_angle), speed * std::sin(rad_angle));

    // setting Sphere velocity
    sphereBody->SetLinearVelocity(velocity);

    // Simulate the world
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 8;

    for (int i = 0; i < 60; ++i) {
        world.Step(timeStep, velocityIterations, positionIterations);

        b2Vec2 spherePosition = sphereBody->GetPosition();
        b2Vec2 sphereSpeedVec = sphereBody->GetLinearVelocity();
        float sphereSpeed = sqrt(sphereSpeedVec.x * sphereSpeedVec.x + sphereSpeedVec.y * sphereSpeedVec.y);
        float KineticEnergy = 0.5f  * sphereSpeed * sphereSpeed;
        std::cout << "Kinetic Energy: " << KineticEnergy << " J\n";
        std::cout << "Ball Speed: " << sphereSpeed * 3.6 << " km/h\n";
        std::cout << "Ball Position: (" << spherePosition.x << "," << spherePosition.y << ")\n";
    }

    // Remember to clean up
    world.DestroyBody(sphereBody);

    return 0;
}