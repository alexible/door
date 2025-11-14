// Audio BFF Player for QT Py RP2040
// Plays WAV files from SD card through MAX98357 I2S amplifier

#include <SD.h>
#include <I2S.h>

// Pin definitions for QT Py RP2040 with Audio BFF
#define SD_CS_PIN     A0    // GPIO26 - SD card chip select
#define I2S_DATA_PIN  A1    // GPIO27 - I2S data pin  
#define I2S_LRCLK_PIN A2    // GPIO28 - I2S word select
#define I2S_BCLK_PIN  A3    // GPIO29 - I2S bit clock

I2S i2s(OUTPUT);

bool isWavFile(const char* filename) {
  int len = strlen(filename);
  if (len < 4) return false;
  return (tolower(filename[len-4]) == '.' &&
          tolower(filename[len-3]) == 'w' &&
          tolower(filename[len-2]) == 'a' &&
          tolower(filename[len-1]) == 'v');
}

bool isHiddenFile(const char* filename) {
  return filename[0] == '.';
}

void setup() {
  delay(1000);
  
  if (!SD.begin(SD_CS_PIN)) {
    while (1) delay(1000);
  }
}

void loop() {
  File root = SD.open("/");
  if (!root) {
    delay(5000);
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (!file.isDirectory()) {
      const char* filename = file.name();
      
      if (!isHiddenFile(filename) && isWavFile(filename)) {
        playWAV(file);
        delay(2000);
      }
    }
    file.close();
    file = root.openNextFile();
  }
  
  root.close();
  delay(3000);
}

void playWAV(File wavFile) {
  char buffer[4];
  uint32_t value32;
  uint16_t value16;
  
  wavFile.seek(0);
  
  // Read RIFF header
  wavFile.read((uint8_t*)buffer, 4);
  if (strncmp(buffer, "RIFF", 4) != 0) return;
  
  wavFile.read((uint8_t*)&value32, 4); // File size
  
  // Read WAVE format
  wavFile.read((uint8_t*)buffer, 4);
  if (strncmp(buffer, "WAVE", 4) != 0) return;
  
  // Find fmt chunk
  bool fmtFound = false;
  uint16_t audioFormat, numChannels, bitsPerSample;
  uint32_t sampleRate;
  
  while (wavFile.available() && !fmtFound) {
    wavFile.read((uint8_t*)buffer, 4);
    wavFile.read((uint8_t*)&value32, 4);
    
    if (strncmp(buffer, "fmt ", 4) == 0) {
      wavFile.read((uint8_t*)&audioFormat, 2);
      wavFile.read((uint8_t*)&numChannels, 2);
      wavFile.read((uint8_t*)&sampleRate, 4);
      wavFile.seek(wavFile.position() + 6); // Skip byteRate and blockAlign
      wavFile.read((uint8_t*)&bitsPerSample, 2);
      
      if (value32 > 16) {
        wavFile.seek(wavFile.position() + (value32 - 16));
      }
      
      fmtFound = true;
    } else {
      wavFile.seek(wavFile.position() + value32);
    }
  }
  
  if (!fmtFound || audioFormat != 1) return;
  
  // Find data chunk
  bool dataFound = false;
  uint32_t dataSize = 0;
  
  while (wavFile.available() && !dataFound) {
    wavFile.read((uint8_t*)buffer, 4);
    wavFile.read((uint8_t*)&value32, 4);
    
    if (strncmp(buffer, "data", 4) == 0) {
      dataSize = value32;
      dataFound = true;
    } else {
      wavFile.seek(wavFile.position() + value32);
    }
  }
  
  if (!dataFound || dataSize == 0) return;
  
  // Initialize I2S
  if (!i2s.setBCLK(I2S_BCLK_PIN) ||
      !i2s.setDATA(I2S_DATA_PIN) ||
      !i2s.setBitsPerSample(16) ||
      !i2s.begin(sampleRate)) {
    return;
  }
  
  // Play audio data
  uint32_t bytesRemaining = dataSize;
  uint16_t bytesPerSample = (bitsPerSample / 8) * numChannels;
  const size_t bufferSize = 512;
  uint8_t audioBuffer[bufferSize];
  
  while (bytesRemaining > 0 && wavFile.available()) {
    size_t bytesToRead = min(bufferSize, bytesRemaining);
    size_t bytesRead = wavFile.read(audioBuffer, bytesToRead);
    
    if (bytesRead == 0) break;
    
    for (size_t i = 0; i < bytesRead; i += bytesPerSample) {
      if (i + bytesPerSample > bytesRead) break;
      
      int16_t leftSample = 0;
      int16_t rightSample = 0;
      
      if (bitsPerSample == 16) {
        if (numChannels == 1) {
          leftSample = rightSample = ((int16_t*)(audioBuffer + i))[0];
        } else {
          leftSample = ((int16_t*)(audioBuffer + i))[0];
          rightSample = ((int16_t*)(audioBuffer + i))[1];
        }
      } else if (bitsPerSample == 8) {
        if (numChannels == 1) {
          leftSample = rightSample = ((int8_t)audioBuffer[i] - 128) << 8;
        } else {
          leftSample = ((int8_t)audioBuffer[i] - 128) << 8;
          rightSample = ((int8_t)audioBuffer[i + 1] - 128) << 8;
        }
      }
      
      i2s.write(leftSample);
      i2s.write(rightSample);
    }
    
    bytesRemaining -= bytesRead;
  }
  
  i2s.end();
}
