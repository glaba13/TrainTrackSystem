#include "trackgraph.h"


using namespace std;

/*
 * Adds a segment
 */
void TrackGraph:: addSegment(const int id)
{
    addSegmentIfNotExist(id);
}

void TrackGraph:: addSegmentIfNotExist(const int id)
{
    smap::iterator itr = segments.find(id);
    if (itr == segments.end())
    {
        segment *s;
        s = new segment(id);
        segments[id] = s;
        return;
    }
}

/*
 * Adds an efge between segments, creates segment if not exist
 */
void TrackGraph:: addEdge(const int from, const int to)
{
    //add if not exist
    addSegmentIfNotExist(from);
    addSegmentIfNotExist(to);

    segment *f = (segments.find(from)->second);
    segment *t = (segments.find(to)->second);
    pair<segment *, segmentConnection> edge = make_pair(t, segmentConnection::END);
    f->connections.push_back(edge);
    edge = make_pair(f, segmentConnection::START);
    t->connections.push_back(edge);
}

/*
 * Cost, currently just 1
 */
int TrackGraph::cost(segment *from, segment * to)
{
    return 1;
}

/*
 * Easy access by index
 */
segment * TrackGraph::operator[](int i) {
    return segments[i];
}


TrackGraph::TrackGraph()
{

}
