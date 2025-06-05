#pragma once

#include "imgui.h"
#include "implot.h"
#include "implot_internal.h"

#include <cmath>
#include <vector>

namespace benchmarks
{

template <typename T>
class BenchmarkLines
{
public:
  void render()
  {
    ImGui::Begin("Benchmark Line");
    // =================

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

    // =================
    ImGui::End();
  };

private:
  std::vector<T> m_x;
  std::vector<T> m_y;

};

template <typename T>
class BenchmarkScatter
{
public:
  void render() {
    ImGui::Begin("Benchmark Scatter");
    // =================

    char inputLabel[64];
    snprintf(inputLabel, 64, "Side length (current: %zu)", (size_t)std::sqrt(m_y.size()));
    ImGui::InputScalar(inputLabel, ImGuiDataType_U64, &m_sideLength);
    if (ImGui::Button("Apply"))
    {
      if (m_sideLength * m_sideLength != m_y.size())
      {
        printf("Resized scatter vectors\n");
        m_y.resize(m_sideLength * m_sideLength);
        m_x.resize(m_sideLength * m_sideLength);
        for (int i = 0; i < m_sideLength; ++i)
        {
          for (int j = 0; j < m_sideLength; ++j)
          {
            m_x[i * m_sideLength + j] = static_cast<T>(i);
            m_y[i * m_sideLength + j] = static_cast<T>(j);
          }
        }
      }
    }

    if (ImPlot::BeginPlot("Data"))
    {
      if (!m_y.empty())
        ImPlot::PlotScatter("scatterplot", m_x.data(), m_y.data(), m_y.size());

      ImPlot::EndPlot();
    }

    // =================
    ImGui::End();
  };

private:
  size_t m_sideLength = 100;
  std::vector<T> m_x;
  std::vector<T> m_y;

};

}// namespace benchmarks
