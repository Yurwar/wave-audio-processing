#include <iostream>
#include <fstream>

using namespace std;

typedef struct {
    int32_t chunkId;
    int32_t chunkSize;
    int32_t format;
} RIFFHEADER;

typedef struct {
    int32_t subchunk1Id;
    int32_t subchunk1Size;
    int32_t audioFormat;

    int16_t numChannels;

    int32_t sampleRate;
    int32_t byteRate;
    int32_t blockAlign;

    int16_t bitsPerSample;
} SUBCHUNK1;

typedef struct {
    char subchunk2Id[4];
    int32_t subchunk2Size;

    int8_t data[];
} SUBCHUNK2;


int main(int argc, char* argv[]) {
    FILE* file = fopen(argv[1], "rb");
    if(file == nullptr) {
        cout << "Can not open the file" << endl;
        exit(1);
    } else {
        RIFFHEADER riffheader;
        fread(&riffheader, sizeof(riffheader), 1, file);

        printf("WAV File Header read:\n");
        printf("File Type: %d\n", riffheader.chunkId);
        printf("File Size: %d\n", riffheader.chunkSize);
        printf("WAV Marker: %d\n", riffheader.format);

        SUBCHUNK1 subchunk1;
        fread(&subchunk1, sizeof(subchunk1), 1, file);
        printf("Format name: %d\n", subchunk1.subchunk1Id);
        printf("Format length: %d\n", subchunk1.subchunk1Size);
        printf("Format type: %d\n", subchunk1.audioFormat);
        printf("Number of channels: %d\n", subchunk1.numChannels);
        printf("Sample rate: %d\n", subchunk1.sampleRate);
        printf("Sample Rate * Bits/Sample * Channels / 8: %d\n", subchunk1.byteRate);
        printf("Bits per Sample * Channels / 8.1: %d\n", subchunk1.blockAlign);
        printf("Bits per Sample: %d\n", subchunk1.bitsPerSample);

        SUBCHUNK2 subchunk2;
        printf("id\t" "size\n");


    }
}