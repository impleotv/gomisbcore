# Supported MISB 601 tags

| Tag       |    Description                                        | Note |
|-----------|:------------------------------------------------------|------|
|    1      |    Checksum                                           |      |        
|    2      |    Precision Time Stamp                               |      |  
|    3    	|     Mission ID                                        |      | 
|    4    	|     Platform Tail Number                              |      | 
|    10    	|    Platform Designation                               |      | 
|    11    	|    Image Source Sensor                                |      | 
|    12    	|    Image Coordinate System                            |      | 
|    5    	|     Platform Heading Angle                            |      | 
|    6    	|     Platform Pitch Angle                              |      | 
|    7    	|     Platform Roll Angle                               |      | 
|    8    	|     Platform True Airspeed                            |      | 
|    9    	|     Platform Indicated Airspeed                       |      | 
|    13     |     Sensor Latitude                                   |      | 
|    14     |     Sensor Longitude                                  |      | 
|    15    	|     Sensor True Altitude                              |      | 
|    16    	|     Sensor Horizontal Field of View                   |      | 
|    17    	|     Sensor Vertical Field of View                     |      | 
|    18    	|     Sensor Relative Azimuth Angle                     |      | 
|    19    	|     Sensor Relative Elevation Angle                   |      | 
|    20    	|     Sensor Relative Roll Angle                        |      | 
|    21    	|     Slant Range                                       |      | 
|    22    	|     Target Width                                      |      | 
|    23    	|     Frame Center Latitude                             |      | 
|    24    	|     Frame Center Longitude                            |      | 
|    25    	|     Frame Center Elevation                            |      |
|    26    	|     Offset Corner Latitude Point 1                    |      | 
|    28    	|     Offset Corner Latitude Point 2                    |      | 
|    30    	|     Offset Corner Latitude Point 3                    |      | 
|    32    	|     Offset Corner Latitude Point 4                    |      |
|    27    	|     Offset Corner Longitude Point 1                   |      | 
|    29    	|     Offset Corner Longitude Point 2                   |      |
|    31    	|     Offset Corner Longitude Point 3                   |      |
|    33    	|     Offset Corner Longitude Point 4                   |      |    
|    34    	|      Icing Detected                                   |      |
|    35    	|    Wind Direction                                     |      |       
|    36    	|    Wind Speed                                         |      |
|    37    	|    Static Pressure                                    |      |
|    38    	|    Density Altitude                                   |      |
|    39    	|    Outside Air Temperature                            |      |
|    40    	|    Target Location Latitude                           |      |
|    41    	|    Target Location Longitude                          |      |
|    42    	|    Target Location Elevation                          |      |
|    43    	|    Target Track Gate Width                            |      |
|    44    	|    Target Track Gate Height                           |      |
|    45    	|    Target Error Estimate - CE90                       |      |
|    46    	|    Target Error Estimate - LE90                       |      |
|    47    	|    Generic Flag Data                                  |      |
|    48    	|    [Security Local Metadata Set](./st102-supported.md)                        |      |
|    49    	|    Differential Pressure                              |      |
|    50     |    Platform Angle of Attack                           |      |
|    51    	|    Platform Vertical Speed                            |      |
|    52    	|    Platform Sideslip Angle                            |      |
|    53    	|    Airfield Barometric Pressure                       |      |
|    54    	|    Airfield Elevation                                 |      |
|    55    	|    Relative Humidity                                  |      |
|    56    	|    Platform Ground Speed                              |      |
|    57    	|    Ground Range                                       |      |
|    58    	|    Platform Fuel Remaining                            |      |
|    59    	|    Platform Call Sign                                 |      |
|    60    	|    Weapon Load                                        |      |
|    61    	|    Weapon Fired                                       |      |
|    62    	|    Laser PRF Code                                     |      |
|    63    	|    Sensor Field of View Name                          |      |
|    64    	|    Platform Magnetic Heading                          |      |
|    65    	|    UAS Datalink LS Version Number                     |      |
|    67    	|    Alternate Platform Latitude                        |      |
|    68    	|    Alternate Platform Longitude                       |      |
|    69    	|    Alternate Platform Altitude                        |      |
|    70    	|    Alternate Platform Name                            |      |
|    71    	|    Alternate Platform Heading                         |      |
|    72    	|     Event Start Time - UTC                            |      |
|    [73](./st806-supported.md)    	|    [RVT Local Data Set](./st806-supported.md)         |      |
|    [74](./st903-supported.md)    	|    [VMTI Local Data Set](./st903-supported.md)        | Partial support    | 
|    75    	|    Sensor Ellipsoid Height                            |                    |          
|    76    	|    Alternate Platform Ellipsoid Height                |      |
|    77    	|    Operational Mode                                   |      |
|    78    	|    Frame Center Height Above Ellipsoid                |      |
|    79    	|    Sensor North Velocity                              |      |             
|    80    	|    Sensor East Velocity                               |      |
|    81    	|    Image Horizon Pixel Pack                           |      |
|    82    	|    Corner Latitude Point 1                            |      |
|    84    	|    Corner Latitude Point 2                            |      |
|    86    	|    Corner Latitude Point 3                            |      |
|    88    	|    Corner Latitude Point 4                            |      |
|    83    	|    Corner Longitude Point 1                           |      |
|    85    	|    Corner Longitude Point 2                           |      |
|    87    	|    Corner Longitude Point 3                           |      |
|    89    	|    Corner Longitude Point 4                           |      |
|    90    	|    Platform Pitch Angle(Full)                         |      |
|    91    	|    Platform Roll Angle(Full)                          |      |
|    92    	|    Platform Angle of Attack(Full)                     |      |
|    93    	|    Platform Sideslip Angle(Full)                      |      |
|    [94](./st1204-supported.md)    	|    [MIIS Core Identifier](./st1204-supported.md)                               |      |
|    96    	|    Target Width Extended                              |      |
|    [98](./st1601-supported.md)    	|    [Geo-Registration Local Set](./st1601-supported.md)                         |  Partial support    | 
|    100   	|    **Segment Local Set**                                  |      |
|    101   	|    **Amend LS**                                           |      |
|    103   	|    Density Altitude Extended                          |      |
|    104    |    Sensor Ellipsoid Height Extended                   |      |                                                 
|    105   	|    Alternate Platform Ellipsoid Height Extended       |      |
|    106    |    Stream Designator                                  |      |
|    107    |    Operational Base                                   |      |
|    108    |    Broadcast Source                                   |      |
|    109    |    Range To Recovery Location                         |      |
|    110    |    Time Airborne                                      |      |
|    111    |    Propulsion Unit Speed                              |      |
|    112    |    Platform Course Angle                              |      |
|    113    |    Altitude AGL                                       |      |
|    114    |    Radar Altimeter                                    |      |
|    115    |    Control Command                                    |      |
|    116    |    Control Command Verification List                  |      |
|    117    |    Sensor Azimuth Rate                                |      |
|    118    |    Sensor Elevation Rate                              |      |
|    119    |    Sensor Roll Rate                                   |      |
|    120    |    On-board MI Storage Percent Full                   |      |
|    121    |    Active Wavelength List                             |      |
|    122    |    Country Codes                                      |      |
|    123    |    Number of NAVSATs in View                          |      |
|    124    |    Positioning Method Source                          |      |
|    125    |    Platform Status                                    |      |
|    126    |    Sensor Control Mode                                |      |
|    127    |    Sensor Frame Rate Pack                             |      |
|    128    |    Wavelengths List                                   |      |
|    129    |    Target ID                                          |      |
|    130    |    Airbase Locations                                  |      |
|    131    |    Take-off Time                                      |      |
|    132    |    Transmission Frequency                             |      |
|    133    |    On-board MI Storage Capacity                       |      |
|    134    |    Zoom Percentage                                    |      |
|    135    |    Communications Method                              |      |
|    136    |    Leap Seconds                                       |      |
|    137    |    Correction Offset                                  |      |
|    138    |    Payload List                                       |      |
|    139    |    Active Payloads                                    |      |
|    140    |    Weapons Stores                                     |      |

 