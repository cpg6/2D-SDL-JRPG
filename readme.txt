Final Hexen
Christopher Guerra

This submission is the final product for Final Hexen. A 2d JRPG, that uses 
elements of final fantasy and hexen put together. I do not own or plan to distribute any sound, images 
or otherwise miss use and copyrighted property. This is purely academic for a class project. 

Controls (Overworld):

Move up: 	w or Up_Arrow
Move Down: 	s or Down_Arrow
Move Left:	a or Left_Arrow
Move Right:	d or Right_Arrow
Display Stats:	k


Controls (Combat):

Attack: 			Click the sword icon
Increase Block for 1 turn: 	Click Shield Icon


For the Delieverables:
Audio, menu, Statistics and 3 levels with a boss fight are all present for this tech demo.
Statistics screen was reworked from its origional state previously shown. Combat as well was
re-worked to resemble more of a JRPG than just a spam fest with crap timers. More effecient timers
were implemented to fix this issue. The Screen that previously wouldnt load after a small amount of time
was due to poor resource management after not realizing what SDL does in certain cases vs. regular coding.
Put in a boss mechanic requiring the use of the shield at his 4th attack. But this optional.

One issue that im unsure of is the text display for damage done by the player or enemy. Currently it is a quick
flash. Wasnt able to figure out a way to delay it from disappearing. 

End Conditions: hit escape, both players die

To add: During the trouble shooting of memory loss, prior to realizing poor memory management, I found a 
	Blog about increasing memory for the program. It can be found at:
	"http://blogs.msdn.com/b/calvin_hsia/archive/2010/09/27/10068359.aspx"

	Essentially the next 2 lines are added to the Post-Build Events. If there are compiler issues or glitches
	This is currently part of my setup under project properties.

	call "$(DevEnvDir)..\..\vc\vcvarsall.bat" x86
	"$(DevEnvDir)..\..\vc\bin\EditBin.exe" "$(TargetPath)"  /LARGEADDRESSAWARE


