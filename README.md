# cpp_sql_builder

`cpp_sql_builder` is a lightweight, header-only C++ library for constructing SQL queries programmatically. It provides an intuitive API for building `SELECT`, `INSERT`, `UPDATE`, and `DELETE` SQL statements using modern C++.

## Features
- Type-safe SQL query generation
- Header-only (no separate compilation required)
- Supports filtering, ordering, joins, and value bindings
- Chainable API for building complex queries

## Installation

### Using Git Clone

Clone the repository and include the `include/` directory in your project:

```sh
git clone https://github.com/nekzabirov/cpp_sql_builder.git
```

Or, integrate `cpp_sql_builder` as a submodule:

```sh
git submodule add https://github.com/nekzabirov/cpp_sql_builder.git
```

### Using FetchContent with CMake

If using CMake, you can include `cpp_sql_builder` using `FetchContent`:

```cmake
include(FetchContent)
FetchContent_Declare(
    cpp_sql_builder
    GIT_REPOSITORY https://github.com/nekzabirov/cpp_sql_builder.git
    GIT_TAG 1.0.0  # Use the latest version or specify a tag
)
FetchContent_MakeAvailable(cpp_sql_builder)

include_directories(${cpp_sql_builder_SOURCE_DIR}/include)
```

Then, link it in your CMake project:

```cmake
target_link_libraries(your_project PRIVATE cpp_sql_builder)
```

## Usage

### **Select Query**
```cpp
#include "sql_builder/sql.hpp"
#include <iostream>

int main() {
    bool active = true;
    int minAge = 18;
    int limit = 10;
    int offset = 5;
    
    auto query = nek::sql::select("id", "name", "created_at")
                .from("users")
                .where(nek::sql::conditional("active") == active && nek::sql::conditional("age") > minAge)
                .orderBy("created_at", "DESC")
                .limit(limit)
                .offset(offset);

    std::cout << query.to_string();
}
```

### **Insert Query**
```cpp
#include "sql_builder/sql.hpp"
#include <iostream>

int main() {
    std::string name = "Alice";
    int age = 30;
    std::string email = "alice@example.com";
    
    auto query = nek::sql::insert("users", {"name", "age", "email"})
                .values(name, age, email)
                .returning({"id", "created_at"});

    std::cout << query.to_string();
}
```

### **Update Query**
```cpp
#include "sql_builder/sql.hpp"
#include <iostream>

int main() {
    std::string newName = "Bob";
    int newAge = 35;
    int userId = 1;
    
    auto query = nek::sql::update("users")
                .set({
                    nek::sql::set("name", newName),
                    nek::sql::set("age", newAge)
                })
                .where(nek::sql::conditional("id") == userId);

    std::cout << query.to_string();
}
```

### **Delete Query**
```cpp
#include "sql_builder/sql.hpp"
#include <iostream>

int main() {
    int userId = 1;
    auto query = nek::sql::delete_from("users")
                .where(nek::sql::conditional("id") == userId);

    std::cout << query.to_string();
}
```

### **Join Example**
```cpp
#include "sql_builder/sql.hpp"
#include <iostream>

int main() {
    std::string userAlias = "u";
    std::string postAlias = "p";
    
    auto query = nek::sql::select(userAlias + ".id", userAlias + ".name", postAlias + ".id AS post_id", postAlias + ".title")
                .from("users", userAlias)
                .leftJoin("posts", postAlias, nek::sql::conditional(userAlias + ".id") == nek::sql::conditional(postAlias + ".user_id"))
                .where(nek::sql::conditional(userAlias + ".active") == true);

    std::cout << query.to_string();
}
```

## License
This project is licensed under the MIT License.

