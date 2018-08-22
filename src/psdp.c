#include <string.h>
#include <ctype.h>
#include "psdp.h"

/*
   RFC4566 Summary

   a) format
      <type>=<value>, no space is allowed between '='. type is case sensitive


   b) structure
      <session-level section>
      <zero or more medial-level sections>

      session-level section starts with "v=" and continues to the first media-level section.

      Each media-level section starts with an "m=" line and continues to the next media-level
      section or end of the whore session description

      Some lines are REQUIRED and some are OPTIONAL but all MUST appear in exactly the order
      given here. * is optional

      Session description
        v=  (protocol version)
        o=  (originator and session identifier)
        s=  (session name)
        i=* (session information)
        u=* (URI of description)
        e=* (email address)
        p=* (phone number)
        c=* (connection information -- not required if included in all media)
        b=* (zero or more bandwidth information lines) One or more time descriptions ("t=" and "r=" lines; see below)
        z=* (time zone adjustments)
        k=* (encryption key)
        a=* (zero or more session attribute lines)
        Zero or more media descriptions
   
      Session description
        t=  (time the session is active)
        r=* (zero or more repeat times)

      Media description, if present
        m=  (media name and transport address)
        i=* (media title)
        c=* (connection information -- optional if included at session level)
        b=* (zero or more bandwidth information lines)
        k=* (encryption key)
        a=* (zero or more media attribute lines)
    
   c) misc.
      1)an SDP parser MUST completely ignore any session description that contains a type letter that it does not understand.
      2)Text fields such as the session name and information are octet strings that may contain any octet with the
        exceptions of 0x00 (Nul), 0x0a (ASCII newline), and 0x0d (ASCII carriage return)
      3)The sequence CRLF (0x0d0a) is used to end a record, although parsers SHOULD be tolerant and also accept records
        terminated with a single newline character.
*/

/*
   My Implementation Summary.

   XXX this implementation is not gonna follow the RFC SDP parsing rules.

   a) the order doesn't matter in session-parsing level
   b) the same type that appears later overrides the previous
   c) for b=/a=, each appearace is just added to the array
   d) m= switches to media descriptor parsing mode.
      also, m= increments the number of media descriptor counter.
   e) overflown type-values are silently ignored
   f) overflow media type-values are silently ignored

   I think this implementation is much better and flexible than the parsing rule specified in RFC.
   And it will parse valid SDPs correctly.
*/

typedef enum
{
  psdp_type_v,
  psdp_type_o,
  psdp_type_s,
  psdp_type_i,
  psdp_type_u,
  psdp_type_e,
  psdp_type_p,
  psdp_type_c,
  psdp_type_b,
  psdp_type_z,
  psdp_type_k,
  psdp_type_a,
  psdp_type_t,
  psdp_type_r,
  psdp_type_m,
  psdp_unknown,
} psdp_tv_type_t;

typedef struct
{
  const char*       str_t;
  psdp_tv_type_t    t;
} psdp_known_type_t;

static const psdp_known_type_t    _known_types[] = 
{
  { "v=", psdp_type_v },
  { "o=", psdp_type_o },
  { "s=", psdp_type_s },
  { "i=", psdp_type_i },
  { "u=", psdp_type_u },
  { "e=", psdp_type_e },
  { "p=", psdp_type_p },
  { "c=", psdp_type_c },
  { "b=", psdp_type_b },
  { "z=", psdp_type_z },
  { "k=", psdp_type_k },
  { "a=", psdp_type_a },
  { "t=", psdp_type_t },
  { "r=", psdp_type_r },
  { "m=", psdp_type_m },
};

static inline uint8_t
psdp_parser_msg_left(psdp_parser_t* parser)
{
  if(parser->ndx >= parser->msg_len)
  {
    return PSDP_FALSE;
  }
  return PSDP_TRUE;
}

static inline uint8_t
psdp_parser_cmp(psdp_parser_t* parser, const char* c)
{
  uint32_t    ndx = parser->ndx;

  for(uint32_t i = 0; i < strlen(c); i++)
  {
    if(ndx >= parser->msg_len)
    {
      return PSDP_FALSE;
    }

    if(parser->msg[ndx] != (uint8_t)c[i])
    {
      return PSDP_FALSE;
    }
    ndx++;
  }
  parser->ndx = ndx;

  return PSDP_TRUE;
}

static inline void
psdp_read_line(psdp_parser_t* parser, psdp_str* line)
{
  line->val     = &parser->msg[parser->ndx];
  line->val_len = 0;

  while(parser->ndx < parser->msg_len)
  {
    if(psdp_parser_cmp(parser, "\r\n") == PSDP_TRUE)
    {
      break;
    }

    if(psdp_parser_cmp(parser, "\n") == PSDP_TRUE)
    {
      break;
    }

    line->val_len++;
    parser->ndx++;
  }
}

static psdp_tv_type_t
psdp_get_type(psdp_parser_t* parser)
{
  for(int i = 0; i < sizeof(_known_types)/sizeof(psdp_known_type_t); i++)
  {
    if(psdp_parser_cmp(parser, _known_types[i].str_t) == PSDP_TRUE)
    {
      return _known_types[i].t;
    }
  }
  return psdp_unknown;
}

static inline void
psdp_ignore_line(psdp_parser_t* parser)
{
  psdp_str    ignored;

  psdp_read_line(parser, &ignored);
}

static inline void
psdp_parse_if_session_mode_ignore_otherwise(psdp_parser_t* parser, psdp_str* s)
{
  if(parser->parsing_session)
  {
    psdp_read_line(parser, s);
  }
  else
  {
    psdp_ignore_line(parser);
  }
}

static void
psdp_parse_internal(psdp_parser_t* parser, psdp_t* psdp)
{
  switch(psdp_get_type(parser))
  {
  case psdp_type_v:
    psdp_parse_if_session_mode_ignore_otherwise(parser, &psdp->v);
    break;

  case psdp_type_o:
    psdp_parse_if_session_mode_ignore_otherwise(parser, &psdp->o);
    break;

  case psdp_type_s:
    psdp_parse_if_session_mode_ignore_otherwise(parser, &psdp->s);
    break;

  case psdp_type_i:
    if(parser->parsing_session)
    {
      psdp_read_line(parser, &psdp->i);
    }
    else
    {
      if(parser->cm != NULL)
      {
        psdp_read_line(parser, &parser->cm->i);
      }
      else
      {
        psdp_ignore_line(parser);
      }
    }
    break;

  case psdp_type_u:
    psdp_parse_if_session_mode_ignore_otherwise(parser, &psdp->u);
    break;

  case psdp_type_e:
    psdp_parse_if_session_mode_ignore_otherwise(parser, &psdp->e);
    break;

  case psdp_type_p:
    psdp_parse_if_session_mode_ignore_otherwise(parser, &psdp->p);
    break;

  case psdp_type_c:
    if(parser->parsing_session)
    {
      psdp_read_line(parser, &psdp->c);
    }
    else
    {
      if(parser->cm != NULL)
      {
        psdp_read_line(parser, &parser->cm->c);
      }
      else
      {
        psdp_ignore_line(parser);
      }
    }
    break;

  case psdp_type_b:
    if(parser->parsing_session)
    {
      if(psdp->num_b >= PSDP_MAX_BANDWIDTH_INFO)
      {
        psdp_ignore_line(parser);
      }
      else
      {
        psdp_read_line(parser, &psdp->b[psdp->num_b]);
        psdp->num_b++;
      }
    }
    else
    {
      if(parser->cm == NULL || parser->cm->num_b >= PSDP_MAX_BANDWIDTH_INFO)
      {
        psdp_ignore_line(parser);
      }
      else
      {
        psdp_read_line(parser, &parser->cm->b[parser->cm->num_b]);
        parser->cm->num_b++;
      }
    }
    break;

  case psdp_type_z:
    psdp_parse_if_session_mode_ignore_otherwise(parser, &psdp->z);
    break;

  case psdp_type_k:
    if(parser->parsing_session)
    {
      psdp_read_line(parser, &psdp->k);
    }
    else
    {
      if(parser->cm != NULL)
      {
        psdp_read_line(parser, &parser->cm->k);
      }
      else
      {
        psdp_ignore_line(parser);
      }
    }
    break;

  case psdp_type_a:
    if(parser->parsing_session)
    {
      if(psdp->num_a >= PSDP_MAX_SESSION_ATTR)
      {
        psdp_ignore_line(parser);
      }
      else
      {
        psdp_read_line(parser, &psdp->a[psdp->num_a]);
        psdp->num_a++;
      }
    }
    else
    {
      if(parser->cm == NULL || parser->cm->num_a >= PSDP_MAX_SESSION_ATTR)
      {
        psdp_ignore_line(parser);
      }
      else
      {
        psdp_read_line(parser, &parser->cm->a[parser->cm->num_a]);
        parser->cm->num_a++;
      }
    }
    break;

  case psdp_type_t:
    psdp_parse_if_session_mode_ignore_otherwise(parser, &psdp->t);
    break;

  case psdp_type_r:
    psdp_parse_if_session_mode_ignore_otherwise(parser, &psdp->r);
    break;

  case psdp_type_m:
    if(parser->parsing_session)
    {
      parser->parsing_session = PSDP_FALSE;

      if(psdp->num_m >= PSDP_MAX_MEDIA)
      {
        parser->cm = NULL;
        psdp_ignore_line(parser);
      }
      else
      {
        parser->cm = &psdp->media[psdp->num_m];
        psdp->num_m++;

        psdp_read_line(parser, &parser->cm->m);
      }
    }
    else
    {
      if(psdp->num_m >= PSDP_MAX_MEDIA)
      {
        parser->cm = NULL;
        psdp_ignore_line(parser);
      }
      else
      {
        parser->cm = &psdp->media[psdp->num_m];
        psdp->num_m++;

        psdp_read_line(parser, &parser->cm->m);
      }
    }
    break;

  case psdp_unknown:
    psdp_ignore_line(parser);
    break;
  }
}

void
psdp_parse(psdp_parser_t* parser, psdp_t* psdp, uint8_t* sdp_msg, uint32_t sdp_msg_len)
{
  // initialize parser first
  parser->ndx     = 0;
  parser->msg_len = sdp_msg_len;
  parser->msg     = sdp_msg;
  parser->cm      = NULL;

  parser->parsing_session = PSDP_TRUE;

  // initialize sdp
  memset(psdp, 0, sizeof(psdp_t));

  while(psdp_parser_msg_left(parser) == PSDP_TRUE)
  {
    psdp_parse_internal(parser, psdp);
  }
}
