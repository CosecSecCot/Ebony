#include "Application.h"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace Ebony {

void Application::Run() const {
    std::cerr << "Hello from Ebony!" << std::endl;

    std::ofstream render(std::filesystem::path("./image.ppm"));

    std::cerr << "Render Started!" << std::endl;

    render << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
    for (int j = 0; j < imageHeight; j++) {
        for (int i = 0; i < imageWidth; i++) {
            double r = static_cast<double>(i) / (imageWidth - 1);
            double g = static_cast<double>(j) / (imageHeight - 1);
            double b = 0.0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            render << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::cerr << "Render Finnished!" << std::endl;

    render.close();
}

} // namespace Ebony
