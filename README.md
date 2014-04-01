RayTracer
=========

A play around with ray tracing and optimisation

Another of my projects based on something found at CalTech`s programming track online, you can find the original 
materials here : http://courses.cms.caltech.edu/cs11/material/advcpp

However it mainly serves as a way to teach the STL to students and crazy template tomfoolery, it serves as a good base for your 
own optimisations. 

I intend to alter it not to use virtual functions/superclasses, add some intrinsic instructions and then look
into ray tracing specific optimisation strategies to make it fast, and then make it pretty by adding stuff such as
textured objects, bokeh, and hopefully get it rendered to a bitmap and textured to the screen to allow camera movement
and so on in real-time.

History:

2014/04/01 - initial commit of basic raytracer, no optimisations, merely renders lit spheres and planes, no reflections
