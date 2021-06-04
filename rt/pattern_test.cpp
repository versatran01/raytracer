#include "rt/pattern.h"

#include <doctest/doctest.h>

#include "rt/sphere.h"

namespace {

using namespace rt;

SCENARIO("Creating a stripe pattern") {
  const StripePattern p{colors::kWhite, colors::kBlack};
  CHECK(p.a == colors::kWhite);
  CHECK(p.b == colors::kBlack);
}

SCENARIO("A stripe pattern is constant in y") {
  const StripePattern p{colors::kWhite, colors::kBlack};
  CHECK(p.PatternAt({0, 0, 0}) == colors::kWhite);
  CHECK(p.PatternAt({0, 1, 0}) == colors::kWhite);
  CHECK(p.PatternAt({0, 2, 0}) == colors::kWhite);
}

SCENARIO("A stripe pattern is constant in z") {
  const StripePattern p{colors::kWhite, colors::kBlack};
  CHECK(p.PatternAt({0, 0, 0}) == colors::kWhite);
  CHECK(p.PatternAt({0, 0, 1}) == colors::kWhite);
  CHECK(p.PatternAt({0, 0, 2}) == colors::kWhite);
}

SCENARIO("A stripe pattern alternates in z") {
  const StripePattern p{colors::kWhite, colors::kBlack};
  CHECK(p.PatternAt({0, 0, 0}) == colors::kWhite);
  CHECK(p.PatternAt({0.9, 0, 0}) == colors::kWhite);
  CHECK(p.PatternAt({1, 0, 0}) == colors::kBlack);
  CHECK(p.PatternAt({-0.1, 0, 0}) == colors::kBlack);
  CHECK(p.PatternAt({-1, 0, 0}) == colors::kBlack);
  CHECK(p.PatternAt({-1.1, 0, 0}) == colors::kWhite);
}

SCENARIO("Stipes with an object transformation") {
  Sphere s;
  s.transform = Scaling3(2);
  const StripePattern sp;
  const auto c = sp.PatternAtShape(s, Point3(1.5, 0, 0));
  CHECK(c == colors::kWhite);
}

SCENARIO("Stipes with a pattern transformation") {
  Sphere s;
  StripePattern p{colors::kWhite, colors::kBlack};
  p.transform = Scaling3(2);
  const auto c = p.PatternAtShape(s, Point3(1.5, 0, 0));
  CHECK(c == colors::kWhite);
}

SCENARIO("Stipes with both an object and a pattern transformation") {
  Sphere s;
  s.transform = Scaling3(2);
  StripePattern p{colors::kWhite, colors::kBlack};
  p.transform = Translation3(0.5, 0, 0);
  const auto c = p.PatternAtShape(s, Point3(2.5, 0, 0));
  CHECK(c == colors::kWhite);
}

SCENARIO("A pattern with an object transformation 2") {
  Sphere s;
  s.transform = Scaling3(2);
  const Pattern p;
  CHECK(p.PatternAtShape(s, {2, 3, 4}) == Color(1, 1.5, 2));
}

SCENARIO("A pattern with a pattern transformation 2") {
  const Sphere s;
  Pattern p;
  p.transform = Scaling3(2);

  CHECK(p.PatternAtShape(s, {2, 3, 4}) == Color(1, 1.5, 2));
}

SCENARIO("A pattern with both an object and a pattern transformation 2") {
  Sphere s;
  s.transform = Scaling3(2);
  Pattern p;
  p.transform = Translation3(0.5, 1, 1.5);

  CHECK(p.PatternAtShape(s, {2.5, 3, 3.5}) == Color(0.75, 0.5, 0.25));
}

SCENARIO("A gradient linearly interpolates between colors") {
  const GradientPattern p;
  CHECK(p.PatternAt({0, 0, 0}) == Color::White());
  CHECK(p.PatternAt({0.25, 0, 0}) == Color::Constant(0.75));
  CHECK(p.PatternAt({0.5, 0, 0}) == Color::Constant(0.5));
  CHECK(p.PatternAt({0.75, 0, 0}) == Color::Constant(0.25));
}

SCENARIO("A ring shoudl extend in both x and z") {
  const RingPattern p;
  CHECK(p.PatternAt({0, 0, 0}) == Color::White());
  CHECK(p.PatternAt({1, 0, 0}) == Color::Black());
  CHECK(p.PatternAt({0, 0, 1}) == Color::Black());
  CHECK(p.PatternAt({0.708, 0, 0.708}) == Color::Black());
}

SCENARIO("Checkers should repeat in x") {
  const CheckerPattern p;
  CHECK(p.PatternAt({0, 0, 0}) == Color::White());
  CHECK(p.PatternAt({0.99, 0, 0}) == Color::White());
  CHECK(p.PatternAt({1.01, 0, 0}) == Color::Black());
}

SCENARIO("Checkers should repeat in y") {
  const CheckerPattern p;
  CHECK(p.PatternAt({0, 0, 0}) == Color::White());
  CHECK(p.PatternAt({0, 0.99, 0}) == Color::White());
  CHECK(p.PatternAt({0, 1.01, 0}) == Color::Black());
}

SCENARIO("Checkers should repeat in z") {
  const CheckerPattern p;
  CHECK(p.PatternAt({0, 0, 0}) == Color::White());
  CHECK(p.PatternAt({0, 0, 0.99}) == Color::White());
  CHECK(p.PatternAt({0, 0, 1.01}) == Color::Black());
}

}  // namespace