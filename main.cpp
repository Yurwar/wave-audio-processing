#include <iostream>
#include <fstream>

using namespace std;

struct RIFFHEADER {
    int32_t chunkId;
    int32_t chunkSize;
    int32_t format;
};

struct SUBCHUNK1 {
    int32_t subchunk1Id;
    int32_t subchunk1Size;
    int16_t audioFormat;
    int16_t numChannels;
    int32_t sampleRate;
    int32_t byteRate;
    int16_t blockAlign;
    int16_t bitsPerSample;
};

struct SUBCHUNK2{
    int32_t subchunk2Id;
    int32_t subchunk2Size;

    int8_t data[];
};


int main(int argc, char* argv[]) {
    FILE* file = fopen(argv[1], "rb");
    if(file == nullptr) {
        cout << "Can not open the file" << endl;
        exit(1);
    } else {
        ///First variant of filling data

        RIFFHEADER riffheader;
        fread(&riffheader, sizeof(RIFFHEADER), 1, file);
        SUBCHUNK1 subchunk1;
        fread(&subchunk1, sizeof(SUBCHUNK1), 1, file);

        SUBCHUNK2 subchunk2;
        fread(&subchunk2, sizeof(SUBCHUNK2), 1, file);

        cout << "chunkId:\t" << riffheader.chunkId << endl                              //1179011410
             << "chunkSize:\t" << riffheader.chunkSize << endl                          //57636
             << "format:\t" << riffheader.format << endl                                //1163280727
             << "subchunk1Id:\t" << subchunk1.subchunk1Id << endl                       //544501094
             << "subchunk1Size:\t" << subchunk1.subchunk1Size << endl                   //16
             << "audioFormat:\t" << subchunk1.audioFormat << endl                       //1
             << "numChannels:\t" << subchunk1.numChannels << endl                       //1
             << "sampleRate:\t" << subchunk1.sampleRate << endl                         //11025
             << "byteRate:\t" << subchunk1.byteRate << endl                             //22050
             << "blockAlign:\t" << subchunk1.blockAlign << endl                         //2
             << "bitsPerSample:\t" << subchunk1.bitsPerSample << endl                   //16
             << "subchunk2Id:\t" << subchunk2.subchunk2Id << endl                       //1635017060
             << "subchunk2Size:\t" << subchunk2.subchunk2Size << endl;                  //57600


        ///Second variant of filling data
        /*
        int32_t chunkId;
        int32_t chunkSize;
        int32_t format;
        int32_t subchunk1Id;
        int32_t subchunk1Size;
        int16_t audioFormat;
        int16_t numChannels;
        int32_t sampleRate;
        int32_t byteRate;
        int16_t blockAlign;
        int16_t bitsPerSample;
        int32_t subchunk2Id;
        int32_t subchunk2Size;

        int8_t data[] = {};

        fread(&chunkId, sizeof(int32_t), 1, file);            //1179011410
        fread(&chunkSize, sizeof(int32_t), 1, file);          //57636
        fread(&format, sizeof(int32_t), 1, file);             //1163280727
        fread(&subchunk1Id, sizeof(int32_t), 1, file);        //544501094
        fread(&subchunk1Size, sizeof(int32_t), 1, file);      //16
        fread(&audioFormat, sizeof(int16_t), 1, file);        //1
        fread(&numChannels, sizeof(int16_t), 1, file);        //1
        fread(&sampleRate, sizeof(int32_t), 1, file);         //11025
        fread(&byteRate, sizeof(int32_t), 1, file);           //22050
        fread(&blockAlign, sizeof(int16_t), 1, file);         //2
        fread(&bitsPerSample, sizeof(int16_t), 1, file);      //16
        fread(&subchunk2Id, sizeof(int32_t), 1, file);        //1635017060
        fread(&subchunk2Size, sizeof(int32_t), 1, file);      //57600

        cout << "chunkId:\t" << chunkId << endl
             << "chunkSize:\t" << chunkSize << endl
             << "format:\t" << format << endl
             << "subchunk1Id:\t" << subchunk1Id << endl
             << "subchunk1Size:\t" << subchunk1Size << endl
             << "audioFormat:\t" << audioFormat << endl
             << "numChannels:\t" << numChannels << endl
             << "sampleRate:\t" << sampleRate << endl
             << "byteRate:\t" << byteRate << endl
             << "blockAlign:\t" << blockAlign << endl
             << "bitsPerSample:\t" << bitsPerSample << endl
             << "subchunk2Id:\t" << subchunk2Id << endl
             << "subchunk2Size:\t" << subchunk2Size << endl;
        */
    }
}