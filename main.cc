#include "requests.h"
#include <iostream>

int main() {
  auto response = requests::get("https://api.github.com/",
                                {{"User-Agent", "librequests/0.1"}});

  std::cout << response.status_code << std::endl;
  std::cout << response.body << std::endl;

  return 0;
}
