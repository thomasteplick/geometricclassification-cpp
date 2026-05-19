//============================================================================
// Name        : runclassification.cpp
// Author      : Tom Teplick
// Version     :
// Copyright   : ThomasTeplick
// Description : GeometricClassification in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <limits>
#include "geometric3D.h"
#include "runclassification.h"

// static constant members
const std::string Geometric::addr = "127.0.0.1:8080";   // http server listen address
const std::string Geometric::geometricobject = "geometricobject.txt"; // 3D geometric object file containing the densities, 50x50x50
const std::string Geometric::geometricrefdims = "geometricrefdim.txt";  // dimension of references
const std::string Geometric::dataDir = "data/";  // directory for geometric objects
const double Geometric::deg2rad = 3.14159265358979 / 180.0; // convert degrees to radians

extern const char *geometricObjects[];

// Find the reference mass plane with the least square error
double Geometric::searchPlaneReferences(int cls, int axis, int plane, int refMassPlane)
{
	/*  Find the square error between the reference mass and the sample
		There are five sections to consider:  the section with reference mass (1)
		and all others (4).  If the reference has no mass, then the squared error
		is just the square of all the mass in this sample; otherwise take the
	    difference between the reference and the sample and square it.
	*/


	struct SrchBnds {
		int rowStart;
		int rowEnd;
		int colStart;
		int colEnd;
	};

	// get the bounds (number of rows and columns) for this refMass plane
	int nrows = geoRefDims[cls][axis][refMassPlane].nrows;
	int ncols = geoRefDims[cls][axis][refMassPlane].ncols;
	int rowShifts = planeDim - nrows;
	int colShifts = planeDim - ncols;

	double minSqErr = std::numeric_limits<double>::max();

	// shift the reference mass over the sample and find the shift having the min sq error
	// the allowable number of shifts is determined by the reference bounds
	switch (axis) {
	case 0:
		// if no reference plane mass, then error is the square of the row and col sums
		if (nrows == 0) {
			int minSqErr = 0;
			for k := range rowShifts {
				for m := range colShifts {
					minSqErr += int(geo.density[plane][k][m] * geo.density[plane][k][m])
				}
			}
			for m := range colShifts {
				for k := range rowShifts {
					minSqErr += int(geo.density[plane][k][m] * geo.density[plane][k][m])
				}
			}
			return double(minSqErr);
		}

		// We have reference plane mass
		for i := range rowShifts {
			for j := range colShifts {
				section := [4]SrchBnds{
					{
						rowStart: 0,
						rowEnd:   i,
						colStart: 0,
						colEnd:   planeDim,
					},
					{
						rowStart: i,
						rowEnd:   i + nrows,
						colStart: 0,
						colEnd:   j,
					},
					{
						rowStart: i,
						rowEnd:   i + nrows,
						colStart: j + ncols,
						colEnd:   planeDim,
					},
					{
						rowStart: i + nrows,
						rowEnd:   planeDim,
						colStart: 0,
						colEnd:   planeDim,
					},
				}

				// These sections are outside the reference mass boundary and
				// the error only consists of the sample mass
				sqErr := 0
				for secn := range section {
					for row := section[secn].rowStart; row < section[secn].rowEnd; row++ {
						for col := section[secn].colStart; col < section[secn].colEnd; col++ {
							sqErr += int(geo.density[plane][row][col] * geo.density[plane][row][col])
						}
					}
				}

				// this section contains reference mass so find the squared difference
				// between the reference mass and the sample

				// sum the rows
				for k := range geo.geoRefDims[class][axis][refMassPlane].nrows {
					rowsum := 0
					for m := range geo.geoRefDims[class][axis][refMassPlane].ncols {
						rowsum += int(geo.density[plane][k+i][m+j])
					}
					diff := geo.geoRefMass[axis][refMassPlane].row[k] - rowsum
					sqErr += diff * diff
				}
				// sum the columns and find the squared difference from reference
				for m := range geo.geoRefDims[class][axis][refMassPlane].ncols {
					colsum := 0
					for k := range geo.geoRefDims[class][axis][refMassPlane].nrows {
						colsum += int(geo.density[plane][k+i][m+j])
					}
					diff := geo.geoRefMass[axis][refMassPlane].col[m] - colsum
					sqErr += diff * diff
				}
				if float64(sqErr) < minSqErr {
					minSqErr = float64(sqErr)
				}
			}
		}
		return double(minSqErr);
	case 1:
		// if no reference plane mass, then error is the square of the row and col sums
		if nrows == 0 {
			minSqErr := 0
			for k := range rowShifts {
				for m := range colShifts {
					minSqErr += int(geo.density[k][plane][m] * geo.density[plane][k][m])
				}
			}
			for m := range colShifts {
				for k := range rowShifts {
					minSqErr += int(geo.density[k][plane][m] * geo.density[plane][k][m])
				}
			}
			return double(minSqErr);
		}

		// We have reference plane mass
		for i := range rowShifts {
			for j := range colShifts {
				section := [4]SrchBnds{
					{
						rowStart: 0,
						rowEnd:   i,
						colStart: 0,
						colEnd:   planeDim,
					},
					{
						rowStart: i,
						rowEnd:   i + nrows,
						colStart: 0,
						colEnd:   j,
					},
					{
						rowStart: i,
						rowEnd:   i + nrows,
						colStart: j + ncols,
						colEnd:   planeDim,
					},
					{
						rowStart: i + nrows,
						rowEnd:   planeDim,
						colStart: 0,
						colEnd:   planeDim,
					},
				}

				// These sections are outside the reference mass boundary and
				// the error only consists of the sample mass
				sqErr := 0
				for secn := range section {
					for row := section[secn].rowStart; row < section[secn].rowEnd; row++ {
						for col := section[secn].colStart; col < section[secn].colEnd; col++ {
							sqErr += int(geo.density[row][plane][col] * geo.density[row][plane][col])
						}
					}
				}

				// this section contains reference mass so find the squared difference
				// between the reference mass and the sample

				// sum the rows
				for k := range geo.geoRefDims[class][axis][refMassPlane].nrows {
					rowsum := 0
					for m := range geo.geoRefDims[class][axis][refMassPlane].ncols {
						rowsum += int(geo.density[k+i][plane][m+j])
					}
					diff := geo.geoRefMass[axis][refMassPlane].row[k] - rowsum
					sqErr += diff * diff
				}
				// sum the columns and find the squared difference from reference
				for m := range geo.geoRefDims[class][axis][refMassPlane].ncols {
					colsum := 0
					for k := range geo.geoRefDims[class][axis][refMassPlane].nrows {
						colsum += int(geo.density[k+i][plane][m+j])
					}
					diff := geo.geoRefMass[axis][refMassPlane].col[m] - colsum
					sqErr += diff * diff
				}
				if float64(sqErr) < minSqErr {
					minSqErr = float64(sqErr)
				}
			}
		}
		return double(minSqErr);
	case 2:
		// if no reference plane mass, then error is the square of the row and col sums
		if nrows == 0 {
			minSqErr := 0
			for k := range rowShifts {
				for m := range colShifts {
					minSqErr += int(geo.density[k][m][plane] * geo.density[plane][k][m])
				}
			}
			for m := range colShifts {
				for k := range rowShifts {
					minSqErr += int(geo.density[k][m][plane] * geo.density[plane][k][m])
				}
			}
			return float64(minSqErr);
		}

		// We have reference plane mass
		for i := range rowShifts {
			for j := range colShifts {
				section := [4]SrchBnds{
					{
						rowStart: 0,
						rowEnd:   i,
						colStart: 0,
						colEnd:   planeDim,
					},
					{
						rowStart: i,
						rowEnd:   i + nrows,
						colStart: 0,
						colEnd:   j,
					},
					{
						rowStart: i,
						rowEnd:   i + nrows,
						colStart: j + ncols,
						colEnd:   planeDim,
					},
					{
						rowStart: i + nrows,
						rowEnd:   planeDim,
						colStart: 0,
						colEnd:   planeDim,
					},
				}

				// These sections are outside the reference mass boundary and
				// the error only consists of the sample mass
				sqErr := 0
				for secn := range section {
					for row := section[secn].rowStart; row < section[secn].rowEnd; row++ {
						for col := section[secn].colStart; col < section[secn].colEnd; col++ {
							sqErr += int(geo.density[row][col][plane] * geo.density[row][col][plane])
						}
					}
				}

				// this section contains reference mass so find the squared difference
				// between the reference mass and the sample

				// sum the rows
				for k := range geo.geoRefDims[class][axis][refMassPlane].nrows {
					rowsum := 0
					for m := range geo.geoRefDims[class][axis][refMassPlane].ncols {
						rowsum += int(geo.density[k+i][m+j][plane])
					}
					diff := geo.geoRefMass[axis][refMassPlane].row[k] - rowsum
					sqErr += diff * diff
				}

				// sum the columns and find the squared difference from reference
				for m := range geo.geoRefDims[class][axis][refMassPlane].ncols {
					colsum := 0
					for k := range geo.geoRefDims[class][axis][refMassPlane].nrows {
						colsum += int(geo.density[k+i][m+j][plane])
					}
					diff := geo.geoRefMass[axis][refMassPlane].col[m] - colsum
					sqErr += diff * diff
				}

				if float64(sqErr) < minSqErr {
					minSqErr = float64(sqErr)
				}
			}
		}
		return double(minSqErr);
	default:
		fmt.Printf("invalid axis chosen: %d\n", axis)
        return 0.0;
    }
}

// get min sq error for this plane
void Geometric::getPlaneMassError(int cls, int axis, int plane)
{
	/*
		Loop over all geoRefMass planes for this class, axis, and plane.  Call searchPlaneReferences()
		to find minimum square error.
	*/
	minSqErr := math.MaxFloat64
	for refMassPlane := range planeDim {
		sqErr := geo.searchPlaneReferences(class, axis, plane, refMassPlane)
		if sqErr < minSqErr {
			minSqErr = sqErr
		}
	}
	planeErrorChan <- minSqErr
}

// compute min square error for all planes in this axis and return via channel
void Geometric::getAxisMassError(int cls, int axis)
{
	// loop over planes and get plane mass errors using goroutines and channel
	planeErrorChan := make(chan float64)
	for plane := range planeDim {
		// each goroutine finds the minimum square error for its assigned plane
		go geo.getPlaneMassError(class, axis, plane, planeErrorChan)
	}

	// sum the plane square errors
	minSqError := 0.0
	for range planeDim {
		minSqError += <-planeErrorChan
	}

	// send the plane square error to caller
	axisErrorChan <- minSqError
}

// Construct a Geometric instance for classification
Geometric::Geometric()
{
	// get number of samples
	txt := r.FormValue("samples")
	if len(txt) == 0 {
		plot.Status = "Enter number of samples and noise level"
		// Write to HTTP using template and grid
		if err := tmplGeometricClassification.Execute(w, plot); err != nil {
			log.Fatalf("Write to HTTP output using template with error: %v\n", err)
		}
		return
	}

	// get noise level
	txt := r.FormValue("noiselevel")
	if len(txt) == 0 {
		fmt.Printf("enter noise level\n")
		return nil, fmt.Errorf("enter noise level")
	}

	noiseLevel, err := strconv.Atoi(txt)
	if err != nil {
		fmt.Printf("noiseLevel int conversion error: %v\n", err)
		return nil, fmt.Errorf("noiseLevel int conversion error: %v", err.Error())
	}

	// get shift
	txt = r.FormValue("shiftgeometric")
	shift := false
	if txt == "shiftgeometric" {
		shift = true
	}

	// allocate memory for containers

	densities := make([][][]byte, planeDim)
	for i := range densities {
		densities[i] = make([][]byte, planeDim)
		for j := range densities[i] {
			densities[i][j] = make([]byte, planeDim)
		}
	}

	planeMass := make([][]PlaneMass, naxes)
	for i := range planeMass {
		planeMass[i] = make([]PlaneMass, planeDim)
	}

	planeDims := make([][][]PlaneDim, classes)
	for i := range planeDims {
		planeDims[i] = make([][]PlaneDim, naxes)
		for j := range planeDims[i] {
			planeDims[i][j] = make([]PlaneDim, planeDim)
		}
	}

	fdim, err := os.Open(filepath.Join(dataDir, geometricrefdims))
	if err != nil {
		fmt.Printf("open %s error: %v\n", geometricrefdims, err.Error())
		return nil, fmt.Errorf("open %s error: %v", geometricrefdims, err.Error())
	}
	defer fdim.Close()

	// read in the geometric reference dimensions in order:
	// [class][axis][plane]planeDim
	// class 0, 1, ..., classes-1
	// axis 0, 1, 2
	// plane0 nrows,ncols
	// ...
	// plane49 nrows,ncols
	nrows := 0
	ncols := 0
	for i := range planeDims {
		for j := range planeDims[i] {
			for k := range planeDims[i][j] {
				fmt.Fscanf(fdim, "%d %d\n", &nrows, &ncols)
				planeDims[i][j][k] = PlaneDim{nrows: nrows, ncols: ncols}
			}
		}
	}

	geo := Geometric{
		plot:       plot,
		density:    densities,
		nsamples:   nsamples,
		noiseLevel: noiseLevel,
		shift:      shift,
		Endpoints: Endpoints{
			ymin: 0.0,
			ymax: 100.0,
			xmin: 0,
			xmax: float64(classes - 1),
		},
		pcError: make([]float64, classes),
		statistics: Stats{
			correct:    make([]int, classes),
			classCount: make([]int, classes)},
		geoRefMass: planeMass,
		geoRefDims: planeDims,
	}
}

// classify the geometric objects
void Geometric::classifyGeometric()
{
	// communicate results of mass error from each axis/plane
	axisError := make(chan float64)

	// loop over the number of samples
	for range geo.nsamples {
		// min sq mass error
		minSqError := math.MaxFloat64
		// class with min sq error
		minClass := 0
		// generate a geometric object with noise level and shift using geoRefDims
		ngeometricObj := rand.Intn(classes)
		geometricObj := geometricObjects[ngeometricObj]
		geometricObject.CreateObject(geometricObj, geo.noiseLevel, geo.shift)

		// Open the geometric object file containing the densities
		fgeometric, err := os.Open(filepath.Join(dataDir, geometricobject))
		if err != nil {
			fmt.Printf("Open file %s error: %v\n", geometricobject, err)
			return fmt.Errorf("Open file %s error: %v\n", geometricobject, err.Error())
		}

		// Read the geometric object file containing the densities
		for i := range planeDim {
			for j := range planeDim {
				for k := range planeDim - 1 {
					_, err := fmt.Fscanf(fgeometric, "%d", &geo.density[i][j][k])
					if err != nil {
						fmt.Printf("Fscanf 1 for densities[%d][%d][%d] error: %v\n", i, j, k, err.Error())
						return fmt.Errorf("function Fscanf 1 for densities[%d][%d][%d] error: %v", i, j, k, err.Error())
					}
				}
				_, err := fmt.Fscanf(fgeometric, "%d\n", &geo.density[i][j][planeDim-1])
				if err != nil {
					fmt.Printf("Fscanf 2 for densities[%d][%d] newline error: %v\n", i, j, err.Error())
					return fmt.Errorf("function Fscanf 2 for densities[%d][%d][%d] newline error: %v", i, j, planeDim-1, err.Error())
				}
			}
		}
		fgeometric.Close()

		// loop over geometric references and open one at a time
		for class, obj := range geometricObjects {
			// read geometric reference mass sums into memory for this class reference only
			fgeoref, err := os.Open(filepath.Join(dataDir, obj+".txt"))
			if err != nil {
				fmt.Printf("open %s error: %v\n", geometricObj, err.Error())
				return fmt.Errorf("open %s error: %v", geometricObj, err.Error())
			}
			for axes := range geo.geoRefMass {
				for plane := range geo.geoRefMass[axes] {
					nrows := geo.geoRefDims[class][axes][plane].nrows
					if nrows == 1 {
						fmt.Fscanf(fgeoref, "%d\n", &geo.geoRefMass[axes][plane].row[0])
					} else if nrows > 1 {
						for m := range nrows - 1 {
							fmt.Fscanf(fgeoref, "%d", &geo.geoRefMass[axes][plane].row[m])
						}
						fmt.Fscanf(fgeoref, "%d\n", &geo.geoRefMass[axes][plane].row[nrows-1])
					}

					ncols := geo.geoRefDims[class][axes][plane].ncols
					if ncols == 1 {
						fmt.Fscanf(fgeoref, "%d\n", &geo.geoRefMass[axes][plane].col[0])
					} else if ncols > 1 {
						for n := range ncols - 1 {
							fmt.Fscanf(fgeoref, "%d", &geo.geoRefMass[axes][plane].col[n])
						}
						fmt.Fscanf(fgeoref, "%d\n", &geo.geoRefMass[axes][plane].col[ncols-1])
					}
				}
			}
			// close file
			fgeoref.Close()

			// find minimum mass error over rowsums and colsums for all axes and planes
			// launch goroutines for each axis and each plane :  3*50 goroutines
			// use channel communication between goroutines
			// use geoRefDims for shifting the object inside the planes
			for axes := range naxes {
				go geo.getAxisMassError(class, axes, axisError)
			}

			sqerr := 0.0
			for range naxes {
				sqerr += <-axisError
			}
			if sqerr < minSqError {
				minSqError = sqerr
				minClass = class
			}
		}

		// store geometric class count and correct classification
		geo.statistics.classCount[ngeometricObj]++
		if minClass == ngeometricObj {
			geo.statistics.correct[ngeometricObj]++
		}
	}
}

// insert test results into table for display
void Geometric::tabulateTestResults()
{
	geo.plot.TestResults = make([]Results, classes)

	totalCount := 0
	totalCorrect := 0
	classCount := 0
	// tabulate TestResults by converting numbers to string in Results
	for i := range geo.plot.TestResults {
		classCount = geo.statistics.classCount[i]
		totalCount += classCount
		totalCorrect += geo.statistics.correct[i]
		if classCount > 0 {
			geo.plot.TestResults[i] = Results{
				Class:     strconv.Itoa(i),
				Geometric: geometricObjects[i],
				Count:     strconv.Itoa(classCount),
				Correct:   strconv.Itoa(geo.statistics.correct[i] * 100 / classCount),
			}
		} else {
			geo.plot.TestResults[i] = Results{
				Class:     strconv.Itoa(i),
				Geometric: geometricObjects[i],
				Count:     strconv.Itoa(classCount),
				Correct:   "0",
			}
		}
	}
	geo.plot.TotalCount = strconv.Itoa(totalCount)
	geo.plot.TotalCorrect = strconv.Itoa(totalCorrect * 100 / totalCount)
	geo.plot.Status = "Geometric classification results completed."

	return nil
}

void Geometric::displayTestResults()
{
	// Show index, geometric name, class count, and %correct for each geometric class
	// Show totals

}

void handleGeometricClassification()
{
	// initialize random number generator
	std::srand(std::time(0));
	// Create geometric3D instance
	// Create geometric references if they don't exist by calling geometric3D member, create a Geometric object
	// Construct a Geometric instance for classification, pass number of samples and noise level
	// Call the private classifygeometric Geometric member
	// Call the private tabulate test results Geometric member
	// Call the private Display test results Geometric member
}


int main() 
{
	// call handleGeometricClassification() in try/catch
	try {
	    handleGeometricClassification();
	}
	catch(std::runtime_error &re) {
		std::cout << "runtime error: " << re.what() << std::endl;
		return 1;
	}
	catch (std::exception &e)
	{
		std::cout << "standard exception: " << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cout << "unknown error" << std::endl;
	}
	return 0;
}

