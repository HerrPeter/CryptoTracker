#include <string>
#include <curl/curl.h>
#include <sstream>
#include "CC_Data.hpp"


size_t writer (void *ptr, size_t size, size_t nmemb, void *stream) {
  std::string data((const char*) ptr, (size_t) size * nmemb);
  *((std::stringstream*) stream) << data << std::endl;
  return size * nmemb;
}

CC_Data::CC_Data() {
  curl = curl_easy_init();
}

CC_Data::~CC_Data() {
  curl_easy_cleanup(curl);
}

std::string CC_Data::data(const std::string& url) {
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");
  std::stringstream out;
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
  CURLcode res = curl_easy_perform(curl);

//  if(res != CURLE_OK)
//    out = NULL;

  return out.str();
}

std::string CC_Data::get_coin_symbol(const std::string& coin_name) {
  std::string target = "\"" + coin_name + " (";
  std::string coin_list = data("https://www.cryptocompare.com/api/data/coinlist");
  int pos = coin_list.find(target);
  coin_list = coin_list.substr(pos + target.length(),5);

  for(int i = 3; i < 5; i++) { 
    if(coin_list[i] == ')') {
      coin_list = coin_list.substr(0, i);
      break;
    }
  }
  return coin_list;
}

