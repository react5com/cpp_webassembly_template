#pragma once
#include <iostream>
#include <string>

static void logMessage(const std::string& msg)
{
#ifdef DEBUG
  std::cout << msg << std::endl;
#endif
}
