#ifndef GRAPH_FLOW_SUMMARY_FLOW_SUMMARY_FLOW_COLORSCHEME_H
#define GRAPH_FLOW_SUMMARY_FLOW_SUMMARY_FLOW_COLORSCHEME_H

#include <DGtal/io/Color.h>

#include <initializer_list>

namespace SummaryFlow {
class ColorSchemeIterator {
 private:
  typedef DGtal::Color Color;
  typedef std::vector<Color> Container;
  typedef Container::const_iterator Iterator;

 public:
  ColorSchemeIterator(const Container& container);

  void operator++();
  void operator++(int);
  Color operator*() const;

 private:
  const Container& container;
  Iterator it;
};

class ColorScheme {
 public:
  typedef DGtal::Color Color;

 public:
  ColorScheme();
  ColorScheme(const Color& first, const Color& last, const Color& extra,
              std::initializer_list<Color> colorList);

  ColorSchemeIterator begin() const;
  Color first() const { return m_first; }
  Color last() const { return m_last; }
  Color extra() const { return m_extra; }

 private:
  std::vector<Color> m_colorVector;

  Color m_first;
  Color m_last;
  Color m_extra;
};

namespace DefaultColorSchemes {
extern ColorScheme Classic;
extern ColorScheme RainyJungle;
extern ColorScheme Lollipop;
}  // namespace DefaultColorSchemes

}  // namespace SummaryFlow

#endif  // GRAPH_FLOW_SUMMARY_FLOW_COLORSCHEME_H
