#include <string>

#ifndef _CC_DATA
#define _CC_DATA
class CC_Data {

public:
  CC_Data();
  ~CC_Data();
  std::string data(const std::string& url);
  std::string get_coin_symbol(const std::string& coin_name);
private:
  void* curl;
};

#endif
