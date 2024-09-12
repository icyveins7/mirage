#include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"
#include "implot.h"
#include "implot_internal.h"

#include <vector>
#include <GLFW/glfw3.h> // same as main.cpp, use this to drag OpenGL

template <typename T>
class BenchmarkWindow
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
    ImGui::Separator();
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
          (void*)m_imgtexture,
          bmin, bmax
        );
      }
      ImPlot::EndPlot();
    }
    // =================
    ImGui::End();
  };

private:
  std::vector<T> m_x;
  std::vector<T> m_y;

  std::vector<T> m_imgdata;
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
        T val = (i+j) / (2.0*sideLength);
        m_imgdata[i*sideLength + j] = val;
      }
    }

    // Remake the image
    // Create a OpenGL texture identifier
    GLuint m_imgtexture;
    glGenTextures(1, &m_imgtexture);
    glBindTexture(GL_TEXTURE_2D, m_imgtexture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
                 sideLength, // width
                 sideLength, // height
                 0, GL_LUMINANCE, // let's try grayscale for now
                 GL_UNSIGNED_BYTE, m_imgdata.data());

  }
};
