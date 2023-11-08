#include <iostream>
#include <Box2D/Box2D.h>
#include <Box2D/b2_time_of_impact.h>
#include <Box2D/b2_wheel_joint.h>
#include <SFML/Graphics.hpp>

constexpr float SCALE = 30.0f;

class Ball {
public:
    Ball(b2World &world, float x, float y, float density = 1.0f){
        b2BodyDef bodyDef;
        bodyDef.position.Set(x / SCALE, y / SCALE);

        bodyDef.type = b2_dynamicBody;

        body = world.CreateBody(&bodyDef);

        b2CircleShape dynamicBall;
        dynamicBall.m_radius = (10.0f /  2) / SCALE;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBall;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        body->CreateFixture(&fixtureDef);

        sphere.setRadius(500.0f / SCALE);
        sphere.setFillColor(sf::Color::Red);
        sphere.setOrigin(5.0f,5.0f);
    }

    void update(){
        sphere.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        sphere.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const{
        win.draw(sphere);
    }

    void resetPosition() {
        body->SetTransform(b2Vec2(0, 0), body->GetAngle());
    }

    void stop() {
        body->SetLinearVelocity(b2Vec2(0, 0));
    }

    b2Body *getBody() {
        return body;
    }

private:
    sf::CircleShape sphere;
    b2Body *body;
};

int main() {
    // Create the SFML Window
    sf::RenderWindow window(sf::VideoMode(800,600),"Examen Simuladores de Fisica");

    // Creating the World
    b2Vec2 gravity(0.0f, -0.01f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f / SCALE, 0.0f / SCALE);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f / SCALE, 10.0f / SCALE);

    groundBody->CreateFixture(&groundBox, 0.0f);

    // Creating the Ball in the Scene

    Ball ball(world, 100, 305);
    Ball ball2(world, 500, 200);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(100,300);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape staticStartPoint;
    staticStartPoint.SetAsBox(5.0f,10.0f);

    b2WheelJointDef jointDef;
    jointDef.Initialize(ball.getBody(), ball2.getBody(), ball.getBody()->GetWorldCenter(), b2Vec2(0,1));
    jointDef.enableMotor = true;
    jointDef.maxMotorTorque= 1.0f;
    jointDef.motorSpeed = 0.1f;

    b2WheelJoint* joint = (b2WheelJoint*)world.CreateJoint(&jointDef);

// Start the game loop
    while(window.isOpen()){
        // Process Events
        sf::Event event{
            
        };

        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                ball.getBody()->ApplyForceToCenter(b2Vec2(0.1f, 0.0f), true);
                ball2.getBody()->ApplyForceToCenter(b2Vec2(0.1f, 0.0f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                ball.getBody()->ApplyForceToCenter(b2Vec2(-0.1f, 0.0f), true);
                ball2.getBody()->ApplyForceToCenter(b2Vec2(-0.1f, 0.0f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                ball.getBody()->ApplyForceToCenter(b2Vec2(0.0f, -0.1f), true);
                ball2.getBody()->ApplyForceToCenter(b2Vec2(0.0f, -0.1f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                ball.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 0.1f), true);
                ball2.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 0.1f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                ball.resetPosition();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                ball.stop();
                ball.stop();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                window.close();
            }
        }

        world.Step(1 / 60.f, 8, 3);
        ball.update();

        window.clear();
        ball.draw(window);
        ball2.draw(window);
        window.display();

    }
    return 0;
}
