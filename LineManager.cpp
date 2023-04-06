#include "LineManager.h"
using namespace std;
namespace sdds
{
    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations)
    {
        Utilities ut;
        bool more = true;

        ifstream assmblyLineFile(file);
        if (!assmblyLineFile)
        {
            throw "Unable to open [" + file + "] file.";
        }
        else
        {
            string record;
            while (std::getline(assmblyLineFile, record))
            {
                size_t next_pos = 0;

                Workstation *ws{};
                std::string station = ut.extractToken(record, next_pos, more);
                if (more)
                {
                    std::string next_station = ut.extractToken(record, next_pos, more);

                    for_each(stations.begin(), stations.end(), [&station, &ws](Workstation *wstemp)
                             { if (wstemp->getItemName() == station) { ws = wstemp; } });
                    for_each(stations.begin(), stations.end(), [&next_station, &ws](Workstation *nstemp)
                             { if (nstemp->getItemName() == next_station) { ws->setNextStation(nstemp); } });
                    m_activeLine.push_back(ws);
                }
                else
                {

                    for_each(stations.begin(), stations.end(), [&station, &ws](Workstation *wstemp)
                             {
                                 if (wstemp->getItemName() == station)
                                 {
                                     ws = wstemp;
                                     ws->setNextStation(nullptr);
                                 } });
                    m_activeLine.push_back(ws);
                }
            }
        }

        // cout << "######## constructor m_activeLine: ########" << endl;
        // for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation *ws)
        //          { cout << ws->getItemName() << "," << endl; });
        // cout << "######## constructor m_activeLine endl ########" << endl;

        assmblyLineFile.close();
        m_cntCustomerOrder = g_pending.size();

        // find the first station

        std::vector<Workstation *> temp_activeLine = m_activeLine;
        Workstation *temp_firstStation{};

        for_each(m_activeLine.begin(), m_activeLine.end(), [&temp_activeLine, &temp_firstStation](Workstation *ws)
                 {
                     bool found{};

                     for_each(temp_activeLine.begin(), temp_activeLine.end(), [&ws, &found, &temp_firstStation](Workstation *ns)
                              {

                  if (ns->getNextStation() && ws->getItemName() == ns->getNextStation()->getItemName()) {

                     found = true;
                  } });
                     if (!found && ws->getNextStation() != nullptr)
                     {
                         temp_firstStation = ws;
                     } });
        m_firstStation = temp_firstStation;
    }

    void LineManager::reorderStations()
    {

        std::vector<Workstation *> temp;
        temp.push_back(m_firstStation);
        Workstation *current_station = m_firstStation;
        while (current_station->getNextStation())
        {
            current_station = current_station->getNextStation();
            temp.push_back(current_station);
        }
        m_activeLine = temp;

        // cout << "######## reorderStations m_activeLine: ########" << endl;
        // for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation *ws)
        //          { cout << ws->getItemName() << "," << endl; });
        // cout << "######## reorderStations m_activeLine endl ########" << endl;
    }

    bool LineManager::run(std::ostream &os)
    {
        bool ret = false;
        static size_t count = 0;
        ++count;
        os << "Line Manager Iteration: " << count << endl;

        if (g_pending.size() > 0)
        {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation *wsptr)
                 { wsptr->fill(os); });

        for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation *wsptr)
                 { wsptr->attemptToMoveOrder(); });

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