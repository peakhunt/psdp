# psdp
This is an extremely simple implementation of Session Description Protocol defined in RFC4566.


In this implementation, I don't try to implement every detail of parsing/validating/decoding SDP messages as defined in RFC3556.
Instead, I choose to adopt a simple tokening approach when parsing SDP messages. The overall SDP message is parsed, tokenized into a predefined SDP message structure as type/value pair. That's all. Detailed validation or interpretation of each field in a SDP message is left up to you.

## Implementation Details
Here is the list of details of my implementation.

* the order doesn't matter in session level.
  RFC4566 spcifies that type/value pairs should be listed in the order specified in the spec.
  This implementation doesn't.

  So
```
  v=0
  s=title
```

  is same as

```
  s=title
  v=0
```

* 
