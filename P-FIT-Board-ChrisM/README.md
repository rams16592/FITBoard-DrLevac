# P-FIT-Board

Assembly
========
Using atmel studio to build the assembly and then avrdude to push it to the Attiny85

The current basic config is to:
1. Install WinAvr
2. Install Atmel Studio
3. At the moment create an assembly project to pull in headers for the attiny
4. Copy over assembly from the folder
~4. Or cross your fingers and open the assembly file into your project/open your project
5. Build it (Not debug or run)
6. Use an external tool with avrdude to push it to the attiny
7. Cross your fingers

The external tool should only require these arguments
```
-C"C:\WinAVR-20100110\bin\avrdude.conf" -v {program.verify} -pattiny85 -cstk500v1 -PCOM4 -b19200 -Uflash:w:$(ProjectDir)Debug/$(TargetName).hex:i 
```
which are portable. The command we are excuting itself is just the avrdude.exe executable
