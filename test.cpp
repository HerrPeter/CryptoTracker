#include "CC_Data.hpp"
#include <string>
#include <iostream>
using namespace std;

int main() {

  CC_Data coin;
  string coin_name;
  cout << "Enter the name of a cryptocurrency to receive its symbol: ";
  cin >> coin_name;
  string coin_symbol = coin.get_coin_symbol(coin_name);
  cout << "The symbol for " << coin_name << " is " << coin_symbol << endl;
}
