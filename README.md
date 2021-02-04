# JPEG XL WIC

JPEG XL WIC provides a WIC (Windows Imaging Component) architecture implementation dedicated for JPEG XL image codec. It allows Windows system to recognize JPEG XL file format and use JPEG XL codec directly in its image processing operations. This technology simplifies image viewing to just using Windows Explorer, Microsoft Photo Viewer or Microsoft Photos.

JPEG XL WIC, as well as JPEG XL codec, are still in progress. The goal is to utilize a JPEG XL codec in Windows system, with a focus on HDR/WCG images decoding.

This project is based on JPEG XL reference implementation (https://gitlab.com/wg1/jpeg-xl) which repository is attached to the project as submodule.

## Supported output formats:
|Format|Number of channels|Bytes per sample
|---|---|---|
|GUID_WICPixelFormat32bppRGBA|4|4|
|GUID_WICPixelFormat32bppR10G10B10A2HDR10|4|4|

## Getting started:
 - make sure you have Inno Setup Compiler installed and according value is added to your `PATH` environment variable,
 - run `vcvars64` and `nmake` in project directory (binary files will be stored in `"./release/bin/x86_64"` directory),
 - run `installator.bat` in project directory to build an installator,
 - run `"./release/bin/x86_64/jpegxl_wic_setup.exe"`
