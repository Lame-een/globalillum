# Global Illumination raytracer
## Bachelor's project
### Mentor: doc. dr. sc. Domagoj Ševerdija
### Author: Antonio Janjić

# Overview
This project is meant as an implementation of a global illumination raytracer as described by Peter Shirley and in the book ["Advanced Global Illumination"][1].

# Getting started

## Dependencies
* This project uses [`premake5`](https://premake.github.io/) for automatic configuration building.
* `OpenMP` is necessary to run the release build of the program.
* [`GLM`](https://github.com/g-truc/glm) is used for it's powerful vectors, matrices and corresponding functions.
* Helper classes and functions are taken from [my tiny utility library]().
* [stbimage's](https://github.com/nothings/stb) headers for image loading and writing are used for image file handling.

## Downloading
Cloning the repository can be done with `git clone --recursive https://github.com/Lame-een/livhy`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.

## Installing

### Windows
Run premake5 alongside the premake5.lua file with the `vs2022` argument to create a Visual Studio solution.

### Linux
Make sure that `OpenMP` is installed, if it isn't it can be installed by running `sudo apt install libomp-dev`.

Run premake5 alongside the premake5.lua file with the `gmake` argument to create a Makefile, which can be used to compile the program. 

The default configuration should produce a release build. The configuration can be chosen by setting the make's config argument to either `config=release` or `config=debug`.

## Running the program
By default the application will be built in the `./bin/x64/%configuration%` directory.

The program can be run in the CLI using the following arguments:

```
LiVHY.exe [OPTIONS] output_image_name
```

The program settings can be set by adding `OPTIONS` flags. Here's a breakdown of all of them:
* Raytracer Options:
    * `-help` -- Display the help screen.
	* `-s, -samples` -- Set the samples per pixel. (default `1024`)
	* `-depth` -- Set maximum recursion depth. (default `25`)
	* `-w, -width` -- Set the viewport width. (default `640`)
	* `-h, -height` -- Set the viewport height. (default `640`)
	* `-fov` -- Set the camera Field Of View (in degrees). (default `60`)
	* `-bg, -background` -- Set the scene background in hex RGB (default `"#3a3a3a"`).
	* `-bgimg, -background-image` -- Set the scene background to `day` or `night` (default `none`).
	* `-gamma` -- Set the output image gamma correction. (default `2.2`)
* Demo Options:
	* `-demo` -- Choose one of the raytracing demo scenes.
	* `-demo-list` -- List all available demos.

(Note: All options are case sensitive.)


Example usage:
* `$ LiVHY.exe -help` -- displays all of the possible CLI arguments.

* `$ LiVHY.exe -w 250 -h 250 -demo 0 demo_0_render` -- sets the width and height to 250px, and starts rendering the demo #0 while saving it as "demo_0_render.png".

# How it works
The program is a raytracer which uses Monte Carlo integration for approximation luminance. As with a standard raytracer, rays are sent out from a point which simulates a camera sensor or the eye's retina.
For each pixel of the image `samples` amount of rays are sent through the pixel each slightly displaced.

Each ray is checked for intersection with objects in the scene or the background. Upon an intersection with an object the hit is saved in a `HitInfo` object and the material of the object will return data about the scattering of the ray with the help of the `ScatterInfo` struct.

With the data in the `ScatterInfo` struct we can proceed with recursively casting rays from the intersection point depending on which kind of interaction it is.

The cast rays carry the color/luminance data back via the recursion and all rays are added up and averaged. This presents the final color of the pixel.

# For developers

## Code style
This project uses a variant of Microsoft's style. For a more general look into the style please check the code itself.

Class member implementations should be avoided inside header files.

### Naming conventions
Classes, functions, member functions, enums, namespaces are always in *PascalCase*.
Helper functions are allowed to be *camelCase* in case they're "private", i.e. used by a function and not really expected to be called by other developers in normal circumstances.

* Local variables and function parameters are **always** *camelCase*. 
* Private member variables are prefixed with m_ and start with a capital letter.
* Static variables are prefixed with an s_ and start with a capital letter

An example of the style:

```c++
namespace ExampleNamespace{
	static int s_StaticInt = 0;

    static void StaticFunction();

    class ExampleClass
    {
    public:
        void MemberFunction(int var)
        {
            m_MemberVar = var;

            std::vector<int> localVector;
			localVector.push_back(var);
        }
    private:
        int m_MemberVariable = 0;
    };
}
```

## Code organisation
All source files must be *cameCase*. They must be in the `./LiVHY/src` directory and their corresponding header files much be next to them in the same directory.
Helper classes, functions and other objects should be in the `./LiVHY/src/util` directory.

Vendor files and other dependencies *must* be in the `./LiVHY/vendor` directory.

# Licenses

GLM license can be found [here](https://github.com/g-truc/glm/blob/master/copying.txt) as well as in the `./licenses` directory.

# Credits and acknowledgments
I want to thank:
* The team over at [Scratchapixel]() for their wide array of lessons on the basics of computer graphics.

* *Peter Shirley* and his team for the book on ["Fundamentals of Computer Graphics"][2] as well as the ["Raytracer in Weekend"](https://raytracing.github.io/) series.

* My mentor on this project ** for introducing me into the field of 3D computer graphics as well as helping me with his mentorship around the project.

# Gallery

...pics here

# References

1. [Philip Dutr ́e, Kavita Bala, Philippe Bekaert. *Advanced Global Illumination* ISBN 13: 978-1-56881-307-3, A K Peters, Ltd][1]

2. [Shirley Peter. Fundamentals of Computer Graphics, ISBN-13: 978-148222-939-4, A K Peters, Ltd][2]

[1]: https://www.oreilly.com/library/view/advanced-global-illumination/9781439864951/
[2]: https://books.google.com/books/about/Fundamentals_of_Computer_Graphics.html?id=QUQ3EAAAQBAJ