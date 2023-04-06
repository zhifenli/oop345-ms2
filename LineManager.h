#pragma once
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "Workstation.h"

namespace sdds
{
    class LineManager
    {
        std::vector<Workstation *> m_activeLine{};
        size_t m_cntCustomerOrder{0};
        Workstation *m_firstStation{nullptr};

    public:
        LineManager(const std::string &file, const std::vector<Workstation *> &stations);
        void reorderStations();
        bool run(std::ostream &os);
        void display(std::ostream &os) const;
        void swap2(size_t i1, size_t i2);
    };

}