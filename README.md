<h3> 
Classification of Three-dimensional Geometric Objects using C++
</h3>
<p>
This program is written in C++11 and used Eclipse CDE 2025-12 IDE with GCC compiler. 
The program is single-threaded.  The geometric samples are processed in one for loop.
Each axes and plane is also processed in a for loop.  No attempt was made to use C++ concurrency
methods such as thread, mutex, or condition variable to take advantage of the multi-core processor.
</p>

<p>
Geometric Classification classifies the internal structure of 3D geometric objects
such as ellipsoids, parabloids, cubes, boxes, planes, lemniscates, cardiods, four-leaf rose, or cones.
It slices the geometric objects along axial planes in the Cartesian coordinate system.
The object can be solids as well as surfaces.
It gives an overview of the planes in i, j, k axes along with the option
of zooming in on a particular axial plane.  It is possible to select and
view particular planes in the geometric object with different step sizes.
It will classify the geometric object and display the results.  It does this
by comparing the noisy test samples that are displaced randomly in space with
references of the geometric objects that are noise free and centered.  The metrics
are mass sums of the rows and columns of plane in each axes in the Cartesian
coordinate system.  The least square error determines how the sample is classified.
The difference between the reference class mass sums and the test sample is the error.
</p>

<p>
Since the classification involves 3-dimensional searches, it takes a long time to 
finish execution.  For classification of 100 samples of the 19 geometric objects,
it took about 13.5 hours.  The geometric objects are represented by densities which
can be any concentration quantity.  By summing up the row or column densities you
can obtain a quantity proportional to mass.	Thus the row sums and columns sums 
distinguish different geometric objects and can be used to classify the object.
</p>

<h4>Classification of 100 samples, level 3 noise, 19 geometric objects.</h4>

<pre>
---------- Geometric Classification Running ----------
Start local time and date: Sun May 31 11:55:40 2026

Enter the number of samples, noise level, and shift, separated by space
50<=[samples]<= 500, 0<=[noise level]<= 9, [0=false|1=true]
For example, '50 3 1'
100 3 1
You entered: 100 3 1
Geometric geo constructed, start classifyGeometric
classifyGeometric, start loop over the samples

**************************************************
**************************************************

leaving classifyGeometric
tabulateTestResults
displayTestResults

|======================================================|
|Class  |Geometric                 |Count  |Correct (%)|
|=======|==========================|=======|===========|
|0      |ellipsoidsurface          |8      |100        |
|1      |ellipsoidsolid            |2      |100        |
|2      |plane                     |5      |100        |
|3      |paraboloid                |7      |100        |
|4      |paraboloidsolid           |5      |100        |
|5      |cube                      |5      |100        |
|6      |cone                      |3      |100        |
|7      |conesolid                 |8      |100        |
|8      |box                       |7      |100        |
|9      |hyperbolicparaboloid      |6      |100        |
|10     |cylindersurface           |9      |100        |
|11     |cylindersolid             |4      |100        |
|12     |potentialwell             |1      |100        |
|13     |cardioidrevolution        |2      |100        |
|14     |cardioidrevolutionsolid   |5      |100        |
|15     |lemniscaterevolution      |9      |100        |
|16     |lemniscaterevolutionsolid |5      |40         |
|17     |rose4leafrevolution       |6      |83         |
|18     |rose4leafrevolutionsolid  |3      |100        |
|------------------------------------------------------|
|Totals |                          |100    |96         |
|======================================================|

Finish local time and date: Mon Jun 01 01:10:43 2026
</pre>
<h4>Classification of 100 samples, level 5 noise, 19 geometric objects.</h4>
