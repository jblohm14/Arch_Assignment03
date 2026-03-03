#ifndef MOCK_ITEM_SERVICE_H
#define MOCK_ITEM_SERVICE_H

#include "ItemService.h"
#include <gmock/gmock.h>

class Mock_ItemService : public ItemService {
  public:
    MOCK_METHOD(double, getPrice, (Item & item), (override));
};

#endif // MOCK_ITEM_SERVICE_H