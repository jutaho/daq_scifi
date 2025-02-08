//This is an object interface for reading HIT data files
//See HIT documentation for details and examples.
/*
  THIS DOESN'T WORK!
  .L hitreader.c

  Hitdata data;
  data.read(“my_file.da2”);                                            //to load whole file at once – forget it! See below.
  data.read(“my_file.da2”,1000,100,10)                    //to read 100 frames starting from frame 1000 and incrementing by 10 (i.e. frame 1000, 1010, 1020, ... 1990 will be read)
  //Reading 10 000 frames is reasonable. Reading 100 000 frames made my VM beg for memory.

  data.nrFrames                                                                  //to see how many frames you have
  data.frames[0].nrBoards                                              //to see how many boards you had in the system
  data.frames[0].boards[0].nrChannels                    //to see how many channels you have in board 0
  data.frames[10].boards[0].data[100]                      //get signal value for frame 10, board 0, channel 100
  data.frames[10].boards[0].syncframe.local_ctr //get the local synchro counter for frame 10, board 0
  //same for .global_ctr, .sma_state, .dummy, .device_nr, .data_ok

 */

//*********************** Helper *************************
#include <fstream>
#include <iostream>

using namespace std;

//#define debug(str)	std::cout << "HIT DEBUG: " << str << endl;
#define debug(str)

//*********************** Syncframe *************************
class Syncframe
{
 public:
  Syncframe()
    {
      debug("Syncframe()");

      local_ctr = global_ctr = 0;
      sma_state = dummy = 0;
      device_nr = -1;
      data_ok = 0;
    };
	
  ~Syncframe()	
    {
      debug("~Syncframe()");
    };

  int sizeInFile()
  {
    return 16;
  };

  int read(std::ifstream* file)
  {
    char buffer[16];
    file->read(buffer,16);
    if (file->fail())
      return 0;
    local_ctr 	= *(unsigned short*)(buffer+0);
    global_ctr 	= *(unsigned short*)(buffer+2);
    sma_state	= *(unsigned short*)(buffer+4);
    dummy 		= *(unsigned short*)(buffer+6);
    device_nr	= *(int*)(buffer+8);
    data_ok		= *(int*)(buffer+12);
    //  std::cout << "Syncframe:" << local_ctr << " " << global_ctr << " " << sma_state << " " << dummy << " " << device_nr << " " << data_ok << std::endl;

    return 1;
  };

  
  unsigned short 	local_ctr;
  unsigned short 	global_ctr;
  unsigned short 	sma_state;
  unsigned short 	dummy;
  int 		device_nr;
  unsigned int 	data_ok;
};

//*********************** Sensorframe *************************
class Boardframe
{
 public:
  Boardframe(int nr_channels = 0)
    {
      debug("Boardframe()");

      data = NULL;
      resize (nr_channels);
    };

  Boardframe(const Boardframe& in)
    {
      debug("Boardframe(Boardframe&)");

      data = NULL;
      resize(in.nrChannels);
      for (int i = 0; i < nrChannels; i++)
	data[i] = in.data[i];
      syncframe = in.syncframe;
    };

  Boardframe& operator=(const Boardframe& in)
    {
      debug("Boardframe::operator==");

      resize(in.nrChannels);//creates an array called data of length nrChannels
      for (int i = 0; i < nrChannels; i++)
	data[i] = in.data[i];
      syncframe = in.syncframe;
      return *this;
    };

  ~Boardframe()
    {
      debug("~Boardframe()");

      if (data)
	delete[] data;
    };

  void resize(int nr_channels)
    {
      if (data)
	delete[] data;
      nrChannels = nr_channels;
      if (nrChannels)
	data = new unsigned short[nrChannels];
      else
	data = NULL;
    };	

  int sizeInFile()
  {
    // std::cout << "boardframe.sizeInFile() = " <<  syncframe.sizeInFile() + nrChannels*2 << std::endl;
    return syncframe.sizeInFile() + nrChannels*2;
    
  };

  int read(std::ifstream* file)
  {
    if (syncframe.read(file) == 0)//get the syncframe before the board data
      return 0;
    //I must be already resized at this point!
    file->read((char*)data,2*nrChannels);
    if (file->fail())
      return 0;
    //  std::cout<< "data[" << nrChannels << "]: ";
    // for (int i = 0;i<nrChannels;i++) std::cout << data[i] << " ";
    //  std::cout << std::endl;
    
    return 1;
  };

  unsigned short& operator[] (int index)
  {
    return data[index];
  };

  Syncframe syncframe;
  int nrChannels;
  unsigned short* data;
};

//*********************** Fullframe *************************
class Fullframe
{
 public:
  Fullframe(int nr_boards = 0)
    {
      debug("Fullframe()");
      boards = NULL;			
      resize(nr_boards);
    };

  Fullframe(const Fullframe& in)
    {
      debug("Fullframe(Fullframe&)");
      boards = NULL;			
      resize(in.nrBoards);
      for (int i = 0; i < nrBoards; i++)
	boards[i] = in.boards[i];
    };

  Fullframe& operator=(const Fullframe& in)
    {
      debug("Fullframe::operator==");
      resize(in.nrBoards);
      for (int i = 0; i < nrBoards; i++)
	boards[i] = in.boards[i];

      return *this;
    };

  ~Fullframe()
    {	
      debug("~Fullframe()");
      if (boards)
	delete[] boards;
    };

  void resize (int nr_boards)
    {
      if (boards)
	delete[] boards;
      nrBoards = nr_boards;
      if (nrBoards)
	boards = new Boardframe[nrBoards];
      else
	boards = NULL;
    }

  int sizeInFile()
  {
    if (boards){
      //   std::cout << "Fullframe.sizeInFile() = " << 2 + nrBoards*2 + nrBoards * boards[0].sizeInFile() << std::endl;
      // return 2 + nrBoards*2 + nrBoards * boards[0].sizeInFile();
      ////  boards[0].sizeInFile() returns 656 for every board...
      return 2 + 4*2 + (16 + 320 * 2) + (16 + 128*2)*3;  //1482
    }
    else
      return 0;	//no boards, makes no sense...
  };

  int read(std::ifstream* file)
  {
    //Read number of boards
    unsigned short nr_boards;
    file->read((char*)&nr_boards,2);
    if(file->fail()){
      std::cerr << "File read failed." <<  std::endl; 
      return 0;
    }
    if (nr_boards!=4){
      std::cerr << "Unrealistic number(!=) of boards to be read:"<< nr_boards <<  std::endl;
      std::cerr << "Will try to resync frame." <<  std::endl; 
      for (int j = 0;j<741;j++){
	file->read((char*)&nr_boards,2);
	if (nr_boards==4) break;
      }
      if ( nr_boards!=4){
	std::cerr << "Resync failed." <<  std::endl; 
	return 0;
      }
     
    }
    //std::cout << " nr_boards: " << nr_boards << std::endl;
    //Read channel counts
    unsigned short* channel_counts = new unsigned short[nr_boards];
    file->read((char*)channel_counts,nr_boards*2);
    if (file->fail())
      {
	delete[] channel_counts;
	return 0;
      }


    
    //Read board frames
    resize(nr_boards);
    for (int board_nr = 0; board_nr < nr_boards; board_nr++)
      {
	//	std::cout << " channel_counts[" << board_nr << "]: "<< channel_counts[board_nr] << std::endl;

	boards[board_nr].resize(channel_counts[board_nr]);
	if (boards[board_nr].read(file) == 0)//read the board
	  {
	    delete[] channel_counts;
	    return 0;
	  }
      }		

    delete[] channel_counts;		
    return 1;
  };
	
  int nrChannels()
  {
    int result = 0;
    for (int board_nr = 0; board_nr < nrBoards; board_nr++)
      result += boards[board_nr].nrChannels;
    return result;
  };

  unsigned short& operator[] (int index)
  {
    for (int board_nr = 0; board_nr < nrBoards; board_nr++)
      {
	if (index >= boards[board_nr].nrChannels)
	  index -= boards[board_nr].nrChannels;
	else
	  return boards[board_nr][index];
      }
		
    std::cerr << " ### Fullframe::operator[]: index out of range!" << std::endl;
    //   return (*NULL); //this will cause crash (intended).
    return boards[nrBoards][index];
  };

  int nrBoards;
  Boardframe* boards;
};

//*********************** Hitdata *************************

class Hitdata
{
 public:
  Hitdata(int nr_frames = 0)
    {
      frames = NULL;
      resize(nr_frames);
    };

  Hitdata(const Hitdata& in)
    {
      frames = NULL;			
      resize(in.nrFrames);
      for (int i = 0; i < nrFrames; i++)
	frames[i] = in.frames[i];
    };

  Hitdata& operator=(const Hitdata& in)
    {
      resize(in.nrFrames);
      for (int i = 0; i < nrFrames; i++)
	frames[i] = in.frames[i];

      return *this;
    };

  ~Hitdata()
    {
      if (nrFrames)
	delete[] frames;
    };

  void resize (int nr_frames)
    {
      if (nrFrames)
	delete[] frames;
      nrFrames = nr_frames;
      if (nrFrames)
	frames = new Fullframe[nrFrames];
      else
	frames = NULL;
    };
	
  //Read data from a given file. 
  //first_frame is the number of first frame to be read
  //nr_frames is the maximum number of frames to be read
  //-1 to read all of them
  //increment allows you reading once every nth sample 
  //Return number of frames read or 0 in case of failure
  int readFile(char* filename, int first_frame = 1, int nr_frames = -1, int increment = 1)
  {
    std::ifstream file;
    //Open the file
    file.open(filename, ios_base::in | ios_base::binary);
    if (!file.is_open())
      {
	std::cerr << " ### Hitdata: File could not be open!" << std::endl;
	return 0;	//file could not be opened 
      }

    //Read first record to find board configuration
    Fullframe sampleframe;
    if (sampleframe.read(&file) == 0)
      {
	std::cerr << " ### Hitdata: First frame could not be read!" << std::endl;
	file.close();
	return 0;
      }
    else {
      std::cout << "Sample frame size (bytes): " << sampleframe.sizeInFile() << std::endl;
    }
		
    //Check file size
    file.seekg(0, std::ios::beg);
    std::streamsize fsize = file.tellg();
    file.seekg(0, std::ios::end);
    fsize = file.tellg() - fsize;

    //Determine real frames to read
    unsigned int max_frames = fsize / sampleframe.sizeInFile();
    if ((max_frames == -1) || (max_frames < nr_frames))
      nr_frames = max_frames;

    std::cout << "     Hitdata: Nr frames to be read: " << nr_frames << std::endl;

    //Read!
    //   resize(nr_frames); //make an array of Fullframes called frames of size nr_frames
    file.seekg(first_frame * sampleframe.sizeInFile(), std::ios::beg);
    for (int frame_nr = first_frame; frame_nr < nr_frames; frame_nr++)
      {
	if ((frame_nr%10000) == 0)
	  std::cout << "        Frame " << frame_nr << std::endl;

	file.seekg((frame_nr*increment) * sampleframe.sizeInFile() , std::ios::beg);
	if (file.eof()) {
	  std::cerr<< "end of file reached." << std::endl;
	  return frame_nr;
	}
	if ( sampleframe.read(&file) == 0) //read the next frame
	  {
  	    std::cerr << " ### Hitdata: Frame " << frame_nr << " could not be read!" << std::endl;
	    file.close();		//read error, finish!
	    // frames = frame_nr;	//Kinky! We decrease nr_frames, but the actual array size remains unchanged! 	
	    ///???? I don't know what the above line does.
	    return frame_nr;
	  }
	//	std::cout << frames[frame_nr].nrBoards << std::endl;
      }

    //Finished
    file.close();
    return nr_frames;
  };
	
  Fullframe& operator[] (int index)
    {
      if (index < nrFrames)		
	return frames[index];
      else
	{
	  std::cerr << " ### Hitdata::operator[]: index out of range!" << std::endl;
	  // return (*NULL);	//this will cause crash (intended).
	  return frames[index];
	  
	}
    };

  int nrFrames;
  Fullframe* frames;
};






