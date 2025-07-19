cmake_minimum_required(VERSION 3.14)
project(QueryHouse)

set(BUILD_SHARED_LIBS ON)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O2 -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
find_package(PkgConfig)

# Target DBMSs
option(ALL "Build all types of database" ON)
option(SQLITE "Build sqlite" OFF)
option(MYSQL "Build mysql" OFF)
option(POSTGRESQL "Build postgresql" OFF)
option(ORACLE "Build oracle" OFF)
option(MARIADB "Build mariadb" OFF)

if (ALL)
  set(SQLITE ON)
  set(MYSQL ON)
  set(POSTGRESQL ON)
  set(ORACLE ON)
  set(MARIADB ON)
endif()

#  BATCH_SIZE   Number of queries in a batch execution (positive integers)
#               add `-DBATCH_SIZE=N` (default: 100)
#               Bad or too large values can result in errors.
#               Zero will default to predefined value.
option(BATCH_SIZE "Number of queries in a batch execution" 100)
if(BATCH_SIZE)
  add_compile_definitions(BATCH_SIZE=${BATCH_SIZE})
endif()

#  ENABLE_TRANSPILER  Enable transpiler (default: ON)
#                     Add `-DENABLE_TRANSPILER=OFF` to execute exactly same queries in DBMSs
#                     For evaluation-use only.
option(ENABLE_TRANSPILER "Enable transpiler" ON)
if (ENABLE_TRANSPILER)
    add_compile_definitions(ENABLE_TRANSPILER)
endif()

# LOG_KWCOV  Enable keyword coverage logging (default: OFF)
#            Add `-DLOG_KWCOV=ON` to enable keyword coverage logging
option(LOG_KWCOV "Enable keyword coverage logging" OFF)
if (LOG_KWCOV)
    add_compile_definitions(LOG_KWCOV)
endif()

# LOG_INSTANT_KWCOV  Enable instantaneous keyword coverage logging (default: OFF)
#                    Add `-DLOG_INSTANT_KWCOV=ON` to enable instantaneous keyword coverage logging
# TODO: Check if kwcov is reset when llm is disabled
option(LOG_INSTANT_KWCOV "Enable instantaneous keyword coverage logging" OFF)
if (LOG_INSTANT_KWCOV)
    add_compile_definitions(LOG_INSTANT_KWCOV)
endif()

# LOG_LLM  Enable LLM invocation logging (default: OFF)
#          Add `-DLOG_LLM=ON` to enable LLM invocation logging
option(LOG_LLM "Enable LLM invocation logging" OFF)
if (LOG_LLM)
    add_compile_definitions(LOG_LLM)
endif()

# LOG_INPUT  Enable input logging (default: OFF)
#            Add `-DLOG_INPUT=ON` to enable input logging
option(LOG_INPUT "Enable input logging" OFF)
if (LOG_INPUT)
    add_compile_definitions(LOG_INPUT)
endif()

# LOG_TRANSPILE_FAIL  Enable transpiler failure logging (default: OFF)
#                     Add `-DLOG_TRANSPILE_FAIL=ON` to enable transpiler failure logging
option(LOG_TRANSPILE_FAIL "Enable transpiler failure logging" OFF)
if (LOG_TRANSPILE_FAIL)
    add_compile_definitions(LOG_TRANSPILE_FAIL)
endif()

# Pybind
include(FetchContent)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG        v2.10.1
)
FetchContent_MakeAvailable(pybind11)

# Build DBMS client
if(MYSQL)
  pkg_check_modules(MySQL REQUIRED mysqlclient>=5.7)
  message(STATUS "MySQL include directories: ${MySQL_INCLUDE_DIRS}")
  add_library(mysql_client OBJECT srcs/internal/client/client_mysql.cc)
  target_include_directories(mysql_client BEFORE PUBLIC
      ${MySQL_INCLUDE_DIRS}                              # MySQL headers
      ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/client   # Other includes
  )
  target_link_libraries(mysql_client PUBLIC ${MySQL_LIBRARIES} ${YAML_CPP_LIBRARIES})
  target_compile_options(mysql_client PRIVATE -fPIC)
  list(APPEND LINK_CLIENT mysql_client)
  list(APPEND CLIENT_DEFINITION __QUERYHOUSE_MYSQL__)
endif()

if(POSTGRESQL)
  find_package(PostgreSQL REQUIRED)
  add_library(postgresql_client OBJECT srcs/internal/client/client_postgresql.cc)
  target_include_directories(postgresql_client PUBLIC 
      ${PostgreSQL_INCLUDE_DIRS}                        # PostgreSQL headers 
      ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/client  # Other includes
  )
  target_link_libraries(postgresql_client PUBLIC ${PostgreSQL_LIBRARIES} ${YAML_CPP_LIBRARIES}
                        absl::strings absl::str_format)
  target_compile_options(postgresql_client PRIVATE -fPIC)
  list(APPEND LINK_CLIENT postgresql_client)
  list(APPEND CLIENT_DEFINITION __QUERYHOUSE_POSTGRESQL__)
endif()

if(SQLITE)
  list(APPEND DBMS sqlite)
  find_package(SQLite3 REQUIRED)
  add_library(sqlite_client OBJECT srcs/internal/client/client_sqlite.cc)
  target_include_directories(sqlite_client PUBLIC
      ${SQLite3_INCLUDE_DIRS}                           # SQLite headers
      ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/client  # Other includes
  )
  target_link_libraries(sqlite_client PUBLIC ${SQLite3_LIBRARIES} ${YAML_CPP_LIBRARIES}
                        absl::strings absl::str_format)
  target_compile_options(sqlite_client PRIVATE -fPIC)
  list(APPEND LINK_CLIENT sqlite_client)
  list(APPEND CLIENT_DEFINITION __QUERYHOUSE_SQLITE__)
endif()

if(ORACLE)
  set(Oracle_INCLUDE_DIRS "/opt/oracle/product/23ai/dbhomeFree/lib/SDK/instantclient_23_5/sdk/include")
  set(Oracle_LIBRARY_DIRS "/opt/oracle/product/23ai/dbhomeFree/lib/OCI/instantclient_23_5")
  find_library(Oracle_LIBRARIES NAMES clntsh PATHS ${Oracle_LIBRARY_DIRS} NO_DEFAULT_PATH)
  if(Oracle_LIBRARIES)
    message(STATUS "Found Oracle Client Library: ${Oracle_LIBRARIES}")
  else()
    message(FATAL_ERROR "Oracle Client Library (libclntsh.so) not found")
  endif()
  add_library(oracle_client OBJECT srcs/internal/client/client_oracle.cc)
  target_include_directories(oracle_client PUBLIC 
      ${Oracle_INCLUDE_DIRS}                            # OracleDB headers
      ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/client  # Other includes
  )
  target_link_directories(oracle_client PUBLIC ${Oracle_LIBRARY_DIRS})
  target_link_libraries(oracle_client PUBLIC ${Oracle_LIBRARIES} ${YAML_CPP_LIBRARIES})
  target_compile_options(oracle_client PRIVATE -fPIC)
  list(APPEND LINK_CLIENT oracle_client)
  list(APPEND CLIENT_DEFINITION __QUERYHOUSE_ORACLE__)
endif()

if(MARIADB)
  set(MARIADB_INCLUDE_DIR /usr/local/mariadb/include/mysql)
  set(MARIADB_LIBRARY /usr/local/mariadb/lib/libmariadb.so)
  add_library(mariadb_client OBJECT srcs/internal/client/client_mariadb.cc)
  target_include_directories(mariadb_client PUBLIC 
      ${MARIADB_INCLUDE_DIR}                            # MariaDB headers
      ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/client  # Other includes
  )
  target_link_libraries(mariadb_client PUBLIC ${MARIADB_LIBRARY} ${YAML_CPP_LIBRARIES})
  target_compile_options(mariadb_client PRIVATE -fPIC)
  list(APPEND LINK_CLIENT mariadb_client)
  list(APPEND CLIENT_DEFINITION __QUERYHOUSE_MARIADB__)
endif()

# YAML-CPP
include(FetchContent)
find_package(yaml-cpp REQUIRED)
include_directories(${YAML_INCLUDE_DIRS})

set(ABSL_PROPAGATE_CXX_STD ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
add_subdirectory(third_party/abseil-cpp)
string(REPLACE " -w" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(AFLPP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/AFLplusplus/include)
include_directories(${AFLPP_DIR})

# Mutator build (DBMS = { "sqlite" })
foreach(dbms IN LISTS DBMS)
  add_library(${dbms}_impl OBJECT
    srcs/internal/${dbms}/${dbms}.cc
    srcs/internal/${dbms}/${dbms}.h
    srcs/internal/${dbms}/srcs/ast.cpp
    srcs/internal/${dbms}/srcs/mutator.cpp
    srcs/internal/${dbms}/srcs/utils.cpp
    srcs/internal/${dbms}/parser/bison_parser.cpp
    srcs/internal/${dbms}/parser/flex_lexer.cpp
    srcs/transpile.cc
    srcs/postprocess.cc
    srcs/cov/kwcov.cpp
  )
  target_include_directories(${dbms}_impl PRIVATE 
      ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/${dbms}/include 
      ${CMAKE_CURRENT_SOURCE_DIR}/srcs)
  # sqlite_impl needs to include the directory that contains client.h
  if("${dbms}" STREQUAL "sqlite")
    target_include_directories(sqlite_impl PRIVATE 
      ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/client)
  endif()
  target_compile_options(${dbms}_impl PRIVATE -fPIC)
  target_link_libraries(${dbms}_impl ${YAML_CPP_LIBRARIES} absl::strings
                        absl::str_format pybind11::embed llm_api common)

  string(TOUPPER ${dbms} UPPER_CASE_DBMS)
  add_library(${dbms}_mutator SHARED srcs/custom_mutator.cc srcs/db_factory.cc)
  target_link_libraries(${dbms}_mutator ${dbms}_impl config_validator string_helpers common)
  target_include_directories(${dbms}_mutator PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/${dbms} 
        ${CMAKE_CURRENT_SOURCE_DIR}/srcs
        ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/client)
  target_compile_definitions(${dbms}_mutator PRIVATE __QUERYHOUSE_${UPPER_CASE_DBMS}__)
endforeach()

# Driver build 
if(MYSQL OR POSTGRESQL OR SQLITE)
  # Exclude global include_directories
  # Force include order for each target
  # add_library(libs OBJECT
  #   srcs/executor.cc
  #   # srcs/internal/sqlite/srcs/ast.cpp
  #   # srcs/internal/sqlite/srcs/mutator.cpp
  #   # srcs/internal/sqlite/srcs/utils.cpp
  #   # srcs/internal/sqlite/parser/bison_parser.cpp
  #   # srcs/internal/sqlite/parser/flex_lexer.cpp
  # )
  # target_include_directories(libs PUBLIC 
  #     ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/client)
  #     # ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/sqlite/include)
  # target_link_libraries(libs PRIVATE common)
      
  add_executable(db_driver srcs/db_driver.cc srcs/executor.cc)
  target_include_directories(db_driver PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/client)
    # ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/sqlite/include
    # ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/sqlite/srcs)
  target_link_libraries(db_driver ${YAML_CPP_LIBRARIES} common all_client string_helpers)
    # libs absl::strings absl::str_format pybind11::embed llm_api)

  add_library(all_client SHARED srcs/internal/client/client.cc)
  target_include_directories(all_client BEFORE PUBLIC
      ${MySQL_INCLUDE_DIRS}                               # /usr/include/mysql, from pkg-config
      ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/client
  )
  # Higher priority for MySQL headers (registered as system include)
  target_compile_options(all_client PRIVATE "-isystem/usr/include/mysql")
  target_link_libraries(all_client PUBLIC ${LINK_CLIENT})
  target_compile_definitions(all_client PRIVATE ${CLIENT_DEFINITION})
endif()

# config_validator
add_library(config_validator OBJECT srcs/utils/config_validate.cc)
target_include_directories(config_validator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/srcs/utils)
target_link_libraries(config_validator PRIVATE ${YAML_CPP_LIBRARIES}
                                               absl::strings absl::str_format)
target_compile_options(config_validator PRIVATE -fPIC)

# string_helpers
add_library(string_helpers OBJECT srcs/utils/string_helpers.cpp)
target_include_directories(string_helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/srcs/utils)
target_link_libraries(string_helpers PRIVATE ${YAML_CPP_LIBRARIES}
                                               absl::strings absl::str_format)
target_compile_options(string_helpers PRIVATE -fPIC)

# common
add_library(common OBJECT srcs/common.cc)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/srcs)
target_compile_options(common PRIVATE -fPIC)

# llm_api
add_library(llm_api SHARED srcs/llm_api.cc)
target_include_directories(llm_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/srcs)
target_link_libraries(llm_api PRIVATE pybind11::embed)

# seed_formatter executable
add_executable(seed_formatter srcs/utils/seed_formatter.cc)
target_include_directories(seed_formatter PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/sqlite/include
  ${CMAKE_CURRENT_SOURCE_DIR}/srcs/internal/client
  ${CMAKE_CURRENT_SOURCE_DIR}/srcs)
target_link_libraries(seed_formatter PRIVATE sqlite_mutator)
target_compile_definitions(seed_formatter PRIVATE ${CLIENT_DEFINITION})

include(lint.cmake)
