/* c_tokenizer.c */

#include <stdlib.h>
#include <string.h>

#include "tokenzer.h"

#ifndef strdup
#define strdup sdup
static char* sdup( const char* s )
{
  size_t n = strlen( s ) + 1;
  char*  p = malloc( n );
  return p ? memcpy( p, s, n ) : NULL;
}
#endif

tokenizer_t tokenizer( const char* s, const char* delimiters, int empties )
{
  char* strdup( const char* );

  tokenizer_t result;

  result.s                 = (s && delimiters) ? strdup( s ) : NULL;
  result.delimiters        = delimiters;
  result.current           = NULL;
  result.next              = result.s;
  result.is_ignore_empties = (empties != TOKENIZER_EMPTIES_OK);

  return result;
}

const char* free_tokenizer( tokenizer_t* tokenizer )
{
  free( tokenizer->s );
  return tokenizer->s = NULL;
}

const char* tokenize( tokenizer_t* tokenizer )
{
  if (!tokenizer->s) return NULL;

  if (!tokenizer->next)
    return free_tokenizer( tokenizer );

  tokenizer->current = tokenizer->next;
  tokenizer->next = strpbrk( tokenizer->current, tokenizer->delimiters );

  if (tokenizer->next)
  {
    *tokenizer->next = '\0';
    tokenizer->next += 1;

    if (tokenizer->is_ignore_empties)
    {
      tokenizer->next += strspn( tokenizer->next, tokenizer->delimiters );
      if (!(*tokenizer->current))
        return tokenize( tokenizer );
    }
  }
  else if (tokenizer->is_ignore_empties && !(*tokenizer->current))
    return free_tokenizer( tokenizer );

  return tokenizer->current;
}
