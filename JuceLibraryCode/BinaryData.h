/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   blackChip_png;
    const int            blackChip_pngSize = 128089;

    extern const char*   reversiIcon_png;
    const int            reversiIcon_pngSize = 12399;

    extern const char*   whiteChip_png;
    const int            whiteChip_pngSize = 100785;

    extern const char*   woodenSquare_png;
    const int            woodenSquare_pngSize = 153798;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 4;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}
