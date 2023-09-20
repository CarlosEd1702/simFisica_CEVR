#include <iostream>
#include <Box2d/Box2d.h>

//Dejar caer un cubo de Carburo de Tungsteno a 15 metros de altura en la luna

int main(){
    b2Vec2 gravity(0.0f, -2.0f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);

    groundBody->CreateFixture(&groundBox, 3340.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 15.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 15630.0f;
    fixtureDef.friction = 0.0f;

    body->CreateFixture(&fixtureDef);

    float timeStep = 1.0f;

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for (int32 i = 0; i < 8; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }
}