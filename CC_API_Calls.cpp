//compile with g++ -std=c++11 CC_API_Calls.cpp -lcurl

#ifndef CC_API_CALLS
#define CC_API_CALLS
#include "Data_Downloader.cpp"
#include <ctime>

std::string get_price(std::string coin_symbol);
std::string get_price(std::string coin_symbol, std::string curr_symbol);
std::string get_price(std::string coin_symbol, long int timestamp);
std::string get_price(std::string coin_symbol, std::string curr_symbol, long int timestamp);
std::string get_coin_symbol(std::string coin_name);
long int get_timestamp();

std::string get_price(std::string coin_symbol) {
  return get_price(coin_symbol, "USD", 0);
}

std::string get_price(std::string coin_symbol, std::string curr_symbol) {
  return get_price(coin_symbol, curr_symbol, 0);
}

std::string get_price(std::string coin_symbol, long int timestamp) {
  return get_price(coin_symbol, "USD", timestamp);
}

std::string get_price(std::string coin_symbol, std::string curr_symbol, long int timestamp) {
  Data_Downloader pr;

  std::string price;
  std::string ts = std::to_string(timestamp);

  if(timestamp == 0)
     price = pr.download("https://min-api.cryptocompare.com/data/price?fsym=" + coin_symbol + "&tsyms=" + curr_symbol);
  else
     price = pr.download("https://min-api.cryptocompare.com/data/pricehistorical?fsym=" + coin_symbol + "&tsyms=" + curr_symbol + "&ts=" + ts + "&extraParams=CryptoTracker");

  int t;
  int index = price.find(curr_symbol);
  for(int i = index + curr_symbol.length() + 1; price[i+1] != '}'; i++)
     t++;

  return price.substr(index + curr_symbol.length() +1, t++);
}

std::string get_coin_symbol(const std::string coin_name) {
  Data_Downloader symbol_data;
  std::string coin_list = 
        symbol_data.download("https://www.cryptocompare.com/api/data/coinlist/");
  std::string target = "\"" + coin_name + " (";
  unsigned int pos = coin_list.find(target);

  if(pos == std::string::npos)
    coin_list = "";

  else {
    coin_list = coin_list.substr(pos + target.length(),5);

    for(int i = 3; i < 5; i++) { 
      if(coin_list[i] == ')') {
        coin_list = coin_list.substr(0, i);
        break;
      }
    }
  }

  return coin_list;
}

long int get_timestamp() {
  time_t t = std::time(0);
  return t;
}

#endif
