#ifndef MAPFILEENTRY_HPP
#define MAPFILEENTRY_HPP

#include "../Common.h"

class EXPORT MapFileEntry {
public:
	/** Class constants. */
	enum Constants {
		/** Maximum number of characters in map file entry name. */
		MAX_NAME = 256
	};

	///
	MapFileEntry();

	/** Creates an entry with specified section, offset, length and name. */
	MapFileEntry(long section, long offset, long length, const char* name);

	/** Returns section of the entry. */
	long section() const;

	/** Returns offset of the entry. */
	long offset() const;

	/** Returns length of the entry (only defined for segments). */
	long length() const;

	/** Returns name of the entry. */
	const char*	name() const;

	/** Returns true if the offset of this entry is before the other one. */
	bool operator<(const MapFileEntry & other) const;

private:
	long	m_sec;
	long	m_addr;
	long	m_len;
	char	m_name[MAX_NAME + 1];
};

#endif
