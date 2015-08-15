#include "requests.h"
#include <curl/curl.h>

static int body_writer(char *data, size_t size, size_t nmemb,
                       requests::Response *response) {
  response->body.append(data, size * nmemb);
  return size * nmemb;
}

static int header_writer(char *data, size_t size, size_t nmemb,
                         requests::Response *response) {
  // TODO: implement this. curl doesn't make this easy.

  return size * nmemb;
}

requests::Response::Response() { status_code = 0; }

requests::Response requests::get(std::string url, Headers headers) {
  Request req;

  req.method = "GET";
  req.url = url;
  req.headers = headers;

  return call(req);
}

requests::Response requests::post(std::string url, const std::string &body,
                                  Headers headers) {
  Request req;

  req.method = "POST";
  req.url = url;
  req.headers = headers;
  req.body = body;

  return call(req);
}

requests::Response requests::put(std::string url, const std::string &body,
                                 Headers headers) {
  Request req;

  req.method = "PUT";
  req.url = url;
  req.headers = headers;
  req.body = body;

  return call(req);
}

requests::Response requests::call(const Request &request) {
  requests::Response response;

  CURL *curl = curl_easy_init();

  struct curl_slist *headers = nullptr;

  for (auto header : request.headers) {
    std::string header_line = header.first + ": " + header.second;
    headers = curl_slist_append(headers, header_line.c_str());
  }

  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request.method.c_str());
  curl_easy_setopt(curl, CURLOPT_URL, request.url.c_str());
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.body.c_str());

  curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

  // curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
  // curl_easy_setopt(curl, CURLOPT_ENCODING, "identity");

  curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 10);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

  curl_easy_setopt(curl, CURLOPT_HEADER, 0);

  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, body_writer);

  curl_easy_setopt(curl, CURLOPT_WRITEHEADER, &response);
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_writer);

  curl_easy_perform(curl);
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status_code);

  curl_slist_free_all(headers);
  curl_easy_cleanup(curl);

  return response;
}
