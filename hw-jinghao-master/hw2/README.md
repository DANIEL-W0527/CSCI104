# Homework 2 Programming Part
Name: Jinghao (Daniel) Wang
USC ID: 4237145509
USC Net ID: jinghao

## Contents
- amazon.cpp
- book.h
- book.cpp
- clothing.h
- clothing.cpp
- datastore.h
- db_parser.h
- db_parser.cpp
- movie.h
- movie.cpp
- mydatastore.h
- mydatastore.cpp
- product.h
- product.cpp
- product_parser.h
- product_parser.cpp
- user.h
- user.cpp
- util.h
- util.cpp
- Makefile
- README.md

## Compile Method
Simply by typing make as indicated in Makefile

## Assignment Expected Behavior
### Menu Option
- Search (AND or OR command)
    1. When OR or AND command used with no input terms, output the message "No results found!"
    2. When OR or AND command used with one input term, output the product with the only input term as keyword (Same behavior for OR and AND command)
    3. When AND command used with more than one input terms, ouput each product that has all the input terms as keyword
    4. When OR command used with more than one input terms, ouput each product if it has at least one of the input terms as keyword

- Adding to Carts (ADD command)
    1. When ADD command used with no input username, output the message "Invalid request"
    2. When ADD command used with a string as username (valid or not valid), if no hit index input, output the message "Invalid request"
    3. When ADD command used with a string (valid or not valid), if hit index input in not valid(hit index is not in the range given by search), output the message "Invalid request"
    4. When ADD command used with a string as username and a valid index hit index, but the username input is an invalid username(user is not listed in the database file), output the message "Invalid request"
    5. When ADD command used with a valid username (user is listed in the database file) and a valid hit index, add selected product into user's cart
    6. When ADD command used with more than two input terms, we only take the first term entered as input username and the second term input as hit index, ignoring the rest of the input terms 

- Viewing to Carts (VIEWCART command)
    1. When VIEWCART command used with no input username, output the message "Invalid username"
    2. When VIEWCART command used with an invalid input username (user is not listed in the database file), output the message "Invalid username"
    3. When VIEWCART command used with a valid input username (user is listed in the database file), if the user's cart is empty, output the message "Empty cart"
    4. When VIEWCART command used with a valid input username (user is listed in the database file), if the user's cart is not empty, output each product in the user's cart
    5. When VIEWCART command used with more than one input terms, and we only take the first term entered as input username, ignoring the rest of input terms

- Buying the cart (BUYCART command)
    1. When BUYCART command used with no input username, output the message "Invalid username"
    2. When BUYCART command used with an invalid input username (user is not listed in the database file), output the message "Invalid username"
    3. When BUYCART command used with a valid input username (user is listed in the database file), if the user's cart is empty, do nothing
    4. When BUYCART command used with a valid input username (user is listed in the database file), if the user's cart is not empty, using FIFO order to go through the cart: 
        (1) If the product is in stock and user has enough balance, decrease the quantity of the product by 1, decrease the balance of the user by the price of the product and remove the product in the cart; 
        (2) If the product is not in stock or the user doesn't have enough balance, leave the product in the cart and do nothing, move on to the next product in the cart
    5. When BUYCART command used with more than one input terms, and we only take the first term entered as input username, ignoring the rest of input terms

- Quitting (QUIT command)
    1. When QUIT command used with no input filename, do nothing and quit the program
    2. When QUIT command used with an input filename, output all the information of products and users in the database form into a file named with the input filename
    3. When QUIT command used with more than one input terms, and we only take the first term entered as input filename, ignoring the rest of input terms

- Other command
    When other command used (not listed above), output the message "Unknown command"