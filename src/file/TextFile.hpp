#ifndef TEXTFILE_HPP
#define TEXTFILE_HPP

#include "../Common.h"

//Pretty self explanatory
class EXPORT TextFile {
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

	/** Opens a file. */
	explicit TextFile(const char* filename);

	///
	~TextFile();

	/**
	* Reads a single character.
	* @return true if read ok.
	*/
	bool readChar(char* ch);

	/**
	* Peeks a single character.
	* @return true if peek ok.
	*/
	bool peekChar(char* ch);

	/**
	* Reads whitespace delimited string.
	* If the string doesnt fit to the buffer then
	* the rest of the string is skipped. Buffer
	* is always 0-terminated.
	* @param buf [out] Pointer to string buffer.
	* @param size String buffer size. Must be larger than 0.
	* @return false if end-of-file reached before any characters was read.
	*/
	bool readString(char* buf, int size);

	/** Skips the rest of the line. */
	void skipLine();

	/** Reads hex integer. Skips preceding whitespace. */
	long readHex();

	/**
	* Skips whitespace characters.
	* @return false if end-of-file reached.
	*/
	bool skipWhitespace();

	/** Returns true if end-of-file have been reached. */
	bool eof() const;

	/** Returns error code or 0 (ERROR_NONE) if no error. */
	ErrorType	error() const;

	/** Returns line number of last successful read character. */
	int line() const;

private:
	class TextFileImpl;
	TextFileImpl* m_this;

	TextFile(const TextFile &);
	TextFile & operator=(const TextFile &);
};

#endif
