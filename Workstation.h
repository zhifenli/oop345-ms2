#pragma once
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds
{
    class Workstation : public Station
    {
        std::deque<CustomerOrder> m_orders;
        Workstation *m_pNextStation;

    public:
        std::deque<CustomerOrder> g_pending;
        std::deque<CustomerOrder> g_completed;
        std::deque<CustomerOrder> g_incomplete;

        Workstation(const std::string &str);
        void fill(std::ostream &os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation *station = nullptr);
        Workstation *getNextStation() const;
        void display(std::ostream &os) const;
        Workstation &operator+=(CustomerOrder &&newOrder);
    };
}