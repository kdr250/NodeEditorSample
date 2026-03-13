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

enum class PinType
{
    value,
    execute,
};

static inline PinType GetPinType(NodeType nodeType)
{
    switch (nodeType)
    {
        case NodeType::add:
        case NodeType::multiply:
        case NodeType::sine:
        case NodeType::time:
        case NodeType::value:
            return PinType::value;

        case NodeType::execute:
        case NodeType::print:
        case NodeType::ultimate:
        case NodeType::ultimate2:
            return PinType::execute;

        default:
            break;
    }
}

struct Node
{
    NodeType type;
    PinType pinType;
    float value;

    explicit Node(const NodeType t) : type(t), value(0.f)
    {
        pinType = GetPinType(type);
    }

    Node(const NodeType t, const float v) : type(t), value(v)
    {
        pinType = GetPinType(type);
    }
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