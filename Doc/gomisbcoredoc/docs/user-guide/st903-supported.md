# Supported MISB 903 (VMTI) tags

| Tag       |    Description                                        | Note |
|-----------|:------------------------------------------------------|------|
|    1      |    Checksum                                           |      |        
|    2      |    Precision Time Stamp                               |      |  
|    3    	|    VMTI System Name / Description                     |      | 
|    4    	|    VMTI LS Version Number                             |      | 
|    5  	|    Total Number of Targets Detected in the Frame      |      | 
|    6    	|    Number of Reported Targets                         |      | 
|    7   	|    Motion Imagery Frame Number                        |      | 
|    8    	|    Frame Width                                        |      | 
|    9    	|    Frame Height                                       |      | 
|    10    	|    VMTI Source Sensor                                 |      | 
|    11    	|    VMTI Sensor Horizontal Field of View               |      | 
|    12    	|    VMTI Sensor Vertical Field of View                 |      | 
|    13     |    Motion Imagery ID                                  |      | 
|    101    |    **VTargetSeries**                                  |      |
|  101 / 1  |      Target Centroid Pixel Number                     |      | 
|  101 / 2  |      Bounding Box Top Left Pixel Number               |      | 
|  101 / 3  |      Bounding Box Bottom Right Pixel Number           |      | 
|  101 / 4  |      Target Priority                                  |      | 
|  101 / 5 	|      Target Confidence Level                          |      | 
|  101 / 6 	|      New Detection Flag / Target History              |      | 
|  101 / 7 	|      Percentage of target Pixels                      |      | 
|  101 / 8 	|      Target Color                                     |      | 
|  101 / 9 	|      Target Intensity                                 |      | 
|  101 / 10	|      Target Location Latitude Offset                  |      | 
|  101 / 11	|      Target Location Longitude Offset                 |      |
|  101 / 12	|      Target Height                                    |      | 
|  101 / 13 |      Bounding Box Top Left Latitude Offset            |      | 
|  101 / 14	|      Bounding Box Top Left Longitude Offset           |      | 
|  101 / 15	|      Bounding Box Bottom Right Latitude Offset        |      |
|  101 / 16	|      Bounding Box Bottom Right Longitude Offset       |      | 
|  101 / 17 |      Target Location                                  |      | 
|  101 / 18	|      Target Boundary                                  |      | 
|  101 / 19	|      Target Centroid Pixel Row                        |      |
|  101 / 20	|      Target Centroid Pixel Column                     |      | 
|  101 / 21 |      FPA Index                                        |      | 
|  101 / 102|      **VObject LS**                                   |      | 
|  101 / 102 / 1 |    Ontology                                      |      | 
|  101 / 102 / 2 |    Ontology Class                                |      | 
|  101 / 104|      **VTracker LS**                                  |      | 
|  101 / 104 / 1 |    Track ID                                      |      | 
|  101 / 104 / 2 |    Detection Status                              |      | 
|  101 / 104 / 3 |    Start Time Stamp                              |      | 
|  101 / 104 / 4 |    End Time Stamp                                |      | 
|  101 / 104 / 5 |    Algorithm                                     |      | 
|  101 / 104 / 6 |    New Detection Flag / Target History           |      | 
|  101 / 104 / 7 |    Confidence                                    |      | 
|  101 / 104 / 8 |    Number of Track Points                        |      | 
|  101 / 104 / 9 |    Locus                                         |      | 
|  101 / 104 / 10|    Velocity                                      |      | 
|  101 / 104 / 11|   Acceleration                                   |      | 
|  101 / 104 / 8 |   Number of Track Points                         |      | 
|  101 / 105 |      **VChip LS**                                    |      | 
|  101 / 105 / 1 |    Image Type                                    |      | 
|  101 / 105 / 2 |    Image URI                                     |      | 
|  101 / 105 / 3 |    Embedded Image                                |      |
|  101 / 106     |  **VChipSeries**                                 |      |  
|  101 / 107     |  **vObjectSeries**                               |      |
|  101 / 107 / 3 |    ontologyId                                    |      |
|  101 / 107 / 4 |    confidence                                    |      |
|    102    |    **AlgorithmSeries**                                |      |
|    103    |    **OntologySeries**                                 |      |






