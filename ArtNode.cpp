/*
 *  ArtNode.cpp
 *
 *  modified by Alex Christoffer Rasmussen 12-July 2017
 *
 *  Created by Tobias Ebsen on 6/2/13.
 *
 */

// #include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include "ArtNode.h"

ArtNode::ArtNode() {
  this->config = new NodeConfig_t();
}

ArtNode::ArtNode(NodeConfig_t & config) {
  ArtNode(config, 530);
}

ArtNode::ArtNode(NodeConfig_t & config, int size) {
  this->config = &config;
  this->bufferSize = size;
  this->buffer = new uint8_t[size];
  if (this->config->numSubNodes > 8) {this->config->numSubNodes=8;}
  if (this->config->numSubNodes <= 1) {
    this->config->numSubNodes=1;
    this->subConfig[0] = new SubNodeConfig_t;
    this->subConfig[0]->bindIndex = 0;
    this->subConfig[0]->net = this->config->startNet[0];
    this->subConfig[0]->subnet = this->config->startSubnet[0];
    this->subConfig[0]->portAddrOut[0] = this->config->startUnivers[0];
    this->subConfig[0]->numPorts = this->config->numPorts;
  }else {
    for(int i = 0; i < this->config->numSubNodes; i++) {
      this->subConfig[i] = new SubNodeConfig_t;
      this->subConfig[i]->bindIndex = i+1;
      this->subConfig[i]->net = this->config->startNet[i];
      this->subConfig[i]->subnet = this->config->startSubnet[i];
      int startUnivers = this->config->startUnivers[i];
      this->subConfig[i]->portAddrOut[0] = startUnivers++;
      this->subConfig[i]->portAddrOut[1] = startUnivers++;
      this->subConfig[i]->portAddrOut[2] = startUnivers++;
      this->subConfig[i]->portAddrOut[3] = startUnivers++;
      this->subConfig[i]->numPorts = this->config->numPorts;
    }
  }
}

ArtNode::ArtNode(NodeConfig_t & config, int size, uint8_t * buffer) {
  this->config = &config;
  this->bufferSize = size;
  this->buffer = buffer;
  if (this->config->numSubNodes > 8) {this->config->numSubNodes=8;}
  if (this->config->numSubNodes <= 1) {
    this->config->numSubNodes=1;
    this->subConfig[0] = new SubNodeConfig_t;
    this->subConfig[0]->bindIndex = 0;
    this->subConfig[0]->net = this->config->startNet[0];
    this->subConfig[0]->subnet = this->config->startSubnet[0];
    this->subConfig[0]->portAddrOut[0] = this->config->startUnivers[0];
    this->subConfig[0]->numPorts = this->config->numPorts;
  }else {
    for(int i = 0; i < this->config->numSubNodes; i++) {
      this->subConfig[i] = new SubNodeConfig_t;
      this->subConfig[i]->bindIndex = i+1;
      this->subConfig[i]->net = this->config->startNet[i];
      this->subConfig[i]->subnet = this->config->startSubnet[i];
      int startUnivers = this->config->startUnivers[i];
      this->subConfig[i]->portAddrOut[0] = startUnivers++;
      this->subConfig[i]->portAddrOut[1] = startUnivers++;
      this->subConfig[i]->portAddrOut[2] = startUnivers++;
      this->subConfig[i]->portAddrOut[3] = startUnivers++;
      this->subConfig[i]->numPorts = this->config->numPorts;
    }
  }
}

// ArtNode::ArtNode() {
//     this->config = new ArtConfig_t();
// }
//
// ArtNode::ArtNode(ArtConfig_t & config) {
//     ArtNode(config, 530);
// }
//
// ArtNode::ArtNode(ArtConfig_t & config, int size) {
//     this->config = &config;
//     this->bufferSize = size;
//     this->buffer = new uint8_t[size];
// }
//
// ArtNode::ArtNode(ArtConfig_t & config, int size, uint8_t * buffer) {
//     this->config = &config;
//     this->bufferSize = size;
//     this->buffer = buffer;
// }

uint32_t ArtNode::broadcastIP() {
    uint32_t mask = config->mask[0] | (config->mask[1] << 8) | (config->mask[2] << 16) | (config->mask[3] << 24);
    uint32_t ip = config->ip[0] | (config->ip[1] << 8) | (config->ip[2] << 16) | (config->ip[3] << 24);
    return (~mask) | ip;
}

uint16_t ArtNode::getAddress(uint8_t subUni, uint8_t net) {
  return subUni + (net << 8);
}

uint16_t ArtNode::getStartAddress(uint8_t bind_index) {
  return config->startUnivers[bind_index] + (config->startSubnet[bind_index] << 4) + (config->startNet[bind_index] << 8);
}

// uint16_t ArtNode::getStartAddress() {
//   return config->portAddrOut[0] + (config->subnet << 4) + (config->net << 8);
// }

// uint8_t ArtNode::getPort(uint8_t subUni, uint8_t net) {
//     if ((net == config->net) && ((subUni >> 4) == config->subnet)) {
//         subUni &= 0x0F;
//         for (int i=0; i<config->numPorts; i++) {
//             if ((config->portTypes[i] & PortTypeInput) && (subUni == config->portAddrIn[i]))
//                 return i;
//             if ((config->portTypes[i] & PortTypeOutput) && (subUni == config->portAddrOut[i]))
//                 return i;
//         }
//     }
//     return -1;
// }

void ArtNode::createPollReply(uint8_t bind_index) {
  ArtPollReply_t *reply = (ArtPollReply_t*)buffer;
  memset(buffer, 0, sizeof(ArtPollReply_t));

  memcpy(reply->ID, "Art-Net", 8);
  reply->OpCode = OpPollReply;
  memcpy(reply->BoxAddr.IP, config->ip, 4);
  reply->BoxAddr.Port = config->udpPort;

  reply->VersionInfoHi = config->verHi;
  reply->VersionInfoLo = config->verLo;

  reply->NetSwitch = subConfig[bind_index]->net;
  reply->SubSwitch = subConfig[bind_index]->subnet;

  reply->OemHi = config->OEM>>8;
  reply->OemLo = config->OEM & 0xFF;

  if (config->extendedFeatures == true) {
    reply->OemHi |= 0x8000;
  }

  strcpy((char*)reply->ShortName, config->shortName);
  strcpy((char*)reply->LongName, config->longName);

  int numPorts = subConfig[bind_index]->numPorts;
  reply->NumPortsLo = numPorts;

  for(int i = 0; i < numPorts; i ++) {
    reply->PortTypes[i] = PortTypeDmx | PortDirOut;
  }
  memset(reply->GoodInput, 0x8, numPorts);          // Input disabled
  memset(reply->GoodOutput, 0x80, numPorts);        // Very important for MadMapper!
  memset(reply->SwIn, 0, numPorts);
  memcpy(reply->SwOut, subConfig[bind_index]->portAddrOut, numPorts);
  reply->Style = StNode;
  memcpy(reply->Mac, config->mac, 6);
  reply->Status2 = 0x8; // Supports 15bit address (ArtNet 3)
  if(config->dhcp == true) {
    reply->Status2 |= 0x6;
  }
  memcpy(reply->BindIp, config->ip, 4);
  reply->BindIndex = bind_index+1;
}

// void ArtNode::createPollReply(uint8_t bind_index) {
//     ArtPollReply_t *reply = (ArtPollReply_t*)buffer;
//     memset(buffer, 0, sizeof(ArtPollReply_t));
//
//     memcpy(reply->ID, "Art-Net", 8);
//     reply->OpCode = OpPollReply;
//     memcpy(reply->BoxAddr.IP, config->ip, 4);
//     reply->BoxAddr.Port = config->udpPort;
//
//     reply->VersionInfoHi = config->verHi;
//     reply->VersionInfoLo = config->verLo;
//
//     reply->NetSwitch = config->net;
//     reply->SubSwitch = config->subnet;
//
//     reply->OemHi = config->OEM>>8;
//     reply->OemLo = config->OEM & 0xFF;
//
//     if (config->extendedFeatures == true) {
//       reply->OemHi |= 0x8000;
//     }
//
//     strcpy((char*)reply->ShortName, config->shortName);
//     strcpy((char*)reply->LongName, config->longName);
//
//     reply->NumPortsLo = config->numPorts;
//     memcpy(reply->PortTypes, config->portTypes, config->numPorts);
//     memset(reply->GoodInput, 0x8, config->numPorts);          // Input disabled
//     memset(reply->GoodOutput, 0x80, config->numPorts);        // Very important for MadMapper!
//     memcpy(reply->SwIn, config->portAddrIn, config->numPorts);
//     memcpy(reply->SwOut, config->portAddrOut, config->numPorts);
//     reply->Style = StNode;
//     memcpy(reply->Mac, config->mac, 6);
//     reply->Status2 = 0x8; // Supports 15bit address (ArtNet 3)
//     if(config->dhcp == true) {
//       reply->Status2 |= 0x6;
//     }
//     reply->BindIndex = bind_index;
// }

void ArtNode::createIpProgReply() {
    ArtIpProgReply_t *reply = (ArtIpProgReply_t*)buffer;
    memset(buffer, 0, sizeof(ArtIpProgReply_t));

    memcpy(buffer, "Art-Net", 8);
    reply->OpCode = OpIpProgReply;

    reply->ProtVerLo = ProtocolVersion;

    reply->ProgIpHi = config->ip[0];
    reply->ProgIp2 = config->ip[1];
    reply->ProgIp1 = config->ip[2];
    reply->ProgIpLo = config->ip[3];

    reply->ProgSmHi = config->mask[0];
    reply->ProgSm2 = config->mask[1];
    reply->ProgSm1 = config->mask[2];
    reply->ProgSmLo = config->mask[3];

    reply->ProgPortHi = config->udpPort >> 8;
    reply->ProgPortLo = config->udpPort & 0xFF;
    reply->Status = config->dhcp ? 0 : 0x40;
}
