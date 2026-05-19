/*
 * GeometricClassification.h
 *
 *  Created on: May 11, 2026
 *      Author: Tom Teplick
 */

#ifndef GEOMETRICCLASSIFICATION_H_
#define GEOMETRICCLASSIFICATION_H_

#include <string>

// non-zero masses in a plane in the two coordinates
struct PlaneDim
{
	int nrows;
	int ncols;
};

// Type to hold the minimum and maximum data values
struct Endpoints
{
	double xmin;
	double xmax;
	double ymin;
	double ymax;
};

class Geometric
{
	static const int planeDim = 50; // number of cells in a plane in x and y in overview
	static const int nclasses = 19;  // number of classes or geometric objects
	static const int naxes = 3;     // number of axes in Cartesian coordinate system
	char density[planeDim][planeDim][planeDim]; // geometric object 3D densities
	PlaneMass geoRefMass[naxes][planeDim];  // [axis][plane]
	PlaneDim geoRefDims[nclasses][nclasses][planeDim]; // [class][axis][plane]
	double pcError[nclasses];      // classification percent error
	int nsamples;            // #samples to classify
	int noiseLevel;            // noise level in the samples
	bool shift;           // shift the geometric object
	Endpoints endpoints;
	Stats statistics;

	double searchPlaneReferences(int cl, int axis, int plane, int refMassPlane);
	void getPlaneMassError(int cls, int axis, int plane);
	void getAxisMassError(int cls, int axis);
	void tabulateTestResults();
	void displayTestResults();
public:
	static const std::string addr;   // http server listen address
	static const std::string geometricobject; // 3D geometric object file containing the densities, 50x50x50
	static const std::string geometricrefdims;  // dimension of references
	static const std::string dataDir;  // directory for geometric objects
	static const int rows = 300; // rows in canvas
	static const int cols = 300; // columns in canvas
	static const int naxes = 3; // number of axes in Cartesian coordinates
	static const int nplanes = 12; // number of planes per axis (2 rows) in overview
	static const int nplanes2 = nplanes / 2; // number of planes in each row in overview
	static const int axisDim = 100;                        // number of cells in each axis in y direction in overview
	static const double deg2rad; // convert degrees to radians
	static const int classes = 19; // number of classes or geometric objects

	Geometric() = default;
	~Geometric() = default;
	Geometric(const Geometric& geo) = delete;
	Geometric& operator=(const Geometric& geo) = delete;
	Geometric(Geometric&& geo) = delete;
	Geometric& operator=(Geometric&& geo) = delete;
	void classifyGeometric();
};

// masses for a plane in the two coordinates
struct PlaneMass
{
	int row[Geometric::planeDim];
	int col[Geometric::planeDim];
};

// classification results
struct Stats
{
	int correct[Geometric::nclasses]; // % correct classifcation
	int classCount[Geometric::nclasses]; // #samples in each class
};


#endif /* GEOMETRICCLASSIFICATION_H_ */
