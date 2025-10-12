#pragma once

#ifdef __EMSCRIPTEN__
#include "Tokenizer.hpp"
#include <emscripten/bind.h>
#include <emscripten/val.h>
#endif

#ifdef __EMSCRIPTEN__

static emscripten::val vector_string_to_js_array(const std::vector<std::string>& v)
{
  emscripten::val arr = emscripten::val::array();
  for (unsigned i = 0; i < v.size(); ++i)
    arr.set(i, v[i]);
  return arr;
}
emscripten::val tokenize_wrapper(Tokenizer& self, const std::string& text)
{
  return vector_string_to_js_array(self.tokenize(text));
}

EMSCRIPTEN_BINDINGS(Tokenizer)
{
  emscripten::register_vector<std::string>("VectorString");
  emscripten::register_vector<Point>("VectorPoint");
  emscripten::class_<Tokenizer>("Tokenizer")
      .constructor<bool>()
      .function("tokenize", &Tokenizer::tokenize)
      .function("tokenize2", &tokenize_wrapper)
      .function("calculatePoints", &Tokenizer::calculatePoints);
}
#endif
