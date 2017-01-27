#include <cstdlib>
#include "Application.h"
#include "CubeRenderer.h"
#include "TriangleRenderer.h"
#include "Renderers/Round/RoundRenderer.h"

int main(int argc, const char *argv[])
{
    OpenGL::Application app("OpenGL Learning", 800, 800);
    app.SetRenderer(new OpenGL::Renderers::RoundRenderer());
    app.Run();
    return EXIT_SUCCESS;
}
