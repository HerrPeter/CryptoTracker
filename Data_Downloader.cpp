//compile with g++ Data_Downloader.cpp -lcurl
#ifndef _DD_CPP
#define _DD_CPP
#include <string>
#include <curl/curl.h>
#include <sstream>
#include "Data_Downloader.hpp"


size_t writer (void *ptr, size_t size, size_t nmemb, void *stream) {
  std::string data((const char*) ptr, (size_t) size * nmemb);
  *((std::stringstream*) stream) << data << std::endl;
  return size * nmemb;
}

Data_Downloader::Data_Downloader() {
  curl = curl_easy_init();
}

Data_Downloader::~Data_Downloader() {
  curl_easy_cleanup(curl);
}

//returns API data as a string, if data is not found returns NULL
std::string Data_Downloader::download(const std::string& url) {
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");
  std::stringstream out;
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
  CURLcode res = curl_easy_perform(curl);

  if(res != CURLE_OK)
    return NULL;

  return out.str();
}
#endif
