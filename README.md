requests
========

Wrapper around libcurl to make http requests a bit easier.
There are `get`, `post` and `put` functions. If you need something else, create a `Request` object and use `call`.

Example usage:

```c++
#include "hugopeixoto/requests.h"
#include <iostream>

int main() {
  auto response = requests::get(
      "https://api.github.com/",
      {{"User-Agent", "librequests/0.1"}});

  std::cout << response.status_code << std::endl;
  std::cout << response.body << std::endl;

  for (auto kv : response.headers) {
    std::cout << << kv.first << ": " << kv.second << std::endl;
  }

  return 0;
}
```

TODO
----

- Specify request timeout
- Handle errors
