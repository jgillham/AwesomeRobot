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
template< class T >
class ArrayBuilder {
  private:
    // Declare type aliases.
    typedef T* TPointer;
    //typedef char* TArray;                // A pointer to a char array.
    typedef const TPointer Constant_TPointer; // Unchangeable string.
    typedef int Count;                    // The number of items.
    typedef int Index;                    // Corresponds to an array.

    /// The pointer to the beginning of the string.
    TPointer tip;
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
    bool expand( Count newAllocSize ) NO_EXCEPTIONS {
        int byteSize = sizeof( T ) * ( newAllocSize + 1);
        TPointer newTip = (TPointer)realloc( tip, byteSize );
        if( newTip == 0 )
            return false;
        tip = newTip;
          // Initialize all characters to null.
        clear( allocSize, newAllocSize );
        allocSize = newAllocSize;
        return true;
    }

    /**
     * Fill in characters in the allocation with NULLs.
     *
     * @param startIndex the first index.
     * @param endIndex the last index.
     */
    void clear( Index startIndex, Index endIndex ) NO_EXCEPTIONS {
        for( Index i = startIndex; i <= endIndex; ++i ) {
            tip[ i ] = (T)0;
        }
    }

  public:
    /**
     * Initializes the instance of StringBuilder.
     */
    ArrayBuilder() NO_EXCEPTIONS:
          allocSize( 0 ), tip( 0 ), newCharIndex( 0 ) {
        // What to do if expand returns false?
        this->expand( STRING_BUILDER_BASE_SIZE );
    }

    /**
     * The deconstructor is called before the object is
     *  destroyed. It frees the memory allocated.
     */
    ~ArrayBuilder() NO_EXCEPTIONS {
        free( tip );
    }

    /**
     * Fills in all characters with NULLs and starts
     *  the inserting index at the beginning.
     */
    void reset() NO_EXCEPTIONS {
        this->clear( 0, newCharIndex - 1 );
        newCharIndex = 0;
    }

    /**
     * Writes when character to the end of the string.
     *
     * @param element the character to write.
     */
    bool append( T element ) NO_EXCEPTIONS {
        if ( newCharIndex >= allocSize )
        //XXX The case of expand() return false should be handled better.
          if ( !this->expand( allocSize + STRING_BUILDER_BASE_SIZE ) )
            return false;

        tip[ newCharIndex++ ] = element;
        return true;
    }

    /**
     * Writes a string to the end.
     *
     * @param str the string to append.
     *
     * @return TRUE if the operation succeeds or FALSE otherwise.
     */
    bool appends( Constant_TPointer str ) {
      int len = strlen( str );
      // Count the null also.
      if ( newCharIndex + len >= allocSize ) {
        //XXX The case of expand() return false should be handled better.
        if ( !this->expand( allocSize + STRING_BUILDER_BASE_SIZE ) )
          return false;
      }

      char* end = tip + newCharIndex;
      strcpy( end, str );
      // Wind to the end.
      while( newCharIndex != 0 ) {
        ++newCharIndex;
      }
    }

    /**
     * Accesses the length of the string, that is,
     *  the number characters before the NULL.
     *
     * @return the length of the string.
     */
    Count len() CONSTANT_METHOD NO_EXCEPTIONS  {
        return INDEX_TO_COUNT( newCharIndex );
    }

    /**
     * Accesses an immutable string.
     *
     * @return a constance and unchangable string pointer.
     */
    operator Constant_TPointer () CONSTANT_METHOD NO_EXCEPTIONS {
          // Make the characters in the string unchangeable.
        return const_cast< Constant_TPointer >( tip );
    }
};
#endif
