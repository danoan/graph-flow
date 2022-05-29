#include <iostream>
#include <opencv2/highgui.hpp>
#include <queue>

#include "GUIControl.h"
#include "InputData.h"

using namespace SeedSelector;

void print_instructions() {
  std::cout << "***Seed selector instructions***\n\n"
            << "Press p to select the region containing the object to be segmented\n"
            << "Press f to change to foreground mode and select foreground seeds\n"
            << "Press b to change to background mode and select the background image seeds\n"
            << "Press r to erase the seeds in the current mode\n"
            << "Press + to increase the pen width\n"
            << "Press - to decrease the pen width\n"
            << "Press s to save the masks\n"
            << "Press q to quit the seed selector interface\n\n";
}

void handleEvent(int key, GUIData& gd, bool& onExecution) {
  switch (key) {
    case 'p': {
      probablyForegroundCallback(1, &gd);
      break;
    }
    case 'f': {
      foregroundCallback(1, &gd);
      break;
    }
    case 'b': {
      backgroundCallback(1, &gd);
      break;
    }
    case 'r': {
      restartCallback(1, &gd);
      break;
    }
    case 's': {
      saveCallback(1, &gd);
      break;
    }
    case 'q': {
      onExecution = false;
      break;
    }
    case '+': {
      gd.penWidth += gd.penWidth < 255 ? 1 : 0;
      displayStatusBar(gd);
      break;
    }
    case '-': {
      gd.penWidth -= gd.penWidth > 0 ? 1 : 0;
      displayStatusBar(gd);
      break;
    }
  }
}

void testMode(const std::string& testModeString, GUIData& gd) {
  bool onExecution = true;
  for (char c : testModeString) {
    int key = (int)c;
    handleEvent(key, gd, onExecution);
    if (onExecution == false) break;
    refreshWindow(gd);
  }
}

int main(int argc, char* argv[]) {
  InputData id = readInput(argc, argv);
  print_instructions();

  GUIData gd = GUIData::initGUIData("RefineSeed", id.outputFolder, id.imagePath,
                                    id.once);
  cv::namedWindow(gd.windowName);

  if (!id.segImageMask.empty()) gd.loadContours(id.segImageMask);

  gd.loadPbFgMask(id.unknownImageMask);
  gd.loadFgMask(id.fgImageMask);
  gd.loadBgMask(id.bgImageMask);

  cv::createButton("Probably Foreground", probablyForegroundCallback, &gd,
                   cv::QT_RADIOBOX, true);
  cv::createButton("Foreground", foregroundCallback, &gd, cv::QT_RADIOBOX,
                   false);
  cv::createButton("Background", backgroundCallback, &gd, cv::QT_RADIOBOX,
                   false);
  cv::createButton("Restart", restartCallback, &gd);

  cv::createButton("Save", saveCallback, &gd);

  displayStatusBar(gd);
  setRectMouseCallback(gd);

  if (id.testModeFlag)
    testMode(id.testModeString, gd);
  else {
    bool onExecution = true;
    while (onExecution) {
      int key = cv::waitKey(10);
      handleEvent(key, gd, onExecution);
      refreshWindow(gd);
    }
  }

  cv::destroyWindow(gd.windowName);

  return 0;
}