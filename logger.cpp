#include "logger.h"

Severity Logger::m_severity = Severity::INFO;
std::string Logger::m_filename;
int Logger::m_line;
std::string Logger::m_funcname;