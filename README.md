# Arch_Assignment03
This assignment explores unit tests and how mocks can be used to isolate behavior so that targeted tests can be constructed. The premise here is that we are a developer who is tasked with validating a function used to calculate the subtotal of an online shopping cart. A another team is responsible for implementing the unit-specific pricing logic and is not done with it, or has not yet begun. Using mocks, we can abstract away this absent functionality by assigning expected prices for items. This will let us strictly test the function `Cart::getCartTotalAmount()` for which we are responsible.

## Test Cases
Listed below are three test cases I devised that can be used to simulate a `Cart` of `Items` with various prices and quantities. For each I have developed a unit test that will construct the Cart, fill it with the Items and test the calculation of the Cart's total amount.

1. **Grocery List**

    | Item | Name     | Quantity | Price |
    |:-----|:---------|:---------|:------|
    | 0    | Apple    | 2        | 1.29  |
    | 1    | Banana   | 3        | 5.99  |
    | 2    | Grapes   | 2        | 1.75  |
    | 3    | Avocado  | 5        | 3.49  |
    | 4    | Peach    | 7        | 1.23  |
    | 5    | Pear     | 9        | 2.00  |

   **Expected Result:** 68.11

2. **PC Build List**

    | Item | Name         | Quantity | Price      |
    |:-----|:-------------|:---------|:-----------|
    | 10   | keyboard     | 1        | 55.00      |
    | 11   | mouse        | 1        | 15.00      |
    | 12   | monitor      | 1        | 250.00     |
    | 13   | motherboard  | 1        | 1200.00    |
    | 14   | ram          | 4        | 8000.00    |
    | 15   | gpu          | 1        | 1000000.00 |

   **Expected Result:** 1033520.00

3. **Wardrobe Inventory List**

    | Item | Name     | Quantity | Price  |
    |:-----|:---------|:---------|:-------|
    | 20   | socks    | 12       | 5.00   |
    | 21   | shoes    | 15       | 100.00 |
    | 22   | hat      | 7        | 21.99  |
    | 23   | Tshirt   | 18       | 17.50  |
    | 24   | shorts   | 5        | 55.35  |
    | 25   | belt     | 2        | 22.17  |
    | 26   | tie      | 10       | 32.53  |
    | 27   | jacket   | 3        | 78.56  |

   **Expected Result:** 2911.00

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

## Test Fixture 
A test fixture can also be used to implement setup and teardown logic to build anything the test might need.
```
    using ::testing::AtLeast;
    using ::testing::Return;

    /**
    * Test Fixture for the Cart Test Suite
    */
    class CartTest : public ::testing::Test {
    protected:
        /**
        * Specific logic require to setup this test fixture
        *  For this assignment only a print statement is sufficient
        *
        */
        void SetUp() override {
            std::cout << "Setting up test fixture" << std::endl;
        }

        /**
        * Specific logic require to tear down this test fixture
        *  For this assignment only a print statement is sufficient
        *
        */
        void TearDown() override {
            std::cout << "Tearing down test fixture" << std::endl;
        }
    };  
```    

## Unit Tests
1. Below is the unit-test for a Grocery List 
```
    /**
    * Test Case 1: Grocery List using CartTest fixture
    */
    TEST_F(CartTest, grocery_list) {
        Cart cart;

        // test case participants
        Item Apple("0", "Apple", 2);
        Item Banana("1", "Banana", 3);
        Item Grapes("2", "Grapes", 2);
        Item Avacado("3", "Avacado", 5);
        Item Peach("4", "Peach", 7);
        Item Pear("5", "Pear", 9);

        std::vector<Item> items = {
            Apple, Banana, Grapes, Avacado, Peach, Pear,
        };

        Mock_ItemService service;

        // Assert a price return for various inputs to getPrice()
        EXPECT_CALL(service, getPrice(Apple)).WillOnce(Return(1.29));
        EXPECT_CALL(service, getPrice(Banana)).WillOnce(Return(5.99));
        EXPECT_CALL(service, getPrice(Grapes)).WillOnce(Return(1.75));
        EXPECT_CALL(service, getPrice(Avacado)).WillOnce(Return(3.49));
        EXPECT_CALL(service, getPrice(Peach)).WillOnce(Return(1.23));
        EXPECT_CALL(service, getPrice(Pear)).WillOnce(Return(2.00));

        cart.setItemService(&service);
        cart.setItems(items);

        // EXPECT a result with precision suitable for type DOUBLE
        EXPECT_DOUBLE_EQ(cart.getCartTotalAmount(), 68.11);
    }
```
### Results:
![grocery-test](media/Screenshot%202026-03-02%20214103.png)

2. Below is the unit-test for a PC List
```
    /**
    * Test Case 2: PC List using CartTest fixtrure
    */
    TEST_F(CartTest, pc_list) {
        Cart cart;

        // test case participants
        Item keyboard("10", "keyboard", 1);
        Item mouse("11", "mouse", 1);
        Item monitor("12", "monitor", 1);
        Item motherboard("13", "motherboard", 1);
        Item ram("14", "ram", 4);
        Item gpu("15", "gpu", 1);

        std::vector<Item> items = {
            keyboard, mouse, monitor, motherboard, ram, gpu,
        };

        Mock_ItemService service;

        // Assert a price return for various inputs to getPrice()
        EXPECT_CALL(service, getPrice(keyboard)).WillOnce(Return(55.00));
        EXPECT_CALL(service, getPrice(mouse)).WillOnce(Return(15.00));
        EXPECT_CALL(service, getPrice(monitor)).WillOnce(Return(250.00));
        EXPECT_CALL(service, getPrice(motherboard)).WillOnce(Return(1200.00));
        EXPECT_CALL(service, getPrice(ram)).WillOnce(Return(8000.00));
        EXPECT_CALL(service, getPrice(gpu)).WillOnce(Return(1000000.00));

        cart.setItemService(&service);
        cart.setItems(items);

        // EXPECT a result with precision suitable for type DOUBLE
        EXPECT_DOUBLE_EQ(cart.getCartTotalAmount(), 1033520.00);
    }
```
### Results:
![pc-test](media/Screenshot%202026-03-02%20214129.png)

3. Below is the unit-test for a Wardrobe List
```
    /**
    * Test Case 3: Wardrobe List using CartTest fixture
    */
    TEST_F(CartTest, wardrobe_list) {
        Cart cart;

        // test case participants
        Item socks("20", "socks", 12);
        Item shoes("21", "shoes", 15);
        Item hat("22", "hat", 7);
        Item Tshirt("23", "Tshirt", 18);
        Item shorts("24", "shorts", 5);
        Item belt("25", "belt", 2);
        Item tie("26", "tie", 10);
        Item jacket("27", "jacket", 3);

        std::vector<Item> items = {
            socks, shoes, hat, Tshirt, shorts, belt, tie, jacket,
        };

        Mock_ItemService service;

        // Assert a price return for various inputs to getPrice()
        EXPECT_CALL(service, getPrice(socks)).WillOnce(Return(5.00));
        EXPECT_CALL(service, getPrice(shoes)).WillOnce(Return(100.00));
        EXPECT_CALL(service, getPrice(hat)).WillOnce(Return(21.99));
        EXPECT_CALL(service, getPrice(Tshirt)).WillOnce(Return(17.50));
        EXPECT_CALL(service, getPrice(shorts)).WillOnce(Return(55.35));
        EXPECT_CALL(service, getPrice(belt)).WillOnce(Return(22.17));
        EXPECT_CALL(service, getPrice(tie)).WillOnce(Return(32.53));
        EXPECT_CALL(service, getPrice(jacket)).WillOnce(Return(78.56));

        cart.setItemService(&service);
        cart.setItems(items);

        // EXPECT a result with precision suitable for type DOUBLE
        EXPECT_DOUBLE_EQ(cart.getCartTotalAmount(), 2911.00);
    }
```
### Results:
![wardrobe-test](media/Screenshot%202026-03-02%20214150.png)
