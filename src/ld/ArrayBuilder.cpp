#include "StringBuilder.h"
// Include arduino libraries.
#include <WProgram.h>

/// Just an integer.
#define Count StringBuilder::Count
/// Just an integer.
#define Index StringBuilder::Index

/**
 * Reallocate memory to suite the expanding size of the message.
 *
 * @param newAllocSize is the new size of the allocation.
 *
 * @return TRUE if the expansion was successful OR FALSE
 *  otherwise.
 */
bool StringBuilder::expand( Count newAllocSize ) NO_EXCEPTIONS {
    CString newTip = (CString)realloc( tip, newAllocSize + 1);
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
void StringBuilder::clear( Index startIndex, Index endIndex ) NO_EXCEPTIONS {
    for( Index i = startIndex; i <= endIndex; ++i ) {
        tip[ i ] = NULL;
    }
}

/**
 * Initializes the instance of StringBuilder.
 */
StringBuilder::StringBuilder() NO_EXCEPTIONS:
      allocSize( 0 ), tip( 0 ), newCharIndex( 0 ) {
    this->expand( STRING_BUILDER_BASE_SIZE );
}

/**
 * The deconstructor is called before the object is
 *  destroyed. It frees the memory allocated.
 */
StringBuilder::~StringBuilder() NO_EXCEPTIONS {
    free( tip );
}

/**
 * Fills in all characters with NULLs and starts
 *  the inserting index at the beginning.
 */
void StringBuilder::reset() NO_EXCEPTIONS {
    this->clear( 0, newCharIndex - 1 );
    newCharIndex = 0;
}

/**
 * Writes when character to the end of the string.
 *
 * @param chr the character to write.
 */
bool StringBuilder::append( char chr ) NO_EXCEPTIONS {
    if ( newCharIndex >= allocSize )
    //XXX The case of expand() return false should be handled better.
      if ( !this->expand( allocSize + STRING_BUILDER_BASE_SIZE ) )
        return false;

    tip[ newCharIndex++ ] = chr;
    return true;
}

/**
 * Writes a string to the end.
 *
 * @param str the string to append.
 *
 * @return TRUE if the operation succeeds or FALSE otherwise.
 */
bool StringBuilder::appends( const char* str ) {
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
Count StringBuilder::len() CONSTANT_METHOD NO_EXCEPTIONS  {
    return INDEX_TO_COUNT( newCharIndex );
}

/**
 * Accesses an immutable string.
 *
 * @return a constance and unchangable string pointer.
 */
StringBuilder::operator Constant_CString () CONSTANT_METHOD NO_EXCEPTIONS {
      // Make the characters in the string unchangeable.
    return const_cast< Constant_CString >( tip );
}
