#include <cstdlib>
#include "Application.h"
#include "CubeRenderer.h"
#include "TriangleRenderer.h"

int main(int argc, const char *argv[])
{
    OpenGL::Application app("OpenGL Learning", 800, 600);
    app.SetRenderer(new OpenGL::Renderers::CubeRenderer());
    app.Run();
    return EXIT_SUCCESS;
}
