# Introduction to Plugin Development

Plugins allow you to extend the functionality of **User Defined Data** encoder and decoder without touching MisbCore SDK or encoding / decoding applications that use them.


## Plugins location

**MisbCore** looks for plugins in a **./plugins** sub-directory, so installation simply involves copying the plugin binaries into this directory.


## Rvt User Defined data plugin

**Rvt User Defined data plugin** allows proprietary data encoding, decoding and presentation within a **MISB 601** and **MISB 806** standards. Once your proprietary data is inserted into STANAG 4609 stream, users that have the plugin installed will seamlessly have the user defined data decoded and presented as **json** (or Detailed json, with field description). Users that do not have the plugin will only see a binary buffer.

### Plugin interface

Every plugin for RvtUserDefinedData must implement **IRvtUserDefinedData** interface

```cs
public interface IRvtUserDefinedData
{
    /// <summary>
    /// Supported data type ids
    /// </summary>
    string[] DataTypes { get; }

    /// <summary>
    /// Brief plugin description
    /// </summary>
    string Description { get; }

    /// <summary>
    /// Decode Item buffer with user defined data
    /// </summary>
    /// <param name="id">string</param>  data type id
    /// <param name="tag">ushort</param> item tag
    /// <param name="buf">byte[]</param> item buffer
    /// <returns>JProperty</returns>
    JProperty DecodeItemBuffer(string id, ushort tag, byte[] buf);

    /// <summary>
    /// Encode packet with user defined data. 
    /// This method receives a json packet and returns a list of encoded values 
    /// </summary>
    /// <param name="pckt">JToken</param>
    /// <returns>List<Tuple<ushort, byte[]>></returns>
    List<Tuple<ushort, byte[]>> EncodeBuffer(JToken pckt);

    /// <summary>
    /// Convert json packet (compact to detailed)
    /// </summary>
    /// <param name="pckt">JObject</param>
    /// <returns>JObject</returns>
    JObject ToDetailed(JObject pckt);
}
```

### Demo plugin

Plugin development is fairly straightforward - the code must implement the IRvtUserDefinedData interface. MISB 806 includes a demo project called **RvtUserDefinedDataPluginDemo** that illustrates this.

The demo shows some basic implementations for simple data types, such as bytes, integers, and strings. It also includes other values (such as latitude, longitude, and altitude) that require mapping based on a specified range, similar to the MISB0601 implementation.
