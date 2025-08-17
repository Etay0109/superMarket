cmake_minimum_required(VERSION 3.30)
project(Part1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Part1 main.c
        customer.c
        customer.h
        date.c
        date.h
        product.c
        product.h
        shoppingcart.c
        shoppingcart.h
        shoppingitem.c
        shoppingitem.h
        supermarket.c
        supermarket.h)
