#ifndef _MYSQL_CONN
#define _MYSQL_CONN
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class MySQL_conn {
  private:
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    sql::PreparedStatement *pstmt;
  public:
    MySQL_conn();
    ~MySQL_conn();
    void MySQL_exe(std::string input);
    sql::ResultSet* MySQL_fetch(std::string input);
};

#endif
