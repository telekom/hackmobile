# Installing Arduino IDE for Tuino 1


To start using the Tuino 1 you need to install the Arduino IDE ( >= 1.6.4 ).<br/> 
Find the latest version on the official Arduino website [www.arduino.cc](https://www.arduino.cc/).<br/>
Once you have installed the IDE you need to load the board manager file for the Tuino 1. Here the steps:<br/>
1) Launch the Arduino IDE<br/>
2) Open the Menu File, and go to Preferences<br/><br/>
<img src="https://raw.githubusercontent.com/gimasi/TUINO_ONE/master/docs/arduino_ide_1.png"><br/><br/>
3) Inside the dialog that appears, go to the 'Additional Boards Manager URLs' text box and copy the following URL inside the text box: `https://raw.githubusercontent.com/gimasi/TUINO_ONE/master/arduino_ide/package_tuino_index.json`<br/><br/>
<img src="https://raw.githubusercontent.com/gimasi/TUINO_ONE/master//docs/arduino_ide_2.png"><br/><br/>
4) Click Ok.<br/>
5) Now to go to the '<b>Tools</b>' menu, select the '<b>Board…</b>'' menu item, another menu will open on the right, select '<b>Boards Manager</b>'<br/><br/>
<img src="https://raw.githubusercontent.com/gimasi/TUINO_ONE/master//docs/arduino_ide_3.png"><br/><br/>
The Board Manager dialog box will appear, type in the search text box the word Tuino. The Tuino board files will appear, click on the text to select it and the '<b>Install</b>' button will appear.<br/><br/>
<img src="https://raw.githubusercontent.com/gimasi/TUINO_ONE/master//docs/arduino_ide_4.png"><br/><br/>
6) Click Install... Once the installation has finished you can close the dialog.<br/>
7) Reopen the '<b>Tool</b>' menu, select the '<b>Board...</b>' menu item, on the menu that opens on the right you should see at the bottom the '<b>Tuino 1</b>'... Select it<br/><br/>
<img src="https://raw.githubusercontent.com/gimasi/TUINO_ONE/master//docs/arduino_ide_5.png"><br/><br/>
8) You are now ready to start working with your first examples<br/>
<br/>
Find [here](/documentation/tuino_example_sketch/) the initial template sketch.<br/>
