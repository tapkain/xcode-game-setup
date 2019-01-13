//
//  WorldRenderer.hpp
//  gish-mobile
//
//  Created by Eugene Velizhenkov on 1/13/19.
//  Copyright © 2019 Yevhenii Velizhenkov. All rights reserved.
//

#ifndef WorldRenderer_hpp
#define WorldRenderer_hpp

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

struct WorldRenderer: public b2Draw {
  WorldRenderer(sf::RenderTarget &target, int scale);
  
  void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
  
  void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
  
  void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
  
  void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
  
  void DrawParticles(const b2Vec2 *centers, float32 radius, const b2ParticleColor *colors, int32 count);
  
  void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
  
  void DrawTransform(const b2Transform& xf);
  
private:
  sf::RenderTarget &mTarget;
  int mScale;
};

#endif /* WorldRenderer_hpp */
