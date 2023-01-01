cmake_minimum_required(VERSION 3.12)
project(ampersand
        VERSION 0.1.0
        LANGUAGES CXX)

add_subdirectory   (submodule/mp11)
add_subdirectory   (submodule/jsoncpp)
set                (CMAKE_CXX_STANDARD 20)
set                (CMAKE_C_STANDARD   11)

option(AMPERSAND_BUILD_EXAMPLES ON)

option(AMPERSAND_FEATURE_PROTO  ON)
option(AMPERSAND_FEATURE_MYSQL  ON)
option(AMPERSAND_FEATURE_JSON   ON)
option(AMPERSAND_FEATURE_SCHEMA ON)
option(AMPERSAND_FEATURE_POLY   ON)

if(WIN32)
        set(AMPERSAND_EXTERNAL_MYSQL_INCLUDEPATH "C:/Program Files/MySQL/Connector C++ 8.0/include")
        set(AMPERSAND_EXTERNAL_MYSQL_LIBPATH     "C:/Program Files/MySQL/Connector C++ 8.0/lib64/vs14")
endif()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/submodule/mp11/include)

if(AMPERSAND_FEATURE_MYSQL)
        include_directories(${AMPERSAND_EXTERNAL_MYSQL_INCLUDEPATH})
        link_libraries     (${AMPERSAND_EXTERNAL_MYSQL_LIBPATH}/mysqlcppconn.lib)
        link_libraries     (${AMPERSAND_EXTERNAL_MYSQL_LIBPATH}/mysqlcppconn-static.lib)
        link_libraries     (${AMPERSAND_EXTERNAL_MYSQL_LIBPATH}/libcrypto.lib)
        link_libraries     (${AMPERSAND_EXTERNAL_MYSQL_LIBPATH}/libssl.lib)
endif()

add_subdirectory(ampersand/meta)

if (AMPERSAND_FEATURE_JSON)
        include_directories(${CMAKE_SOURCE_DIR}/submodule/jsoncpp/include)
        add_subdirectory(ampersand/extension/json)
endif()

if (AMPERSAND_FEATURE_PROTO)
        add_subdirectory(ampersand/proto)
endif()

if(AMPERSAND_FEATURE_MYSQL)
        add_subdirectory(ampersand/extension/mysql)
endif()

if(AMPERSAND_FEATURE_SCHEMA)
        add_subdirectory(ampersand/schema)
endif()

if(AMPERSAND_FEATURE_POLY)
        include_directories(${CMAKE_SOURCE_DIR}/submodule/crisp)
        add_subdirectory(poly_machine)
        add_subdirectory(ampersand/poly)
        add_subdirectory(submodule/crisp)
endif()

if(BUILD_EXAMPLES)
        add_subdirectory(example/meta)

        if(AMPERSAND_FEATURE_PROTO)
                add_subdirectory(example/proto)
        endif()

        if(AMPERSAND_FEATURE_MYSQL)
                add_subdirectory(example/extension/mysql)
        endif()

        if(AMPERSAND_FEATURE_JSON)
                add_subdirectory(example/extension/json)
        endif()

        if(AMPERSAND_FEATURE_SCHEMA)
                add_subdirectory(example/schema)
        endif()

        if(AMPERSAND_FEATURE_POLY)
                add_subdirectory(example/poly)
        endif()
endif()