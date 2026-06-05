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

<h4>Classification of 100 samples, level 0 noise, 19 geometric objects</h4>

<pre>
C:\Users\Thoma\eclipse-workspace\GeometricClassification\Debug>GeometricClassification.exe
Choose Classify Geometric = 1 or Display Geometric = 2: 1
---------- Geometric Classification Running ----------
Start local time and date: Sat May 30 10:39:12 2026

Enter the number of samples, noise level, and shift, separated by space
50<=[samples]<= 500, 0<=[noise level]<= 9, [0=false|1=true]
For example, '50 3 1'
100 0 0
You entered: 100 0 0
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
|0      |ellipsoidsurface          |5      |100        |
|1      |ellipsoidsolid            |1      |100        |
|2      |plane                     |5      |100        |
|3      |paraboloid                |9      |100        |
|4      |paraboloidsolid           |7      |100        |
|5      |cube                      |2      |100        |
|6      |cone                      |5      |100        |
|7      |conesolid                 |4      |100        |
|8      |box                       |10     |100        |
|9      |hyperbolicparaboloid      |3      |100        |
|10     |cylindersurface           |8      |100        |
|11     |cylindersolid             |7      |100        |
|12     |potentialwell             |8      |100        |
|13     |cardioidrevolution        |3      |100        |
|14     |cardioidrevolutionsolid   |3      |100        |
|15     |lemniscaterevolution      |2      |100        |
|16     |lemniscaterevolutionsolid |4      |100        |
|17     |rose4leafrevolution       |5      |100        |
|18     |rose4leafrevolutionsolid  |9      |100        |
|------------------------------------------------------|
|Totals |                          |100    |100        |
|======================================================|

Finish local time and date: Sun May 31 00:06:26 2026  
</pre>

<h4>Classification of 100 samples, level 3 noise, 19 geometric objects.</h4>

<pre>
C:\Users\Thoma\eclipse-workspace\GeometricClassification\Debug>GeometricClassification.exe
Choose Classify Geometric = 1 or Display Geometric = 2: 1
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

<pre>
C:\Users\Thoma\eclipse-workspace\GeometricClassification\Debug>GeometricClassification.exe
Choose Classify Geometric = 1 or Display Geometric = 2: 1
---------- Geometric Classification Running ----------
Start local time and date: Mon Jun 01 08:06:22 2026

Enter the number of samples, noise level, and shift, separated by space
50<=[samples]<= 500, 0<=[noise level]<= 9, [0=false|1=true]
For example, '50 3 1'
100 5 1
You entered: 100 5 1
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
|0      |ellipsoidsurface          |4      |100        |
|1      |ellipsoidsolid            |8      |100        |
|2      |plane                     |4      |100        |
|3      |paraboloid                |3      |100        |
|4      |paraboloidsolid           |2      |100        |
|5      |cube                      |6      |100        |
|6      |cone                      |4      |100        |
|7      |conesolid                 |9      |100        |
|8      |box                       |8      |100        |
|9      |hyperbolicparaboloid      |4      |0          |
|10     |cylindersurface           |4      |75         |
|11     |cylindersolid             |8      |100        |
|12     |potentialwell             |2      |100        |
|13     |cardioidrevolution        |5      |80         |
|14     |cardioidrevolutionsolid   |5      |100        |
|15     |lemniscaterevolution      |5      |80         |
|16     |lemniscaterevolutionsolid |2      |0          |
|17     |rose4leafrevolution       |9      |100        |
|18     |rose4leafrevolutionsolid  |8      |100        |
|------------------------------------------------------|
|Totals |                          |100    |91         |
|======================================================|

Finish local time and date: Mon Jun 01 23:59:35 2026 
</pre>

<h4>Display Geometric </h4>
<pre>
Choose Classify Geometric = 1 or Display Geometric = 2:  2
</pre>
<img width="1069" height="1024" alt="image" src="https://github.com/user-attachments/assets/8b43c6b3-e1df-4bf5-9c20-947203764ee2" />
<h4>Display Geometric</h4>
<img width="1074" height="1019" alt="image" src="https://github.com/user-attachments/assets/50b87977-aa6d-45ae-a718-dc7b8e507c9b" />

