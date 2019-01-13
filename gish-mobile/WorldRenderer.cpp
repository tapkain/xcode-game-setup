//
//  WorldRenderer.cpp
//  gish-mobile
//
//  Created by Eugene Velizhenkov on 1/13/19.
//  Copyright © 2019 Yevhenii Velizhenkov. All rights reserved.
//

#include "WorldRenderer.hpp"
#include <array>
#include <cstdio>

sf::Color toSfColor(const b2Color& color) {
  return sf::Color(color.r*255, color.g*255, color.b*255);
}

WorldRenderer::WorldRenderer(sf::RenderTarget &target, int scale) : mTarget(target), mScale(scale) {}

void WorldRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
  sf::VertexArray vertex{sf::LinesStrip, static_cast<size_t>(vertexCount)};
  for (auto i = 0; i < vertexCount; i++) {
    vertex[i].position = sf::Vector2f{vertices[i].x * mScale, vertices[i].y * mScale};
    vertex[i].color = toSfColor(color);
  }
  
  mTarget.draw(vertex);
}

void WorldRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
  sf::VertexArray vertex{sf::TrianglesFan, static_cast<size_t>(vertexCount)};
  for (auto i = 0; i < vertexCount; i++) {
    vertex[i].position = sf::Vector2f{vertices[i].x * mScale, vertices[i].y * mScale};
    vertex[i].color = toSfColor(color);
  }
  
  mTarget.draw(vertex);
}

void WorldRenderer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
  sf::CircleShape circle{radius};
  circle.setOrigin(center.x * mScale, center.y * mScale);
  circle.setOutlineColor(toSfColor(color));
  mTarget.draw(circle);
}

void WorldRenderer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
  sf::CircleShape circle{radius};
  circle.setOrigin(center.x * mScale, center.y * mScale);
  circle.setFillColor(toSfColor(color));
  mTarget.draw(circle);
}

void WorldRenderer::DrawParticles(const b2Vec2 *centers, float32 radius, const b2ParticleColor *colors, int32 count) {
  printf("DrawSolidCircle");
}

void WorldRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
  const auto vertexCount = 2;
  sf::VertexArray vertex{sf::LinesStrip, static_cast<size_t>(vertexCount)};
  std::array<b2Vec2, vertexCount> vertices = {p1, p2};
  
  for (auto i = 0; i < vertexCount; i++) {
    vertex[i].position = sf::Vector2f{vertices[i].x * mScale, vertices[i].y * mScale};
    vertex[i].color = toSfColor(color);
  }
  
  mTarget.draw(vertex);
}

void WorldRenderer::DrawTransform(const b2Transform& xf) {
  b2Vec2 p1 = xf.p, p2;
  const float32 k_axisScale = 0.0f;
  
  p2 = p1 + k_axisScale * xf.q.GetXAxis();
  DrawSegment(p1, p2, b2Color(1, 0, 0));
  
  p2 = p1 + k_axisScale * xf.q.GetYAxis();
  DrawSegment(p1, p2, b2Color(0, 1, 0));
}
