#ifdef __EMSCRIPTEN__
#include "Point.hpp"
#include <emscripten/bind.h>
#endif

#ifdef __EMSCRIPTEN__

EMSCRIPTEN_BINDINGS(Point)
{
  emscripten::class_<Point>("Point")
      .constructor<double, double>()
      .property("x", &Point::getX)
      .property("y", &Point::getY);
}
#endif
