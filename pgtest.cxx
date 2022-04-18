#include <iostream>
#include <pqxx/pqxx>

int main(int, char *argv[])
{
  pqxx::connection c{"postgresql://postgres:terces##@localhost/finance"};
  pqxx::work txn{c};

  // Normally we'd query the DB using txn.exec().  But for querying just one
  // single value, we can use txn.query_value() as a shorthand.
  //
  // Use txn.quote() to escape and quote a C++ string for use as an SQL string
  // in a query's text.
  //int vendor_number = txn.query_value<int>(
  //  "SELECT vendor_number "
  //  "FROM vendors"
  //  "WHERE vendor_short_desc = 'Ethos'");


  std::string stmt = "SELECT vendor_number, vendor_short_desc FROM finance.vendors";
  std::string desc = "Testing query from pqxx";
  pqxx::result resultset = txn.exec(stmt, desc);
  pqxx::row row;
  for (pqxx::result::size_type i=0; i < resultset.size(); ++i) {
      row = resultset.at(i);
      std::cout << row["vendor_number"] << " | " << row["vendor_short_desc"] << '\n';
  }

  
  //std::cout  << row["vendor_number"] << '\n';

  // Update the employee's salary.  Use exec0() to perform a query and check
  // that it produces an empty result.  If the result does contain data, it
  // will throw an exception.
  //
  // The ID is an integer, so we don't need to escape and quote it when using
  // it in our query text.  Just convert it to its PostgreSQL string
  // representation using to_string().
  //txn.exec0(
  //  "UPDATE EMPLOYEE "
  //  "SET salary = salary + 1 "
  //  "WHERE id = " + pqxx::to_string(employee_id));

  // Make our change definite.
  //txn.commit();
}