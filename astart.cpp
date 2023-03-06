#include "astart.h"

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
 * Internal custom proiotity queue with path
 */
template<typename T, typename priority_t>
struct PriorityQueue {
    typedef std::pair<priority_t, T> PriorityQueuePair;
    std::priority_queue<PriorityQueuePair, std::vector<PriorityQueuePair>,
    std::greater<PriorityQueuePair>> elements;

    bool empty() const {
        return elements.empty();
    }

    void put(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
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
std::vector<segment *> get_final_path(
        segment *start, segment *goal,
        std::unordered_map<segment *, segment *> came_from
        ) {
    std::vector<segment *> path;
    segment *current = goal;
    if (came_from.find(goal) == came_from.end()) {
        return path; // no path can be found
    }
    while (current != start) {
        path.push_back(current);
        current = came_from[current];
    }
    path.push_back(start); // optional
    std::reverse(path.begin(), path.end());
    return path;
}


/*
 * Gets the final path (reverses the result for display)
 */
void a_star_search
(TrackGraph graph,
 segment *start,
 segment *goal,
 std::unordered_map<segment *, segment *>& came_from,
 std::unordered_map<segment *, double>& cost_so_far,
 Heuristic *h,
 segmentConnection dir)
{
    PriorityQueue<segment *, double> frontier;
    frontier.put(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        segment * current = frontier.get();

        if (current == goal) {
            break;
        }


        for (segment::infoSegment next : current->connections) {
            if(next.second != dir) {
                continue;
            }
            double new_cost = cost_so_far[current] + graph.cost(current, next.first) + h->heuristic(next.first, goal);

            if (cost_so_far.find(next.first) == cost_so_far.end()
                    || new_cost < cost_so_far[next.first]) {
                cost_so_far[next.first] = new_cost;
                double priority = new_cost + h->heuristic(next.first, goal);
                frontier.put(next.first, priority);
                came_from[next.first] = current;
            }
        }
    }
}
