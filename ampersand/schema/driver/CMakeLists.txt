cmake_minimum_required(VERSION 3.12)

project    (ampersand.schema.driver VERSION 0.1.0 LANGUAGES C)
add_library(ampersand.schema.driver STATIC
            driver.h
            driver_type.h
            driver.c
            schema_type.h
            schema_init.h
            schema_manip.h
            schema_init.c
            schema_manip.c)