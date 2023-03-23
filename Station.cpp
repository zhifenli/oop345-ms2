
// Name: Zhifen Li
// Seneca Student ID: 168833218
// Seneca email: fli92@myseneca.ca
// Date of completion: Mar 14
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"
using namespace std;
namespace sdds
{
    Station::Station(const std::string &str)
    {
        Utilities ut;
        size_t next_pos = 0;
        bool more = true;
        m_id = ++id_generator;
        m_name = trim(ut.extractToken(str, next_pos, more));
        if (m_widthField < ut.getFieldWidth())
        {
            m_widthField = ut.getFieldWidth();
        }
        m_serialNumber = stoi(trim(ut.extractToken(str, next_pos, more)));
        m_quantity = stoi(trim(ut.extractToken(str, next_pos, more)));
        m_desc = trim(ut.extractToken(str, next_pos, more));
    }

    const std::string &Station::getItemName() const
    {
        return m_name;
    }

    size_t Station::getNextSerialNumber()
    {

        return m_serialNumber++;
    }
    size_t Station::getQuantity() const
    {
        return m_quantity;
    }
    void Station::updateQuantity()
    {
        if (m_quantity > 0)
        {
            --m_quantity;
        }
    }
    void Station::display(std::ostream &os, bool full) const
    {
        os << setw(3) << setfill('0') << right << m_id << " | "
           << setw(m_widthField) << setfill(' ') << std::left << m_name
           << "  | " << setw(6) << setfill('0') << right << m_serialNumber << " | ";

        if (full)
            os << setw(4) << setfill(' ') << right << m_quantity << " | "
               << m_desc;

        os << std::endl;
    }

}