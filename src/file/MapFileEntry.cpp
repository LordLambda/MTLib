#include "MapFileEntry.hpp"

MapFileEntry::MapFileEntry() {
	m_sec = 0;
	m_addr = 0;
	m_len = 0;
	m_name[0] = 0;
}

MapFileEntry::MapFileEntry(long section, long offset, long length, const char* name) {
	m_sec = section;
	m_addr = offset;
	m_len = length;

	strncpy(m_name, name, MAX_NAME);
	m_name[MAX_NAME] = 0;
}

long MapFileEntry::section() const {
	return m_sec;
}

long MapFileEntry::offset() const {
	return m_addr;
}

long MapFileEntry::length() const  {
	return m_len;
}

const char* MapFileEntry::name() const {
	return m_name;
}

bool MapFileEntry::operator<(const MapFileEntry & other) const {
	if (m_sec < other.m_sec)
		return true;
	if (m_sec > other.m_sec)
		return false;
	return m_addr < other.m_addr;
}
