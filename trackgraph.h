#ifndef TRACK_GRAPH_H
#define TRACK_GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

/*
 *            ______
 *  Start -> |      | <- End
 *            ------
 *
 */
typedef enum segmentConnection {
    START,
    END
} segmentConnection;


/*
 *  Segment
 */
typedef struct segment {
    int id;
    bool startSignal; //singal at start
    bool endSignal; //signal at end

    typedef pair<segment*, segmentConnection> infoSegment; //segment + cost of going to segment
    vector<infoSegment> connections;

    segment(int s) : id(s), startSignal(false), endSignal(false) {}

    bool operator== (segment &ot) { return ot.id == id;}
} segment;


/*
 * Entire graph
 *
 *
 */

class TrackGraph
{
    typedef map<int, segment *> smap;  //segment map
    smap segments;
    /*
     * Adds a segment with identifier only if not exists
     */
    void addSegmentIfNotExist(const int);

public:
    /*
     * Adds a segment with identifier
     */
    void addSegment(const int);
    void addEdge(const int from, const int to);
    //Cost from traveling from one point to other
    int cost(segment *from, segment * to);
    segment * operator[](int i);
    TrackGraph();
};

#endif // TRACK_GRAPH_H
