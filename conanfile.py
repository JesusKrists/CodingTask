import os

from conan import ConanFile
from conan.tools.files import copy

class Recipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"

    def layout(self):
        self.folders.generators = "conan"

    def requirements(self):
        self.requires("qt/6.7.1") # type: ignore

    def build_requirements(self):
        self.test_requires("catch2/3.7.0") # type: ignore