
# TruckTrainSolver

This program showsh the simulation of a train traffic and signaling system. 

## System

The system consist of :
- Trucks (a segment which has a start and an end)
- Connection between tracks 
   - Direct
   - Junction with others
- Signals (which are placed optionaly at the tracks)


### Graph

In order to model the problem, the data model is defined as following:
- Tracks/Segments are described as  Node/Vertex
    - Each node has:
      - id
      - location (optional for GUI)
      - Connection (Note that each conection has identification if it is from start or from end)
- Edges/Arcs: If two Segments are connected, an edge is places with the proper direction
- Trains have sdirection and start at the current Segmen (Node)


![](https://raw.githubusercontent.com/glaba13/ImageResources/master/train_1.gif)

# Algorithm

To find the path A-Star  graph traversal and path search algorithm is utilized.

## Heuristic

For euristic after various trials the final custom hauristic is defined.
For simple 1 train case it deafults to dejickstra algorith,
Current Heuristic has a context and every time if the path si on the way of existing train it adds the cost of the whole path which are blocked by other train.

## Architecture

- Train
    - start, end
    - id
    - curr location
    - direction
    - is stopped or not
- Graph
- connection 
   - form
   - to
- Segment (Node) 
    - id
    - location
    - connections
- TrackGUI (abstract GUI)
- GraphGUI (actual QT implementation)


## Layout

Custom format XML is utilized to describe Layout

Example:

```xml
<data>
    <segment id="1" x="800" y = "200">
        <link id="3"/>
    </segment>
    <segment id="2"  x="400" y = "500">

       <link id="1"/>
    </segment>
    <segment id="3"  x="400" y = "200">

      <link id="2"/>
    </segment>
    <segment id="4"  x="800" y = "500">
      <link id="1"/>
    </segment>
    <segment id="5"  x="1000" y = "500">
      <link id="1"/>
    </segment>
    <train from = "5" to = "2"/>
</data>

```

## TrackGUI
Abstract TrackGUI is utilized to make solution platfor independant, however more work is needed to remove all dependencies

```cpp
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

```
## Examples
![](https://raw.githubusercontent.com/glaba13/ImageResources/master/train_2.gif)
![](https://raw.githubusercontent.com/glaba13/ImageResources/master/train_3.gif)
## Technical Requirements

- QT >5.1
- VS2017
- QuickQanava (QML)

# Contact

Please open an issue/PR for any questions/imporovements