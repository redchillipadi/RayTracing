RayTracing
==========

Build a software path tracer following Ray Tracing in One Weekend and Ray Tracing: The Next Week available at https://raytracing.github.io

Changes from the Series:
* This uses SFML to display the image line by line during rendering rather than saving it to disk as a file.
* The classes were organised into folders (Materials, Shapes, Textures)
* Their implementations were moved into separate translation units compared to the header only style of the original.
* Documentation was added.

As a software renderer, the images take significant time to generate, but the process of writing the code develops understanding of the fundamentals of ray tracing.
