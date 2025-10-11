#include "Tokenizer.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Tokenizer Test - Punctuation as Separate Token", "[Tokenizer]")
{
  Tokenizer tokenizer(true);
  REQUIRE(tokenizer.tokenize("Hello, world!") ==
          std::vector<std::string>{"Hello", ",", "world", "!"});
}

TEST_CASE("Tokenizer Test - Punctuation No Separate Token", "[Tokenizer]")
{
  Tokenizer tokenizer(false);
  REQUIRE(tokenizer.tokenize("Hello, world!") == std::vector<std::string>{"Hello", "world"});
}

TEST_CASE("Point Calculation Test", "[Tokenizer]")
{
  Tokenizer tokenizer(true);
  auto points = tokenizer.calculatePoints(2);
  REQUIRE(points.size() == 2);
  REQUIRE(points[0].getX() == 0.0);
  REQUIRE(points[0].getY() == 0.0);
  REQUIRE(points[1].getX() == 1.0);
  REQUIRE(points[1].getY() == 2.0);
}