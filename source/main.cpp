#include <QtPlugin>

#ifdef PLATFORM_WINDOWS
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif

#include "Application.hpp"

int main(int argc, char** argv)
{
    CodeTask::Application app(argc, argv);
    return app.run();
}
