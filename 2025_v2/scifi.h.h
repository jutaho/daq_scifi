/******************************************************************************
* Copyright                                                                   *
* Scintillating Fibre Beam Profile Monitor Software by Michal Dziewiecki,     *
* Blake Leverington and Liqing Qin is licensed under CC BY 4.0                *
* https://creativecommons.org/licenses/by/4.0/                                *
* funded by the Deutsche Forschungsgemeinschaft                               *
* (DFG, German Research Foundation) Projektnummer 419255448                   *
* Project Leader: B.Leverington                                               *
*******************************************************************************
* Create Date - 2019                                                          *
* Author: M.Dziewiecki                                                        *
* Module - hitreader.h                                                        *
* Edited by J. Horn on 24.02.2025                                            *
******************************************************************************/

// This is an object interface for reading SciFi data files for testbeam 2024Feb/Aug with the new FPGA firmware.
// See documentation by M. Dziewiecki for details and examples: "Beam Position Monitor: A bundle of random information" v1.0, 2019-12-12

/*
  .L hitreader.c

  Scifidata data;
  data.readFile(“my_file.da2”);                                            //to load whole file at once – forget it! See below.
  data.readFile(“my_file.da2”,1000,100,10)                    //to read 100 frames starting from frame 1000 and incrementing by 10 (i.e. frame 1000, 1010, 1020, ... 1990 will be read)
  //Reading 10 000 frames is reasonable. Reading 100 000 frames made my VM beg for memory.

  data.nrFrames                                                                  //to see how many frames you have
  data.frames[0].nrBoards                                              //to see how many boards you had in the system
  data.frames[0].boards[0].nrChannels                    //to see how many channels you have in board 0
  data.frames[10].boards[0].data[100]                      //get signal value for frame 10, board 0, channel 100
  data.frames[10].boards[0].syncframe.local_ctr //get the local synchro counter for frame 10, board 0
  //same for .global_ctr, .sma_state, .dummy, .device_nr, .data_ok

 */

/******************************************************************************
* SciFireader.h                                                               *
* A 64-bit safe header for reading SciFi .da2 files.                          *
*                                                                             *
* Adapted from original hitreader/scifireader code.                           *
* Uses 64-bit integers to avoid overflow on large files.                      *
******************************************************************************/

#ifndef SCIFIREADER_H
#define SCIFIREADER_H

#include <fstream>
#include <iostream>
#include <cstdint>
#include <limits>
#include <algorithm>

//*****************************************************************************
//  Class for measurement details (results) for one board
//  Total size: 16 bytes
//*****************************************************************************
class MeasurementDetails {
public:
  MeasurementDetails() : Position(0.0), Sigma(0.0), Peak(0), Status(0), Dummy0(0), Dummy1(0) {}
  ~MeasurementDetails() {}

  // Returns size in file (in bytes)
  int sizeInFile() const { return 16; }

  int read(std::ifstream *file) {
    char buffer[16];
    file->read(buffer, 16);
    if (file->fail()) return 1;
    // Read as unsigned shorts/ints; note that Position and Sigma are scaled
    Position = *(unsigned short *)(buffer + 0) * 0.05;
    Sigma    = *(unsigned short *)(buffer + 2) * 0.05;
    Peak     = *(unsigned short *)(buffer + 4);
    Status   = *(unsigned short *)(buffer + 6);
    Dummy0   = *(int *)(buffer + 8);
    Dummy1   = *(int *)(buffer + 12);
    return 0;
  }

  int write(std::ofstream *file) {
    char buffer[16];
    *(unsigned short *)(buffer + 0) = static_cast<unsigned short>(Position / 0.05);
    *(unsigned short *)(buffer + 2) = static_cast<unsigned short>(Sigma / 0.05);
    *(unsigned short *)(buffer + 4) = Peak;
    *(unsigned short *)(buffer + 6) = Status;
    *(int *)(buffer + 8) = Dummy0;
    *(int *)(buffer + 12) = Dummy1;
    file->write(buffer, 16);
    if (file->fail()) return 1;
    return 0;
  }

  double Position;       // 2 bytes stored as unsigned short (scaled)
  double Sigma;          // 2 bytes stored as unsigned short (scaled)
  unsigned short Peak;   // 2 bytes
  unsigned short Status; // 2 bytes (bit flags for BKG_SUB_ON, HAS_CLUSTER, NO_CLUSTER)
  int Dummy0;            // 4 bytes (can encode two 16-bit window values)
  int Dummy1;            // 4 bytes
};

//*****************************************************************************
//  Class for board data block (raw data + calibration data)
//  For one board with N channels:
//    - Raw data block: N channels x 2 bytes (unsigned)
//    - Cal data block: N channels x 2 bytes (signed)
//  Total size = N x 4 bytes
//*****************************************************************************

class BoardData {
public:
  BoardData(int nr_channels = 0) : nrChannels(nr_channels), rawData(nullptr), calData(nullptr) {
    resize(nr_channels);
  }
  BoardData(const BoardData &in) : nrChannels(in.nrChannels) {
    rawData = new unsigned short[nrChannels];
    calData = new short[nrChannels];
    for (int i = 0; i < nrChannels; i++) {
      rawData[i] = in.rawData[i];
      calData[i] = in.calData[i];
    }
  }
  BoardData &operator=(const BoardData &in) {
    if (this == &in) return *this;
    resize(in.nrChannels);
    nrChannels = in.nrChannels;
    for (int i = 0; i < nrChannels; i++) {
      rawData[i] = in.rawData[i];
      calData[i] = in.calData[i];
    }
    return *this;
  }
  ~BoardData() {
    if (rawData) delete[] rawData;
    if (calData) delete[] calData;
  }

  void resize(int nr_channels) {
    nrChannels = nr_channels;
    if (rawData) { delete[] rawData; rawData = nullptr; }
    if (calData) { delete[] calData; calData = nullptr; }
    if (nrChannels > 0) {
      rawData = new unsigned short[nrChannels];
      calData = new short[nrChannels];
    }
  }

  // Size in file = (nrChannels x 2 bytes) for raw + (nrChannels x 2 bytes) for cal data
  int sizeInFile() const { return nrChannels * 4; }

  // Read raw data then calibration data from file.
  int read(std::ifstream *file) {
    // Read raw data block (unsigned shorts)
    file->read(reinterpret_cast<char*>(rawData), nrChannels * 2);
    if (file->fail()) return 1;
    // Read cal data block (signed shorts)
    file->read(reinterpret_cast<char*>(calData), nrChannels * 2);
    if (file->fail()) return 1;
    return 0;
  }

  int write(std::ofstream *file) {
    file->write(reinterpret_cast<char*>(rawData), nrChannels * 2);
    if (file->fail()) return 1;
    file->write(reinterpret_cast<char*>(calData), nrChannels * 2);
    if (file->fail()) return 1;
    return 0;
  }

  int nrChannels;
  unsigned short *rawData;  // Raw data (unsigned), 2 bytes per channel
  short *calData;           // Calibration data (signed), 2 bytes per channel
};

//*****************************************************************************
//  Fullframe represents one complete frame in the .da2 file.
//  A frame consists of:
//    1. Frame header: 
//         - [2 bytes] Number of Boards
//         - [2 bytes x nrBoards] Channel count for each board
//    2. For each board: BoardData (raw + cal data)
//    3. Measurement Details for each board (16 bytes per board)
//*****************************************************************************

class Fullframe {
public:
  Fullframe() : nrBoards(0), boardData(nullptr), measDetails(nullptr) {}
  Fullframe(const Fullframe &in) {
    nrBoards = in.nrBoards;
    if (nrBoards > 0) {
      boardData = new BoardData[nrBoards];
      measDetails = new MeasurementDetails[nrBoards];
      for (int i = 0; i < nrBoards; i++) {
        boardData[i] = in.boardData[i];
        measDetails[i] = in.measDetails[i];
      }
    } else {
      boardData = nullptr;
      measDetails = nullptr;
    }
  }
  Fullframe &operator=(const Fullframe &in) {
    if (this == &in) return *this;
    if (boardData) delete[] boardData;
    if (measDetails) delete[] measDetails;
    nrBoards = in.nrBoards;
    if (nrBoards > 0) {
      boardData = new BoardData[nrBoards];
      measDetails = new MeasurementDetails[nrBoards];
      for (int i = 0; i < nrBoards; i++) {
        boardData[i] = in.boardData[i];
        measDetails[i] = in.measDetails[i];
      }
    } else {
      boardData = nullptr;
      measDetails = nullptr;
    }
    return *this;
  }
  ~Fullframe() {
    if (boardData) delete[] boardData;
    if (measDetails) delete[] measDetails;
  }

  // Resize this frame to hold 'nr_boards' boards.
  // (Channel counts are later set from the header.)
  void resize(int nr_boards) {
    nrBoards = nr_boards;
    if (boardData) { delete[] boardData; boardData = nullptr; }
    if (measDetails) { delete[] measDetails; measDetails = nullptr; }
    if (nrBoards > 0) {
      boardData = new BoardData[nrBoards];
      measDetails = new MeasurementDetails[nrBoards];
    }
  }

  // Returns the total frame size (in bytes):
  // Header: 2 bytes (nrBoards) + (nrBoards x 2 bytes for channel counts)
  // + Sum(board data block sizes) + (nrBoards x 16 bytes for measurement details)
  int sizeInFile() const {
    int headerSize = 2 + (nrBoards * 2);
    int boardsSize = 0;
    for (int i = 0; i < nrBoards; i++) {
      boardsSize += boardData[i].sizeInFile();
    }
    int measSize = nrBoards * 16;
    return headerSize + boardsSize + measSize;
  }

  // Read a frame from file:
  //  1. Read the header (nrBoards and per-board channel counts).
  //  2. For each board, resize its BoardData using the channel count.
  //  3. Read the raw+cal data for each board.
  //  4. Read the measurement details block for each board.
  
  int read(std::ifstream *file) {
    // Read number of boards (2 bytes)
    unsigned short nboards = 0;
    file->read(reinterpret_cast<char*>(&nboards), 2);
    if (file->fail()) return 1;
    resize(nboards);
    // For each board, read its channel count (2 bytes each)
    for (int i = 0; i < nrBoards; i++) {
      unsigned short nch = 0;
      file->read(reinterpret_cast<char*>(&nch), 2);
      if (file->fail()) return 1;
      boardData[i].resize(nch);
    }
    // For each board, read the raw and calibration data blocks.
    for (int i = 0; i < nrBoards; i++) {
      if (boardData[i].read(file)) return 1;
    }
    // Finally, read the measurement details block (16 bytes per board)
    for (int i = 0; i < nrBoards; i++) {
      if (measDetails[i].read(file)) return 1;
    }
    return 0;
  }

  int write(std::ofstream *file) {
    // Write header: number of boards and then each board's channel count.
    unsigned short nboards = static_cast<unsigned short>(nrBoards);
    file->write(reinterpret_cast<char*>(&nboards), 2);
    if (file->fail()) return 1;
    for (int i = 0; i < nrBoards; i++) {
      unsigned short nch = static_cast<unsigned short>(boardData[i].nrChannels);
      file->write(reinterpret_cast<char*>(&nch), 2);
      if (file->fail()) return 1;
    }
    // Write each board's data block.
    for (int i = 0; i < nrBoards; i++) {
      if (boardData[i].write(file)) return 1;
    }
    // Write measurement details for each board.
    for (int i = 0; i < nrBoards; i++) {
      if (measDetails[i].write(file)) return 1;
    }
    return 0;
  }

  // Optional: direct access to board data by index.
  BoardData &operator[](int index) {
    if (index < 0 || index >= nrBoards) {
      std::cerr << "Fullframe::operator[]: index out of range!" << std::endl;
      return boardData[0];
    }
    return boardData[index];
  }

  int nrBoards;
  BoardData *boardData;
  MeasurementDetails *measDetails;
};

//*****************************************************************************
//  Scifidata: container for multiple frames and functions for file I/O.
//*****************************************************************************

class Scifidata {
public:
  Scifidata(int64_t nr_frames = 0) : nrFrames(nr_frames), frames(nullptr) {
    resize(nr_frames);
  }
  Scifidata(const Scifidata &in) : frames(nullptr) {
    resize(in.nrFrames);
    for (int64_t i = 0; i < nrFrames; i++) {
      frames[i] = in.frames[i];
    }
  }
  Scifidata &operator=(const Scifidata &in) {
    if (this == &in) return *this;
    resize(in.nrFrames);
    for (int64_t i = 0; i < nrFrames; i++) {
      frames[i] = in.frames[i];
    }
    return *this;
  }
  ~Scifidata() {
    if (frames) delete[] frames;
  }

  void resize(int64_t nr_frames) {
    if (frames) { delete[] frames; frames = nullptr; }
    nrFrames = nr_frames;
    if (nrFrames > 0) {
      frames = new Fullframe[nrFrames];
    }
  }

  // Read frames from file:
  //   filename: file name
  //   first_frame: starting frame index
  //   nr_frames: number of frames to read (if -1, read all available)
  //   increment: skip factor between frames
  // Returns number of frames read.
  int64_t readFile(const char *filename,
                   int64_t first_frame = 0,
                   int64_t nr_frames   = -1,
                   int64_t increment   = 1) {
    if (increment <= 0) {
      std::cerr << "Invalid increment!" << std::endl;
      return 0;
    }
    std::ifstream file(filename, std::ios_base::in | std::ios_base::binary);
    if (!file.is_open()) {
      std::cerr << "Scifidata::readFile: Could not open file!" << std::endl;
      return 0;
    }
    // Read one sample frame to determine frame size.
    Fullframe sampleframe;
    if (sampleframe.read(&file)) {
      std::cerr << "Scifidata::readFile: First frame could not be read!" << std::endl;
      file.close();
      return 0;
    }
    file.seekg(0, std::ios::end);
    std::streamoff fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    int frameSize = sampleframe.sizeInFile();
    if (frameSize <= 0) {
      std::cerr << "Scifidata::readFile: Invalid frame size!" << std::endl;
      file.close();
      return 0;
    }
    int64_t total_frames = fileSize / frameSize;
    int64_t max_frames = (total_frames - first_frame + (increment - 1)) / increment;
    if (max_frames < 0) max_frames = 0;
    if (nr_frames < 0 || nr_frames > max_frames) {
      nr_frames = max_frames;
    }
    resize(nr_frames);
    for (int64_t i = 0; i < nr_frames; i++) {
      int64_t offsetBytes = (first_frame + i * increment) * frameSize;
      if (offsetBytes + frameSize > fileSize) {
        file.close();
        return i;
      }
      file.seekg(offsetBytes, std::ios::beg);
      if (frames[i].read(&file)) {
        std::cerr << "Scifidata::readFile: Could not read frame index "
                  << (first_frame + i * increment) << std::endl;
        file.close();
        return i;
      }
    }
    file.close();
    return nr_frames;
  }

  // Quickly get the total number of frames in the file (assuming uniform frame size).
  int64_t getTotalFrames(const char *filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
      std::cerr << "Error: Could not open file " << filename << std::endl;
      return -1;
    }
    Fullframe sampleframe;
    if (sampleframe.read(&file)) {
      std::cerr << "Error: Could not read first frame from file " << filename << std::endl;
      file.close();
      return -1;
    }
    file.seekg(0, std::ios::end);
    std::streamoff fileSize = file.tellg();
    file.close();
    int frameSize = sampleframe.sizeInFile();
    if (frameSize <= 0) return -1;
    return fileSize / frameSize;
  }

  // Direct access to a frame by index (after reading the file)
  Fullframe &operator[](int64_t index) {
    if (index < 0 || index >= nrFrames) {
      std::cerr << "Scifidata::operator[]: index out of range!" << std::endl;
      return frames[0];
    }
    return frames[index];
  }

  int64_t nrFrames;
  Fullframe *frames;
};

#endif // SCIFIREADER_H
