#include <QGuiApplication>
#include <QtQml>
#include <QQuickStyle>
#include <QuickQanava.h>

#include "./TrainTrackSolver.h"
#include "trackgraph.h"
#include "parser.h"
#include "graphgui.h"
#include "astart.h"
#include "buttonCust.h"

using namespace qan;

const QString ConfigPath =   "C:/Users/SESA666234/Documents/CVS/MV/QuickQanava-2.2.0/QuickQanava-2.2.0/samples/cpp/Test2.xml";


/*
 * Some QCanva Helper functions
 *
 */
QQmlComponent*  CustomGroup::delegate(QQmlEngine &engine, QObject* parent) noexcept {
    Q_UNUSED(parent)
    static std::unique_ptr<QQmlComponent> delegate;
    if (!delegate)
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:/CustomGroup.qml");
    return delegate.get();
}

qan::NodeStyle* CustomGroup::style(QObject* parent) noexcept {
    Q_UNUSED(parent)
    static std::unique_ptr<qan::NodeStyle> style;
    if (!style) {
        style = std::make_unique<qan::NodeStyle>();
    }
    return style.get();
}

QQmlComponent*  CustomNode::delegate(QQmlEngine &engine, QObject* parent) noexcept
{
    Q_UNUSED(parent)
    static std::unique_ptr<QQmlComponent> customRectNode_delegate;
    if (!customRectNode_delegate)
        customRectNode_delegate =
                std::make_unique<QQmlComponent>(&engine, "qrc:/CustomNode.qml");
    return customRectNode_delegate.get();
}

qan::NodeStyle *CustomNode::style(QObject* parent) noexcept
{
    Q_UNUSED(parent)
    static std::unique_ptr<qan::NodeStyle> customRectNode_style;
    if (!customRectNode_style) {
        customRectNode_style = std::make_unique<qan::NodeStyle>();
        customRectNode_style->setBackColor(QColor("#ff29fc"));
    }
    return customRectNode_style.get();
}

QQmlComponent *CustomEdge::delegate(QQmlEngine &engine, QObject* parent) noexcept {
    Q_UNUSED(parent)
    static std::unique_ptr<QQmlComponent> customEdge_delegate;
    if (!customEdge_delegate)
        customEdge_delegate =
                std::make_unique<QQmlComponent>(&engine, "qrc:/CustomEdge.qml");
    return customEdge_delegate.get();
}

qan::EdgeStyle *CustomEdge::style(QObject* parent) noexcept {
    Q_UNUSED(parent)
    static std::unique_ptr<qan::EdgeStyle> customEdge_style;
    if (!customEdge_style)
        customEdge_style = std::make_unique<qan::EdgeStyle>();
    return customEdge_style.get();
}

qan::Group *CustomGraph::insertCustomGroup() {
    return qan::Graph::insertGroup<CustomGroup>();
}

qan::Node *CustomGraph::insertCustomNode() {
    return qan::Graph::insertNode<CustomNode>(nullptr);
}

qan::Edge *CustomGraph::insertCustomEdge(qan::Node *source,
                                         qan::Node *destination) {
    const auto engine = qmlEngine(this);
    if (source != nullptr &&
            destination != nullptr &&
            engine != nullptr)
        return qan::Graph::insertEdge<CustomEdge>(*source, destination, CustomEdge::delegate(*engine));
    return nullptr;
}

void delay(int secs = 1)
{
    QTime dieTime= QTime::currentTime().addMSecs(500);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


/*
 * Custom single button
 */
ButtonCust runButton;
bool ButtonCust::pressed = false;
void waitPress() {
    while(!runButton.wasPressed()) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    }
}

/*
 * Helper function, checks if there is a way for a tain, used for simulation to stop a train
 */
bool IsWayFree(int train_indx, vector<int> &curr_steps, vector<Train> & trains,  std::vector<std::vector<segment *>>& paths) {
    //return true;

    int curr_step_train = curr_steps[train_indx];
    auto path = paths[train_indx];
    for(int i = curr_step_train; i < path.size(); i++) {
        for(int j = 0; j < trains.size(); j++) {
            if(j==train_indx) continue;

            if(trains[j].current == path[i]->id) return false;
        }
    }
    return true;
}

/*
 * Find a solution using AStar and Custom Euristic and finilize results in result path vectors
 */
void solve(TrackGraph &tg, vector<Train> &trains, std::vector<std::vector<segment *>> &results) {
    MyHeuristic myHeur;
    for(int i= 0; i < trains.size(); i++) {
        qDebug()<< " Train " << i << trains[i].start << trains[i].end;
        std::unordered_map<segment *, segment *> came_from;
        std::unordered_map<segment *, double> cost_so_far;
        myHeur.setTrainID(i);
        a_star_search(tg, tg[trains[i].start], tg[trains[i].end], came_from, cost_so_far, &myHeur, trains[i].dir ? segmentConnection::END : segmentConnection::START);

        std::vector<segment *> path = get_final_path(tg[trains[i].start], tg[trains[i].end], came_from);
        qDebug() << "Result" << path.size();
        myHeur.addPath(path);
        results.push_back(path);
    }
}

/*
 *  Simulate results and train movement
 */
void simulate( GraphGui& gg, TrackGraph &tg, vector<Train> &trains, std::vector<std::vector<segment *>> &results) {

    gg.DisaplayTrains(trains);
    waitPress();
    vector<int> curr_steps;
    for(int i = 0; i < results.size(); i++) {
        curr_steps.push_back(1);
    }
    bool more_steps  = true;
    while(more_steps) {
        more_steps = false;
        for(int p=0; p < results.size(); p++) {
            vector<segment *> &path = results[p];
            int step = curr_steps[p];
            if(step < path.size()) {
                more_steps = true;
                qDebug() << p << " step " <<step<< "path "<<path[step]->id<< endl;
                if(IsWayFree(p,  curr_steps, trains, results)) {
                    trains[p].current = path[step]->id;
                    trains[p].stopped = false;
                    gg.AddConnection(((step == 0) ? trains[step].start : path[step - 1]->id), path[step]->id, p + 1, true);
                    curr_steps[p]++;
                } else {
                    trains[p].stopped = true;
                }
            }
            gg.DisaplayTrains(trains);
        }
        delay();
    }
}

/*
 * Run the algorithm and simulation
 */
void run(QPointer<CustomGraph> &graph) {
    TrackGraph tg;
    GraphGui gg(graph);
    vector<Train> trains;
    std::vector<std::vector<segment *>> results;

    ParseConfig(ConfigPath, gg, tg, trains);
    qDebug() << "Train len" << trains.size();


    solve(tg, trains, results);
    simulate(gg, tg, trains, results);

}


//-----------------------------------------------------------------------------
int	main( int argc, char** argv )
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;
    engine.addPluginPath(QStringLiteral("../../src")); // Necessary only for development when plugin is not installed to QTDIR/qml
    QuickQanava::initialize(&engine);
    //Loading defult stles
    qmlRegisterType<CustomGroup>("MyModule", 1, 0, "CustomGroup");
    qmlRegisterType<CustomNode>("MyModule", 1, 0, "CustomNode");
    qmlRegisterType<CustomGraph>("MyModule", 1, 0, "CustomGraph");
    qmlRegisterType<CustomEdge>("MyModule", 1, 0, "AbstractCustomEdge");

    engine.load(QUrl("qrc:/TrainTrackSolver.qml"));



    {
        QPointer<CustomGraph> graph = nullptr;
        QObject *button = nullptr;

        for (const auto rootObject : engine.rootObjects()) {
            graph = qobject_cast<CustomGraph*>(rootObject->findChild<QQuickItem *>("graph"));
            if (graph)
                break;
        }

        for (const auto rootObject : engine.rootObjects()) {
            button = rootObject->findChild<QObject *>("btn");
            if (button)
                break;
        }
        QObject::connect(button, SIGNAL(clicked()), &runButton, SLOT(insert()));

        if (graph) {
            //RUN
            run(graph);
        }
    }

    return app.exec();
}
//-----------------------------------------------------------------------------


