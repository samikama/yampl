#ifndef IPC_ZMQSOCKETFACTORY_H
#define IPC_ZMQSOCKETFACTORY_H

#include <zmq.hpp>

#include "SocketFactory.h"

namespace IPC{

class ZMQSocketFactory : public ISocketFactory{
  public:
    ZMQSocketFactory(){
      static bool initialized = false;

      if(!initialized){
	m_context = new zmq::context_t(1);
	initialized = true;
      }
    }

    virtual ISocket *createProducerSocket(Channel channel, bool ownership = true, void (*deallocator)(void *, void *) = defaultDeallocator);
    virtual ISocket *createConsumerSocket(Channel channel, bool ownership = true);
    virtual ISocket *createClientSocket(Channel channel, bool ownership = true, void (*deallocator)(void *, void *) = defaultDeallocator);
    virtual ISocket *createServerSocket(Channel channel, bool ownership = true, void (*deallocator)(void *, void *) = defaultDeallocator);

  private:
    static zmq::context_t *m_context;
};

}

#endif
