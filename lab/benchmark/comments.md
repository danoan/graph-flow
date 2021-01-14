# Benchmark comments

<img alt="Last benchmark" src="https://github.com/danoan/graph-flow/blob/master/lab/benchmark/last-benchmark.png" height="600" />

## v0.2.5
There is a nitid increase in the execution time for the shape evolution application. That is due to the use of the more general contour detection function `extractAll2DSCellContours`.

Previously, we used a function that assumed that the genus of the shape was zero.

An issue was opened in order to track the contour points between iterations and avoid the call to `extractAll2DSCellContours` every time.

## v0.2.4
No apparent change in execution time for this version.

## v0.2.3
The remove of BTools dependency resulted in an important reduction in execution time.

## v0.2.2
No apparent change in execution time for this version.

## v0.2.1
No apparent change in execution time for this version.
