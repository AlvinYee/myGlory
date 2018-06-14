# myGlory
the best work I've ever done
Coco platform GEN 3.5 design specification
Motivation
This work was initiated with the intention to make project-specific variant of Coco based on configuration and automatic code-generation afterwards.
Problem analysis and abstraction
First, we divide the Coco SW into two parts: fixed part for all projects, and configurable part for specific project. From component level point of view, it is easy to see that the messages transmitted via I2C to Coco are the main changes, together with some application level parameters, they consist of the whole project-specific changes.
Here are the summary of all possible things we need to do with these messages.
a)	Timeout monitor
b)	CRC check
c)	Alive counter check
d)	Signal layout
e)	Logics on signals
Together with application level
f)	Parameters
All of these are configurable behaviors.
Below is the latest version of configuration table.
 

Architecture design
 
i.	CocoConfigurator covers configuration items of a) Timeout monitor, b) CRC check, c) Alive counter check, f) Parameters
ii.	LayoutGenerator covers d) signal layout	
iii.	Template covers implementation of a) Timeout monitor b) CRC check, c) Alive counter check, e) Logics on signals, together with the configuration items and parameters defined in Coco.xml, the template becomes the final HCM_LCD.c
Component design
1.	LayoutGenerator
2.	CocoConfigurator
3.	Template

Configuration table 

