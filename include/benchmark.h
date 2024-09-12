#include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"
#include "implot.h"
#include "implot_internal.h"

#include <vector>

template <typename T>
class BenchmarkWindow
{
public:
  void render()
  {
    ImGui::Begin("Benchmark");

    static size_t dataLength = 10000;
    ImGui::InputScalar("Data length", ImGuiDataType_U64, &dataLength);
    if (dataLength != m_data.size())
      m_data.resize(dataLength);
    ImGui::Text("Current data length: %zu", m_data.size());

    if (ImPlot::BeginPlot("Data"))
    {
      if (!m_data.empty())
        ImPlot::PlotLine("lineplot", m_data.data(), m_data.size());

      ImPlot::EndPlot();
    }
    ImGui::End();

  };

private:
  std::vector<T> m_data;
};
