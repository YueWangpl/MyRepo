This project is currently configured to run on Microsoft Visual Studio 2012 or newer.
We recommend that you download the latest version of Visual Studio Community to run this project (it's free!).

Upon opening the project, a popup may appear stating that the project was built using an old version of Visual Studio and that the build files need to be updated to a newer version. Please accept the prompt so Visual Studio can update your files automatically.

If you encounter an error stating the build tools do not exist, the instructions on how to fix it shows up in the console window at the bottom. Simply go to the project properties and select the build tools version available in your Visual Studio.

If any library is missing from your system, Visual Studio can automatically download and install them for your project. Go to the Tools menu from the top of the window, and go to "NuGet Package Manager". Select "Manage NuGet Packages for Solution," search for any library your computer is missing under the browse tab, then hit Install.

## HW2

- Transform.cpp: This is similar to the Transform.cpp file in HW1, but now we add code stubs for translations, scales, and perspective projection.
- readfile.cpp: This file is for reading the input file (the parser structure is in place, but you need to deal with various other aspects).
- display.cpp: This file is for displaying the scene.
- shaders/light.frag.glsl: This file is for the actual fragment shader.  
We provide two scene files hw1.txt and demo.txt, the first of which corresponds to the scene seen in homework 1, and the second roughly to the demo OpenGL program.

### User Interaction
When your program is run with a scene file, it must interpret it as above, and draw the scene. Most of the basics for user interaction are already in the skeleton. In particular, the program should recognize the same keys as in homework 1 (namely h, +,-,ESC), as well as the following extensions:

- g as before, this switches between the glm::lookAt and the user commands. Now, it should also switch between glm::Perspective and your command, and by default it should call your code.
- r should reset the transformation to the initial scene. The amount of transformation given by keyboard input should also be reset.
- v should set the motion to correspond to rotating the camera (this should be the default and what you did for homework 1). Note that the camera need no longer be looking at the origin as the center, but you will still move the camera about the origin, keeping the center or look at point fixed.
- t should set the motion to translating the scene. In this case, the arrow keys should now move the scene in the x and y directions (in world space) respectively. The amount should be scaled by 0.01 for this purpose. (Note that amount is initially set to 5).
- s should do the same for scaling the scene, again in x and y directions. Again, amount should be scaled by 0.01. By pressing t, v or s one controls whether you modify translation, scale, or view. If one modifies say view, and then hits t to modify translation, the system should remember and keep the view change, i.e., should not revert to the original view.

## HOMEWORK 2: Detailed Steps and HINTS
Below are step-by-step instructions and hints from Fall 2012 student KolegA, and futher below also very detailed hints from hekimgil and from Spring 2013 student Aldur.  Obviously, these hints are optional and not "official course policy" (and they used somewhat earlier skeleton versions... I have tried to update them to the current skeleton) but you will likely find them very useful.  Also, this is a very long list of things, and you don't necessarily need to read this full page before starting. You may want to start the homework and refer to the basic hints first as you go along, and then look at the more detailed hints only if you get stuck.

- Step 0. Blue screen. Compile framework, run, you should see window with blue background. It's normal.  (For this iteration of the class, we have modified the program so it will show the teapot outline without shading, but the teapot won't be in the right place in any case).  

- Step 1. Where is my teapot? I prefer to add functionality little by little, make sure it works and than move to the next. So let us show something on screen. Select file hw1.txt as command line argument. Since we can't see blue teapot on blue screen we need to change background color (first line in display() function) or object's color (finalcolor variable from file light.frag.glsl). For example change object colors to red (this step has already been done in the current skeleton, with the shader setting the color to black if you do nothing; you can always change it to red if you prefer). Comment line modelview = transf from display() function, run it, press 'g' to switch to glm::LookAt and glm::Perspective functions. Now you should see red (or black if you made no changes to the shader) teapot on blue background.

- Step 2. Copy-paste HW1. Copy transform functions from your hw1. Run, press 'g', check if everything works like in hw1.

- Step 3. I want bigger teapot. Implement scale and translate matrices, uncomment modelview = transf and think how to combine current modelview transposed matrix, scale and translation. Review lecture about composing transformations if you have troubles with this step. Don't be upset if you can't make it work from the first try. Run, press 'g', make sure you can change size and position.

- Step 4. Perspective teapot. Review lecture on gluPerspective. There is enough information to implement the perspective matrix. Compare it with glm::Perspective.

- Step 5. Turn on the light. Fill the arrays lightposn and lightcolor in readfile.cpp. Use for-loop, memcpy or std::copy. Pass them to the light.frag.glsl using glUniform4fv. Dont't forget to transform lightposn first, use array lightransf, function transformvec and hw0 and hw1 as example. Implement shader (file light.frag.glsl) like in hw0 but with for-loop. There are point lights and directional lights. Directional lights have zero in last element 'w' of the vector. Compare picture with picture from hw0.

- Step 6. Almost done. Camera and transformations left. Every object has matrix transform change it in readfile.cpp (almost everything done by skeleton code), combine it with transf matrix and set modelview for every object in display.cpp. (In the current skeleton, the drawing routines like solidCube take care of setting the appropriate matrix transform for the modelview matrix in the shader, so your code in display just needs to update modelview but you do need to set the shader uniforms for the material properties explicitly).  

### HOMEWORK 2: Detailed set of HINTS (courtesy hekimgil)
**What needs to be done**:

There are 5 C++ files of which 3 you have to complete, in addition there are 2 GLSL files of which 1 you have to complete. main.cpp and shaders.cpp are complete but you have to do coding in display.cpp, readfile.cpp, Transform.cpp. Similarly, in the shaders folder light.vert.glsl (your vertex shader) file is fine but you have work to do on light.frag.glsl (your fragment shader) file.

**What needs coding**:

readfile.cpp reads the external file given in the command line argument (again as in HW1 this is automatically done with MSVS skeleton file but you will have to type it in for other systems) for environment information such as lights, objects and other attributes related to them. Most of the work is ready but you have to do some coding for the following "commands" in the input file: "light", "camera", "translate", "scale", "rotate"

Transform.cpp is your helper file with the necessary transformation functions to be used by the rest of the program. Just like in HW1, you have "rotate", "left", "up", and "lookAt" functions you have to code. But this time, in addition you also have "perspective", "scale", and "translate" functions to code.

display.cpp, unlike the other two files, does not have whole isolated functions to code but some specific places within the main display() function. Three of them to be specific: one that passes the light info to the shader, one that sets up a "net transformation matrix" for the objects, and finally one that actually passes the object info to the shader.

light.frag.glsl is the shader file where you have to do your lighting magic but luckily, much of what is done there is very similar to previous homework so you do not have "rebuild Rome", you just have to understand the concepts to tweak the code from the previous homeworks.

**Start slow**:

As suggested in the instructions, it is a good idea to start slow and use a different input file for objects, such as the lonely teapot in hw1.txt.

Easier to start with what you already have:

Since we all have done much transformation work in HW1, it may be easier to start there. The rotate, left, up, and lookAt functions are "likely the same as in HW1" as the comments in the code suggest. Completing the rest of the functions for perspective, scale, and translate is also pretty straightforward if you watched the lectures. You just spend much time thinking and considering and then get surprised that you spent so much time to write a really short and simple line of code...

Easier to continue with what you think you already have:

It may be a good idea to follow with the camera, translate, scale, rotate functions since we started the transformations. Be careful with the order of vector components when the "camera" command is called.

**Blue screen of death**:

"In the beginning, there was nothing; then there was light!" You see nothing at the beginning as you did not do the coding for lighting/shading. As the instructions suggest, you may start seeing an object as soon as you "temporarily" change the fragment color in light.frag.glsl file. Specifically, you will change the variable assignment for finalcolor at the end from blue (0,0,1,1) to something different like red (1,0,0,1).  [This has already been set to black in the current skeleton].

Are we done with the transformations:

The answer lies in the actual demo.txt file for HW2. The lonely teapot from hw1.txt was easy since you did not have much information to read and many objects to fiddle with. demo.text has 10 objects to play with:
```
teapot  
floor (well,,. actually a flattened cube...)  
4 x (sphere + cube)  
```

So if you are really done with the transformations, you will be able to see all those objects and do some rotating, scaling, translating with the keys when you run the program.

But if you are really really done with the transformations, when you press i and submit your non-shaded pictures for HW2, your objects will be in the same locations as the objects in the grader's output pictures. Don't worry about submission, you have unlimited submission trials, and I found it particularly useful to submit wireframe images and check their placement on the submission difference pictures (the third ones on the far right side).

As Sridhara suggested in the forum, it is a good idea to temporarily put a  
    `glPolygonMode( GL_FRONT_AND_BACK, GL_LINE )`;  
code in the beginning of your display() function to see the wireframe objects so that you can check if they are well aligned.

Very likely, you will experience problems with these alignments and might want to check not only your separate transformation functions but also the "ring that binds them all", your net transformation matrix. Most of us had problems with the their order or their transposings...

Let there be light!

Much of the code here is much like what is used in HW0 and in HW1 so you do not have to recreate things, but you will have to understand what is going on in order to do the necessary changes. With the display() file, just make sure you did the necessary transformations and passed the necessary values to your shaders by a bunch of glUniformxxxx commands. And with your fragment shader, the main challenge is to figure out what to do with different kinds of light sources from the input file.

### DEBUGGING:

- If you have a single big cube on your screen:

You have a problem with your transformations and all 10 objects appear together in the center. You only see the largest cubes on the outside.

- If your objects seem to "look" different:

Check your transformation functions and especially the part where you calculate the net transformation matrix.

- If you check the input.txt file (use Wordpad instead of Notepad if you are in a Windows PC), 
- you can also get an idea of how the grader pictures are produced and what pictures test what:

Pic 1: initial positions without any action  
Pics 2-3-4: rotations  
Pics 5-6-7-8: translations on top of 2-3-4  
Pic 9: reset and translation alone  
Pic 10: your lookAt  
Pics 11-12-13: scaling  

- A single color for all objects:  

Did you pass all of the object attributes to the shader?

- Colors are off:

Check the reflections on the spheres: There have to be two and none of them should be pointing at you. If there is one reflection on the spheres, you are missing a light. If a reflection is always pointed at you, the light seems to come from your camera, thus the light is not properly positioned.

### HOMEWORK 2: DETAILED SET OF HINTS 2 (COURTESY Aldur)
#### General

it is best to get transformations right before moving to lighting  
you can use hw1.txt to get the teapot outline and then play with all the transformations checking if they don't seem weird
once you have the transformations really working (you see 4 pillar outlines and such), dump the screenshots and compare autograder output; if the outline is not accurate, continue to work on transformations until you get it 100% right
if you are using visual studio express, for your shader editing you can use notepad++ with [GLSL syntax highlighting](http://www.lighthouse3d.com/2013/01/notepad-glsl-4-3-syntax-highlight/)
and if you really end up stuck, search thoroughly through the discussion, you may not get exactly the answer you seek, but a hint good enough to get back on track

#### Transform.cpp

you should copy the rotate, left, up and lookat from HW1  
rotate needs a small tweak: axis needs to be normalized before use  
implementing remaining functions can be done by strictly following math from lectures in Unit1, it helps a lot to write the function contents similarly to lecture slides, for example to initialize mat4 with full 16-argument constructor, write them as if you were writing math matrix, then transposing them before returning (because glm is column major, not row major)
remember that any angles need to be converted to radians before being used  
it is crucial to implement these functions correctly straight away, else they will haunt you later and possibly interfere with finding source of subtle bugs

#### readfile.cpp

at every point where you are asked to write code, you can use `values[]` array to actually get the data, that has been read from file; slightly above `readvals()` has a comment indicating what values are available in what order, for example "readvals(s, 8, values); // Position/color for lts." means that values[0] to values[ 3 ] hold a single light position corrsesponding to 4 vector coordinates, then values[4] to values[7] light color by analogy
light position and color vectors need to be sequentially added to `lightposn[]` and `lightcolor[]`, one coordinate per array index, therefore a single `vec4` takes 4 indices in such array, this means every 4 indices consist of a vector of one light (0-3 first light, 4-7 second light and so on)
make good use of numused variable when saving light position and color to their respective array indexes
I did not need to use `upvector()` for camera implementation
translate, scale, rotate are also straightforward, use `rightmultiply()` and as second argument the transform stack itself, be sure to UNDERSTAND why this is working

#### display.cpp

if you decide to use `transformvec()` for light transformations, you need to first load into opengl the matrix created via Transform lookAt(); this is because transformvec() obtains this matrix directly from opengl, check its definition! [This is no longer very relevant in the modern OpenGL skeleton, and transformvec takes the modelview matrix]. 
transforming light positions by view matrix is indeed necessary and can be done for example via `transformvec()` function, you need to extract `pos` vector values from appropriate array one by one, apply this function to each set of 4 and then add results to lightransf array in exactly the same order and positions.
you need to provide all light colors and transformed (!) positions in a SINGLE glUniform call per array, this call and the process of passing data to shader is quite unintuitive, therefore I suggest reading glUniform documentation and also I've found a very helpful hint to avoid certain error, available here
below lighting block, you need to construct transform matrix (transf), by multiplying translate, scale and modelview (mv) matrices (not necessarily in this order!), lectures provide all the information necessary to figure the correct order.
you can access object fields by using "obj->fieldname" notation, this is C++ specific, remember to finally load matrix into modelview  that furthermore correctly includes current object transform and your general transform! This makes perfect sense since you need to include both camera orientation and object orientation! If this still seems confusing, imagine that objects are drawn one after another, each with their own transformations and material properties applied beforehand (this is not entirely true, but serves as a good visualization of how this code flows).
make sure to supply shader with shininess and other material properties using float version of glUniform, not the int!
light.frag.glsl

this may look like a very hard part, but in essence you just need to apply HW0 shader of the same name, then modify the light code to instead iterate over all light sources and apply them one after another to the result.

**you should use shader code from HW0**, not HW1, as the latter has only 2 point light sources and does not show how to handle directional lights. Also lectures L7V3 and L7V4 describe this in even further detail. 

If in doubt on how to implement lighting calculation "pipeline", follow the HOMEWORK 2: BASIC IMPLEMENTATION HINTS => Lighting formula.

You should treat attenuation as if there was none (even for point lights). If you are using HW1 shader as base, then it's already coded for no attenuation and you do not need to change anything in that regard.
