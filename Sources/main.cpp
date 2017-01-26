#include <cstdlib>
#include "Application.h"
#include "CubeRenderer.h"

int main(int argc, const char *argv[])
{
    auto app = OpenGL::Application("OpenGL Learning", 800, 600);
    app.SetRenderer(new OpenGL::Renderers::CubeRenderer());
    app.Run();
    return EXIT_SUCCESS;
}
