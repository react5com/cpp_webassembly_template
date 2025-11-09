#include "Tokenizer.embind.hpp"
#include "Point.embind.hpp"
#include <emscripten/emscripten.h>
#include <sanitizer/lsan_interface.h>

int main()
{
  return 0;
}

extern "C" EMSCRIPTEN_KEEPALIVE void lsan_check_now() {
  //__lsan_do_leak_check();
  // or non-fatal variant:
  __lsan_do_recoverable_leak_check();
}
