# Arch_Assignment03
This assignment explores unit tests and how mocks can be used to isolate behavior so that targeted tests can be constructed. The premise here is that we are a developer who is tasked with validating a function used to calculate the subtotal of an online shopping cart. A another team is responsible for implementing the unit-specific pricing logic and is not done with it, or has not yet begun. Using mocks, we can abstract away this absent functionality by assigning expected prices for items. This will let us strictly test the function `Cart::getCartTotalAmount()` for which we are responsible.

## Test Cases
Listed below are three test cases I devised that can be used to simulate a `Cart` of `Items` with various prices and quantities. For each I have developed a unit test that will construct the Cart, fill it with the Items and test the calculation of the Cart's total amount.

1. Grocery List  
    | Item | Name | Quantity | Price |
    |------|------|----------|-------|
    | 0 | Apple   | 2 | 1.29
    | 1 | Banana  | 3 | 5.99 
    | 2 | Grapes  | 2 | 1.75
    | 3 | Avacado | 5 | 3.49 
    | 4 | Peach   | 7 | 1.23
    | 5 | Pear    | 9 | 2.00

    Expected Result: `68.11`
    
2. PC Build List   
    | Item | Name | Quantity | Price |
    |------|------|----------|-------|
    | 10 | keyboard    | 1 | 55.00 
    | 11 | mouse       | 1 | 15.00 
    | 12 | monitor     | 1 | 250.00 
    | 13 | motherboard | 1 | 1200.00 
    | 14 | ram         | 4 | 8000.00 
    | 15 | gpu         | 1 | 1000000.00 

    Expected Result: `1033520.00`

3. Wardrobe Inventory List
    | Item | Name | Quantity | Price |
    |------|------|----------|-------|
    | 20 | socks   | 12 | 5.00
    | 21 | shoes   | 15 | 100.00
    | 22 | hat     | 7  | 21.99
    | 23 | Tshirt | 18 | 17.50
    | 24 | shorts  | 5  | 55.35
    | 25 | belt    | 2  | 22.17
    | 26 | tie     | 10 | 32.53
    | 27 | jacket  | 3  | 78.56

    Expected Result: `2911.00`

## ItemService Mock
The [ItemService](include/ItemService.h) class developed by another team is responsible for getting the price of a specific item. For our purposes, we will instead simulates the functionality with the mock shown in the snippet below. 

```
#ifndef MOCK_ITEM_SERVICE_H
#define MOCK_ITEM_SERVICE_H

#include "ItemService.h"
#include <gmock/gmock.h>

class Mock_ItemService : public ItemService {
  public:
    MOCK_METHOD(double, getPrice, (Item & item), (override));
};

#endif // MOCK_ITEM_SERVICE_H
```
Then, within our unit-test, we can assert an expectation that a call of `getPrice()` for a given `<Item>` must once return a `<PRICE>`. Each of the unit-tests will use a a variation of this pseudocode. 
```
Mock_ItemService service;

// Assert a price return for various inputs to getPrice()
EXPECT_CALL(service, getPrice(<ITEM>)).WillOnce(Return(<PRICE>));
...
```

### Unit Tests
1. Grocery List
![grocery-test](media/Screenshot%202026-03-02%20214103.png)
2. PC List
![pc-test](media/Screenshot%202026-03-02%20214129.png)
3. Wardrobe List
![wardrobe-test](media/Screenshot%202026-03-02%20214150.png)
