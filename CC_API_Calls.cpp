//compile with g++ -std=c++11 CC_API_Calls.cpp -lcurl

#ifndef CC_API_CALLS
#define CC_API_CALLS
#include "CC_API_Calls.hpp"
#include "Data_Downloader.hpp"
#include <ctime>

std::string CC_API_Calls::get_price(std::string coin_symbol) {
  return get_price(coin_symbol, "USD", 0);
}

std::string CC_API_Calls::get_price(std::string coin_symbol, std::string curr_symbol) {
  return get_price(coin_symbol, curr_symbol, 0);
}

std::string CC_API_Calls::get_price(std::string coin_symbol, long int timestamp) {
  return get_price(coin_symbol, "USD", timestamp);
}

std::string CC_API_Calls::get_price(std::string coin_symbol, std::string curr_symbol, long int timestamp) {
  Data_Downloader pr;

  std::string price;
  std::string ts = std::to_string(timestamp);

  if(timestamp == 0)
     price = pr.download("https://min-api.cryptocompare.com/data/price?fsym=" + coin_symbol + "&tsyms=" + curr_symbol);
  else
     price = pr.download("https://min-api.cryptocompare.com/data/pricehistorical?fsym=" + coin_symbol + "&tsyms=" + curr_symbol + "&ts=" + ts + "&extraParams=CryptoTracker");

  int t = 0;
  std::string target = curr_symbol + "\":";
  int index = price.find(target) + target.length();
  for(int i = index; price[i] != '}'; i++)
     t++;

  return price.substr(index, t-1);
}

std::string CC_API_Calls::get_coin_symbol(std::string coin_name) {
  Data_Downloader symbol_data;
  std::string coin_list = symbol_data.download("https://www.cryptocompare.com/api/data/coinlist/");
  std::string target = "\"FullName\":\"" + coin_name + " (";
  unsigned int pos = coin_list.find(target);

  if(pos == std::string::npos)
    coin_list = "";

  else {
    pos = pos + target.length();
    coin_list = coin_list.substr(pos, 40);
    coin_list = coin_list.substr(0, coin_list.find(")"));
  }

  return coin_list;
}

long int CC_API_Calls::get_timestamp() {
  time_t t = std::time(0);
  return t;
}

#endif
