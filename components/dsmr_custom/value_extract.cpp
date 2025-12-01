#include "value_extract.h"

#include <algorithm>

namespace esphome {
namespace dsmr_custom {

ObisLineParts extract_obis_and_last_value(const std::string &line_str) {
  ObisLineParts parts{};

  size_t first_paren_pos = line_str.find('(');
  if (first_paren_pos == std::string::npos) {
    return parts;
  }

  parts.obis_code_str = line_str.substr(0, first_paren_pos);
  parts.obis_code_str.erase(
      std::remove_if(parts.obis_code_str.begin(), parts.obis_code_str.end(), ::isspace),
      parts.obis_code_str.end());

  // Extract all parenthesized value segments; pick the last one to ensure we skip timestamps.
  size_t search_pos = first_paren_pos;
  while (search_pos != std::string::npos && search_pos < line_str.length()) {
    size_t seg_start = line_str.find('(', search_pos);
    if (seg_start == std::string::npos) break;
    size_t seg_end = line_str.find(')', seg_start + 1);
    if (seg_end == std::string::npos || seg_end <= seg_start + 1) {
      break;  // malformed or empty segment
    }
    parts.last_value_segment = line_str.substr(seg_start + 1, seg_end - (seg_start + 1));
    search_pos = seg_end + 1;
  }

  return parts;
}

}  // namespace dsmr_custom
}  // namespace esphome
