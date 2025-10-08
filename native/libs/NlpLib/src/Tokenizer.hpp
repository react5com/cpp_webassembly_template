#pragma once

#include <string>
#include <vector>
#include "Point.hpp"

class Tokenizer
{
public:
  Tokenizer() = delete;
  explicit Tokenizer(bool treatPunctuationAsSeparateToken);
  Tokenizer(const Tokenizer&) = default;
  Tokenizer& operator=(const Tokenizer&) = default;
  Tokenizer(Tokenizer&&) = default;
  Tokenizer& operator=(Tokenizer&&) = default;
  ~Tokenizer();
  std::vector<std::string> tokenize(const std::string& text) const;
  std::vector<Point> calculatePoints(int n) const;

protected:
  Point findMeanPoint(const std::vector<Point>& points) const;
private:
  bool treatPunctuationAsSeparateToken_;
};
