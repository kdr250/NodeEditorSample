#pragma once

enum class NodeType
{
    execute,
    next,
    add,
    multiply,
    sine,
    time,
    value,
    print,
    ultimate,
    ultimate2,
    IF,
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
    IF,
};

enum class PinType
{
    value,
    execute,
};

struct Node
{
    NodeType type;
    float value;

    explicit Node(const NodeType t) : type(t), value(0.f) {}

    Node(const NodeType t, const float v) : type(t), value(v) {}

    static inline PinType GetPinType(NodeType nodeType)
    {
        switch (nodeType)
        {
            case NodeType::add:
            case NodeType::multiply:
            case NodeType::sine:
            case NodeType::time:
            case NodeType::value:
            case NodeType::ultimate:
            case NodeType::ultimate2:
                return PinType::value;

            case NodeType::execute:
            case NodeType::next:
            case NodeType::print:
            case NodeType::IF:
                return PinType::execute;

            default:
                break;
        }
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
            int next;
        } ultimate;

        struct
        {
            int execute;
            int input;
            int next;
        } ultimate2;

        struct
        {
            int execute;
            int input;
            int next;
        } IF;
    } ui;
};