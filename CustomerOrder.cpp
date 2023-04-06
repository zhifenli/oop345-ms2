#include <iostream>
#include <vector>
#include <iomanip>
#include <memory>
#include <algorithm>
#include "CustomerOrder.h"

using namespace std;
namespace sdds
{
    CustomerOrder::CustomerOrder(const std::string &str) : m_lstItem(nullptr)
    {
        Utilities ut;
        size_t next_pos = 0;
        vector<string> temp;
        bool more = true;
        m_name = trim(ut.extractToken(str, next_pos, more));
        m_product = trim(ut.extractToken(str, next_pos, more));

        if (m_widthField < ut.getFieldWidth())
        {
            m_widthField = ut.getFieldWidth();
        }
        string s = {};

        do
        {
            s = trim(ut.extractToken(str, next_pos, more));
            if (s.length() != 0)
            {
                temp.push_back(s);
                m_cntItem++;
            }
        } while (more);

        m_lstItem = new Item *[m_cntItem];
        for (size_t i = 0; i < m_cntItem; i++)
        {
            m_lstItem[i] = new Item(temp[i]);
        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder &src)
    {
        throw std::string(" ERROR: Cannot make copies of CustomerOrder.");
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&src) noexcept
    {
        m_lstItem = nullptr;
        *this = std::move(src);
    }
    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&src) noexcept
    {
        if (this != &src)
        {
            for (size_t i = 0; i < m_cntItem; i++)
            {
                delete m_lstItem[i];
                m_lstItem[i] = nullptr;
            }

            delete[] m_lstItem;
            m_lstItem = nullptr;

            m_name = src.m_name;
            src.m_name = {};

            m_product = src.m_product;
            src.m_product = {};

            m_cntItem = src.m_cntItem;
            src.m_cntItem = 0;

            m_lstItem = src.m_lstItem;
            src.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder()
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    std::string CustomerOrder::getName() const
    {
        return m_name;
    }

    bool CustomerOrder::isOrderFilled() const
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_isFilled == false)
                return false;
        }
        return true;
    }
    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
                return false;
        }
        return true;
    }

    size_t CustomerOrder::findItemByName(std::string name, bool &isFound)
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_itemName == name && !m_lstItem[i]->m_isFilled)
            {
                isFound = true;
                return i;
            }
        }
        isFound = false;
        return m_cntItem + 1;
    }

    void CustomerOrder::fillItem(Station &station, std::ostream &os)
    {
        bool isFound = false;
        size_t index = findItemByName(station.getItemName(), isFound);

        if (!isFound)
        {
            return;
        }

        Item *iptr = m_lstItem[index];
        if (station.getQuantity() > 0)
        {
            station.updateQuantity();
            iptr->m_serialNumber = station.getNextSerialNumber();
            iptr->m_isFilled = true;
            os << "    Filled " << m_name << ", " << m_product << " [" << iptr->m_itemName << "]" << endl;
        }
        else
        {
            os << "    Unable to fill " << m_name << ", " << m_product << " [" << iptr->m_itemName << "]" << endl;
        }
    }
    void CustomerOrder::display(std::ostream &os) const
    {
        os << m_name << " - " << m_product;

        os << endl;

        for (size_t i = 0; i < m_cntItem; i++)
        {
            os << "[" << setw(6) << setfill('0') << right << m_lstItem[i]->m_serialNumber << "] ";
            os << setw(m_widthField) << setfill(' ') << left << m_lstItem[i]->m_itemName;
            os << "  - ";
            if (m_lstItem[i]->m_isFilled)
            {
                os << "FILLED";
            }
            else
            {
                os << "TO BE FILLED";
            }
            os << endl;
        }
    }
}