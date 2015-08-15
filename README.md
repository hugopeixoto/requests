requests
========

Wrapper around libcurl to make http requests a bit easier.

Example usage:

    #include "requests.h"

    int main() {
      auto response = requests::get(
        "https://api.github.com/",
        {{"User-Agent", "librequests/0.1"}});

      std::cout << response.body << std::endl;

      return 0;
    }

TODO
----

- Parse response headers
- Specify request timeout
- Handle errors
