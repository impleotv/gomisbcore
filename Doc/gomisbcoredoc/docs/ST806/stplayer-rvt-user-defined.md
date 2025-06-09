Plugins allow you to extend the functionality of **StPlayer** without any modification to the application.  

**StPlayer**> will look for existing plugins (and try to enumerate and load them) in the C:\Program Files\ImpleoTV\StPlayer\Bin\x64\plugins directory (if installed with defaults).

So, installing new plugins is basically copying the plugins dlls into this folder.

You can see installed plugins in the Options->Plugins

![Plugins](./Plugins.png)


# Using RvtUserDefinedData plugin

Each plugin implements its specific functionality.  
For example, if user doesn't have **RvtUserDefinedData** plugin installed, **StPlayer** will show User defined RVT data as a data buffer.

![Compact form](./RvtWithoutPlugin.png)

Once the **RvtUserDefinedData** plugin is copied into plugins directory, the player will be able to decode and present the data:

Compact form: 

![Compact form](./stplayer-rvt-user-defined.png)

Detailed form: 

![Detailed form](./stplayer-rvt-user-defined-detailed.png)

