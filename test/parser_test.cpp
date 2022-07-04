#include <hsql/SQLParser.h>
#include <hsql/util/sqlhelper.h>

#include <iostream>
#include <string>
using namespace std;
int main() {
  string sql;
  getline(cin, sql);

  hsql::SQLParserResult result;
  hsql::SQLParser::parse(sql, &result);
  if (result.isValid()) {
    printf("Parsed successfully!\n");
    printf("Number of statements: %lu\n", result.size());

    for (auto i = 0u; i < result.size(); ++i) {
      // Print a statement summary.
      hsql::printStatementInfo(result.getStatement(i));
    }
    return 0;
  } else {
    fprintf(stderr, "Given string is not a valid SQL query.\n");
    fprintf(stderr, "%s (L%d:%d)\n", result.errorMsg(), result.errorLine(),
            result.errorColumn());
    return -1;
  }
}