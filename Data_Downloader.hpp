#ifndef _Data_Downloader
#define _Data_Downloader
#include <string>

class Data_Downloader {

public:
  Data_Downloader();
  ~Data_Downloader();
  std::string download(const std::string& url);
private:
  void* curl;
};

#endif
