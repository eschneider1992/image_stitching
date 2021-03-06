#include "d_point.h"


void DPoint::createEdge(const int idxOfPoint)
{
    std::vector<int>::iterator it;
    it = find(m_connections.begin(), m_connections.end(), idxOfPoint);
    if ( it == m_connections.end() )
    {
        m_connections.push_back(idxOfPoint);
    } else
    {
        std::cout << "Tried to create edge from " << m_idx << " to " << idxOfPoint <<
                     ", but that edge already existed\n";
    }
}


void DPoint::deleteEdge(const int idxToDelete)
{
    std::vector<int>::iterator it;
    it = find(m_connections.begin(), m_connections.end(), idxToDelete);
    if ( it == m_connections.end() )
    {
        std::cout << "Tried to delete edge from " << m_idx << " to " << idxToDelete <<
                     ", but that edge doesn't exist\n";
    } else
    {
        m_connections.erase(it);
    }
}


bool DPoint::isConnected(const int idx)
{
    std::vector<int>::iterator it;
    it = find(m_connections.begin(), m_connections.end(), idx);
    return it != m_connections.end();
}


DPoint& DPoint::operator= (const DPoint &dpSource)
{
    if (this == &dpSource)
        return *this;

    m_idx = dpSource.m_idx;
    m_x = dpSource.m_x;
    m_y = dpSource.m_y;
    m_connections = dpSource.m_connections;
    return *this;
}


std::ostream& operator<< (std::ostream &out, DPoint &dp)
{
    out << "DPoint [" << dp.m_idx << "], at " <<
           "(" << dp.m_x << ", " << dp.m_y   << "), connected to DPoints [";
    for (int i{}; i < static_cast<int>(dp.m_connections.size()); ++i)
    {
        std::cout << dp.m_connections[i];
        if (i != (static_cast<int>(dp.m_connections.size()) - 1) )
        {
            std::cout << ", ";
        }
    }
    std::cout << "]";
    return out;
}
