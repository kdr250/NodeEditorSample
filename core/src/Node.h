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
    integer,
    boolean,
    print,
    ultimate,
    ultimate2,
    IF,
    ELSE,
    END_IF,
    less,
    LOOP,
    END_LOOP,
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
    ELSE,
    END_IF,
    less,
    LOOP,
    END_LOOP,
};

enum class PinType
{
    value,
    integer,
    boolean,
    execute,
};

struct Node
{
    NodeType type;

    union
    {
        struct
        {
            float value;
        };

        struct
        {
            int id;
        };

        struct
        {
            int integer;
        };

        struct
        {
            bool condition;
        };
    };

    explicit Node(const NodeType t) : type(t), value(0.f) {}

    Node(const NodeType t, const float v) : type(t), value(v) {}
    Node(const NodeType t, const int id) : type(t), id(id) {}
    Node(const NodeType t, const bool c) : type(t), condition(c) {}

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

            case NodeType::integer:
                return PinType::integer;

            case NodeType::boolean:
            case NodeType::less:
                return PinType::boolean;

            case NodeType::execute:
            case NodeType::next:
            case NodeType::print:
            case NodeType::IF:
            case NodeType::ELSE:
            case NodeType::END_IF:
            case NodeType::LOOP:
            case NodeType::END_LOOP:
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
        } If;

        struct
        {
            int execute;
            int next;
        } Else;

        struct
        {
            int execute;
            int next;
        } EndIf;

        struct
        {
            int lhs, rhs;
        } less;

        struct
        {
            int execute;
            int count;
            int next;
        } Loop;

        struct
        {
            int execute;
            int next;
        } EndLoop;
    } ui;
};