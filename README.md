<div align="center">
  <img src="https://web.archive.org/web/20240422141350/https://upload.wikimedia.org/wikipedia/commons/d/d7/FNF-Logo.svg" width="200" alt="Friday Night Funkin' logo" />
  <h3>Wii Port</h3>
</div>

# Friday Night Funkin' — Wii Port

A rewrite of <a href="https://github.com/FunkinCrew/Funkin">Friday Night Funkin'</a> made to run on the Nintendo Wii.

## Prerequisites
- devkitPro (includes devkitPPC): https://www.devkitpro.org/
- CMake (with presets enabled)

## Dependencies
- GRRLIB: https://github.com/GRRLIB/GRRLIB
- TinyXML2: https://github.com/leethomason/tinyxml2
- libromfs-ogc: https://github.com/NateXS/libromfs-ogc

Install TinyXML2 via devkitPro pacman:
```bash
sudo dkp-pacman -S ppc-tinyxml2
```

For GRRLIB and libromfs-ogc, follow their READMEs.


## Build (Wii)
Use the CMake preset:
```bash
cmake --preset wii
cmake --build --preset wii
```

## Output
The .dol will be generated in the build folder.