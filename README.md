# LiVHY - Global Illumination raytracer
## Bachelor's project
#### Made by (Antonio Janjić)

# Overview
This project is meant as an implementation of a global illumination raytracer as described by Peter Shirley and in the book ["Advanced Global Illumination"][1].

# Getting started

## Installing
This project uses `premake5` for automatic configuration building. 
To install the program run the premake5.lua file with premake and then either open the resulting solution file in Visual Studio or run `make` on the output makefile.

## Running the program
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


# Licenses

# Credits

# Gallery

# References

[1] "Advanced Global Illumination"...