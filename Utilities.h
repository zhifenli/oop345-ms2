// Name: Zhifen Li
// Seneca Student ID: 168833218
// Seneca email: fli92@myseneca.ca
// Date of completion: Mar 14
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#pragma once

namespace sdds
{
    class Utilities
    {
        size_t m_widthField{1};
        inline static char m_delimiter;

    public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string &str, size_t &next_pos, bool &more);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };
    std::string trim(std::string str);
}