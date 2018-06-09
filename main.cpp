#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

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

    int16_t **data16;
};


int main(int argc, char* argv[]) {
    FILE* file = fopen(argv[1], "rb");
    if(file == nullptr) {
        cout << "Opening problem, please check your file" << endl;
        exit(1);
    } else {

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


        float fDurationSeconds = 1.f * subchunk2.subchunk2Size / (subchunk1.bitsPerSample / 8) / subchunk1.numChannels / subchunk1.sampleRate;
        int iDurationMinutes = (int)floor(fDurationSeconds) / 60;
        fDurationSeconds = fDurationSeconds - (iDurationMinutes * 60);
        cout << "Input-audio duration in seconds:\t" << fDurationSeconds << endl;

        int numSamples = (8 * subchunk2.subchunk2Size) / (subchunk1.numChannels * subchunk1.bitsPerSample);
        cout << "Number of samples:\t" << numSamples << endl;

        numSamples = subchunk2.subchunk2Size / subchunk1.blockAlign; //all right
//        cout << subchunk2.subchunk2Size << " " << subchunk1.blockAlign <<  " " << numSamples << endl;
        subchunk2.data16 = new int16_t *[subchunk1.numChannels];
        for(int i = 0; i < subchunk1.numChannels; i++)
            subchunk2.data16[i] = new int16_t[numSamples];

        for(int i = 0; i < numSamples; i++) {
            for (int j = 0; j < subchunk1.numChannels; j++) {
                fread(&subchunk2.data16[j][i], sizeof(int16_t), 1, file);
//                cout << hex << subchunk2.data16[j][i] << "   ";
            }
        }

        cout << endl;

        int counter = atoi(argv[2]);
        cout << "Your audio will be slown down by " << counter << " times." << endl;
        numSamples = counter * numSamples;
        subchunk2.subchunk2Size = subchunk1.blockAlign * numSamples;
        riffheader.chunkSize = subchunk2.subchunk2Size + 36;
//        cout << riffheader.chunkSize << " " << subchunk2.subchunk2Size << endl;


        for(int i = 0; i < numSamples; i++)
                for (int j = 0; j < subchunk1.numChannels; j++) {
//                    cout << hex << subchunk2.data16[j][i] << "   ";

                }

        RIFFHEADER outRiffheader;
        SUBCHUNK1 outSubchunk1;
        SUBCHUNK2 outSubchunk2;

        memcpy (&outRiffheader, &riffheader, sizeof(RIFFHEADER));
        memcpy(&outSubchunk1, &subchunk1, sizeof(SUBCHUNK1));
        memcpy(&outSubchunk2, &subchunk2, sizeof(SUBCHUNK2));

//        outRiffheader.format = riffheader.format;
//        outRiffheader.chunkSize = riffheader.chunkSize;
//        outRiffheader.chunkId = riffheader.chunkId;
//
//        outSubchunk1.subchunk1Id = subchunk1.subchunk1Id;
//        outSubchunk1.subchunk1Size = subchunk1.subchunk1Size;
//        outSubchunk1.audioFormat = subchunk1.audioFormat;
//        outSubchunk1.numChannels = subchunk1.numChannels;
//        outSubchunk1.sampleRate = subchunk1.sampleRate;
//        outSubchunk1.byteRate = subchunk1.byteRate;
//        outSubchunk1.blockAlign = subchunk1.blockAlign;
//        outSubchunk1.bitsPerSample = subchunk1.bitsPerSample;
//
//        outSubchunk2.subchunk2Id = subchunk2.subchunk2Id;
//        outSubchunk2.subchunk2Size = subchunk2.subchunk2Size;

        FILE* outputFile;
        outputFile = fopen("output.wav", "wb");
        fwrite(&outRiffheader, sizeof(RIFFHEADER), 1, outputFile);
        fwrite(&outSubchunk1, sizeof(SUBCHUNK1), 1, outputFile);
        fwrite(&outSubchunk2, sizeof(SUBCHUNK2), 1, outputFile);



        for(int i = 0; i < numSamples; i++)
            for (int k = 0; k < counter; k++)
                for (int j = 0; j < subchunk1.numChannels; j++) {
                    fwrite(&subchunk2.data16[j][i], sizeof(int16_t), 1, outputFile);
//                    cout << hex << subchunk2.data16[j][i] << "   ";

                }
    }

    return 0;
}