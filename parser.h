#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include "trackgraph.h"
#include "TrainTrackSolver.h"
#include "TrackGUI.h"
#include "Train.h"

/*
 * Parses xml config file and if succesful serilized inside the trackGraph and draws on display
 */
void ParseConfig(QString filename,  TrackGUI &gui, TrackGraph &tg, vector<Train> &trains);


#endif // PARSER_H
