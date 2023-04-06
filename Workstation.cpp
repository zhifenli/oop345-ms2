#include <iostream>
#include "Workstation.h"
#include "CustomerOrder.h"

using namespace std;
namespace sdds
{
    std::deque<CustomerOrder> g_pending{};
    std::deque<CustomerOrder> g_completed{};
    std::deque<CustomerOrder> g_incomplete{};

    Workstation::Workstation(const std::string &str) : Station(str)
    {
    }

    void Workstation::fill(std::ostream &os)
    {

        if (!m_orders.empty())
        {
            cout << "ORDER: " << m_orders.front().getName() << endl;
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder()
    {
        if (m_orders.empty())
        {
            return false;
        }
        auto order = move(m_orders.front());
        m_orders.pop_front();

        if (!order.isItemFilled(this->getItemName()))
        {
            return false;
        }

        if (!m_pNextStation)
        {
            if (order.isOrderFilled())
            {
                g_completed.push_back(order);
            }
            else
            {
                g_incomplete.push_back(order);
            }
            return false;
        }

        *m_pNextStation += std::move(order);
        return true;
    }

    void Workstation::setNextStation(Workstation *station)
    {
        m_pNextStation = station;
    }

    Workstation *Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream &os) const
    {
        os << this->getItemName() << "-->";
        if (!this->m_pNextStation)
        {
            os << "End of Line" << endl;
        }
        else
        {
            m_pNextStation->display(os);
        }
    }

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
    {
        m_orders.push_back(std::move(newOrder));
        // cout << "#####m_orders 2: " << m_orders.empty() << endl;
        return *this;
    }

}