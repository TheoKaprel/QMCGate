# Sampler Penrose [[ODJ04]](https://cseweb.ucsd.edu/~ravir/6160/papers/importancesampling.pdf)


## Files

```
src/samplers/SamplerPenrose.hpp  
src/bin/samplers/Penrose_2dd.cpp
```

## Description


The Penrose sampler from [[ODJ04]](https://cseweb.ucsd.edu/~ravir/6160/papers/importancesampling.pdf).  
For a more precise description of this sampler and its performances in terms of aliasing and discrepancy, please refer to the following web bundle [https://liris.cnrs.fr/ldbn/HTML_bundle/index.html](https://liris.cnrs.fr/ldbn/HTML_bundle/index.html).

## License
```
File: quasisampler_prototype.h
 Quasisampler prototype.

 This is a toy (non-optimized) implementation of the importance sampling
 technique proposed in the paper:
 "Fast Hierarchical Importance Sampling with Blue Noise Properties",
 by Victor Ostromoukhov, Charles Donohue and Pierre-Marc Jodoin,
 to be presented at SIGGRAPH 2004.

 Implementation by Charles Donohue,
Based on Mathematica code by Victor Ostromoukhov.
Universite de Montreal
18.08.04
```


## Execution


Parameters:  

	[HELP]
	-o [string=output_pts.dat]	Output file
	-m [int=1]			Number of poinset realisations
	-n [ullint=1024]		Number of samples to generate
	--silent 			Silent mode
	-h 				Displays this help message


To generate a 2D point set of 1024 samples with a penrose distribution, we can use the following client line command:

     ./bin/samplers/Penrose_2dd -n 1024 -o toto.dat

Or one can use the following C++ code:


    PointsetWriter< 2, double, Point<2, double> > writer;
    writer.open("toto.dat");
    Pointset< 2, double, Point<2, double> > pts;
    SamplerPenrose s;
    unsigned int param_nbsamples = 1024;
    s.generateSamples< 2, double, Point<2, double> >(pts, param_nbsamples);
    writer.writePointset(pts);
    writer.close();


Results
=======

     ./bin/samplers/Penrose_2dd -o penrose_1024.edat -n 1024

File  
[penrose_1024.edat](data/penrose/penrose_1024.edat)

Pointset  
[![](data/penrose/penrose_1024.png)](data/penrose/penrose_1024.png)

Fourier  
[![](data/penrose/penrose_1024_fourier.png)](data/penrose/penrose_1024_fourier.png)

     ./bin/samplers/Penrose_2dd -o penrose_4096.edat -n 4096

File  
[penrose_4096.edat](data/penrose/penrose_4096.edat)

Pointset  
[![](data/penrose/penrose_4096.png)](data/penrose/penrose_4096.png)

Fourier  
[![](data/penrose/penrose_4096_fourier.png)](data/penrose/penrose_4096_fourier.png)
