#include "edgelist.h"

EdgeList::EdgeList()
{

}

void EdgeList::add(int start, int end)
{
    const QPair<int, int> edge(qMin(start, end), qMax(start, end));
    if(!helperSet.contains(edge))
    {
        edges.append(edge);
        helperSet.insert(edge);
    }
}

bool EdgeList::isValidIndex(qsizetype index)
{
    return edges.size() > index;
}

void EdgeList::clear()
{
    edges.clear();
    helperSet.clear();
}

QPair<int, int> &EdgeList::operator[](qsizetype index)
{
    return edges[index];
}
