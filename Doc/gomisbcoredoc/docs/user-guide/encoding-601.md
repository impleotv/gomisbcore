
# Creating KLV encoded MISB 601 packet:

## Using JSON string as a source

To use this method we create a string that represents the metadata packet and call **EncodePacket** method.  

For example, let's create a very simple MISB 601 Local set packet (sample data from MISB ST 0601.16a). JSON **key** represents a MISB **Tag** of a Local Set, whereas the **value** contains a data entry, as defined in the specification.  

```C#
string json = @"{
    2: '2008-10-24T00:13:29.913',
    3: 'MISSION01',
    13: 60.176822966978335,
    14: 128.42675904204452,
    15: 14190.7195,
    16: 144.571298,
    65: 13,
}";
```

Next, we need to create an instance of **MISB601*** and pass the string to the **EncodePacket** method.  

```C#
var misb601 = new MISB601();
var buf = misb601.EncodePacket(json);
```

The resulting buffer is a RAW Klv that comprises all mandatory parts of the packet:  
![Encoded buffer](./images/getting-started-encodedbuf.png)


* The UAS Local Set 16-Byte UL “Key”-<small><span style="background-color:PeachPuff">0x06 0x0E 0x2B 0x34 0x02 0x0B 0x01 0x01 0x0E 0x01 0x03 0x01 0x01 0x00 0x00 0x00</span></small> 
* Packet length - <span style="background-color:Plum">0x30</span> 
* Packet data payload - Klv triplets: <span style="background-color:yellow">tag</span>, <span style="background-color:Lavender">length</span> and <span style="background-color:LightGreen">value</span>
* Checksum  (last klv triplet, last 4 bytes)

This buffer can be injected into STANAG4609 multiplex.

> Note, if a mandatory **Tag 2** (time) is not found in the packet, **MisbCore** will set a current time. You can also force update time by setting *UpdateTimeToCurrentTime* property to **true**.  
 

## Using JSON object as a source  

Using JSON string as a source is not always the best choice - if you create your data programmatically, serializing it to string (and then de-serializing it in the SDK is unnecessary).  
You can directly pass the **JObject** if you're using JSON.NET library. For example:  

### Creating JSON packet instance using the C# collection initializer syntax  

```C#
JObject pckt = new JObject
{
  {"2": "2008-10-24T00:13:29.913Z",
  {"3": "MISSION01"},
  {"13": 60.176822967},
  {"14": 128.426759042},
  {"15": 14190.72},
  {"65": 13},
};
```

Then, you pass the object, instead of string:

```C#
var misb601 = new MISB601();
var buf = misb601.EncodePacket(pckt);
```

### Other JSON.NET object creation methods

You can use any other method defined in JSON.NET to create the **JObject**
Here, for example, declaratively using LINQ:  

```C#
JObject pckt = new JObject(
  new JProperty("2", "2008-10-24T00:13:29.913Z"),
  new JProperty("3", "MISSION01"),
  new JProperty("65", 13)
);
```

or simply add the tag:value pairs, one by one:  

```C#
var pckt601 = new JObject();
pckt601.Add(MISB_601_TAGS_STR.UNIX_Time_Stamp, DateTime.Parse("2008-10-24T00:13:29.913Z"));
pckt601.Add(MISB_601_TAGS_STR.Mission_ID, "MISSION01");
pckt601.Add(MISB_601_TAGS_STR.Platform_Tail_Number, "AF-101");
pckt601.Add(MISB_601_TAGS_STR.UAS_LDS_Version_Number, 16);

var buf = misb601.EncodePacket(pckt601);
```

### Sorting

**MisbCore** encoder can sort the elements of a klv items sequence in ascending order, according to a tag.  
Set **OrderByTags** property to **true** to achieve this.  Default value - **false**.  

```cs
MISB601 misb601 = new MISB601();
misb601.OrderByTags = true;
```

### Raw Klv  

**MisbCore SDK** provides an option for encoding of the **RAW klv** items (tag/value buffer). This can be especially useful for data manipulation where you need the original klvs.  
There are some additional benefits of using RAW Klv for data manipulation:  

* No "generation loss" when you have to re-encode compressed values, without changing them
* Lower CPU usage, as no MISB decoding / Encoding is performed  

**RAW klv** is presented as an array of klv items.

```cs
/// <summary>
/// KlvItem - Raw Klv item
/// </summary>
public class KlvItem
{
    public ushort Tag { get; set; }  
    public byte[] Value { get; set; }

    public KlvItem(ushort tag, byte [] value)
    {
        this.Tag = tag;
        this.Value = value;
    }
}
```

Here is a sample code for **RAW Klv** re-encoding  

```cs  
// Create instance
MISB601 misb601 = new MISB601();
if (!misb601.Activate(licenseFilePath, licenseKey))
    Console.WriteLine("Demo version. Only tags < 15 and tag 65 will be processed");

string json = @"{
    2: '2008-10-24T00:13:29.913',
    3: 'MISSION1',
    13: 60.176822966978335,
    14: 128.42675904204452,
    15: 14190.7195,
    16: 144.571298,
    65: 13,
}";
            
// Encode packet
var buf = misb601.EncodePacket(json);  

// Now, instead of fully decoding the buffer, let's get KLVs only. 

// Decode RAW klvs
var decodedRawKlv = misb601.DecodePacketRawKlv(buf);

// Let's replace some values, without affecting the rest.

var missionItem = decodedRawKlv.Find(item => item.Tag == 3);
if (missionItem != null)
    missionItem.Value = Encoding.UTF8.GetBytes("MISSION2");

var versionItem = decodedRawKlv.Find(item => item.Tag == 65);
if (versionItem != null)
    versionItem.Value = new byte[1] { 14 };

// Re-encode the packet
var bufReencode = misb601.EncodePacketRawKlv(decodedRawKlv);

// Decode it back to json
var decodedPckt = misb601.DecodePacket(bufReencode);    
```

### Timestamps

**MisbCore SDK** accepts strings or DateTime objects as timestamps. If spec defines microseconds, you can pass an integer (uint64) as well.

### Data range

**MisbCore SDK** checks the values to verify that they are within the allowed range. Values that are not in the range will not be accepted.

## Supported tags
[Supported MISB 601 tags](./st601-supported.md)  
