#include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"
#include "implot.h"
#include "implot_internal.h"

#include <vector>
#include <GLFW/glfw3.h> // same as main.cpp, use this to drag OpenGL

template <typename T>
class BenchmarkLines
{
public:
  void render()
  {
    ImGui::Begin("Benchmark");
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

class BenchmarkImage
{
public:
  void render()
  {
    ImGui::Begin("BenchmarkImage");
    // =================

    static size_t sideLength = 1000;
    char sideLenInputLabel[64];
    snprintf(sideLenInputLabel, 64, "Side length (current size: %zu)", m_imgdata.size());
    ImGui::InputScalar(sideLenInputLabel, ImGuiDataType_U64, &sideLength);

    if (ImGui::Button("Apply##img"))
    {
      if (sideLength*sideLength != m_imgdata.size())
      {
        m_imgdata.resize(sideLength*sideLength);

        createImage(sideLength);


      }

    }

    static ImVec2 bmin(0,0);
    static ImVec2 bmax(1,1);
    if (ImPlot::BeginPlot("Image"))
    {
      if (!m_imgdata.empty())
      {
        ImPlot::PlotImage(
          "test image",
          reinterpret_cast<void*>(m_imgtexture),
          bmin, bmax
        );
      }
      ImPlot::EndPlot();
    }

    // // use original imgui
    // if (!m_imgdata.empty())
    // {
    //   ImGui::Image(reinterpret_cast<void*>(m_imgtexture), ImVec2(sideLength, sideLength));
    //   // ImGui::Image((ImTextureID)(intptr_t)m_imgtexture, ImVec2(sideLength, sideLength));
    // }

    // =================
    ImGui::End();
  }

private:
  std::vector<float> m_imgdata;
  GLuint m_imgtexture;


  void createImage(size_t sideLength){
    printf("createImage %zd\n", sideLength);
    /*
    Want a diagonal gradient, with brightest spot at top right.
    */
    for (size_t i = 0; i < sideLength; ++i)
    {
      for (size_t j = 0; j < sideLength; ++j)
      {
        // T val = static_cast<T>(std::sqrt(i*i + j*j) / std::sqrt(sideLength*sideLength));
        float val = (i+j) / (2.0*sideLength);
        m_imgdata[i*sideLength + j] = val;
      }
    }

    // Remake the image
    // Create a OpenGL texture identifier
    // GLuint m_imgtexture;
    glGenTextures(1, &m_imgtexture);
    glBindTexture(GL_TEXTURE_2D, m_imgtexture);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                 sideLength, // width
                 sideLength, // height
                 // 0, GL_LUMINANCE, // let's try grayscale for now (this seems like it's obsolete)
                 0, GL_RED, // let's try grayscale for now
                 GL_FLOAT, m_imgdata.data());

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  }
};

template <typename T>
class BenchmarkHeatmap
{
public:
  void render()
  {
    ImGui::Begin("BenchmarkHeatmap");

    static size_t width = 100;
    static size_t height = 100;
    ImGui::InputScalar("Width##heatmap", ImGuiDataType_U64, &width);
    ImGui::InputScalar("Height##heatmap", ImGuiDataType_U64, &height);

    if (ImGui::Button("Apply##heatmap"))
    {
      if (width != m_width || height != m_height)
      {
        m_width = width;
        m_height = height;
        m_heatmapData.resize(width*height);

        prepareHeatmap();
      }
    }

    if (ImPlot::BeginPlot("##Heatmap1")) //,ImVec2(225,225),ImPlotFlags_NoLegend|ImPlotFlags_NoMouseText)) 
    {
      if (!m_heatmapData.empty())
      {

        // ImPlot::SetupAxes(nullptr, nullptr, axes_flags, axes_flags);
        // ImPlot::SetupAxisTicks(ImAxis_X1,0 + 1.0/14.0, 1 - 1.0/14.0, 7, xlabels);
        // ImPlot::SetupAxisTicks(ImAxis_Y1,1 - 1.0/14.0, 0 + 1.0/14.0, 7, ylabels);
        // ImPlot::PlotHeatmap("heat",values1[0],7,7,scale_min,scale_max,"%g",ImPlotPoint(0,0),ImPlotPoint(1,1),hm_flags);

        ImPlot::PlotHeatmap("heatmap", m_heatmapData.data(), m_width, m_height,
                            0, 0, "%g");
      }
      ImPlot::EndPlot();
    }


    // =================
    ImGui::End();
  }


private:
  size_t m_width;
  size_t m_height;
  std::vector<T> m_heatmapData;

  void prepareHeatmap()
  {
    printf("prepareHeatmap %zd x %zd\n", m_width, m_height);
    /*
    Want a diagonal gradient, with brightest spot at top right.
    */
    for (size_t i = 0; i < m_width; ++i)
    {
      for (size_t j = 0; j < m_height; ++j)
      {
        // T val = static_cast<T>(std::sqrt(i*i + j*j) / std::sqrt(sideLength*sideLength));
        if (i < j)
          m_heatmapData[j*m_width + i] = 0.0;
        else
          m_heatmapData[j*m_width + i] = (i+j);
      }
    }

  }

};
