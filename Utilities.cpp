// Name: Zhifen Li
// Seneca Student ID: 168833218
// Seneca email: fli92@myseneca.ca
// Date of completion: Mar 14
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Utilities.h"
#include <cmath>
using namespace std;
namespace sdds
{
    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }
    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more)
    {
        string token = str;
        size_t delim_pos = str.find(m_delimiter, next_pos);

        if (delim_pos == std::string::npos) // found the final column
        {
            token = str.substr(next_pos);
            next_pos = str.size();
            more = false;
        }
        else if (next_pos == delim_pos) // found bad data format: delimeter at the end of line
        {
            more = false;
            throw std::string("ERROR: No token found before the delimiter!");
        }
        else // find a delimeter
        {
            token = trim(str.substr(next_pos, delim_pos - next_pos));
            next_pos = delim_pos + 1;
            more = true;
        }

        // size_t start = token.find_first_not_of(" ");
        // size_t end = token.find_last_not_of(" ");
        // token = token.substr(start, end - start + 1);

        if (m_widthField < token.size())
        {
            m_widthField = token.size();
        }

        // m_widthField = max(m_widthField, token.size());

        return token;
    }

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }
    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }

    std::string trim(std::string str)
    {
        size_t start = str.find_first_not_of(' ');
        size_t end = str.find_last_not_of(' ');
        return str.substr(start, end + 1);
    }

}