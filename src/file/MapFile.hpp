#ifndef MAPFILE_HPP
#define MAPFILE_HPP

#include "../Common.h"

class MapFileEntry;

/**
* Linker generated module map file parser.
*/
class EXPORT MapFile {
public:
	/** Error code. */
	enum ErrorType {
		/** No error. */
		ERROR_NONE,
		/** File open failed. */
		ERROR_OPEN,
		/** File reading failed. */
		ERROR_READ,
		/** Syntax error. */
		ERROR_PARSE
	};

	/** Reads a map file. */
	explicit MapFile(const char* filename);

	///
	~MapFile();

	/** Returns preferred load address. */
	long loadAddress() const;

	/** Returns ith entry from the map file. */
	const MapFileEntry & getEntry(int i) const;

	/** Returns ith segment from the map file. */
	const MapFileEntry & getSegment(int i) const;

	/** Returns number of segments in the map file. */
	int	segments() const;

	/** Returns number of entries in the map file. */
	int	entries() const;

	/** Returns error code or 0 (ERROR_NONE) if no error. */
	ErrorType	error() const;

	/** Returns line number of last successful read character. */
	int	line() const;

	/**
	* Finds entry which contains specified address.
	* @return Entry index or -1 if not found.
	*/
	int	findEntry(long addr) const;

	/**
	* Returns current module name, with map extension.
	* The output buffer is always 0-terminated.
	*/
	static void	getModuleMapFilename(char* buffer, int bufferSize);

private:
	class MapFileImpl;
	MapFileImpl* m_this;

	MapFile(const MapFile &);
	MapFile & operator=(const MapFile &);
};

#endif
