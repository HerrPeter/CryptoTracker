#ifndef _MYSQL_CONN_CPP
#define _MYSQL_CONN_CPP
#include "MySQL_Connect.hpp"
MySQL_conn::MySQL_conn() {
  driver = sql::mysql::get_mysql_driver_instance();
  con = driver->connect("tcp://127.0.0.1.3306", "user","password");
}

MySQL_conn::~MySQL_conn() {
  delete con;
  delete stmt;
  delete res;
  delete pstmt;
}

void MySQL_conn::MySQL_exe(std::string input) {
  con->createStatement();
  stmt->execute(input);
}

sql::ResultSet* MySQL_conn::MySQL_fetch(std::string input) {
  con->createStatement();
  res = stmt->executeQuery(input);
  return res;
}
#endif
