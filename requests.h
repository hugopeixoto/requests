#ifndef HUGOPEIXOTO_NET_REQUESTS_H_
#define HUGOPEIXOTO_NET_REQUESTS_H_

#include <map>
#include <string>

namespace requests {
typedef std::multimap<std::string, std::string> Headers;

struct Response {
  uint32_t status_code;
  Headers headers;
  std::string body;

  Response();
};

struct Request {
  std::string method;
  std::string url;
  Headers headers;
  std::string body;
};

Response get(std::string url, Headers = {});
Response post(std::string url, const std::string &body, Headers = {});
Response put(std::string url, const std::string &body, Headers = {});
Response call(const Request &req);
}

#endif
