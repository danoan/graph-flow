#ifndef GRAPH_FLOW_GRABCUT_GRABCUTOUTPUT_H
#define GRAPH_FLOW_GRABCUT_GRABCUTOUTPUT_H

namespace GrabCut {
struct GrabCutOutput {
  cv::Mat grabCutMask;
  cv::Mat segMaskResult;
};
}  // namespace GrabCut

#endif  // GRAPH_FLOW_GRABCUT_GRABCUTOUTPUT_H
