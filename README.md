# psdp
This is an extremely simple implementation of Session Description Protocol defined in RFC4566.


In this implementation, I don't try to implement every detail of parsing/validating/decoding SDP messages as defined in RFC3556.
Instead, I choose to adopt a simple tokening approach when parsing SDP messages. The overall SDP message is parsed, tokenized into a predefined SDP message structure as type/value pair. That's all. Detailed validation or interpretation of each field in a SDP message is left up to you.

## Implementation Details
Here is the list of details of the current implementation, mostly focusing on RFC4566 noncompliant parts.

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

* the same type that appears later override the previous 
  So
```
  s=ignored title
  s=accepted title
```
  s becomes "accepted title"

* for b=/a=, each appearance is just added to the array.
  if array overflow occurs, the value is simply ignored.

   So assuming max array size configured for b= is 3
```
  b=b1
  b=b2
  b=b3
  b=ignored
  b=ignored
```
  number of items in b= array is 3 and the last 2 are simpley ignored

* m= causes switch to media parsing mode from session parsing mode.
  This means whatever comes next, it won't affect anything in session level type values.
  If m= is valid, which means length of its value is not empty, the number of media descriptor
  is incremented. If there is an overflow, it's simply discarded

* types with zero length value are simply ignored. 


I believe this implementation is much simpler and more flexible. Also it parses valid SDPs correctly.

And as state above, all the nitty gritty semantic checks are up to you.
