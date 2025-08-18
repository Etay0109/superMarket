cmake_minimum_required(VERSION 3.30)
project(Part2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Part2 main.c
        main.h
        ClubMember.c
        ClubMember.h
        Customer.c
        Customer.h
        Date.c
        Date.h
        def.h
        General.c
        General.h
        list.c
        list.h
        Product.c
        Product.h
        ShoppingCart.c
        ShoppingCart.h
        ShoppingItem.c
        ShoppingItem.h
        SuperMarket.c
        SuperMarket.h
        vTable.h
)
