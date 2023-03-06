#ifndef TRAIN_H
#define TRAIN_H

#include <string>

class Train
{

    /*Private variables*/
    int id; //ID of the train (auto generatated by id generator)
    static int id_generator;

public:
    /*Public variables*/
    int start; //start note of the traic
    int end; //end node/segment of the train
    int current; //curent location
    bool stopped; //if stopped
    bool dir;

    /*
     *Constructor
     */
    Train(int s, int e, bool d = true) : start(s), end(e), current(s), stopped(false), dir(d) {
        id = id_generator++;
    }

    int GetId() {return id;}

};

#endif // TRAIN_H
