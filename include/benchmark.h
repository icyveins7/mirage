#include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"
#include "implot.h"
#include "implot_internal.h"

#include <iterator>
#include <vector>

template <typename T>
class BenchmarkWindow
{
public:
  void render()
  {
    ImGui::Begin("Benchmark");

    static size_t dataLength = 10000;
    char inputLabel[64];
    snprintf(inputLabel, 64, "Data length (current: %zu)", m_y.size());
    ImGui::InputScalar(inputLabel, ImGuiDataType_U64, &dataLength);
    if (ImGui::Button("Apply"))
    {
      if (dataLength != m_y.size())
      {
        m_y.resize(dataLength);
        m_x.resize(dataLength);
        for (int i = 0; i < m_y.size(); ++i)
        {
          m_x[i] = static_cast<T>(i);
          m_y[i] = std::sin(0.001 * static_cast<T>(i));
        }
      }
    }

    if (ImPlot::BeginPlot("Data"))
    {
      if (!m_y.empty())
        ImPlot::PlotLine("lineplot", m_x.data(), m_y.data(), m_y.size());

      ImPlot::EndPlot();
    }
    ImGui::End();

  };

private:
  std::vector<T> m_x;
  std::vector<T> m_y;
};
