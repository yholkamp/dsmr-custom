#pragma once

#include <string>

namespace esphome {
namespace dsmr_custom {

struct ObisLineParts {
  std::string obis_code_str;
  std::string last_value_segment;
};

// Extracts the OBIS code (trimmed of whitespace) and the final parenthesized
// value segment (e.g., skipping a timestamp block). Returns empty strings on
// malformed input.
ObisLineParts extract_obis_and_last_value(const std::string &line_str);

}  // namespace dsmr_custom
}  // namespace esphome
