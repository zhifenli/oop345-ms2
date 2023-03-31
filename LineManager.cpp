#include <iostream>
#include <vector>
#include <fstream>

#include "LineManager.h"
#include "Workstation.h"
using namespace std;
namespace sdds
{
    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations)
    {
        std::ifstream is(file);
        string line = {};
        if (file.length() != 0)
        {
            while (getline(is, line))
            {
                size_t i1 = line.find_first_of('|');
                string stationName1 = trim(line.substr(0, i1));

                auto s1 = std::find_if(stations.begin(), stations.end(), [stationName1](Workstation *item)
                                       { return item->getItemName() == stationName1; });
                if (s1 != stations.end())
                {
                    cout << "@ station1: " << s1[0]->getItemName();
                }
                else
                {
                    cout << "NOT FOUND1";
                }

                if (i1 == string::npos)
                {
                    cout << " -> End of Line." << endl;
                }
                else
                {
                    string stationName2 = trim(line.substr(line.find_first_of('|') + 1));

                    if (!stationName2.empty())
                    {
                        auto s2 = std::find_if(stations.begin(), stations.end(), [stationName2](Workstation *item)
                                               { return item->getItemName() == stationName2; });
                        if (s2 != stations.end())
                        {
                            cout << " -> station2: " << s2[0]->getItemName() << endl;
                        }
                        else
                        {
                            cout << " ->NOT FOUND2" << endl;
                        }

                        // m_activeLine.push_back(&workstation);
                    }
                    else
                    {
                        cout << " -> End of Line1." << endl;
                    }
                }
            }

            is.close();
        }
    }

    void LineManager::reorderStations()
    {
    }

    bool LineManager::run(std::ostream &os)
    {

        return false;
    }
    void LineManager::display(std::ostream &os) const
    {
    }
}