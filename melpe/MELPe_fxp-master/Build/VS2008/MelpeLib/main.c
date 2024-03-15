#include "melpeC.h"
#include <stdio.h>


int main(int argc, char* argv[]) {

    int16_t speech[180];
    int16_t npp_speech[180];
    FILE* file_speech, * file_analysis;

    NoiseS_init();

    if (argc < 3)
    {
        printf("Use: %s%s", argv[0], " input.file output.file ");
        return 0;
    }

    file_speech = fopen(argv[2], "wb");
    if (file_speech == NULL) {
        fprintf(stderr, "%s%s%s\n", "Use: ", argv[0], " input.file output.file ");
        return 1;
    }

    file_analysis = fopen(argv[1], "rb");
    if (file_analysis == NULL) {
        fprintf(stderr, "%s%s%s\n", "Use: ", argv[0], " input.file output.file ");
        fclose(file_speech);
        return 1;
    }


    while (1)
    {
        if (fread(speech, 2, 180, file_analysis) != 180)
        {
            printf("process end!\r\n");
            break;
        }

        NoiseSuppression(speech, npp_speech);
        fwrite(npp_speech, 2, 180, file_speech);
    }

    fclose(file_speech);
    fclose(file_analysis);

    return 0;
}


