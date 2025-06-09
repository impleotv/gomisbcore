# Using MisbCoreNative with Nodejs

To use **MisbCoreNative** library with **Nodejs** you can write an **add on** or use npm library like **ffi-napi**.

## Using MisbCoreNative with ffi-napi

Note, you have to add **ffi-napi** package


Here is a code that prints a nodeinfo string, reads a raw binary buffer and decodes it to JSON:

```js
import ffi from 'ffi-napi';
import fs from 'fs';

const binaryBuf = fs.readFileSync('./packet.bin');

const libmCore = ffi.Library('./MisbCoreNativeLib.dll', {
  'GetNodeInfo': [ 'string', [ ] ],
  'Decode': ['string', ['pointer', 'int']],
});

console.log(libmCore.GetNodeInfo());

const jsonPckt = libmCore.Decode(binaryBuf, binaryBuf.length);
console.log(jsonPckt);

```


