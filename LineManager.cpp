#include "LineManager.h"
using namespace std;
namespace sdds
{
    int COUNT = 0;
    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations)
    {
        std::ifstream is(file);
        if (!is)
        {
            throw std::string("Unable to open " + file + "file.");
        }
        string line = {};
        if (file.length() != 0)
        {
            while (getline(is, line))
            {
                Workstation *s1 = nullptr;
                Workstation *s2 = nullptr;

                size_t delimIndex = line.find_first_of('|');
                string stationName1 = trim(line.substr(0, delimIndex));

                auto s1Vector = std::find_if(stations.begin(), stations.end(), [stationName1](Workstation *item)
                                             { return item->getItemName() == stationName1; });

                if (s1Vector != stations.end())
                {
                    s1 = s1Vector[0];
                }

                if (delimIndex != string::npos)
                {
                    string stationName2 = trim(line.substr(line.find_first_of('|') + 1));

                    if (!stationName2.empty())
                    {
                        auto s2Vector = std::find_if(stations.begin(), stations.end(), [stationName2](Workstation *item)
                                                     { return item->getItemName() == stationName2; });
                        if (s2Vector != stations.end())
                        {
                            s2 = s2Vector[0];
                        }
                    }
                }
                m_activeLine.push_back(s1);
                m_activeLine.push_back(s2);
            }
            m_firstStation = m_activeLine[0];
            is.close();
        }
        // std::vector<Workstation *> t_activeLine = m_activeLine;
        // Workstation *t_firstStation{};
        // for_each(t_activeLine.begin(), t_activeLine.end(), [&t_firstStation, &t_activeLine](Workstation *ws)
        //          { bool found(); });
        // for_each(t_activeLine.begin(), t_activeLine.end(), [&ws, &found, &t_firstStation](Workstation *ns)
        //          { if (ns->getNextStation() && ws->getItemName(0)) });
    }

    void LineManager::reorderStations()
    {

        // odd is from, even is to
        size_t nextToIndex = 0;
        for (auto i = 0; i < m_activeLine.size(); i++)
        {
            if (m_activeLine[i] == nullptr)
            {
                // end line
                swap2(i - 1, m_activeLine.size() - 2);
                nextToIndex = m_activeLine.size() - 2;
                break;
            }
        }

        while (nextToIndex > 0 && nextToIndex < m_activeLine.size())
        {
            for (auto i = 1; i < nextToIndex; i += 2)
            {
                if (m_activeLine[i] == m_activeLine[nextToIndex])
                {
                    swap2(i - 1, nextToIndex - 2);
                    nextToIndex -= 2;
                }
            }
        }

        // remove duplicates
        std::vector<Workstation *> copies;

        for (auto i = 0; i < m_activeLine.size(); i++)
        {
            if (m_activeLine[i] && (copies.empty() || copies.back() != m_activeLine[i]))
            {
                copies.push_back(m_activeLine[i]);
            }
        }

        m_activeLine.clear();
        for (auto i = 0; i < copies.size(); i++)
        {
            if (i > 0)
            {
                copies[i - 1]->setNextStation(copies[i]);
            }
            m_activeLine.push_back(copies[i]);
        }
        m_activeLine.back()->setNextStation(nullptr);
        m_firstStation = m_activeLine[0];
    }

    bool LineManager::run(std::ostream &os)
    {
        COUNT++;
        cout << "Line Manager Iteration: " << COUNT << endl;

        if (g_pending.empty())
        {
            throw std::string("No pending order");
        }

        (*m_firstStation) += std::move(g_pending.front());
        g_pending.pop_front();

        Workstation *cur = m_firstStation;

        while (cur)
        {
            cout << "@ Station: " << cur->getItemName() << endl;
            cur->fill(os);
            cur->attemptToMoveOrder();
            cur = cur->getNextStation();
        }

        return g_pending.empty();
    }

    void LineManager::display(std::ostream &os) const
    {
        for (auto i = 0; i < m_activeLine.size(); i += 2)
        {
            cout << m_activeLine[i]->getItemName() << " --> ";
            if (!m_activeLine[i + 1])
            {
                cout << "End of Line";
            }
            else
            {
                cout << m_activeLine[i + 1]->getItemName();
            }
            cout << endl;
        }
    }

    void LineManager::swap2(size_t i1, size_t i2)
    {
        if (i1 < 0 || i2 < 0)
            return;
        auto tmp = m_activeLine[i1];
        m_activeLine[i1] = m_activeLine[i2];
        m_activeLine[i2] = tmp;

        i1++;
        i2++;
        tmp = m_activeLine[i1];
        m_activeLine[i1] = m_activeLine[i2];
        m_activeLine[i2] = tmp;
    }
}