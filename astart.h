#ifndef ASTART_H
#define ASTART_H

#include <QDebug>
#include <queue>
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <iomanip>
#include <cstdlib>
#include "trackgraph.h"

/*
 * Virutal Heirstic Generilized class
 */
class Heuristic {
public:
    virtual double heuristic(segment *a, segment *b) {return 0;}
};

/*
 * Custom  Heurisitc
 *
 * Checks conflicts for the roads and adds the path for the dealy for the score
 */
class MyHeuristic : public Heuristic {
public:
    std::vector<std::vector<segment *>> m_heuristi_map;
    int id;

    /*
     * Add current path to the known min pathes
     */
    void addPath(std::vector<segment *>& p) {
        m_heuristi_map.push_back(p);
    }

    void setTrainID(int id) {
        this->id = id;
    }

    /*
     * Calculate Score
     * @Return: Score
     * @Param, Segmen a, Segment b
     */
    int calculateScore(segment *a, segment *b) {
        //  return 0;

        int res = 0;
        for(int i = 0; i < m_heuristi_map.size(); i++) {
            //  if(i == id) continue;
            for(int j = 0; j < m_heuristi_map[i].size(); j++) {

                if( m_heuristi_map[i][j]->id == a->id) res += m_heuristi_map[i].size();
            }
        }
        qDebug()<< "Train: "<< id<< "    " << a->id  << "->" << b ->id << "=" << res;
        return res;
    }

    double heuristic(segment *a, segment *b) {
        //a on the way to other path + length

        return calculateScore(a,b);
    }
};


/*
 *  A start algorithm, find the optimal path with given Heuristic
 *  graph: Graph stucture
 *  path_from, goal: statt and end
 *  came_from, costs:  utitility maps for the algorithm
 *  h: Heuristic
 *  dir: Originad Direction
 */
void a_star_search
(TrackGraph graph,
 segment *start,
 segment *goal,
 std::unordered_map<segment *, segment *>& path_from,
 std::unordered_map<segment *, double>& costs,
 Heuristic *h,
 segmentConnection dir =  segmentConnection::END);


/*
 * Gets the final path (reverses the result for display)
 */
std::vector<segment *> get_final_path(
        segment *start, segment *goal,
        std::unordered_map<segment *, segment *> came_from);


#endif // ASTART_H
