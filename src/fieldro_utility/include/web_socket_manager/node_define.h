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

enum class ScriptList
{
  Script01 = 1,
  Script02,
  Script03,
  Script04,
  Script05,
  Script06,
  Script07,
  Script08,
  Script09,
  Script10
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

inline std::string script_to_string(ScriptList script)
{
    switch(script)
    {
      case ScriptList::Script01: return "script_01";
      case ScriptList::Script02: return "script_02";
      case ScriptList::Script03: return "script_03";
      case ScriptList::Script04: return "script_04";
      case ScriptList::Script05: return "script_05";
      case ScriptList::Script06: return "script_06";
      case ScriptList::Script07: return "script_07";
      case ScriptList::Script08: return "script_08";
      case ScriptList::Script09: return "script_09";
      case ScriptList::Script10: return "script_10";
      default: return "UNKNOWN";
    }
}

}