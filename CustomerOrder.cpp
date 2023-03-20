#include <iostream>
#include <vector>
#include <iomanip>
#include "CustomerOrder.h"

using namespace std;
namespace sdds
{
    CustomerOrder::CustomerOrder(const std::string &str)
    {
        cout << "Constructor: " << str << endl;
        Utilities ut;
        size_t next_pos = 0;
        vector<string> temp;
        bool more = true;
        m_name = trim(ut.extractToken(str, next_pos, more));
        cout << "\t m_name : " << m_name << endl;
        m_product = trim(ut.extractToken(str, next_pos, more));
        cout << "\t m_product: " << m_product << endl;
        if (m_widthField < ut.getFieldWidth())
        {
            m_widthField = ut.getFieldWidth();
        }
        string s = {};
        do
        {
            s = trim(ut.extractToken(str, next_pos, more));
            if (!s.empty())
            {
                cout << "\t\t temp item: " << s << endl;

                temp.push_back(s);
                m_cntItem++;
            }

        } while (more);
        cout << "\t m_cntItem: " << m_cntItem << endl;

        m_lstItem = new Item *[m_cntItem];
        for (int i = 0; i < m_cntItem; i++)
        {
            m_lstItem[i] = new Item(temp[i]);
        cout << "\t m_itemName : " <<  i << ": " << this->m_lstItem[i]->m_itemName;
        }
    }
    CustomerOrder::CustomerOrder(const CustomerOrder &src)
    {
        cout << "CustomerOrder(const CustomerOrder &src)" << endl;
        throw " ERROR: Cannot make copies.";
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&src) noexcept
    {
        cout << "CustomerOrder(CustomerOrder &&src)" << endl;
        *this = std::move(src);
        cout << "CustomerOrder(CustomerOrder &&src)22222" << endl;

    }
    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&src) noexcept
    {
        cout << "CustomerOrder::operator=" << endl;

        if (this != &src)
        {
            for (int i = 0; i < m_cntItem; i++)
            {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
            if (src.m_lstItem)
            {
                m_lstItem = src.m_lstItem;
            }
            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;
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
        return true;
    }
    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
        return true;
    }
    void CustomerOrder::fillItem(Station &station, std::ostream &os)
    {

    }
    void CustomerOrder::display(std::ostream &os) const 
    {
        os << m_name << " - " << m_product;
        // for(int i = 0; i < m_cntItem; i++){
        //     os << "[" << setw(6) << setfill('0') << m_serialNumber << "] ";
        //     os << setw(m_widthField) << setfill(' ') << left << m_lstItem[i];
        //     if(m_isFilled){
        //         os << "FILLED";
        //     }else{
        //         os << "TO BE FILLED";
        //     }
        //     os << endl;
        // }
        
    }
    // std::string trim(std::string str)
    // {
    //     size_t start = str.find_first_not_of(' ');
    //     size_t end = str.find_last_not_of(' ');
    //     return str.substr(start, end + 1);
    // }

}