/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   whiteChip225_png;
    const int            whiteChip225_pngSize = 27674;

    extern const char*   blackChip225_png;
    const int            blackChip225_pngSize = 23891;

    extern const char*   greenSquare_png;
    const int            greenSquare_pngSize = 10599;

    extern const char*   blackChip_png;
    const int            blackChip_pngSize = 116658;

    extern const char*   reversiIcon_png;
    const int            reversiIcon_pngSize = 12399;

    extern const char*   whiteChip_png;
    const int            whiteChip_pngSize = 51550;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 6;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}
