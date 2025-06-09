# Licensing  

To use **MisbCore SDK** in production, you have to obtain a runtime license.  
Please contact ImpleoTV sales to get a license. A license file (along with the activation key) is delivered via email attachment from the ImpleoTV Administration Center.  

## Demo restrictions

**MisbCore SDK** Demo version is limited to lower (<15) tags of MISB0601 standard.

## Activation

In order to lift demo restrictions, call **Activate** method, providing the license and the key.  

```C#
var misb601 = new MISB601();
misb601.Activate( @"MyMisbCore.lic", "B1ED44DE-154F6591-525FDBB8-60569BB8");  
```

Another option, in case you prefer to store your license as string / resource:  

```C#
var misb601 = new MISB601();
misb601.ActivateLicString( licenseStr, "B1ED44DE-154F6591-525FDBB8-60569BB8");  
```

You can also set the environmental variables:

```
MISBCORE_LICENSE_FILE=/home/myuser/licenses/misbCore/MisbCore-Decode.lic
MISBCORE_LICENSE_KEY=0C203E11-847A7BF1-00B8B052-0B9F9848
```
If these environmental variables are found during the MisbCore instance creation, the library will automatically call **Activate** method (using these env variables). In that case you may skip the **Activate** call.  
If you want to use a different license, the **Activate** call will override the info from the environmental variables.


### Getting Node Info

The SDK is provided as a node-locked SW, so you must submit some HW-specific info about your target machine. There are a few ways to do this:

- Obtain Node Info using demo application  
- Call **GetNodeInfo{}** method

```C#
var misb601 = new MISB601();
var nodeInfo = misb601.GetNodeInfo();
```  
