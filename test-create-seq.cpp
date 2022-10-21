#include <iostream>
#include <string>

#include <visp3/core/vpImage.h>
#include <visp3/core/vpIoTools.h>
#include <visp3/io/vpVideoWriter.h>


template <class Type>
bool test_createSequence(vpImage<Type> &I, const std::string &videoname, unsigned int first_frame, int frame_step,
                         unsigned int nframes)
{
  try {
    vpVideoWriter writer;
    writer.setFileName(videoname);
    writer.setFirstFrameIndex(static_cast<int>(first_frame));
    writer.setFrameStep(frame_step);
    writer.open(I);

    for (unsigned int i = 0; i < nframes; i++) {
      writer.saveFrame(I);
      std::cout << "Frame saved in: " << writer.getFrameName() << std::endl;
    }
    return true;
  } catch (...) {
    return false;
  }
}

int main()
{
  std::string videoname_grey;
  long first_frame = 100;
  int frame_step = 2;
  unsigned int nframes = 3;
  long last_frame = first_frame + static_cast<long>(frame_step) * (nframes - 1);
  vpImage<unsigned char> I(2, 4, 0);


  std::string username = vpIoTools::getUserName();

  // Create a temp folder to save velocities...
#if defined(_WIN32)
  std::string tmp = "C:/temp/" + username + "/video";
#else
  std::string tmp = "/tmp/" + username + "/video";
#endif
  // Test if the output path exist. If no try to create it
  if (vpIoTools::checkDirectory(tmp) == false) {
    try {
      // Create the dirname
        std::cout << "** Create temp directory: " << tmp << std::endl;

      vpIoTools::makeDirectory(tmp);
    } catch (...) {
      std::cerr << std::endl << "ERROR:" << std::endl;
      std::cerr << "  Cannot create " << tmp << std::endl;
    }
  }


  videoname_grey = tmp + std::string("/I%d.pgm");

  test_createSequence(I, videoname_grey, first_frame, frame_step, nframes);

  return EXIT_SUCCESS;
}