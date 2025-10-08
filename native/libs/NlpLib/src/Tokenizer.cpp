#include "Tokenizer.hpp"

#include "log.hpp"
#include <format>
#include <string>
#include <vector>
#include <cctype> // for isalnum
#include "Point.hpp"

Tokenizer::Tokenizer(bool treatPunctuationAsSeparateToken)
    : treatPunctuationAsSeparateToken_(treatPunctuationAsSeparateToken)
{
  logMessage(std::format("Tokenizer constructor called with value: {}, {}",
                         treatPunctuationAsSeparateToken_, (void*) this));
}

Tokenizer::~Tokenizer()
{
  logMessage(std::format("Tokenizer destructor called, {}", (void*) this));
}

std::vector<std::string> Tokenizer::tokenize(const std::string& text) const
{
  std::vector<std::string> tokens;
  std::string current;

  for (const char& c : text)
  {
    if (0 != isalnum(c) || c == '\'')
    {
      current += c;
    }
    else
    {
      if (!current.empty())
      {
        tokens.push_back(current);
        current.clear();
      }
      if (treatPunctuationAsSeparateToken_ && 0 != ispunct(c))
      {
        const std::string punct(1, c);
        tokens.push_back(punct);
      }
    }
  }
  if (!current.empty())
  {
    tokens.push_back(current);
  }

  return tokens;
}

std::vector<Point> Tokenizer::calculatePoints(int n) const
{
  std::vector<Point> points;
  const double xStep = 1.0;
  const double yStep = 2.0;
  points.reserve(n);
  for (int i = 0; i < n; ++i)
  {
    points.emplace_back(i * xStep, i * yStep);
  }
  return points;
}

Point Tokenizer::findMeanPoint(const std::vector<Point>& points) const
{
  if (points.empty())
  {
    return { 0.0, 0.0 };
  }

  double sumX = 0.0;
  double sumY = 0.0;
  const auto nPoints = static_cast<double>(points.size());
  for (const auto& point : points)
  {
    sumX += point.getX();
    sumY += point.getY();
  }
  return { sumX / nPoints, sumY / nPoints };
}
