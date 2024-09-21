#pragma once

#include <QApplication>

#include "Window.hpp"

namespace CodeTask
{

class Application
{
  public:
    Application(int argc, char** argv)
        : m_app(argc, argv)
    {
    }

    int run()
    {
        return m_app.exec();  // NOLINT(readability-static-accessed-through-instance)
    }

  private:
    QApplication m_app;
    Window m_window;
};

}  // namespace CodeTask