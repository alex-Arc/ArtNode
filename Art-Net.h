//////////////////////////////////////////////////////////////
//
//	Copyright Artistic Licence Holdings Ltd 1998-2017
//	Author:	Wayne Howell
//	Email:	Support@ArtisticLicence.com
//
//  modified by Alex Christoffer Rasmussen 12-July 2017
//////////////////////////////////////////////////////////////

#ifndef _ARTNET_H_
#define _ARTNET_H_

#include "Art-NetOemCodes.h"
#include <inttypes.h>

#define NETID0 2
	// Primary 2.x.y.z
#define NETID1 10
	// Secondary 10.x.y.z

#define DefaultPort 0x1936

#define ProtocolVersion 14
	// Art-Net protocol version.

// OpCodes (byte-swapped)

#define OpPoll              0x2000 // Poll
#define OpPollReply   	  	0x2100 // ArtPollReply
#define OpPollFpReply    	  0x2200 // Additional advanced reply
#define OpDiagData	    	  0x2300 // Diagnostics data message
#define OpCommand           0x2400 // Send command / property strings.

#define OpOutput 	       	  0x5000 // Zero start code dmx packets
#define OpDmx	 	       	    0x5000 // Zero start code dmx packets
#define OpNzs	 	       	    0x5100 // Non-Zero start code dmx packets (excluding RDM)
#define OpSync 	       	    0x5200 // to force synchronous transfer of ArtDmx packets to a node’s output.

#define OpAddress 	  	    0x6000 // Program Node Settings

#define OpInput 	          0x7000 // Setup DMX input enables

#define OpTodRequest        0x8000 // Requests RDM Discovery ToD
#define OpTodData        	  0x8100 // Send RDM Discovery ToD
#define OpTodControl        0x8200 // Control RDM Discovery
#define OpRdm	        	    0x8300 // Non-Discovery RDM Message
#define OpRdmSub            0x8400 // Compressed subdevice data

#define OpVideoSetup       	0xA010 // video screen setup information
#define OpVideoPalette      0xA020 //colour palette setup information
#define OpVideoData         0xA040 // display data

#define OpMacMaster         0xF000 //deprecated.
#define OpMacSlave          0xF100 //deprecated.
#define OpFirmwareMaster    0xF200 // For sending firmware updates
#define OpFirmwareReply     0xF300 // Node reply during firmware update
#define OpFileTnMaster      0xF400 // Upload user file to node
#define OpFileFnMaster      0xF500 // Download user file from node
#define OpFileFnReply       0xF600 // Ack file packet received from node

#define OpIpProg	          0xF800 // For sending IP programming info.
#define OpIpProgReply	      0xF900 // Node reply during IP programming.

#define OpMedia	        	  0x9000 // Streaming data from media server
#define OpMediaPatch        0x9100 // Coord setup to media server
#define OpMediaControl      0x9200 // Control media server
#define OpMediaControlReply 0x9300 // Reply from media server

#define OpTimeCode          0x9700 // Transports Time Code
#define OpTimeSync          0x9800 // Time & Date synchronise nodes
#define OpTrigger          	0x9900 // Trigger and macro
#define OpDirectory         0x9a00 // Request node file directory
#define OpDirectoryReply    0x9b00 // Send file directory macro


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Style codes for ArtPollReply
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define StNode	      0	// Responder is a Node (DMX <-> Ethernet Device)
#define StController	1	// Lighting console or similar
#define StMedia       2	// Media Server such as Video-Map, Hippotizer, RadLight, Catalyst, Pandora's Box
#define StRoute	      3	// Data Routing device
#define StBackup	    4	// Data backup / real time player such as Four-Play
#define StConfig	    5	// Configuration tool such as DMX-Workshop
#define StVisual      6 // Visualiser


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Report Codes (Status reports)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define RcDebug       0x0000	// Booted in debug mode (Only used in development
#define RcPowerOk	    0x0001	// Power On Tests successful
#define RcPowerFail	  0x0002	// Hardware tests failed at Power On
#define RcSocketWr1	  0x0003	// Last UDP from Node failed due to truncated length,
						                  //  Most likely caused by a collision.
#define RcParseFail	  0x0004	// Unable to identify last UDP transmission.
						                  // Check OpCode and packet length
#define RcUdpFail	    0x0005	// Unable to open Udp Socket in last transmission attempt
#define RcShNameOk    0x0006	// Confirms that Short Name programming via ArtAddress accepted
#define RcLoNameOk    0x0007	// Confirms that Long Name programming via ArtAddress accepted
#define RcDmxError    0x0008	// DMX512 receive errors detected
#define RcDmxUdpFull	0x0009	// Ran out of internal DMX transmit buffers
				                      //  Most likely caused by receiving ArtDmx
				                      //  packets at a rate faster than DMX512 transmit
				                      //  speed
#define RcDmxRxFull   0x000A	// Ran out of internal DMX rx buffers
#define RcSwitchErr	  0x000B	// Rx Universe switches conflict
#define RcConfigErr	  0x000C	// Node's hardware configuration is wrong
#define RcDmxShort	  0x000D	// DMX output is shorted
#define RcFirmFail	  0x000E	// Last firmware upload failed.
#define RcUserFail	  0x000F	// User attempted to change physical switches when universe switches locked
#define RcFactoryRes  0x0010  // Factory reset has occurred.


// Defines for ArtAddress Command field

#define AcNone          0       // No Action
#define AcCancelMerge   1       // The next ArtDmx packet cancels Node's merge mode
#define AcLedNormal     2       // Node front panel indicators operate normally
#define AcLedMute       3       // Node front panel indicators are muted
#define AcLedLocate     4       // Fast flash all indicators for locate
#define AcResetRxFlags  5       // Reset the receive DMX flags for errors, SI's, Text & Test packets

#define AcMergeLtp0	0x10		// Set Port 0 to merge in LTP.
#define AcMergeLtp1	0x11		// Set Port 1 to merge in LTP.
#define AcMergeLtp2	0x12		// Set Port 2 to merge in LTP.
#define AcMergeLtp3	0x13		// Set Port 3 to merge in LTP.

#define AcMergeHtp0	0x50		// Set Port 0 to merge in HTP. (Default Mode)
#define AcMergeHtp1	0x51		// Set Port 1 to merge in HTP.
#define AcMergeHtp2	0x52		// Set Port 2 to merge in HTP.
#define AcMergeHtp3	0x53		// Set Port 3 to merge in HTP.

#define AcClearOp0	0x90		// Clear all data buffers associated with output port 0
#define AcClearOp1	0x91		// Clear all data buffers associated with output port 1
#define AcClearOp2	0x92		// Clear all data buffers associated with output port 2
#define AcClearOp3	0x93		// Clear all data buffers associated with output port 3

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Firmeware codes
//Defines the packet contents as follows
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Types from server
#define FirmFirst 0x00
#define FirmCont 0x01
#define FirmLast 0x02
#define UbeaFirst 0x03
#define UbeaCont 0x04
#define UbeaLast 0x05

// types from node
#define FirmBlockGood 0x00
#define FirmAll 0x01
#define FirmFail 0xFF

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Port types
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define PortDirOut      0x80
#define PortDirIn       0x40

#define PortTypeDmx     0x00
#define PortTypeMidi    0x01
#define PortTypeAvab    0x02
#define PortTypeCmx     0x03
#define PortTypeAdb     0x04
#define PortTypeArtnet  0x05
//000000 = DMX
//000001 = MIDI
//000010 = Avab
//000011 = Colortran CMX
//000100 = ADB 62.5
//000101 = Art-Net
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Data array lengths
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define MaxNumPorts 4
#define MaxExNumPorts 32
#define ShortNameLength 18
#define LongNameLength 64
#define PortNameLength 32
#define MaxDataLength 512


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Diagnostics priority Codes
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define	DpLow       0x10 //Low priority message
#define	DpMed 		  0x40 //Medium priority message.
#define	DpHigh 		  0x80 //High priority message
#define	DpCritical 	0xe0 //Critical priority message.
#define	DpVol 		  0xf0 //volatile messages are displayed on a caption line in DMX-Workshop, all others are listed in order

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Tod Command defines for RDM discovery.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define TodFull		0	// Full Discovery.
#define TodNak		0xff	// ToD not available.

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RDM discovery control commands.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define AtcNone		0	// No Action.
#define AtcFlush	1	// Force full discovery.

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RDM Message Processing commands.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define ArProcess		0	// Process Message.

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Sub-Structure for IP and Port
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct {
	uint8_t IP[4];	// IP address
	uint16_t Port;	// UDP port	BYTE-SWAPPED MANUALLY
} Addr_t;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Poll request from Server to Node or Server to Server.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct S_ArtPoll {
	uint8_t ID[8];                    // protocol ID = "Art-Net"
	uint16_t OpCode;                  // == OpPoll
	uint8_t ProtVerHi;                // 0
	uint8_t ProtVerLo;                // protocol version, set to ProtocolVersion
	uint8_t TalkToMe;                 // bit 0 = not used
                                  // bit 1 = 0 then Node only sends ArtPollReply when polled
                                  // bit 1 = 1 then Node sends ArtPollReply when it needs
                                  // bit 2 = 0 Do not send me disagnostic messages
                                  // bit 2 = 1 Send me diagnostics messages
                                  // bit 3 = 0 (If Bit 2 then) broadcast diagnostics messages
                                  // bit 3 = 1 (If Bit 2 then) unicast diagnostics messages
	uint8_t Priority;                 // Set the lowest priority of diagnostics message that node should send. See DpXxx defines above.
} ArtPoll_t;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ArtPollReply is sent in reply to an ArtPoll. It is always broadcast
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct S_ArtPollReply {
	uint8_t ID[8];          // protocol ID = "Art-Net"
	uint16_t OpCode;        // == OpPollReply
	Addr_t BoxAddr;       // 0 if not yet configured

	uint8_t VersionInfoHi;  // The node's current FIRMWARE VERS hi
	uint8_t VersionInfoLo;  // The node's current FIRMWARE VERS lo

	uint8_t NetSwitch;      // Bits 14-8 of the 15 bit universe number are encoded into the bottom 7 bits of this field.
	// This is used in combination with SubSwitch and Swin[] or Swout[] to produce the full universe address.

	uint8_t SubSwitch;      // Bits 7-4 of the 15 bit universe number are encoded into the bottom 4 bits of this field.
	// This is used in combination with NetSwitch and Swin[] or Swout[] to produce the full universe address.

	uint8_t OemHi;
	uint8_t OemLo;			   // Manufacturer code, bit 15 set if
					             // extended features avail

	uint8_t UbeaVersion;   // Firmware version of UBEA

	uint8_t Status1;       // bit 0 = 0 UBEA not present
                       // bit 0 = 1 UBEA present
          						 // bit 1 = 0 Not capable of RDM (Uni-directional DMX)
          						 // bit 1 = 1 Capable of RDM (Bi-directional DMX)
          						 // bit 2 = 0 Booted from flash (normal boot)
          						 // bit 2 = 1 Booted from ROM (possible error condition)
                       // bit 3 = Not used
                       // bit 54 = 00 Universe programming authority unknown
                       // bit 54 = 01 Universe programming authority set by front panel controls
                       // bit 54 = 10 Universe programming authority set by network
                       // bit 76 = 00 Indicators Normal
                       // bit 76 = 01 Indicators Locate
                       // bit 76 = 10 Indicators Mute

	uint8_t EstaManLo;		 // ESTA manufacturer id, lo byte
	uint8_t EstaManHi;		 // ESTA manufacturer id, hi byte

	uint8_t ShortName[ShortNameLength]; // short name defaults to IP
	uint8_t LongName[LongNameLength];   // long name

  uint8_t NodeReport[LongNameLength]; // Text feedback of Node status or errors
					                          //  also used for debug info

	uint8_t NumPortsHi;                 // 0
	uint8_t NumPortsLo;                 // 4 If num i/p ports is dif to output ports, return biggest

	uint8_t PortTypes[MaxNumPorts];     // bit 7 is output
                                    // bit 6 is input
                                    // bits 0-5 are protocol number
                                    //000000 = DMX
                                    //000001 = MIDI
                                    //000010 = Avab
                                    //000011 = Colortran CMX
                                    //000100 = ADB 62.5
                                    //000101 = Art-Net
                                    // for DMX-Hub ={0xc0,0xc0,0xc0,0xc0};

  uint8_t GoodInput[MaxNumPorts];  	  // bit 7 is data received
                                    // bit 6 is data includes test packets
                                    // bit 5 is data includes SIP's
                          					// bit 4 is data includes text
                          					// bit 3 set is input is disabled
                                    // bit 2 is receive errors
                          					// bit 1-0 not used, transmitted as zero.
                          					// Don't test for zero!

	uint8_t GoodOutput[MaxNumPorts]; 	  // bit 7 is data is transmitting
                          					// bit 6 is data includes test packets
                          					// bit 5 is data includes SIP's
                          					// bit 4 is data includes text
                          					// bit 3 output is merging data.
                          					// bit 2 set if DMX output short detected on power up
                          					// bit 1 set if DMX output merge mode is LTP
                          					// 0 Set – Output is selected to transmit sACN.
                                    // Clr – Output is selected to transmit Art-Net.

	uint8_t SwIn[MaxNumPorts];   	      // Bits 3-0 of the 15 bit universe number are encoded into the low nibble
                          					// This is used in combination with SubSwitch and NetSwitch to produce the full universe address.
                          					// THIS IS FOR INPUT - ART-NET or DMX
                          					// NB ON ART-NET II THESE 4 UNIVERSES WILL BE UNICAST TO.

	uint8_t SwOut[MaxNumPorts];   	    // Bits 3-0 of the 15 bit universe number are encoded into the low nibble
  // This is used in combination with SubSwitch and NetSwitch to produce the full universe address.
  // data belongs
  // THIS IS FOR OUTPUT - ART-NET or DMX.
  // NB ON ART-NET II THESE 4 UNIVERSES WILL BE UNICAST TO.

	uint8_t SwVideo;		  // Low nibble is the value of the video
					            // output channel

	uint8_t SwMacro;		  // Bit 0 is Macro input 1
					            // Bit 7 is Macro input 8

  uint8_t SwRemote;		  // Bit 0 is Remote input 1
				              // Bit 7 is Remote input 8

	uint8_t Spare1;       // Spare, currently zero
	uint8_t Spare2;       // Spare, currently zero
	uint8_t Spare3;       // Spare, currently zero
	uint8_t Style;        // Set to Style code to describe type of equipment

	uint8_t Mac[6];   	  // Mac Address, zero if info not available

	uint8_t BindIp[4];	  // If this unit is part of a larger or modular product, this is the IP of the root device.
	uint8_t	BindIndex;		// Set to zero if no binding, otherwise this number represents the order of bound devices. A lower number means closer to root device.

	uint8_t Status2;      // bit 0 = 0 Node does not support web browser
        					    // bit 0 = 1 Node supports web browser configuration
                      // bit 1 = 0 Node's IP address is manually configured
        					    // bit 1 = 1 Node's IP address is DHCP configured
        					    // bit 2 = 0 Node is not DHCP capable
                      // bit 2 = 1 Node is DHCP capable
                      // bit 2-7 not implemented, transmit as zero

  uint8_t Filler[26];   // Filler bytes, currently zero.
} ArtPollReply_t;


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// The following packet is used to transfer zero start code DMX packets
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct S_ArtDmx {
	uint8_t ID[8];                   // protocol ID = "Art-Net"
	uint16_t OpCode;                 // == OpOutput
	uint8_t ProtVerHi;               // 0
	uint8_t ProtVerLo;               // protocol version, set to ProtocolVersion
	uint8_t Sequence;                // 0 if not used, else 1-255 incrementing sequence number
	uint8_t Physical;                // The physical i/p 0-3 that originated this packet. For Debug / info only
	uint8_t SubUni;                	 // The low 8 bits of the 15 bit universe address.
	uint8_t Net;                	   // The high 7 bits of the 15 bit universe address.
	uint16_t Length;			           // BYTE-SWAPPED MANUALLY. Length of array below
	uint8_t Data[MaxDataLength];     // Variable length array. First entry is channel 1 level (NOT THE START CODE)
} ArtDmx_t;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// The following packet is used to transfer selected non-zero start code DMX packets
// IT MUST NOT BE USED FOR ZERO OR RDM PACKETS or any ESTA reserved start codes
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct S_ArtNzs {
	uint8_t ID[8];                    // protocol ID = "Art-Net"
	uint16_t OpCode;                  // == OpOutput
	uint8_t ProtVerHi;                // 0
	uint8_t ProtVerLo;                // protocol version, set to ProtocolVersion
	uint8_t Sequence;		             	// 0 if not used, else 1-255 incrementing sequence number
	uint8_t StartCode;                // The start code
	uint8_t SubUni;                	  // The low 8 bits of the 15 bit universe address.
	uint8_t Net;                	    // The high 7 bits of the 15 bit universe address.
	uint16_t Length;			            // BYTE-SWAPPED MANUALLY. Length of array below
	uint8_t Data[MaxDataLength];
} ArtNzs_t;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// The following packet is used to transfer diagnostic data from node to server
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct S_ArtDiagData {
	uint8_t ID[8];                    // protocol ID = "Art-Net"
	uint16_t OpCode;                  // == OpDiagData
	uint8_t ProtVerHi;                // 0
	uint8_t ProtVerLo;                // protocol version, set to ProtocolVersion
	uint8_t Filler1;
	uint8_t Priority;                 // The message priority, see DpXxxx defines above.
	uint8_t Filler2;
	uint8_t Filler3;
	uint16_t Length;			// BYTE-SWAPPED MANUALLY. Length of array below
	uint8_t Data[MaxDataLength]; 	// Variable size array which is defined as maximum here.
} ArtDiagData_t;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// The following packet is used to transfer diagnostic data from node to server
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct S_ArtCommand {
	uint8_t ID[8];                    // protocol ID = "Art-Net"
	uint16_t OpCode;                  // == OpCommand
	uint8_t ProtVerHi;                // 0
	uint8_t ProtVerLo;                // protocol version, set to ProtocolVersion
	uint8_t EstaManHi;		// ESTA manufacturer id, hi byte
	uint8_t EstaManLo;		// ESTA manufacturer id, lo byte  // == 0xffff for the global command set
	uint16_t Length;			// BYTE-SWAPPED MANUALLY. Length of array below. Range 0 - 512
	uint8_t Data[MaxDataLength];  	// Variable size array which is defined as maximum here. Contains null terminated command text.
} ArtCommand_t;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// The following packet is used to transfer settings from server to node
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct S_ArtAddress {
	uint8_t ID[8];                    // protocol ID = "Art-Net"
	uint16_t OpCode;                  // == OpAddress
	uint8_t ProtVerHi;                // 0
	uint8_t ProtVerLo;                // protocol version, set to ProtocolVersion

	uint8_t NetSwitch;		// Bits 14-8 of the 15 bit universe number are encoded into the bottom 7 bits of this field.
					// This is used in combination with SubSwitch and SwIn[] or SwOut[] to produce the full universe address.
					// This value is ignored unless bit 7 is high. i.e. to program a  value 0x07, send the value as 0x87.
					// Send 0x00 to reset this value to the physical switch setting.
					// Use value 0x7f for no change.


	uint8_t BindIndex;                  // BindIndex


	uint8_t ShortName[ShortNameLength]; // null ignored

	uint8_t LongName[LongNameLength];   // null ignored

	uint8_t SwIn[MaxNumPorts];   	// Bits 3-0 of the 15 bit universe number for a given input port are encoded into the bottom 4 bits of this field.
					// This is used in combination with NetSwitch and SubSwitch to produce the full universe address.
					// This value is ignored unless bit 7 is high. i.e. to program a  value 0x07, send the value as 0x87.
					// Send 0x00 to reset this value to the physical switch setting.
					// Use value 0x7f for no change.
					// Array size is fixed

	uint8_t SwOut[MaxNumPorts];   	// Bits 3-0 of the 15 bit universe number for a given output port are encoded into the bottom 4 bits of this field.
					// This is used in combination with NetSwitch and SubSwitch to produce the full universe address.
					// This value is ignored unless bit 7 is high. i.e. to program a  value 0x07, send the value as 0x87.
					// Send 0x00 to reset this value to the physical switch setting.
					// Use value 0x7f for no change.
					// Array size is fixed

	uint8_t SubSwitch;	   	// Bits 7-4 of the 15 bit universe number are encoded into the bottom 4 bits of this field.
					// This is used in combination with NetSwitch and SwIn[] or SwOut[] to produce the full universe address.
					// This value is ignored unless bit 7 is high. i.e. to program a  value 0x07, send the value as 0x87.
					// Send 0x00 to reset this value to the physical switch setting.
					// Use value 0x7f for no change.

	uint8_t SwVideo;		   	// Low nibble is the value of the video
					// output channel
					// Bit 7 hi = use data

	uint8_t Command;                  // see Acxx definition list



} ArtAddress_t;


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Transmitted by Server to set or test the Node's custom IP settings.
//
// NB. This function is provided for specialist applications. Do not implement this functionality
//     unless really needed!!!
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct S_ArtIpProg {
	uint8_t ID[8];                    // protocol ID = "Art-Net"
	uint16_t OpCode;                  // == OpIpProg
	uint8_t ProtVerHi;                // 0
	uint8_t ProtVerLo;                // protocol version, set to ProtocolVersion
	uint8_t Filler1;	                // TalkToMe position in ArtPoll
	uint8_t Filler2;                  // The physical i/p 0-3. For Debug only
	uint8_t Command;			// Bit fields as follows: (Set to zero to poll for IP info)
							// Bit 7 hi for any programming.
                                                        // Bit 6 hi = enable DHCP (overrides all lower bits.
							// Bit 5-4 not used, set to zero.
							// Bit 3 hi = Return all three paraameters to default. (This bit takes priority).
							// Bit 2 hi = Use custom IP in this packet.
							// Bit 1 hi = Use custom Subnet Mask in this packet.
							// Bit 0 hi = Use custom Port number in this packet.

	uint8_t Filler4;			  // Fill to word boundary.
	uint8_t ProgIpHi;			  // Use this IP if Command.Bit2
	uint8_t ProgIp2;
	uint8_t ProgIp1;
	uint8_t ProgIpLo;

	uint8_t ProgSmHi;			  // Use this Subnet Mask if Command.Bit1
	uint8_t ProgSm2;
	uint8_t ProgSm1;
	uint8_t ProgSmLo;

	uint8_t ProgPortHi;		  // Use this Port Number if Command.Bit0
	uint8_t ProgPortLo;

	uint8_t Spare1;			  // Set to zero, do not test in receiver.
	uint8_t Spare2;
	uint8_t Spare3;
	uint8_t Spare4;
	uint8_t Spare5;
	uint8_t Spare6;
	uint8_t Spare7;
	uint8_t Spare8;

} ArtIpProg_t;


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Transmitted by Node in response to ArtIpProg.
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct S_ArtIpProgReply {
	uint8_t ID[8];                    // protocol ID = "Art-Net"
	uint16_t OpCode;                  // == OpIpProgReply
	uint8_t ProtVerHi;                // 0
	uint8_t ProtVerLo;                // protocol version, set to ProtocolVersion
	uint8_t Filler1;
	uint8_t Filler2;
	uint8_t Filler3;			  // Fill to word boundary.
	uint8_t Filler4;			  // Fill to word boundary.

	uint8_t ProgIpHi;			  // The node's current IP Address
	uint8_t ProgIp2;
	uint8_t ProgIp1;
	uint8_t ProgIpLo;

	uint8_t ProgSmHi;			  // The Node's current Subnet Mask
	uint8_t ProgSm2;
	uint8_t ProgSm1;
	uint8_t ProgSmLo;

	uint8_t ProgPortHi;			  // The Node's current Port Number
	uint8_t ProgPortLo;

	uint8_t Status;			// Bit 6 set if DHCP enabled
	uint8_t Spare2;			// Set to zero, do not test in receiver.
	uint8_t Spare3;
	uint8_t Spare4;
	uint8_t Spare5;
	uint8_t Spare6;
	uint8_t Spare7;
	uint8_t Spare8;

} ArtIpProgReply_t;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Frimeware update from Server to Node.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct S_ArtFirmwareMaster {
	uchar ID[8];                    // protocol ID = "Art-Net"
	ushort OpCode;                  // == OpFirmwareMaster
	uchar ProtVerHi;                // 0
	uchar ProtVerLo;                // protocol version, set to ProtocolVersion
  uchar Filler1;
	uchar Filler2;
	uchar Type;			// Defines the packet contents as follows:
                  // 0x00 FirmFirst: The first packet of firmware upload.
                  // 0x01 FirmCont: A continuation packet of a firmware upload.
                  // 0x02 FirmLast: The last packet of a firmware upload.
                  // 0x03 UbeaFirst The first packet of a UBEA upload.
                  // 0x04 UbeaCont A consecutive continuation packet of a UBEA upload.
                  // 0x05 UbeaLast The last packet of a UBEA upload
  uchar BlockId;  // Counts the consecutive blocks of firmware upload. Starting at 0x00 for the FirmFirst or UbeaFirst packet
  uchar FirmwareLength[4];
  uchar Spare[20];
  uchar Data[512];
} T_ArtFirmwareMaster;

typedef struct S_FirmwareFileFormat {
  uchar ChecksumHi; // This is a 16 bit, one’s-complement checksum of the firmware data area.
  uchar ChecksumLo; // LSB of above
  uchar VersInfoHi; // High byte of Node’s firmware revision number. The Controller should only use this field to decide if a firmware update should proceed. The convention is that a higher number is a more recent release of firmware.
  uchar VersInfoLo; // LSB of above
  uchar UserName[30]; // byte field of user name information. This information is not checked by the Node. It is purely for display by the Controller. It should contain a human readable description of file and version number. Whilst this is a fixed length field, it must contain a null termination.
  uchar Oem[256]; // An array of 256 words. Each word is hi byte first and represents an Oem code for which this file is valid. Unused entries must be filled with 0x0000.
  uchar Spare[255];
  uchar Length[4]; // MSB->LSB The total length in words of the firmware information following this field.
  uchar *Data; // The firmware data as an array of 16 bit values ordered hi byte first. The actual data is manufacturer specific.
}T_FirmwareFileFormat;
