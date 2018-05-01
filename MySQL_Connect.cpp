//g++ -Wall -I/usr/include/cppconn MySQL_Connect.cpp -L/usr/lib -lmysqlcppconn
#ifndef _MYSQL_CONN_CPP
#define _MYSQL_CONN_CPP
#include "MySQL_Connect.hpp"
MySQL_conn::MySQL_conn() {
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1", "CryptoTracker","CryptoTracker");
}

MySQL_conn::~MySQL_conn() {
  con = NULL;
  stmt = NULL;
  res = NULL;
  pstmt = NULL;
  delete con;
  delete stmt;
  delete res;
  delete pstmt;
}

void MySQL_conn::MySQL_exe(std::string input) {
  stmt = con->createStatement();
  stmt->execute("USE CryptoTracker");
  stmt->execute(input);
}

sql::ResultSet* MySQL_conn::MySQL_fetch() {
  return res;
}

void MySQL_conn::MySQL_result(sql::ResultSet* query) {
  res = query;
}

void MySQL_conn::MySQL_prep_exe(std::string input) {
  stmt = con->createStatement();
  stmt->execute("USE CryptoTracker");
  pstmt = con->prepareStatement(input);
}

sql::PreparedStatement* MySQL_conn::MySQL_prep() {
  return pstmt;
}
#endif
