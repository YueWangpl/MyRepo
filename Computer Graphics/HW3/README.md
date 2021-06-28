# Overview
In general, you should implement a raytracer. The raytracer can be run on the command line with a single argument, that is an input file. All parameters are contained in the input file, whose format is specified on the next page. Your raytracer will parse the input file, reading in geometry, materials, lights, transforms etc. It will then raytrace the scene displaying an image. The file format is rather similar to that in assignment 2, and so you should already have a handle on some logistical issues like how to parse it and so forth. In fact, the assignment is in some sense simpler than homework 2, since you do not need to implement any user interaction.

Finally, ray tracers (especially unaccelerated ones like what you are building) tend to be very slow. You should display some kind of progress indicator to let one see how much of the scene is done (text printed out is fine). Also, for debugging, always start with low resolution images (say 160 x 120) and make sure things look reasonable before rendering final high resolution (640 x 480 or higher) versions. For a couple of the autograder images with larger scenes, you may need to optimize your raytracer, but worry about that well after getting the basic functionality and correct images in place.

#### Saving Images
For the purpose of (only) actually writing the output image file, you can reuse any image processing libraries either online or that you have for earlier assignments. The image files required by the autograder are in .png format, although you can of course convert from other formats. It is simplest to use the FreeImage library for writing the output file (the same library that was bundled with homeworks 0,1 and 2). If you feel this would be too much bother, you can also write out ppm files as used for the texture in homework 0, and convert them offline. Note that this assignment just requires the ability to write an output file, and does not require OpenGL.

The simplest way to output your image files is probably to use the FreeImage library which we use to save screenshots in HW0/1/2. First, compile your ray tracer with the FreeImage library by including FreeImage.h in your solution as well as -lfreeimage in your linker flags. Take a look at the skeletons for each platform to see how to implement this. On OSX/Linux, the library file must be in one of the directories specified in the makefile or in /usr/lib. Also make sure FreeImage.h is in your include directory for either platform. For Visual Studio, you will likely need to bundle the FreeImage DLL with your solution as well as the library/include files, and specify these in the project properties.

Before you use FreeImage, call FreeImage_Initialise(). To record the colors for each pixel, use an array of one byte elements. Then convert this array to a FIBITMAP object as follows, assuming the bytes are in RGB order:

`FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);`

Where pixels is a pointer to the beginning of your pixel array, w and h are the width and height of the image, w*3 is the number of bytes on one row of pixels, 24 is the number of bits per pixel, the hex values are bit masks for each color R, G and B, and false tells FreeImage that the bottom-left pixel is first. If you start with the top-left pixel, change this to true. This method assumes that your pixel array goes one row at a time.

To save your image as a PNG, use the following command:

`FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);`

Where `FIF_PNG` specifies the file type, img is the pointer you obtained by the function call above, fname is a C++ STL string object converted to a C string for the filename (any C string argument works here), and 0 indicates no special flags are used.

Finally, call `FreeImage_DeInitialise()` to exit cleanly.

#### Debug vs. Release in Visual Studio
The default build option in Visual Studio is Debug, and while this allows for easier debugging, it causes code to run much slower. If you want a speedup after your raytracer is debugged, change the build mode to Release. This will require you to reset your project properties to similar values as in the Debug build mode, as well as copy your FreeImage DLL to the newly created Release directory if you used this image library.

## Homework 3: Assignment Specification
The input file consists of a sequence of lines, each of which has a command. For examples and clarifications, see the example input files. The lines have the following form. Note that in practice, you would not implement all these commands at once but implement the smallest subset to debug the first aspect of your raytracer (camera control), then implement more commands to go to the next step and so on. This page contains the complete file specification for reference.

#comments This is a line of comments. Ignore any line starting with a #.
Blank line The input file can have blank lines that should be ignored.
command parameter1 parameter2 ... The first part of the line is always the command. Based on what the command is, it has certain parameters which should be parsed appropriately.
We now discuss each of the various commands you need to implement, along with the default values to use where appropriate.

#### General
You should implement the following general commands:

- size width height:   
The size command must be the first command of the file, which controls the image size.
- maxdepth depth:  
The maximum depth (number of bounces) for a ray (default should be 5).
- output filename:  
The output file to which the image should be written. You can either require this to be specified in the input, or you can use a suitable default like stdout or raytrace.png (The final files should be .png, with the specific names the autograder requests).
#### Camera
The camera is specified as follows. In general, there should be only one camera specification in the input file; what happens if there is more than one specification can be left undefined. (You can require the camera command to come before any geometry in the file, although it doesn't seem you really need to require that).

camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov specifies the camera in the standard way, as in homework 2. Note that fov stands for the field of view in the y direction. The field of view in the x direction will be determined by the image size. The world aspect ratio (distinct from the width and height that determine image aspect ratio) is always 1; a sphere at the center of a screen will look like a circle, not an ellipse, independent of the image aspect ratio. This is a common convention but different from some previous specifications like the raytracing journal handout.

#### Geometry
For this assignment, you will worry only about spheres and triangles. These can be specified in a number of different ways, and differ substantially from what you were asked to do for assignment 2. The first set of commands you need to implement are as follows:

1. *sphere x y z* radius Defines a sphere with a given position and radius.
2. *maxverts number* Defines a maximum number of vertices for later triangle specifications. It must be set before vertices are defined. (Your program may not need this; it is simply a convenience to allocate arrays accordingly. You can ignore this command [but still parse it] if you don't need it).
3. *maxvertnorms number* Defines a maximum number of vertices with normals for later specifications. It must be set before vertices with normals are defined. (same discussion as above)
4. *vertex x y z* Defines a vertex at the given location. The vertex is put into a pile, starting to be numbered at 0.
5. *vertexnormal x y z nx ny nz* Similar to the above, but define a surface normal with each vertex. The vertex and vertexnormal set of vertices are completely independent (as are maxverts and maxvertnorms).
6. *tri v1 v2 v3* Create a triangle out of the vertices involved (which have previously been specified with the vertex command). The vertices are assumed to be specified in counter-clockwise order. Your code should internally compute a face normal for this triangle.
7. *trinormal v1 v2 v3* Same as above but for vertices specified with normals. In this case, each vertex has an associated normal, and when doing shading, you should interpolate the normals for intermediate points on the triangle.
The provided grader examples do not test vertexnormal, trinormal, or maxvertnorms.  Therefore, implementing this triangle-with-normal functionality is optional, but you may still want to play with these commands to produce interesting smooth shading effects.  Of course, you still need to implement vertex, tri, sphere and maxverts.

#### Transformations
You should be able to apply a transformation to each of the elements of geometry (and also light sources). These correspond to right-multiplying the modelview matrix in OpenGL and have exactly the same semantics, just like in assignment 2. It is up to you how exactly to implement them. At the very least, you need to keep track of the current matrix. (Presumably, you can reuse some of the same implementation you did for assignment 2). For triangles, you might simply transform them to the eye coordinates and store them there. For spheres, you could store the transformation with them, doing the trick of pre-transforming the ray, intersecting with a sphere, and then post-transforming the intersection point. The required transformations to implement are:

1. *translate x y z* A translation 3-vector.
2. *rotate x y z* angle Rotate by angle (in degrees) about the given axis as in OpenGL.
3. *scale x y z* Scale by the corresponding amount in each axis (a non-uniform scaling).
4. *pushTransform* Push the current modeling transform on the stack as in OpenGL. You might want to do pushTransform immediately after setting the camera to preserve the identity transformation.
5. *popTransform* Pop the current transform from the stack as in OpenGL. The sequence of popTransform and pushTransform can be used if desired before every primitive to reset the transformation (assuming the initial camera transformation is on the stack as discussed above).
Note that all of these commands are exactly the same as in assignment 2.

#### Lights
You should implement the following lighting commands.

1. *directional x y z r g b* The direction to the light source, and the color, as in OpenGL.
2. *point x y z r g b* The location of a point source and the color, as in OpenGL.
3. *attenuation const linear quadratic* Sets the constant, linear and quadratic attenuations (default 1,0,0) as in OpenGL. By default there is no attenuation (the constant term is 1, linear and quadratic are 0; that's what we mean by 1,0,0).
4. *ambient r g b* The global ambient color to be added for each object (default is .2,.2,.2).
This is slightly different from the specification in assignment 2. Note also that if no ambient color or attenuation is specified, you should use the defaults (you may have used black as a default in assignment 2; here the defaults are specified). Note that we allow the ambient value to be changed between objects (so different objects will be rendered with a different ambient term; this is used frequently in the examples).  Finally, note that here and in the materials below, we do not include the alpha term in the color specification.

#### Materials
Finally, you need to implement the following material properties.

1. *diffuse r g b* specifies the diffuse color of the surface.
2. *specular r g b* specifies the specular color of the surface.
3. *shininess s* specifies the shininess of the surface.
4. *emission r g b* gives the emissive color of the surface.

## Homework 3: BAsic implementation steps
What follows below is a step-by-step approach to implementing the requirements for your raytracer. We strongly recommend you proceed in the order below.

#### Camera
The first step is to implement the camera model. The user should be able to specify the camera, and you should test using a simple scene (initially, it may be simplest if you test using a single quad as geometry, coding up a simple ray-quad intersection test and don't worry about shading). For this part of the assignment, you will need to know how to set a camera, and how to generate corresponding rays for each pixel. Get this part completely debugged before proceeding further.

Please note that the raytracer for the autograder sends rays through the center of a pixel, i.e. at values 0.5,1.5,... rather than at integers (pixel corners). Please follow the same convention to match images.

#### Ray-Surface Intersection tests
Now, you should implement the core of your raytracer, which are the ray-surface intersection tests, in this case for triangles and spheres. You should debug separately with each primitive, making sure things work as expected. You could try images of the second test scene of a dice (from each of the camera positions specified).

If you are testing only the ray-sphere intersection test, it is much simpler to ignore shading and use only an ambient (constant) term to see the intersections in an image.

Next, you should implement transformations, allowing the user to specify transformed geometry. You might want to try the third test scene (the table with ellipses and spheres). Again, shading is not yet important, but you should be sure the core ray-surface intersection tests for geometry are debugged.

#### Lighting and Shadows
Next, you should implement shading. For this, simply implement the similar shading model as in homework 2. In particular, the color at each point is given by  
$$I = A + E + sum_i V_i L_i/(c_0+c_1 r + c_2 r)(D max(N \dot L, 0) + S max (N \dot H, 0)^S)$$  
where $I$ is the final intensity, $A$ is the ambient term, $E$ is the self-emission, and the diffuse D and specular S are summed over all lights $i$ with intensity $L_i$. $N$ is the surface normal, $L$ is the direction to the light,  $H$ is the half-angle, and $s$ is the shininess. For ray tracers, there is an additional term $V_i$ which is the (binary) visibility to the light, corresponding to shadows. You should cast a shadow ray to all lights at the intersection point to determine if they are visible (determine $V_i$). If visible, we simply compute the diffuse contribution as well as the specular contribution. We also include an attenuation model, new from homework 2, corresponding to traditional OpenGL (the attenuation model applies only to point lights, not directional lights). c0, c1, c2 are the constant, linear and quadratic attenuation terms, while $r$ is the distance to the light. Physical point lights have (c0, c1, c2) = (0,0,1) while the default (no attenuation) is (c0, c1, c2) = (1,0,0).

#### Recursive Ray Tracing
Next, you should implement a recursive ray tracer for mirror reflections. The simplest way of doing it is to shoot a single ray in the mirror direction, weighting its contribution by the specularity or S. Since this reflected ray may spawn additional reflections, the tracing is recursive, with the maximum depth of the ray tree controlled by the maxdepth parameter.


### HOMEWORK 3: Debugging and Implementation notes
These implementation notes are contributed by Fall 2012 student KOlegA.  They are not "official course policy", but are likely to be helpful to you in writing your own raytracer.  

0. Own classes for math or glm (or other lib)
Of course with library functions you can implement the assignment faster and maybe they work faster, but writing your own classes (Vector, Normal, Point, Matrix, Color, ..) gives more flexibility and makes the code easier for understanding. Besides, it's not hard to implement them, and they can be faster because they don't have to be so general. For example in multiplying Matrix4x4 by Vector3 you need to consider only matrix3x3. The only complicated thing to implement is Matrix4x4 inversion, but we don't need that for this assignment. By multiplying inverted transform matrices in reverse order, we can obtain the inverted matrix. (That is, simply invert or undo each transformation, but in reverse order: the last transform applied is the first transform inverted or undone).  $(ABC)^{-1} = C^{-1}B^{-1}A^{-1}$.  Of course, you still need to invert the basic transforms like A^{-1}, but inverting simple translation or rotation is straightforward.  

1. scene4-ambient and scene4-emission
If transforms and intersections are implemented correctly, the image should look like the image from the grader. At this step you can skip implementing the shader and shadows, and just set color equal to ambient + emission.

Image is smaller then it should be: Probably you are calculating fovx incorrectly. Should be

$$tan(fovx/2) = tan(fovy/2) width/height$$.

Or the camera ray is not through the center of the pixel (it may be through integers 0, 1, 2 instead of half-integers 0.5, 1.5, 2.5).

Objects overlap incorrectly: Probably you forgot that you need to find the closest intersection object.

2. scene4-diffuse
Start from marking shadow areas with solid color.

Image has black points: You forgot to make epsilon shift before shooting the ray from the intersection point to the light source.

Image has color stripes: You forgot to normalize direction somewhere.

Shadows are incorrect: Probably you are transforming normals incorrectly. Review the lecture about transforming normals. If you are applying a matrix M to transform a vector, to transform the normal, you should apply the inverted transposed matrix M 3x3.

3. scene4-specular
Shading is almost like in previous homeworks, except attenuation for point light source and eyepos which was previously zero. Initially variable eyepos equals to camera position, after reflection it should be point of reflection. So, eyepos is ray start point.

4. scene 5
If all previous scenes work fine and directional lights are implemented correctly, there shouldn't be any problem.

5. scene 6
Picture black with white cube: Light source could be between two objects. You generated ray from intersection point to the light source and found the intersection, but that intersection was behind the light source, so you should consider only objects between intersection point and light source. 

6. scene 7
Usually, the only problem here is raytracer performance. Don't forget to build a release version before running this scene. Use openmp. For example, on my laptop (i5 2.27Ghz) inside virtual machine without any optimizations, but with openmp it tooks near 30 minutes. My implementation is standard C++.
