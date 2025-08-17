# SuperMarket Management System 🛒

A C project implementing a basic supermarket management system.  
This system allows managing products, customers, shopping carts, and purchases.

## Project Overview

- 🏪 Manage a supermarket with products and registered customers.  
- 🛍️ Only registered customers can make purchases.  
- 🔄 Includes adding products, customers, processing purchases, and printing details.  
- 💾 Dynamic memory allocation ensures flexible storage of products, customers, and shopping carts.

## Features

- ✅ Register new customers  
- ✅ Add new products or update existing products  
- ✅ Process purchases for registered customers  
- ✅ Manage shopping carts with dynamic allocation  
- ✅ Print details of supermarket, products, and customers  
- ✅ Input validation for ID, dates, quantities, prices, and names  
- ✅ Proper memory management and cleanup  

## Main Structures

### 📅 Date
- `int day, month, year`  
- Used to store product expiration dates.

### 🥫 Product
- `char name[20]` – Product name (uppercase letters).  
- `char barcode[7]` – Unique barcode, first two letters represent the type:  
  - SH → Shelf product  
  - FZ → Frozen  
  - FR → Fridge  
  - FV → Fruit/Vegetable  
- `float price` – Product price  
- `int quantity` – Quantity in stock  
- `Date expiration` – Expiration date  

### 👤 Customer
- `char id[9]` – Unique ID (digits only)  
- `char* name` – Customer full name  
- `ShoppingCart cart` – Customer’s shopping cart

### 🛒 ShoppingItem
- `char barcode[7]` – Barcode of the product in the cart  
- `float price` – Product price  
- `int quantity` – Quantity in the cart  

### 🛍️ ShoppingCart
- Dynamic array of `ShoppingItem`  
- Tracks quantities and total cost

### 🏪 SuperMarket
- `char* name` – Supermarket name  
- Dynamic arrays for `Customer` and `Product`  
- Functions include:  
  - `supermarket_init()` – Initialize supermarket  
  - `addProductToSuperMarket()` – Add or update product  
  - `addCustomerToSuperMarket()` – Register new customer  
  - `buyingProcess()` – Handle purchase flow  
  - `printSuperMarket()` – Print supermarket details  
  - `shoppingCartManagement()` – Manage customer carts  
  - `freeSuperMarket()` – Release dynamic memory

## ⚙️ How to Run

### Compilation
```bash
clang main.c customer.c date.c product.c shoppingcart.c shoppingitem.c supermarket.c -o SuperMarket1

### Execution
Run the compiled program with:

```bash
./SuperMarket1
