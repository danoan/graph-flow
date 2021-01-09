#ifndef GRAPHFLOW_UTILS_DIGITAL_MORPHOLOGY_H
#define GRAPHFLOW_UTILS_DIGITAL_MORPHOLOGY_H

#include <DGtal/helpers/StdDefs.h>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "types/StructuringElement.h"
#include "graph-flow/utils/digital/representation.h"

/**
 * \brief Basic morphological operations over DGtal DigitalSet models.
 *
 * It operates on grayscale images only.
 * \author Daniel Martins Antunes
 * \version 0.1
 * \date 2018/08/27
 */
namespace GraphFlow::Utils::Digital::Morphology {
typedef DGtal::Z2i::DigitalSet DigitalSet;
const int IMG_TYPE = CV_8UC1;  // Limited to grayscale images only.

/**
 * \brief Morphological dilation of digital set model.
 * @param dsOut DGtal digital set model output.
 * @param dsIn DGtal digital set model input.
 * @param se Structuring element used for dilation.
 * @param it Number of times dilation is executed.
 */
void dilate(DigitalSet &dsOut, const DigitalSet &dsIn,
            const StructuringElement se, size_t it = 1);

/**
 * \brief Morphological erosion of digital set model.
 * @param dsOut DGtal digital set model output.
 * @param dsIn DGtal digital set model input.
 * @param se Structuring element used for erosion.
 * @param it Number of erosion execution.
 */
void erode(DigitalSet &dsOut, const DigitalSet &dsIn,
           const StructuringElement se, size_t iterations = 1);

void dilate(DigitalSet& dsOut, const DigitalSet& ds, size_t size=1);

void erode(DigitalSet& dsOut, const DigitalSet& ds, size_t size=1);

}  // namespace GraphFlow::Utils::Digital::Morphology

#endif