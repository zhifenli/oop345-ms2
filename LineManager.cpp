#include "LineManager.h"
using namespace std;
namespace sdds
{
    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations)
    {
        Utilities ut;

        ifstream fileStream(file);
        if (!fileStream)
        {
            throw "Unable to open " + file + " file.";
        }
        else
        {
            string line;
            while (std::getline(fileStream, line))
            {
                size_t next_pos = 0;

                bool more = false;
                std::string stationName1 = ut.extractToken(line, next_pos, more);
                Workstation *station1 = nullptr;
                for_each(stations.begin(), stations.end(), [&stationName1, &station1](Workstation *ws)
                         { if (ws->getItemName() == stationName1) { station1 = ws; } });

                m_activeLine.push_back(station1);

                Workstation *station2 = nullptr;

                if (more)
                {
                    // this line has 2 stations
                    std::string stationName2 = ut.extractToken(line, next_pos, more);

                    for_each(stations.begin(), stations.end(), [&stationName2, &station2](Workstation *ws)
                             { if (ws->getItemName() == stationName2) { station2 = ws; } });
                }

                station1->setNextStation(station2);
            }
        }

        fileStream.close();
        m_cntCustomerOrder = g_pending.size();

        std::vector<Workstation *> activeLineCopy = m_activeLine;
        Workstation *temp_firstStation = nullptr;

        for_each(m_activeLine.begin(), m_activeLine.end(),
                 [&activeLineCopy, &temp_firstStation](Workstation *possibleFirst)
                 {
                     bool isActualFirst = true;

                     for_each(activeLineCopy.begin(), activeLineCopy.end(),
                              [&possibleFirst, &isActualFirst, &temp_firstStation](Workstation *other)
                              {
                                  if (other->getNextStation() && other->getNextStation()->getItemName() == possibleFirst->getItemName())
                                  {
                                      isActualFirst = false;
                                  }
                              });

                     if (isActualFirst)
                     {
                         if (temp_firstStation)
                         {
                             throw std::string("Multiple first station found");
                         }
                         temp_firstStation = possibleFirst;
                     }
                 });
        m_firstStation = temp_firstStation;
    }

    void LineManager::reorderStations()
    {
        std::vector<Workstation *> activeline;
        Workstation *cur = m_firstStation;
        while (cur)
        {
            activeline.push_back(cur);
            cur = cur->getNextStation();
        }

        m_activeLine = activeline;
    }

    bool LineManager::run(std::ostream &os)
    {
        bool ret = false;
        static size_t count = 0;
        ++count;
        os << "Line Manager Iteration: " << count << endl;

        if (!g_pending.empty())
        {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for_each(m_activeLine.begin(), m_activeLine.end(),
                 [&os](Workstation *ws)
                 {
                     ws->fill(os);
                     ws->attemptToMoveOrder();
                 });

        if (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder)
        {
            ret = true;
        }
        return ret;
    }

    void LineManager::display(std::ostream &os) const
    {
        for (const auto &station : m_activeLine)
        {
            station->display(os);
        }
    }

}