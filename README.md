# OGL UI

A very simple to use and extend OpenGL based UI library.

I wrote this library over a decade ago (2014) and this repo is a revival of
the project which I will continue to revisit from time to time to keep it 
compiling and improving.

It was initialy created as a starting point for the WireWorld Music project 
but was stable and robust enough to be considered as it's own thing.

I have some new ideas that could use a simple and ready to use GUI. :)

Set of available GUI elements:

![Screenshot 1](/docs/screenshot-1.png)

Any element fits in tabs:

![Screenshot 2](/docs/screenshot-2.png)

Example of a menu:

![Screenshot 3](/docs/screenshot-3.png)

Available GUI Elements:

* Static
* Button
* Frame (with tabs; can contain child elements)
* Edit
* Checkbox
* EditNumber (for int values)
* EditNumberF (for float values)
* Slider

# Structure

The key files to import are the header `gui.h` and the source `gui.cpp` files.

The header file contains the definition of all the controls, while the source file
contains the implementation.

All controls extend from the base Control class, which contains a basic set of state
values (position, size, state...).

Each control sub-class is responsible for its own rendering and other logic.

An example of usage is presented in the `main.h` header and `main.cpp` source files.
This example uses the Microsoft's Win32 API library to set up the minimal needed window
and context for the OpenGL to be rendered in.

The project uses Win32's loop system to process system's messages and capture user input.

# How to compile and use

The requirements to compile this project are:

* Microsoft's Windows system (should work on any version starting at XP)
* A compiler toolchain (like the MinGW-w64 toolchain)
* OpenGL

To build the project just run: `make build`.

To run it: `make run`.

Or, you can download the pre-built binary file from the repository [Releases](https://github.com/ByteHunter/ogl-ui/releases).

# Is there any roadmap?

Yes and no. This project was born as a proof of concept and as a means to learn new
things. But I do intend to continue iterating on it and improve it over time.

Some possible improvements I'm considering may be, but not limited to:

* Modernize to a newer C++ version. This project was created a while back, when C++11 was considered modern.
* Fix any issues with the rendering.
* Tidying the code base.
* Improve this document.