# Benchmark comments

<img alt="Last benchmark" src="https://github.com/danoan/graph-flow/blob/master/lab/benchmark/last-benchmark.png" width="400" /><img alt="Last benchmark" src="https://github.com/danoan/graph-flow/blob/master/lab/benchmark/last-benchmark-contour-correction.png" width="400" />

## v0.2.8
Slightly regression in running time for shape-evolution. Investigate if changes in the graph construction is the culprit. On the other hand, we had a slightly improve in running time for contour-correction.

## v0.2.7
There is a nitid decrease in the execution time for the shape evolution application. That is due to the use of the faster `extractAll2DSCellContoursFromMask` implementation.

## v0.2.6
No significant change in execution time for this version.

## v0.2.5
There is a nitid increase in the execution time for the shape evolution application. That is due to the use of the more general contour detection function `extractAll2DSCellContours`.

Previously, we used a function that assumed that the genus of the shape was zero.

An issue was opened in order to track the contour points between iterations and avoid the call to `extractAll2DSCellContours` every time.

## v0.2.4
No significant change in execution time for this version.

## v0.2.3
The remove of BTools dependency resulted in an important reduction in execution time.

## v0.2.2
No significant change in execution time for this version.

## v0.2.1
No significant change in execution time for this version.
