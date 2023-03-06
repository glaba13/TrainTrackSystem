//-----------------------------------------------------------------------------
#pragma once
// Qt headers
#include <QGuiApplication>
#include <QtQml>
#include <QQuickStyle>

// QuickQanava headers
#include <QuickQanava.h>


class CustomGroup : public qan::Group
{
    Q_OBJECT
public:
    explicit CustomGroup(QObject* parent = nullptr) : qan::Group{parent} {}
    virtual ~CustomGroup() override { /* Nil */ }
private:
    CustomGroup(const CustomGroup &) = delete;

public:
    static QQmlComponent*     delegate(QQmlEngine &engine, QObject* parent = nullptr) noexcept;
    static qan::NodeStyle*    style(QObject* parent = nullptr) noexcept;
};

QML_DECLARE_TYPE(CustomGroup)

class CustomNode : public qan::Node
{
    Q_OBJECT
public:
    explicit CustomNode(QObject* parent = nullptr) : qan::Node{parent} { /* Nil */ }
    virtual ~CustomNode() override { /* Nil */ }
private:
    CustomNode(const CustomNode &) = delete;

public:
    static QQmlComponent*     delegate(QQmlEngine &engine, QObject* parent = nullptr) noexcept;
    static qan::NodeStyle*    style(QObject* parent = nullptr) noexcept;
};

QML_DECLARE_TYPE(CustomNode)

class CustomEdge : public qan::Edge {
    Q_OBJECT
public:
    explicit CustomEdge(QObject* parent = nullptr) : qan::Edge{parent} {}
    virtual ~CustomEdge() override = default;
private:
    CustomEdge(const CustomEdge &) = delete;

public:
    static QQmlComponent*     delegate(QQmlEngine &engine, QObject* parent = nullptr) noexcept;
    static qan::EdgeStyle*    style(QObject* parent = nullptr) noexcept;
};

QML_DECLARE_TYPE(CustomEdge)

class CustomGraph : public qan::Graph {
    Q_OBJECT
public:
    explicit CustomGraph(QQuickItem *parent = nullptr) : qan::Graph{parent} { /* Nil */ }
    virtual ~CustomGraph() override  { /* Nil */ }
private:
    CustomGraph(const CustomGraph &) = delete;

public:
    Q_INVOKABLE qan::Group*   insertCustomGroup();
    Q_INVOKABLE qan::Node*    insertCustomNode();
    Q_INVOKABLE qan::Edge*    insertCustomEdge(qan::Node* source, qan::Node* destination);
};

QML_DECLARE_TYPE(CustomGraph)
