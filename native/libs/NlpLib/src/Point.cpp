#include "Point.hpp"

#include "log.hpp"

#include <format>
#include <string>

Point::Point() : x_(0), y_(0)
{
  logMessage("Point default constructor called");
}
Point::Point(double x, double y) : x_(x), y_(y)
{
  logMessage(
      std::format("Point parameterized constructor called for ({}, {}) {}", x_, y_, (void*) this));
}

Point::Point(const Point& other) : x_(other.x_), y_(other.y_)
{
  logMessage(std::format("Point copy constructor called for ({}, {}) {}", x_, y_, (void*) this));
}

Point& Point::operator=(const Point& other)
{
  if (this != &other)
  {
    x_ = other.x_;
    y_ = other.y_;
    logMessage(
        std::format("Point copy assignment operator called for ({}, {}) {}", x_, y_, (void*) this));
  }
  return *this;
}

Point::Point(Point&& other) noexcept : x_(other.x_), y_(other.y_)
{
  logMessage(std::format("Point move constructor called for ({}, {}) {}", x_, y_, (void*) this));
}

Point& Point::operator=(Point&& other) noexcept
{
  if (this != &other)
  {
    x_ = other.x_;
    y_ = other.y_;
    logMessage(
        std::format("Point move assignment operator called for ({}, {}) {}", x_, y_, (void*) this));
  }
  return *this;
}

Point::~Point()
{
  logMessage(std::format("Point destructor called for ({}, {}) {}", x_, y_, (void*) this));
}
