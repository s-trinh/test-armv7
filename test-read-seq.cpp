#include <iostream>
#include <string>

#include <visp3/core/vpImage.h>
#include <visp3/core/vpIoTools.h>
#include <visp3/io/vpVideoReader.h>

template <class Type>
bool test_readSequence(vpImage<Type> &I, const std::string &videoname, long first_frame, int frame_step, int step,
                       long last_frame)
{
  vpVideoReader reader;
  reader.setFileName(videoname);
  reader.setFrameStep(step);
  reader.open(I);

  long frame = reader.getFirstFrameIndex();
  std::cout << "First frame: " << frame << std::endl;
  if (frame != first_frame) {
    std::cout << "Wrong first frame" << std::endl;
    return false;
  }
  frame = reader.getLastFrameIndex();
  std::cout << "Last frame: " << frame << std::endl;
  if (frame != last_frame) {
    std::cout << "Wrong last frame" << std::endl;
    return false;
  }

  long cpt = 0;
  while (!reader.end()) {
    reader.acquire(I);
    long index = reader.getFrameIndex();
    std::cout << "Read frame with index " << index << " from: " << reader.getFrameName() << std::endl;
    if (index != first_frame + cpt * frame_step) {
      std::cout << "Read wrong frame index" << std::endl;
      return false;
    }
    cpt++;
  }
  return true;
}

int main()
{
  std::string videoname_grey;
  long first_frame = 100;
  int frame_step = 2;
  unsigned int nframes = 3;
  long last_frame = first_frame + static_cast<long>(frame_step) * (nframes - 1);
  int step = 1;
  vpImage<unsigned char> I;

  std::string username = vpIoTools::getUserName();

  // Create a temp folder to save velocities...
#if defined(_WIN32)
  std::string tmp = "C:/temp/" + username + "/video";
#else
  std::string tmp = "/tmp/" + username + "/video";
#endif

  videoname_grey = tmp + std::string("/I%d.pgm");

  test_readSequence(I, videoname_grey, first_frame, frame_step, step, last_frame);

  return EXIT_SUCCESS;
}