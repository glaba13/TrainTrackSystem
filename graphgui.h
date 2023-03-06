#ifndef GRAPHGUI_H
#define GRAPHGUI_H

#include "TrackGUI.h"
#include "TrainTrackSolver.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "train.h"

using namespace std;


/*
 *  QT Graph gui Implementatinn of Track GUI/abstract Class
 */

class GraphGui : public TrackGUI
{

    QPointer<CustomGraph> gui;
    map<int, qan::Node *> nm;
    map<int, bool> colorMap;

public:
    GraphGui();

    GraphGui(QPointer<CustomGraph> &gui) {
        GraphGui();
        this->gui = gui;

    }

    /*
   * Adds node/vertext by id
   */
    void AddNode(int id);

    /*
     * St node coordinates
     */
    void  SetNodeXY(int id, int x, int y);
    /*
     * Add edges/connection with associated optional color and if it is active (act) or not
     */
    void  AddConnection(int from, int to, int color_id = 0, bool ac = 0);

    void Clear();
    void SetActive(int id,  int color_id = 1,  int stopped = false);
    void DisaplayTrains(vector<Train> &trains);

};

#endif // GRAPHGUI_H
