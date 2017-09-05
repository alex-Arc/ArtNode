/*
 *  ArtNode.h
 *
 *  modified by Alex Christoffer Rasmussen 12-July 2017
 *  Update for Art-Net 4 protocol.
 *
 *  Created by Tobias Ebsen 6/2/13
 *
 *  Implementation of the Art-Net 3 protocol.
 *
 *  This file is free software; you can redistribute it and/or modify
 *  it under the terms of GNU General Public License version 3 as
 *  published by the Free Software Foundation.
 *
 *  Art-Net(TM) Designed by and Copyright Artistic Licence Holdings Ltd
 *
 */

#ifndef ArtNode_h
#define ArtNode_h

#pragma pack(1)
#include "Art-Net.h"
#include <inttypes.h>

typedef struct S_ArtHeader {
  uint8_t ID[8];                    // protocol ID = "Art-Net"
  uint16_t OpCode;                  // == OpPoll
} ArtHeader_t;

typedef struct SubNodeConfig_s {
  uint8_t  net;
  uint8_t  subnet;
  uint8_t  numPorts;
  uint8_t  portAddrOut[4];
  uint8_t	 bindIndex;
} SubNodeConfig_t;

typedef struct NodeConfig_s {
  uint8_t  mac[6];
  uint8_t  ip[4];
  uint8_t  mask[4];
  uint16_t udpPort;
  uint8_t  dhcp;
  uint8_t  startNet[8];
  uint8_t  startSubnet[8];
  uint8_t  extendedFeatures;
  uint16_t OEM;
  char     shortName[18];
  char     longName[64];
  uint8_t  numSubNodes;
  uint8_t  numPorts;
  uint8_t  startUnivers[8];
  uint8_t  verHi;
  uint8_t  verLo;
} NodeConfig_t;

typedef struct S_ArtConfig {
  uint8_t  mac[6];
  uint8_t  ip[4];
  uint8_t  mask[4];
  uint16_t udpPort;
  uint8_t  dhcp;
  uint8_t  net;
  uint8_t  subnet;
  uint8_t  extendedFeatures;
  uint16_t OEM;
  char     shortName[18];
  char     longName[64];
  uint8_t  numPorts;
  uint8_t  portTypes[4];
  uint8_t  portAddrIn[4];
  uint8_t  portAddrOut[4];
  uint8_t	 bindIndex;
  uint8_t  verHi;
  uint8_t  verLo;
} ArtConfig_t;

typedef struct S_ArtDmxHeader {
    uint8_t ID[8];
    uint16_t OpCode;
    uint8_t ProtVerHi;
    uint8_t ProtVerLo;
    uint8_t Sequence;
    uint8_t Physical;
    uint8_t SubUni;
    uint8_t Net;
    uint16_t Length;
} ArtDmxHeader_t;

class ArtNode {
public:

    ArtNode();
    ArtNode(NodeConfig_t & config);
    ArtNode(NodeConfig_t & config, int size);
    ArtNode(NodeConfig_t & config, int size, uint8_t * buffer);
    // ArtNode();
    // ArtNode(ArtConfig_t & config);
    // ArtNode(ArtConfig_t & config, int size);
    // ArtNode(ArtConfig_t & config, int size, unsigned char * buffer);

    ArtConfig_t & getConfig();
    uint16_t getAddress(uint8_t subUni, uint8_t net);
    uint16_t getStartAddress(uint8_t bind_index);
    uint16_t getEndAddress(uint8_t bind_index);
    // uint16_t getStartAddress();
    uint8_t* getBufferData();
    uint16_t getBufferSize();

    uint32_t broadcastIP();
    // uint8_t getPort(uint8_t subUni, uint8_t net);

    void createPoll();
    void createPollReply(uint8_t bind_index = 0);
    // void createDmx();
    // void createIpProg();
    void createIpProgReply();

protected:
    // ArtConfig_t *config;
    NodeConfig_t *config;
    SubNodeConfig_t *subConfig[8];
    uint8_t * buffer;
    int bufferSize;
};

#endif
