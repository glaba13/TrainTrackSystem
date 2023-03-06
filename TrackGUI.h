#ifndef TRACKGUI_H
#define TRACKGUI_H

/*
 *  General Track GUI, abstract Class
 */
class TrackGUI
{
public:

    /*
      * Adds node/vertext by id
      */
    virtual void AddNode(int id) = 0;

    /*
     * St node coordinates
     */
    virtual void  SetNodeXY(int id, int x, int y) = 0;


    /*
     * Add edges/connection with associated optional color and if it is active (act) or not
     */
    virtual void  AddConnection(int from, int to, int color_id = 0, bool act = 0 ) = 0;


};

#endif // TRACKGUI_H
