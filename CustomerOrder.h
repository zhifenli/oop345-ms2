#pragma once
#include <iostream>
#include "Station.h"
#include "Utilities.h"
namespace sdds
{
    struct Item
    {
    public:
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string &src) : m_itemName(src){};
        Item(){};
        std::string setItemName(std::string str);
    };
    class CustomerOrder
    {
    private:
        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem{0};
        Item **m_lstItem{nullptr};

        inline static size_t m_widthField{0};
        size_t findItemByNameUnfilled(std::string name, bool &isFound);

    public:
        std::string getName() const;
        CustomerOrder(const std::string &str);
        CustomerOrder(const CustomerOrder &src);
        CustomerOrder &operator=(const CustomerOrder &src) = delete;
        CustomerOrder(CustomerOrder &&src) noexcept;
        CustomerOrder &operator=(CustomerOrder &&src) noexcept;

        ~CustomerOrder();
        bool isOrderFilled() const;
        bool isItemFilled(const std::string &itemName) const;
        void fillItem(Station &station, std::ostream &os);
        void display(std::ostream &os) const;
    };
    // std::string trim(std::string str);

}
