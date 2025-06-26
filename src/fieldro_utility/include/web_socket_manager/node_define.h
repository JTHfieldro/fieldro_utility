#pragma once

#include <string>

namespace frb
{
enum class NodeList
{
  LocalizationNode = 0,
  Target01,
  Target02,
  Target03
};

inline std::string node_to_string(NodeList node)
{
    switch(node)
    {
      case NodeList::LocalizationNode: return "localization_node";
      case NodeList::Target01: return "target_01";
      case NodeList::Target02: return "target_02";
      case NodeList::Target03: return "target_03";
      default: return "UNKNOWN";
    }
}
}