#pragma once

enum class NodeType
{
    execute,
    add,
    multiply,
    sine,
    time,
    value,
    print,
    ultimate,
    ultimate2,
};

enum class UiNodeType
{
    add,
    multiply,
    sine,
    time,
    print,
    ultimate,
    ultimate2,
};

struct Node
{
    NodeType type;
    float value;

    explicit Node(const NodeType t) : type(t), value(0.f) {}

    Node(const NodeType t, const float v) : type(t), value(v) {}
};

struct UiNode
{
    UiNodeType type;
    // The identifying id of the ui node. For add, multiply, sine, and time
    // this is the "operation" node id. The additional input nodes are
    // stored in the structs.
    int id;

    union
    {
        struct
        {
            int lhs, rhs;
        } add;

        struct
        {
            int lhs, rhs;
        } multiply;

        struct
        {
            int input;
        } sine;

        struct
        {
            int execute;
            int input;
        } print;

        struct
        {
            int execute;
            int input;
        } ultimate;

        struct
        {
            int execute;
            int input;
        } ultimate2;
    } ui;
};