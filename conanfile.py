from conan import ConanFile
from conan.tools.cmake import cmake_layout

class Recipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"

    def layout(self):
        self.folders.generators = "conan"
        cmake_layout(self)

    def requirements(self):
        self.requires("fmt/11.0.2") # type: ignore
        self.requires("qt/6.7.1") # type: ignore

    def build_requirements(self):
        self.test_requires("catch2/3.7.0") # type: ignore