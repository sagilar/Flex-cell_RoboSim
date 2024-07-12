#!/usr/bin/env python3

from pathlib import Path

import setuptools

project_dir = Path(__file__).parent

setuptools.setup(
    name="robotDTLab",
    version="0.0.1",
    description="RobotDTLab model",
    # Allow UTF-8 characters in README with encoding argument.
    keywords=["python", "ur robot", "universal robot"],
    author="Santiago Gil",
    author_email="sgil@ece.au.dk",
    packages=setuptools.find_packages("src"),
    package_dir={"": "src"},
    classifiers=[
        "Development Status :: 1 - Beta",
        "Intended Audience :: Developers",
        "Programming Language :: Python :: 3",
    ]
)
