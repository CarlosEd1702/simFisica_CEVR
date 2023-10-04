#include <iostream>
#include <Box2d/Box2d.h>

int main() {
    b2Vec2 gravity(0.0f, -2.0f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    //Triangulo
    b2Vec2 vT[3];
    vT[0].Set(-7.0f, 7.0f);
    vT[1].Set(-6.0f, 5.0f);
    vT[2].Set(-8.0f, 5.0f);

    int32 countT = 3;
    b2PolygonShape triangle;
    triangle.Set(vT, countT);

    //Rectangulo
    b2Vec2 vR[4];
    vR[0].Set(-3.0f, 4.0f);
    vR[1].Set( 3.0f, 4.0f);
    vR[2].Set( 3.0f, 2.0f);
    vR[3].Set(-3.0f, 2.0f);

    int32 countR = 4;
    b2PolygonShape rectangle;
    rectangle.Set(vR, countR);

    //Cuadrado
    b2Vec2 vS[4];
    vS[0].Set( 6.0f, 7.0f);
    vS[1].Set( 8.0f, 7.0f);
    vS[2].Set( 8.0f, 5.0f);
    vS[3].Set( 6.0f, 5.0f);

    int32 countS = 4;
    b2PolygonShape square;
    square.Set(vS, countS);

    //Pentagono
    b2Vec2 vP[5];
    vP[0].Set( -10.0f, -2.0f);
    vP[1].Set( -7.0f, -4.0f);
    vP[2].Set( -8.0f, -7.0f);
    vP[3].Set( -12.0f, -7.0f);
    vP[4].Set( -13.0f, -4.0f);

    int32 countP = 5;
    b2PolygonShape pentagono;
    pentagono.Set(vP, countP);

    //Hexagono
    b2Vec2 vH[6];
    vH[0].Set( -1.0f, -2.0f);
    vH[1].Set(  1.0f, -2.0f);
    vH[2].Set(  2.0f, -4.0f);
    vH[3].Set( 1.0f, -6.0f);
    vH[4].Set( 2.0f, -4.0f);
    vH[6].Set( -1.0f, -6.0f);

    int32 countH = 6;
    b2PolygonShape hexagono;
    hexagono.Set(vH, countH);

    //Octagono
    b2Vec2 vO[8];
    vO[0].Set( 8.0f, -2.0f);
    vO[1].Set( 10.0f, -2.0f);
    vO[2].Set( 12.0f, -4.0f);
    vO[3].Set( 12.0f, -6.0f);
    vO[4].Set( 10.0f, -8.0f);
    vO[5].Set( 8.0f, -8.0f);
    vO[6].Set( 6.0f, -6.0f);
    vO[7].Set( 6.0f, -4.0f);

    int32 countO = 6;
    b2PolygonShape octagono;
    octagono.Set(vO, countO);



    return 0;
}

