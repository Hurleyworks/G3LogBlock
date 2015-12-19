# G3LogBlock
Cinder Block for Kjell Hedström's g3log

https://github.com/KjellKod/g3log

In your own projects just include the g3logger.h and the amalagated g3logger.cpp. Don't include the g3log folder since all the .cpp files within are already included in g3logger.cpp. 

You need to link to the DbgHelp.lib on Windows

In order to compile the samples you need  to have downloaded and built the Cinder Framework
The samples require Microsoft Visual Studio 2013 or 2015

https://github.com/cinder/Cinder

For the samples to work out of the box, you need to clone this reposity so that it is at the same directory level as Cinder.

some root folder/

	Cinder
	
		include
		
		lib
		
		etc
		
	G3LogBlock		
		samples
		
			HelloG3
			
		

	