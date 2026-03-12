#include "LuaScriptBuilder.h"

std::stringstream LuaScriptBuilder::Evaluate(const example::Graph<Node>& graph, const int root_node)
{
    std::stringstream result;

    std::stack<int> postorder;
    dfs_traverse(graph,
                 root_node,
                 [&postorder](const int node_id) -> void
                 {
                     postorder.push(node_id);
                 });

    std::stack<std::string> code_stack;
    unsigned int variable_id = 0;
    while (!postorder.empty())
    {
        const int id = postorder.top();
        postorder.pop();
        const Node node = graph.node(id);

        switch (node.type)
        {
            case NodeType::add:
            {
                std::string rhs = code_stack.top();
                code_stack.pop();
                std::string lhs = code_stack.top();
                code_stack.pop();
                std::string varId = "var" + std::to_string(variable_id++);
                result << varId << " = " << lhs << " + " << rhs << ";" << std::endl;
                code_stack.push(varId);
            }
            break;
            case NodeType::multiply:
            {
                std::string rhs = code_stack.top();
                code_stack.pop();
                std::string lhs = code_stack.top();
                code_stack.pop();
                std::string varId = "var" + std::to_string(variable_id++);
                result << varId << " = " << lhs << " * " << rhs << ";" << std::endl;
                code_stack.push(varId);
            }
            break;
            case NodeType::sine:
            {
                std::string x = code_stack.top();
                code_stack.pop();
                std::string varId = "var" + std::to_string(variable_id++);
                result << varId << " = " << "math.sin(" << x << ");" << std::endl;
                code_stack.push(varId);
            }
            break;
            case NodeType::time:
            {
                std::string varId = "var" + std::to_string(variable_id++);
                result << varId << " = " << "os.clock();" << std::endl;
                code_stack.push(varId);
            }
            break;
            case NodeType::value:
            {
                // If the edge does not have an edge connecting to another node, then just use the value
                // at this node. It means the node's input pin has not been connected to anything and
                // the value comes from the node's UI.
                if (graph.num_edges_from_node(id) == 0ull)
                {
                    code_stack.push(std::to_string(node.value));
                }
            }
            break;

            case NodeType::ultimate:
            {
                std::string x = code_stack.top();
                code_stack.pop();
                std::string varId = "var" + std::to_string(variable_id++);
                result << varId << " = " << "UltimateFunction(" << x << ");" << std::endl;
                code_stack.push(varId);
            }
            break;

            case NodeType::ultimate2:
            {
                std::string x = code_stack.top();
                code_stack.pop();
                std::string varId = "var" + std::to_string(variable_id++);
                result << varId << " = " << "UltimateFunction2(" << x << ");" << std::endl;
                code_stack.push(varId);
            }
            break;

            case NodeType::print:
            {
                std::string input = code_stack.top();
                code_stack.pop();
                result << "print(" << input << ");" << std::endl;
            }
            break;
            default:
                break;
        }
    }

    return result;
}
