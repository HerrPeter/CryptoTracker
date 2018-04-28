#ifndef CC_API_CALLS
#define CC_API_CALLS

std::string get_price(std::string coin_symbol) {
  return get_price(coin_symbol, "USD", NULL);
}

std::string get_price(std::string coin_symbol, std::string curr_symbol) {
  return get_price(coin_symbol, curr_symbol, NULL);
}

std::string get_price(std::string coin_symbol, std::string curr_symbol, int timestamp) {
  std::string price;

  if(timestamp == NULL)
     price = download("https://min-api.cryptocompare.com/data/price?fsym=" + coin_symbol + "&tsyms=" + curr_symbol);
  else
     price = download("https://min-api.cryptocompare.com/data/pricehistorical?fsym=" + coin_symbol + "&tsyms=" + curr_symbol + "&ts=" + timestamp + "&extraParams=CryptoTracker");

  int t;
  int index = price.find(curr_symbol);
  for(int i = index + curr_symbol.length() + 1; price[i+1] != "}"; i++)
     t++;

  return price.substr(index + curr_symbol.length() +1, t++);
}


#endif
