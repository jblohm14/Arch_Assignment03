#include <gtest/gtest.h>

#include "Cart.h"
#include "Item.h"
#include "ItemService.h"
#include "Mock_ItemService.h"

using ::testing::AtLeast;
using ::testing::Return;

/**
 * @brief Test Fixture for the Cart Test Suite
 * 
 */
class CartTest : public ::testing::Test {
  protected:
    
    
    void SetUp() override {
        std::cout << "Setting up test fixture" << std::endl;
    }

    void TearDown() override {
        std::cout << "Tearing down test fixture" << std::endl;
    }
};

/**
 * @brief Test Case: Grocery List using CartTest fixrure
 */
TEST_F(CartTest, grocery_list) {
    Cart cart;

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

    EXPECT_CALL(service, getPrice(Apple)).WillOnce(Return(1.29));
    EXPECT_CALL(service, getPrice(Banana)).WillOnce(Return(5.99));
    EXPECT_CALL(service, getPrice(Grapes)).WillOnce(Return(1.75));
    EXPECT_CALL(service, getPrice(Avacado)).WillOnce(Return(3.49));
    EXPECT_CALL(service, getPrice(Peach)).WillOnce(Return(1.23));
    EXPECT_CALL(service, getPrice(Pear)).WillOnce(Return(2.00));

    cart.setItemService(&service);
    cart.setItems(items);

    EXPECT_DOUBLE_EQ(cart.getCartTotalAmount(), 68.11);
}

/**
 * @brief Test Case: PC List using CartTest fixrure
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

/**
 * @brief Test Case: Wardrobe List using CartTest fixrure
 */
TEST_F(CartTest, wardrobe_list) {
    Cart cart;

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
    EXPECT_DOUBLE_EQ(cart.getCartTotalAmount(), 2911.00);
}