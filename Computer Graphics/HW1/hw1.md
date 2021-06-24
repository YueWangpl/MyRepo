This project is currently configured to run on Microsoft Visual Studio 2012 or newer.
We recommend that you download the latest version of Visual Studio Community to run this project (it's free!).

Upon opening the project, a popup may appear stating that the project was built using an old version of Visual Studio and that the build files need to be updated to a newer version. Please accept the prompt so Visual Studio can update your files automatically.

If you encounter an error stating the build tools do not exist, the instructions on how to fix it shows up in the console window at the bottom. Simply go to the project properties and select the build tools version available in your Visual Studio.

If any library is missing from your system, Visual Studio can automatically download and install them for your project. Go to the Tools menu from the top of the window, and go to "NuGet Package Manager". Select "Manage NuGet Packages for Solution," search for any library your computer is missing under the browse tab, then hit Install.

## HW1
The purpose of the homework is to fill in the code to allow rotation of the viewpoint around a scene, using what is known as a crystal ball interface.  
Fill in the parts of Transform.cpp that say "//FILL IN YOUR CODE HERE". First, you should fill in left() and up(). Once these are working, fill in lookAt(). You must also fill in the helper function rotate() and you can use it in your code (this function simply sets up the rotation matrix for rotation about a given axis; you can use the Rodriguez formula from the lectures). Do not modify any files except for Transform.cpp.

You may use `glm::dot`,  dot-products  
`glm::cross`, cross-products  
`glm::transpose`, matrix transposes  
`glm::normalize`, normalization.  
You do not strictly need to, but you may also use glm::radians and matrix-vector or matrix-matrix multiplication from the glm library (via overloaded operators).

### Basic Hints
You are not required to use or refer to any of the material in these hints, but they are likely to be useful to you.  A more detailed FAQ and step-by-step hints are found later.  This mainly pertains to the material needed in Transform.cpp which is all you need to modify (do not change any other files). main.cpp is reasonably documented, and one goal is for you to try to learn some OpenGL if you want to look at it in more detail.

- Rotate
Rotate just implements the standard axis-angle formula to create a rotation matrix. This is a good exercise in correctly coding vectors and matrices. You will of course need to use standard trigonometric functions and convert degrees to radians.  Please note that namespaces are properly set up so you can simply do sin(angle), cos(angle) in your code.  You can also specify glm matrices simply with mat3 M; without the glm::mat3 qualifier being needed.  

- Left
The simplest function to fill in is left. The input is the degrees of rotation, the current eye 3-vector and current up 3-vector. Note that you may need to convert degrees to radians (in the standard way) to set up a rotation matrix. Your job is to update the eye and up vectors appropriately for the user moving left (and equivalently right). This function should not require more than about 3 lines of code to do the appropriate rotations.

- Up
The up function is slightly more complicated, but satisfies the same basic requirements as left. You might want to make use of helper functions like glm::cross and auxiliary vectors. Again, you need to update the eye and up vectors correctly.

- lookAt
Finally, you need to code in the transformation matrix, given the eye and up vectors. You will likely need to refer to the lecture videos, and especially the derivation of gluLookAat to do this. It is likely to help to define a u v w coordinate frame (as 3 vectors), and to build up an auxiliary 4x4 matrix M which is returned as the result of this function.
