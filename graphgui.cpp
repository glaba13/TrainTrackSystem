#include "graphgui.h"
#include <QDebug>

qan::NodeStyle active,inactive;

#define MAX_NUMBER_STATICS_COLORS   32

/*Some Static global variables which are needed for contex (could be moved as static)*/
qan::NodeStyle styles[MAX_NUMBER_STATICS_COLORS];
static  qan::EdgeStyle edgeStyles[MAX_NUMBER_STATICS_COLORS*MAX_NUMBER_STATICS_COLORS];
qan::EdgeStyle acEdge;
QColor in, ac;


/*
 * Constructor
 */
GraphGui::GraphGui() {
    qDebug()<< "Initilize Graph Gui" ;

    in.setRgba(qRgba(255,255,200, 10));
    ac.setRgba(qRgba(0,0,255, 255));

    active.setBackColor(ac);;
    active.setBorderColor(ac);
    active.setBaseColor(ac);
    active.setEffectColor(ac);
    active.setEffectColor(ac);
    active.setEffectColor(ac);
    active.setEffectEnabled(true);
    acEdge.setLineColor(ac);
    inactive.setBackColor(in);

}

/*
 * Distinct color ganarator for different ids
 */
static QColor ColorGenerator(int id) {
    int r = 255;
    int g = 255;
    int b = 255;
    if (id == 1) {
        r = 255;
        g = 165;
        b = 0;
    }  else if (id == 2) {
        r = 0;
        g = 0;
        b = 255;
    }else if (id == 3) {
        r = 0;
        g = 255;
        b = 0;
    } else if (id == 4) {
        r = 255;
        g = 128;
        b = 0;
    }else if (id == 5) {
        r = 0;
        g = 255;
        b = 255;
    }
    return QColor(r, g, b);
}

/*
* Adds node/vertext by id
*/
void GraphGui::AddNode(int id){
    auto itr = nm.find(id);
    if (itr == nm.end())
    {
        auto node = gui->insertCustomNode();
        node->setLabel(QString::number(id));
        node->getItem()->setItemStyle(&inactive);

        nm[id] = node;
        return;
    }

}

void  GraphGui::SetNodeXY(int id, int x, int y){
    AddNode(id);
    auto node = nm[id];
    static constexpr qreal defaultWidth{60.}, defaultHeight{60.};

    node->getItem()->setRect({qreal(x), (qreal)y,  defaultWidth, defaultHeight});

}
/*
 * Adds connections between nodes
 */
void  GraphGui::AddConnection(int from, int to, int color_id, bool act){
    AddNode(from);
    AddNode(to);
    auto edge =  gui->insertCustomEdge(nm[from], nm[to]);
    qan::EdgeStyle *s = new qan::EdgeStyle;
    s->setDashed(true);
    s->setDstShape(qan::EdgeStyle::ArrowShape::Circle);
    s->setSrcShape(qan::EdgeStyle::ArrowShape::Circle);
    if(act) {

        QColor q = ColorGenerator(color_id);
        int color_id_inxd = from*MAX_NUMBER_STATICS_COLORS + to;
        if(colorMap.find(color_id_inxd) != colorMap.end()) {

            QColor qExisting = edgeStyles[color_id_inxd].getLineColor();
            q = QColor::fromRgb((qExisting.red() + q.red())/2, (qExisting.green() + q.green())/2, (qExisting.blue() + q.blue())/2);

        }
        colorMap[color_id_inxd] = true;
        edgeStyles[color_id_inxd].setLineColor(q);

        edge->getItem()->setStyle(&edgeStyles[color_id_inxd]);
        edge->getItem()->getStyle()->setLineColor(q);

    }
    edge->getItem()->setSrcShape(qan::EdgeStyle::ArrowShape::CircleOpen);
    edge->getItem()->setDstShape(qan::EdgeStyle::ArrowShape::Circle);
    s->setArrowSize((qreal)100);
}

void GraphGui::Clear() {
    for (auto const& x : nm)
    {
        x.second->getItem()->setStyle(&inactive);
    }
}


void GraphGui::SetActive(int id, int color_id,  int stopped){
    QColor qc = ColorGenerator(color_id);

    styles[id].setBackColor(qc);
    styles[id].setBorderColor(stopped ? QColor(255, 0,0) : QColor(0, 0,0) );

    //styles
    nm[id]->getItem()->setStyle(&styles[id]);
}

void GraphGui::DisaplayTrains(vector<Train> &trains) {
    Clear();
    for(int i = 0; i < trains.size(); i++) {
        SetActive(trains[i].current, i+1, trains[i].stopped);
    }

    //endings
    for(int i = 0; i < trains.size(); i++) {
        QColor qc = ColorGenerator(i+1);

        styles[trains[i].end].setLabelColor(qc);
        nm[trains[i].end]->getItem()->setStyle(&styles[trains[i].end]);

    }
}

