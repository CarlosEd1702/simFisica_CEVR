# simFisica_CEVR
Trabajos

Simulación del disparo de una bala, entregando en consola el Tiempo de Impacto de esa bala con el suelo en conjunto con SFML.

#include <Box2D/Box2D.h>
#include <Box2D/b2_time_of_impact.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    b2Vec2 gravity(0.0f, -9.81f);
    b2World world(gravity);

    b2BodyDef bodyDefWorld;
    bodyDefWorld.type = b2_staticBody;
    bodyDefWorld.position.Set(0.0f,0.0f);
    b2Body* bodyWorld = world.CreateBody(&bodyDefWorld);

    b2PolygonShape staticWorld;
    staticWorld.SetAsBox(5.0f,5.0f);

    b2FixtureDef fixtureDefWorld;
    fixtureDefWorld.shape = &staticWorld;
    fixtureDefWorld.density = 5520.0f;
    fixtureDefWorld.friction = 10.0f;
    bodyWorld->CreateFixture(&fixtureDefWorld);
    bodyWorld->SetLinearVelocity(b2Vec2(0.0f,0.0f)); // Does not move

    b2BodyDef bodyDefA;
    bodyDefA.type = b2_dynamicBody;
    bodyDefA.position.Set(0.0f, 40.0f);
    b2Body* bodyA = world.CreateBody(&bodyDefA);

    b2PolygonShape dynamicBoxA;
    dynamicBoxA.SetAsBox(0.05f, 0.02f);

    b2FixtureDef fixtureDefA;
    fixtureDefA.shape = &dynamicBoxA;
    fixtureDefA.density = 1.0f;
    fixtureDefA.friction = 0.3f;
    bodyA->CreateFixture(&fixtureDefA);
    bodyA->SetLinearVelocity(b2Vec2(20.0f, 0.0f));  // Moving rightwards

    // define distance input
    b2DistanceInput distInput;
    distInput.proxyA.Set(&dynamicBoxA, 0);
    distInput.proxyB.Set(&staticWorld, 0);
    distInput.transformA = bodyA->GetTransform();
    distInput.transformB = bodyWorld->GetTransform();
    distInput.useRadii = true;

    // define distance output and cache
    b2DistanceOutput distOutput;
    b2SimplexCache cache;

    // reset cache
    cache.count = 0;

    // calculate the distance
    b2Distance(&distOutput, &cache, &distInput);

    // print the calculated distance
    printf("Distance between bullet and floor: %4.2f m\n", distOutput.distance);

    // Time of impact calculation
    // Initializes the sweep structures for the bodies
    b2Sweep sweepA;
    sweepA.c0 = bodyA->GetPosition();
    sweepA.a0 = bodyA->GetAngle();
    sweepA.c = bodyA->GetWorldCenter() + bodyA->GetLinearVelocity();
    sweepA.a = sweepA.a0;
    sweepA.localCenter.SetZero();

    b2Sweep sweepB;
    sweepB.c0 = bodyWorld->GetPosition();
    sweepB.a0 = bodyWorld->GetAngle();
    sweepB.c = bodyWorld->GetWorldCenter() + bodyWorld->GetLinearVelocity();
    sweepB.a = sweepB.a0;
    sweepB.localCenter.SetZero();

    float tMax = 10.0f;

    b2TOIInput toiInput;
    toiInput.proxyA.Set(&dynamicBoxA, 0);
    toiInput.proxyB.Set(&staticWorld, 0);
    toiInput.sweepA = sweepA;
    toiInput.sweepB = sweepB;
    toiInput.tMax = tMax;

    b2TOIOutput toiOutput{};
    b2TimeOfImpact(&toiOutput, &toiInput);

    float timeOfImpact = toiOutput.t;
    printf("Time of impact: %.2f s\n", timeOfImpact);

    // Create the new Window
    sf::RenderWindow window(sf::VideoMode(800,600),"SFML window");

    sf::Texture texture;
    if(!texture.loadFromFile("shootingRange.png"))
        return EXIT_FAILURE;
    sf::Sprite shootingRange(texture);

    // Load a sprite to display
    sf::Texture texture2;
    if(!texture2.loadFromFile("bullet.png"))
        return EXIT_FAILURE;
    sf::Sprite bullet(texture2);
    bullet.setOrigin(75.f, 50.f);
    bullet.setPosition(400.f,500.f);

    // Start the game loop
    while(window.isOpen()){

        // Process Events
        sf::Event event;
        while(window.pollEvent(event)){

            // Close Window: exit
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        // Clear Screen
        window.clear(sf::Color::Black);

        // Draw the Sprite
        window.draw(shootingRange);
        window.draw(bullet);

        // Update the Window
        window.display();
    }

    return EXIT_SUCCESS;
}