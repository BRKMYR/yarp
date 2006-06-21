// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
#ifndef _YARP2_PORT_
#define _YARP2_PORT_

#include <yarp/os/Contactable.h>
#include <yarp/os/PortReader.h>
#include <yarp/os/PortWriter.h>
#include <yarp/os/PortReaderCreator.h>

namespace yarp {
    namespace os {
        class Port;
    }
}

/**
 * A mini-server for network communication.
 * It maintains a dynamic collection of incoming and
 * outgoing connections.  Data coming from any incoming connection can
 * be received by calling Port::read.  Calls to Port::write
 * result in data being sent to all the outgoing connections.
 * For help sending and receiving data in the background, see
 * BufferedPort, or PortReaderBuffer and PortWriterBuffer.
 *
 * For examples and help, see: \ref what_is_a_port
 *
 */
class yarp::os::Port : public Contactable {

public:
    /**
     * Constructor.  The port begins life in a dormant state. Call
     * Port::open to start things happening.
     */
    Port();


    /**
     * Destructor.
     */
    virtual ~Port();

    // documentation provided in Contactable
    bool open(const char *name);

    // documentation provided in Contactable
    bool open(const Contact& contact, bool registerName = true);

    // documentation provided in Contactable
    bool addOutput(const char *name) {
        return addOutput(Contact::byName(name));
    }

    // documentation provided in Contactable
    bool addOutput(const char *name, const char *carrier) {
        return addOutput(Contact::byName(name).addCarrier(carrier));
    }

    // documentation provided in Contactable
    bool addOutput(const Contact& contact);

    // documentation provided in Contactable
    void close();

    // documentation provided in Contactable
    Contact where();


    /**
     * Write an object to the port.
     * @param writer any object that knows how to write itself to a
     * network connection - see for example Bottle
     * @return true iff the object is successfully written
     */
    bool write(PortWriter& writer);

    /**
     * Write an object to the port, then expect one back.
     * @param writer any object that knows how to write itself to a
     * network connection - see for example Bottle
     * @param reader any object that knows how to read itself from a
     * network connection - see for example Bottle
     * @return true iff an object is successfully written and read
     */
    bool write(PortWriter& writer, PortReader& reader) const;

    /**
     * Read an object from the port.
     * @param reader any object that knows how to read itself from a
     * network connection - see for example Bottle
     * @return true iff the object is successfully read
     */
    bool read(PortReader& reader);

    /**
     * set an external reader for port data
     * @param reader the external reader to use
     */
    void setReader(PortReader& reader);

    void setReaderCreator(PortReaderCreator& creator);

    /**
     * control whether writing from this port is done in the background.
     * @param backgroundFlag if true, calls to Port::write should return 
     * immediately
     */
    void enableBackgroundWrite(bool backgroundFlag);


    /**
     * report whether the port is currently writing data.
     * @result true iff the port is writing in the background.
     */
    bool isWriting();

private:
    void *implementation;

};

#endif
