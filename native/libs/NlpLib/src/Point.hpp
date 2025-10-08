#pragma once

class Point
{
public:
  Point();
  Point(double x, double y);
  Point(const Point& other);
  Point& operator=(const Point& other);
  Point(Point&& other) noexcept;
  Point& operator=(Point&& other) noexcept;
  ~Point();
  double getX() const
  {
    return x_;
  }
  double getY() const
  {
    return y_;
  }
  void setX(double newX)
  {
    x_ = newX;
  }
  void setY(double newY)
  {
    y_ = newY;
  }

private:
  double x_;
  double y_;
};