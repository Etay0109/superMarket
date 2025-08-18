# SuperMarket Management System 🛒 – Part 2

A C project extending the supermarket management system from Part 1.  
This version adds:
- Linked lists
- Generic pointers
- Function pointers
- Vtables
- Membership management
- Uses `qsort` and `bsearch`

---

## 🚀 Project Overview

- 🔗 Shopping carts are now implemented using **singly linked lists** instead of arrays.  
- 👤 Supports **ClubMember** customers with membership discounts based on duration.  
- ⚡ Implements **generic functions** using function pointers.  
- 🏬 Products can be sorted by **name, quantity, or price** and searched using `bsearch` when sorted.  
- 💾 Dynamic memory allocation ensures flexible storage.  

---

## ✨ Key Features

- ✅ Generic singly linked lists for dynamic data storage  
- ✅ Insert shopping cart items in **sorted order** by barcode  
- ✅ Add new products and customers (including ClubMember)  
- ✅ Apply membership discounts automatically  
- ✅ Sort and search products efficiently  
- ✅ Generic array processing with function pointers  
- ✅ Input validation and robust memory management

---

## 🏗️ Main Structures

### 🔹 Generic Linked List
- `Node` stores `void* data`  
- Functions:
  - Initialize list  
  - Add item (in sorted order if needed)  
  - Delete item (optionally freeing memory)  
  - Print list contents  
  - Free list  

### 🔹 ClubMember (inherits from Customer)
- `totalMonths` – Membership duration in months  
- Discount calculation based on duration:  
  - ≤ 24 months: 0.1% per month (max 2.3%)  
  - 25–60 months: 2.5% + 0.5% per year (max 4.5%)  
  - > 60 months: 7.5% fixed  

### 🔹 Function Pointers
- `generalArrayFunction(void* array, size_t n, size_t size, void (*f)(void*))`  
- Applies a function `f` to each element of any array (generic operation)  
- Used to print products dynamically in `printAllProducts()`

### 🔹 SuperMarket Sorting & Searching
- Products can be sorted by name, quantity, or price using `qsort`  
- `bsearch` used for binary search on sorted arrays  
- If array is unsorted, search is disabled with an informative message

---

## ⚙️ Running the Program

### Compilation
```bash
clang *.c -o SuperMarket2 -std=c11 -Wall -g

### Execution
Run the compiled program with:

```bash
./SuperMarket2