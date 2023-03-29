// Name: Zhifen Li
// Seneca Student ID: 168833218
// Seneca email: fli92@myseneca.ca
// Date of completion: Mar 14
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#pragma once
#include <iostream>
namespace sdds
{
    class Station
    {
        int m_id;
        std::string m_name;
        std::string m_desc;
        size_t m_serialNumber;
        size_t m_quantity;

        inline static size_t m_widthField{0};
        inline static size_t id_generator{0};

    public:
        Station(const std::string &str);
        const std::string &getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream &os, bool full) const;
    };

}