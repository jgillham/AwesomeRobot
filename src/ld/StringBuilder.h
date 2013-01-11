#ifndef STRING_BUILDER_CLASS_INCLUDED
#define STRING_BUILDER_CLASS_INCLUDED

// The initial allocation size.
#define STRING_BUILDER_BASE_SIZE 50
// Convert an Index type to a Count.
#define INDEX_TO_COUNT( INDEX ) ( INDEX + 1 )
// Force a method to throw no exceptions.
#define NO_EXCEPTIONS throw()
// Methods which can be accessed when the class is constant.
#define CONSTANT_METHOD const

/**
 * This class is an immitation of higher level libraries
 *  in other languages. This class avoids the heavier classes
 *  from the STL library.
 *
 * @author Josh Gillham
 * @version 12-20-12
 */
class StringBuilder {
  private:
    // Declare type aliases.
    typedef char* CString;                // A pointer to a char array.
    typedef const char* Constant_CString; // Unchangeable string.
    typedef int Count;                    // The number of items.
    typedef int Index;                    // Corresponds to an array.

    /// The pointer to the beginning of the string.
    CString tip;
    /// The amount of characters we can hold before reallocation.
    Count allocSize;
    /// The index to put the next character.
    Index newCharIndex;

    /**
     * Reallocate memory to suite the expanding size of the message.
     *
     * @param newAllocSize is the new size of the allocation.
     *
     * @return TRUE if the expansion was successful OR FALSE
     *  otherwise.
     */
    bool expand( Count newAllocSize ) NO_EXCEPTIONS;

    /**
     * Fill in characters in the allocation with NULLs.
     *
     * @param startIndex the first index.
     * @param endIndex the last index.
     */
    void clear( Index startIndex, Index endIndex ) NO_EXCEPTIONS;
  public:
    /**
     * Initializes the instance of StringBuilder.
     */
    StringBuilder() NO_EXCEPTIONS;

    /**
     * The deconstructor is called before the object is
     *  destroyed. It frees the memory allocated.
     */
    ~StringBuilder() NO_EXCEPTIONS;

    /**
     * Fills in all characters with NULLs and starts
     *  the inserting index at the beginning.
     */
    void reset() NO_EXCEPTIONS;

    /**
     * Writes when character to the end of the string.
     *
     * @param chr the character to write.
     */
    bool append( char chr ) NO_EXCEPTIONS;

    /**
     * Writes a string to the end.
     *
     * @param str the string to append.
     *
     * @return TRUE if the operation succeeds or FALSE otherwise.
     */
    bool appends( const char* str );

    /**
     * Accesses the length of the string, that is,
     *  the number characters before the NULL.
     *
     * @return the length of the string.
     */
    Count len() CONSTANT_METHOD NO_EXCEPTIONS;

    /**
     * Accesses an immutable string.
     *
     * @return a constance and unchangable string pointer.
     */
    operator Constant_CString () CONSTANT_METHOD NO_EXCEPTIONS;
};
#endif
