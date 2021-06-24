This project is currently configured to run on Microsoft Visual Studio 2012 or newer.
We recommend that you download the latest version of Visual Studio Community to run this project (it's free!).

Upon opening the project, a popup may appear stating that the project was built using an old version of Visual Studio and that the build files need to be updated to a newer version. Please accept the prompt so Visual Studio can update your files automatically.

If you encounter an error stating the build tools do not exist, the instructions on how to fix it shows up in the console window at the bottom. Simply go to the project properties and select the build tools version available in your Visual Studio.

If any library is missing from your system, Visual Studio can automatically download and install them for your project. Go to the Tools menu from the top of the window, and go to "NuGet Package Manager". Select "Manage NuGet Packages for Solution," search for any library your computer is missing under the browse tab, then hit Install.

## HW0
Once you have the program running successfully, press i to move the teapot into the correct position for our autograder. Next, press o to output the screenshot to the program's directory. Rename it to "screenshot1.png" so it isn't overwritten by a subsequent screenshot.   Please make sure you do not zoom in or out prior to pressing i or o (if you have earlier played with the mouse, it is best to restart the program and  take the screenshot).   

Next, I want you to change the color of the red highlight on the teapot to yellow (yellow is made by mixing red and green, which are the first two elements of the color vector: the third is blue). This corresponds to a RGBA value of (1,1,0,1). The relevant colors and code are defined in the "display" function of "mytest3.cpp" where it says "add lighting effects." Note that the red highlight is originally somewhat orange with a RGBA value of (1,0.5,0,1). Once you have changed the color of the highlight from red to yellow, recompile, run, and press i then o as before to output a screenshot. Rename this screenshot to "screenshot2.png".
