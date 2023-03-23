#include <iostream>
#include <vector>
#include <iomanip>
#include <memory>
#include <algorithm>
#include "CustomerOrder.h"

using namespace std;
namespace sdds
{
    CustomerOrder::CustomerOrder(const std::string &str)
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

        // cout << "\t m_cntItem: " << m_cntItem << endl;
        // unique_ptr<Item> m_lstItem(new Item *[m_cntItem]);

        m_lstItem = new Item *[m_cntItem];
        for (int i = 0; i < m_cntItem; i++)
        {
            // unique_ptr<Item> m_lstItem[i](new Item(temp[i]));
            m_lstItem[i] = new Item(temp[i]);
        }
    }
    CustomerOrder::CustomerOrder(const CustomerOrder &src)
    {
        throw std::string(" ERROR: Cannot make copies.");
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&src) noexcept
    {
        // cout << "[Constructor2 move]: " << src.m_name << endl;
        // cout << "[] displaying other: " << src.m_name << endl;
        // src.display(cout);
        // cout << "To MOVE ..." << src.m_name << endl;
        *this = std::move(src);
    }
    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&src) noexcept
    {
        // cout << "Moving ..." << src.m_name << endl;
        if (this != &src)
        {
            // cout << "****m_cntItem: " << m_cntItem << endl;
            for (int i = 0; i < m_cntItem; i++)
            {
                // cout << "****  i : " << i << endl;

                delete m_lstItem[i];
                m_lstItem[i] = nullptr;
            }

            delete[] m_lstItem;
            m_lstItem = nullptr;

            m_name = src.m_name;
            m_product = src.m_product;

            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;

            src.m_lstItem = nullptr;
            src.m_cntItem = 0;
            // cout << "\t move is done " << m_cntItem << endl;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder()
    {
        for (int i = 0; i < m_cntItem; i++)
        {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }
    bool CustomerOrder::isOrderFilled() const
    {
        for (int i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_isFilled == false)
                return false;
        }
        return true;
    }
    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
        for (int i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_itemName == itemName)
                return true;
        }
        return false;
    }

    size_t CustomerOrder::findItemByName(std::string name, bool &isFound)
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_itemName == name)
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
            os << "Filled " << m_name << ", " << m_product << " [" << iptr->m_itemName << "]" << endl;
        }
        else
        {
            os << "Unable to fill " << m_name << ", " << m_product << " [" << iptr->m_itemName << "]" << endl;
        }
    }
    void CustomerOrder::display(std::ostream &os) const
    {
        os << m_name << " - " << m_product;

        os << endl;

        for (int i = 0; i < m_cntItem; i++)
        {
            os << "[" << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
            os << setw(m_widthField) << setfill(' ') << left << m_lstItem[i]->m_itemName;
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