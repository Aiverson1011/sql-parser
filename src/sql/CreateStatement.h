#ifndef __CREATE_STATEMENT_H__
#define __CREATE_STATEMENT_H__

#include "SQLStatement.h"

// Note: Implementations of constructors and destructors can be found in statements.cpp.
namespace hsql {
  struct SelectStatement;

  // Represents definition of a table column
  struct ColumnDefinition {
    enum DefinitonType {
        kColumn,
        kPrimaryKey
    };
    enum DataType {
      UNKNOWN,
      TEXT,
      INT,
      DOUBLE
    };

    ColumnDefinition(char* name, DataType type);
    ColumnDefinition();
    virtual ~ColumnDefinition();

    DefinitonType definitionType;
    char* name;
    DataType type;
    std::vector<char*>* primaryKeyColumns;
  };


  // Represents SQL Create statements.
  // Example: "CREATE TABLE students (name TEXT, student_number INTEGER, city TEXT, grade DOUBLE)"
  struct CreateStatement : SQLStatement {
    enum CreateType {
      kTable,
      kTableFromTbl, // Hyrise file format
      kView,
      kIndex
    };

    CreateStatement(CreateType type);
    virtual ~CreateStatement();

    CreateType type;
    bool ifNotExists; // default: false
    char* filePath; // default: NULL
    char* tableName; // default: NULL
    char* indexName; // default: NULL
    char* indexType; // default: NULL
    std::vector<ColumnDefinition*>* columns; // default: NULL
    std::vector<char*>* viewColumns;
    std::vector<char*>* indexColumns;
    SelectStatement* select;
  };

} // namespace hsql
#endif
