#ifndef YAMPL_SHAREDMEMORY_H
#define YAMPL_SHAREDMEMORY_H

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>

namespace yampl{

class SharedMemory{
  public:
    SharedMemory(const std::string& name, size_t size) : m_name(name), m_size(size), m_fd(-1), m_buffer(0){
      if((m_fd = shm_open(m_name.c_str(), O_RDWR | O_CREAT, S_IRWXU)) == -1)
	throw ErrnoException("Failed to open shared memory object");

      int ret = 0;

      if((ret = flock(m_fd, LOCK_EX | LOCK_NB)) == 0){
	// truncate to 0 and only then to size to ensure that the shared object is zero filled
	if(ftruncate(m_fd, 0) == -1)
	  throw ErrnoException("Failed to set the size of the shared memory object");

	if(ftruncate(m_fd, m_size) == -1)
	  throw ErrnoException("Failed to set the size of the shared memory object");
      }else if(ret == -1 && errno != EWOULDBLOCK){ // another process is already using the shared memory object
	throw ErrnoException("Failed to acquire shared lock");
      }

      flock(m_fd, LOCK_SH);

      if((m_buffer = mmap(NULL, m_size, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd, 0)) == NULL)
	throw ErrnoException("Failed to mmap shared object");

      if(mlock(m_buffer, m_size))
	ErrnoException("Failed to mlock shared memory");
    }

    ~SharedMemory(){
      if(munlock(m_buffer, m_size) == 0)
	ErrnoException("Failed to munlock shared memory");

      if(munmap((char *)m_buffer, m_size))
	throw ErrnoException();

      if(close(m_fd))
	throw ErrnoException();
    }

    void *getMemory(){
      return m_buffer;
    }

  private:
    std::string m_name;
    size_t m_size;
    int m_fd;
    void *m_buffer;
};

}

#endif