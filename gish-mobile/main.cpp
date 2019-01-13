//
//  main.cpp
//  gish-mobile
//
//  Created by Eugene Velizhenkov on 1/13/19.
//  Copyright © 2019 Yevhenii Velizhenkov. All rights reserved.
//

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "WorldRenderer.hpp"

b2Vec2 gravity(0, 10);
auto world = std::make_shared<b2World>(gravity);

b2ParticleSystem* makeParticleSystem(float radius, float dampingStrength, float gravityScale, float density) {
  b2ParticleSystemDef particleSystemDef;
  particleSystemDef.radius = radius;
  particleSystemDef.dampingStrength = dampingStrength;
  particleSystemDef.gravityScale = gravityScale;
  particleSystemDef.density = density;
  
  b2ParticleSystem *particleSystem = world->CreateParticleSystem(&particleSystemDef);
  
  return particleSystem;
}

void makeParticleBoxForSystem(b2ParticleSystem* particleSystem, b2Vec2 position, b2Vec2 size) {
  b2PolygonShape shape;
  shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
  
  b2ParticleGroupDef particleGroupDef;
  particleGroupDef.flags = b2_waterParticle;
  particleGroupDef.position.Set(position.x, position.y);
  particleGroupDef.shape = &shape;
  
  particleSystem->CreateParticleGroup(particleGroupDef);
}

void makeGround(b2World& World, float X, float Y, int SCALE) {
  b2BodyDef BodyDef;
  BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
  BodyDef.type = b2_staticBody;
  b2Body* Body = World.CreateBody(&BodyDef);
  
  b2PolygonShape Shape;
  Shape.SetAsBox((800.f / 2) / SCALE, (16.f / 2) / SCALE);
  b2FixtureDef FixtureDef;
  FixtureDef.density = 0.f;
  FixtureDef.shape = &Shape;
  Body->CreateFixture(&FixtureDef);
}

void CreateBox(b2World& World, int MouseX, int MouseY, int SCALE)
{
  b2BodyDef BodyDef;
  BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
  BodyDef.type = b2_dynamicBody;
  b2Body* Body = World.CreateBody(&BodyDef);
  
  b2PolygonShape Shape;
  Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
  b2FixtureDef FixtureDef;
  FixtureDef.density = 1.f;
  FixtureDef.friction = 0.7f;
  FixtureDef.shape = &Shape;
  Body->CreateFixture(&FixtureDef);
}

int main(int argc, const char * argv[]) {
  float32 screenWidth = 800.0;
  float32 screenHeight = 600.0;
  sf::RenderWindow window({static_cast<unsigned int>(screenWidth), static_cast<unsigned int>(screenHeight)}, "Zalypa");
  window.setFramerateLimit(60);
  sf::Event event;
  
  const auto scale = 50;
  WorldRenderer renderer{window, scale};
  world->SetDebugDraw(&renderer);
  uint32 flags = 0;
  flags += b2Draw::e_shapeBit;
  flags += b2Draw::e_jointBit;
  flags += b2Draw::e_aabbBit;
  flags += b2Draw::e_pairBit;
  flags += b2Draw::e_centerOfMassBit;
  renderer.SetFlags(flags);
  
  makeGround(*world, screenWidth, screenHeight, scale);
  
  auto ptmRatio = 32.0;
  auto particleRadius =  9.0;
  auto particleSystem = makeParticleSystem(particleRadius / ptmRatio, 0.2, 1, 1.2);
  makeParticleBoxForSystem(particleSystem, {static_cast<float32>(screenWidth * 0.5 / ptmRatio), static_cast<float32>(screenHeight * 0.5 / ptmRatio)}, {static_cast<float32>(50 / ptmRatio), static_cast<float32>(50 / ptmRatio)});
  
  float32 timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;
  
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::EventType::Closed) {
        window.close();
      }
    }
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      int MouseX = sf::Mouse::getPosition(window).x;
      int MouseY = sf::Mouse::getPosition(window).y;
      CreateBox(*world, MouseX, MouseY, scale);
    }
    
    world->Step(timeStep, velocityIterations, positionIterations);
    
    window.clear();
    world->DrawDebugData();
    window.display();
  }
  
  std::cout << "Hello, World!\n";
  return 0;
}
