# Getting started

The **MisbCore SDK** makes extensive use of JSON concepts and syntax to manage the nested hierarchy of **MISB standards**. Each JSON key represents a MISB **tag** within a Local Set, while the corresponding **value** contains the decoded MISB data.

## Easy to Use...

Creating MISB-compatible metadata using the SDK is straightforward - simply create a JSON object or string representing your metadata packet (using your preferred method) and call the **EncodePacket** method.  
To decode KLV-encoded data, such as STANAG 4609, pass the data buffer to the SDK’s **DecodePacket** method. It will return a JSON-formatted object with MISB 0601 entries at the root level and nested sub-standards as child elements.  

> Make sure you've added the dependency references (either directly from the setup or as a **nuget** package).

For example, let's create a very simple MISB 601 Local set packet (sample data from MISB ST 0601.16a).  

```json
string json = @"{
    2: '2008-10-24T00:13:29.913',
    3: 'MISSION01',
    13: 60.176822966978335,
    14: 128.42675904204452,
    15: 14190.7195,
    16: 144.571298,
    65: 13
}";
```  

Next, we will create an instance of **MISB601*** and pass the string to the **EncodePacket** method.  


```C#
var misb601 = new MISB601();
var buf = misb601.EncodePacket(json);
```

The resulting buffer is a RAW Klv that comprises all the mandatory parts of the packet:  
![Encoded buffer](./images/getting-started-encodedbuf.png)  

* The UAS Local Set 16-Byte UL “Key”-<small><span style="background-color:PeachPuff">0x06 0x0E 0x2B 0x34 0x02 0x0B 0x01 0x01 0x0E 0x01 0x03 0x01 0x01 0x00 0x00 0x00</span></small> 
* Packet length - <span style="background-color:Plum">0x30</span> 
* Packet data payload - Klv triplets: <span style="background-color:yellow">tag</span>, <span style="background-color:Lavender">length</span> and <span style="background-color:LightGreen">value</span>
* Checksum  (last klv triplet, last 4 bytes)


This buffer can be injected into STANAG4609 multiplex: 



If we would need to decode the data:  

```C#
var misb601 = new MISB601();
var json = misb601.DecodePacket(buf);
```

Here is the result:  

```js
{
  "2": "2008-10-24T00:13:29.913Z",
  "3": "MISSION01",
  "13": 60.176822967,
  "14": 128.426759042,
  "15": 14190.72,
  "16": 144.5713,
  "65": 13,
  "1": 53482
}
```

We can work not only with json strings, but for example with **JObject** (Json.NET library), which performs all the data manipulation, or create the packet manually, adding **key**:**value** pairs...

Here is more on this:  

* [Encoding MISB 601 packet](./encoding-601.md)  
* [Decoding MISB 601 packet](./encoding-601.md)  

## Nested data

To allow re-use of metadata items in the UAS Datalink LS, other Local Sets may nest within the UAS Datalink LS.  
**MisbCore SDK** treats the nested data as JSON child items and data arrays as JSON arrays:  
For example, the mandatory Security Metadata set can be easily presented as a JSON object with **48** Key:  

```C#
string json = @"{
    2: '2008-10-24T00:13:29.913',
    3: 'MISSION01',
    48: {
        1: 'UNCLASSIFIED//',
        2: 'ISO_3166_ThreeLetter',
        3: '//IL',
        4: 'Impleo test flight',
        22: 9  
    },
    65: 13
}";
```

Or

```C#
string json = @"{
    2: '2008-10-24T00:13:29.913',
    3: 'MISSION01',
    48: {
        1: 1,
        2: 2,
        3: '//IL',
        4: 'Impleo test flight',
        22: 9  
   },
    65: 13
}";
```

## Multiple items

Though most items within UAS Datalink LS shall be included only once, there are some exceptions.  
Tags 100, 101, 102, 115 noted as *Multiples Allowed*. As json cannot have multiple keys (tags), which are the same, **MisbCore SDK** uses json arrays to address this.  
For example:  

```C#
string json = @"{
    2: '2008-10-24T00:13:29.913',
    3: 'MISSION01',
   	100: [
            {
                13: 60.176822966978335,
                14: 128.42675904204452,
                15: 14190.7195,
            },
            {
                13: 60.176828966,
                14: 128.42678904,
                15: 14192.3,
            }
    ],
    65: 13
}";
```

> Note. If only one instance is present in the Local Set, it can be presented as a JSON object and not an object in the array.  

## Complex types

While most of the data can be represented by **numbers** (byte, integer, float), **strings** or arrays of **numbers** / **strings** , some tags require a bit more complex structures.  
Here are the exceptions:  

- Tag 94. MIIS Core Identifier  

```json
 "94": {
    "Version": 1,
    "SensorID": {
      "Quality": "Physical",
      "UUID": "F592-F023-7336-4AF8-AA91-62C0-0F2E-B2DA"
    },
    "PlatformID": {
      "Quality": "Virtual",
      "UUID": "16B7-4341-0008-41A0-BE36-5B5A-B96A-3645"
    }
  }
```

- Tag 115. Control Command  

```json
   "115": [ 5, "Fly to Waypoint 1", "2008-10-24T00:13:29.913" ]  
```
> Note. The last element (Time) is optional.  

Tag 115 may also contain an array of commands:  
```json
  "115": [
   [ 5, "Fly to Waypoint 1", "2022-04-24T00:13:29.913" ],  
   [ 6, "Fly to Waypoint 2" ],  
  ]
```

Tag 122 Country Codes  
```json
  "122": {
    "CodingMethod": 14,
    "OverflightCountry": "CAN",
    "OperatorCountry": "",
    "CountryOfManufacture": "FRA"
  }
```
 
- Tag 128. Wavelengths List  
```json
  "128": [
    [ 21, 1000, 2000, "NNIR" ]
  ],
```  

- Tag 130. Airbase Locations  

```json
  "130": {
    "TakeOff": [ 38.841859, -77.036784, 3 ],
    "Recovery": [ 38.939353, -77.459811, 95 ]
  }
``` 

- Tag 138. Payload List  
```json
 "138": {
    "PayloadCount": 3,
    "PayloadRecords": [
      [ 0, 0, "VIS Nose Camera" ],
      [ 1, 0, "ACME VIS Model 123" ],
      [ 2, 0, "ACME IR Model 456" ]
    ]
  }
``` 

- Tag 139. Active Payloads  
```json
  "139": 11 
```  
Or array of bytes (Use additional bytes when the Payload List (Item 138) has more than eight payloads. )

```json
  "139": [ 2, 11 ]
```

- Tag 140. Weapons Stores  
```json
  "140":  [
    {
      "WeaponLocation": {
        "StationID": 1,
        "HardpointID": 1,
        "CarriageID": 1,
        "StoreID": 3
      },
      "WeaponsStatus": {
        "EngagementStatus": {
          "FuzeEnabled": false,
          "LaserEnabled": false,
          "TargetEnabled": false,
          "WeaponArmed": true
        },
        "GeneralStatus": 3
      },
      "WeaponsType": "Harpoon"
    },
    {
      "WeaponLocation": {
        "StationID": 1,
        "HardpointID": 1,
        "CarriageID": 2,
        "StoreID": 2
      },
      "WeaponsStatus": {
        "EngagementStatus": {
          "FuzeEnabled": true,
          "LaserEnabled": true,
          "TargetEnabled": true,
          "WeaponArmed": true
        },
        "GeneralStatus": 4
      },
      "WeaponsType": "Hellfire"
    },
    {
      "WeaponLocation": {
        "StationID": 1,
        "HardpointID": 2,
        "CarriageID": 1,
        "StoreID": 1
      },
      "WeaponsStatus": {
        "EngagementStatus": {
          "FuzeEnabled": false,
          "LaserEnabled": false,
          "TargetEnabled": false,
          "WeaponArmed": false
        },
        "GeneralStatus": 3
      },
      "WeaponsType": "GBU-15"
    }
  ] 
```  

> Note: Sending all Weapons Records in one UAS Datalink LS is unnecessary and could contribute to bandwidth spikes.  
 Sending Weapons Records over multiple UAS Datalink LS’s, smooths out the metadata bandwidth and reduces the possibility of bandwidth spikes.  
 

## Getting help

To get help with **MisbCore SDK**, please contact us at *support@impleotv.com*.  
